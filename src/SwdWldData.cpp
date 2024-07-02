#include "SwdWldData.hpp"

#define PRINT_BYTE_AS_HEX
#include <tools/As.hpp>
#include <tools/DumpMemory.hpp>
#include <tools/OutputOperators.hpp>
#include <tools/ReadStringFromBuffer.hpp>

using namespace std;

namespace Offset
{
    constexpr auto file_format_identification = 0;
    constexpr auto title = file_format_identification + 10;
    constexpr auto ui_width = title + 20;
    constexpr auto ui_height = ui_width + 2;
    constexpr auto terrain = ui_height + 2;
    constexpr auto player_count = terrain + 1;
    constexpr auto author = player_count + 1;
    constexpr auto hq_positions = author + 20;
    constexpr auto playable = hq_positions + max_player_count * 4;
    constexpr auto player_faces = playable + 1;
    constexpr auto passable_areas = player_faces + max_player_count;
    constexpr auto map_file_identification = passable_areas + 2250;
    constexpr auto short_block_headers = map_file_identification + 2;
    constexpr auto unknown_multiplier = short_block_headers + 4;
    constexpr auto width = unknown_multiplier + 0;
    constexpr auto height = width + 2;
    constexpr auto blocks = height + 2;
}

constexpr auto block_header_size = 16;
namespace BlockOffset
{
    constexpr auto map_data_identification = 0;
    constexpr auto width = map_data_identification + 6;
    constexpr auto height = width + 2;
    constexpr auto map_data_size = height + 4;
    constexpr auto data = map_data_size + 4;
}

ostream& operator<<(ostream& os, const Block& block)
{
    return os //<< "\nMap data identification: " << block.map_data_identification
              //<< "\nActual width: " << block.width << "\nActual height: " << block.height
              //<< "\nMap data size: " << block.map_data_size
        << "\nData: " << dumpMemory(block.data, MemDumpType::SIMPLE, block.map_data_size) << "\n";
}

ostream& operator<<(ostream& os, const SwdWldData& data)
{
    return os //<< dumpMemory(data.data, MemDumpType::SIMPLE)
              //<< "\nFile format identification: " << data.file_format_identification
        //<< "\nUI width: " << data.ui_width << "\nUI height: " << data.ui_height
        //<< "\nTitle: " << data.title
        << "\nTerrain: " << data.terrain << "\nPlayer count: " << +data.player_count << "\nAuthor: " << data.author
        << "\nHQ positions: "
        << data.hq_pos
        //<< "\nPlayable: " << boolalpha << data.playable
        << "\nPlayer faces: " << data.player_faces << "\nPassable areas: "
        << data.passable_areas
        //<< "\nMap file identification: " << data.map_file_identification
        //<< "\nShort block headers: " << data.short_block_headers
        << "\nWidth: " << data.width << "\nHeight: " << data.height
        << "\nMap data size: " << data.map_data_size // << "\nFooter: " << hex << data.footer
                                                     //<< "\n\nBlocks:" << data.blocks
        ;
}

auto SwdWldData::readString(int begin_offset, int end_offset) const
{
    return ::readString(data, begin_offset, end_offset);
}

SwdWldData::SwdWldData(const IOBuffer& d) : data(cbegin(d), cend(d))
{
    file_format_identification = readString(Offset::file_format_identification, Offset::title);
    title = readString(Offset::title, Offset::terrain);
    terrain = static_cast<TerrainType>(data[Offset::terrain]);
    player_count = data[Offset::player_count];
    author = readString(Offset::author, Offset::hq_positions);
    readHqPositions();
    playable = data[Offset::playable] == 0;
    repeat(max_player_count) player_faces[i] = static_cast<PlayerFace>(data[Offset::player_faces + i]);
    readPassableAreas();
    map_file_identification = as<u16>(data, Offset::map_file_identification);
    repeat(4) short_block_headers[i] = data[Offset::short_block_headers + i];
    width = as<u16>(data, Offset::width);
    height = as<u16>(data, Offset::height);
    map_data_size = width * height;
    readBlocks();
    footer = Buffer{cbegin(data) + Offset::blocks + (block_header_size + map_data_size) * 14, cend(data)};
}

void SwdWldData::readHqPositions()
{
    constexpr auto offset_y_start = Offset::hq_positions + max_player_count * sizeof(u16);
    for (int i = 0, offset_x = Offset::hq_positions, offset_y = offset_y_start; offset_x != offset_y_start;
         ++i, offset_x += sizeof(u16), offset_y += sizeof(u16))
        hq_pos[i] = {as<u16>(data, offset_x), as<u16>(data, offset_y)};
}

void SwdWldData::readPassableAreas()
{
    for (auto offset = Offset::passable_areas; offset != Offset::map_file_identification && data[offset]; offset += 9)
    {
        passable_areas.emplace_back(static_cast<PassableAreaType>(+data[offset]),
                                    as<u16>(data, offset + 1),
                                    as<u16>(data, offset + 3),
                                    as<u32>(data, offset + 5));
    }
}

void SwdWldData::readBlocks()
{
    readBlock("height_map", 0);
    readBlock("tex_triangle_1", 1);
    readBlock("tex_triangle_2", 2);
    readBlock("roads", 3);
    readBlock("object_index", 4);
    readBlock("object_type", 5);
    readBlock("animals", 6);
    readBlock("occupied_by_settler", 7);
    readBlock("buildable_sites", 8);
    readBlock("territory_occupation", 9);
    readBlock("map_editor_cursor_pos", 10);
    readBlock("resources", 11);
    readBlock("gouraud_shading", 12);
    readBlock("passable_areas_block", 13);
}

void SwdWldData::readBlock(std::string name, int n)
{
    auto& block = blocks[name];
    const auto block_offset = Offset::blocks + (block_header_size + map_data_size) * n;
    block.map_data_identification = as<u16>(data, block_offset + BlockOffset::map_data_identification);
    block.width = as<u16>(data, block_offset + BlockOffset::width);
    block.height = as<u16>(data, block_offset + BlockOffset::height);
    block.map_data_size = as<u32>(data, block_offset + BlockOffset::map_data_size);
    block.data = data.data() + block_offset + BlockOffset::data;
}
