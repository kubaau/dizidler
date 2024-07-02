#pragma once

#include <array>
#include <map>
#include <tools/EnumToString.hpp>
#include <tools/Typedefs.hpp>

#include "Constants.hpp"
#include "Position.hpp"

DEFINE_ENUM_CLASS_WITH_STRING_CONVERSIONS(TerrainType, (GREENLAND)(WASTELAND)(WINTER))
DEFINE_ENUM_CLASS_WITH_STRING_CONVERSIONS(
    PlayerFace, (Octavianus)(Julius)(Brutus)(Erik)(Knut)(Olof)(Yamauchi)(Tsunami)(Hakirawashi)(Shaka)(Todo)(Mnga_Tscha))
DEFINE_ENUM_CLASS_WITH_STRING_CONVERSIONS(PassableAreaType, (UNUSED)(LAND)(WATER))

struct PassableArea
{
    PassableArea(PassableAreaType type, u16 x, u16 y, u32 mass) : type(type), x(x), y(y), mass(mass) {}

    PassableAreaType type;
    u16 x, y;
    u32 mass;

    friend auto& operator<<(std::ostream& os, const PassableArea& area)
    {
        return os << area.type << " " << area.x << "x" << area.y << " " << area.mass;
    }
};

struct Block
{
    u16 map_data_identification;
    u16 width;
    u16 height;
    u32 map_data_size;
    const Byte* data;

    friend std::ostream& operator<<(std::ostream&, const Block&);
};

class SwdWldData
{
    friend std::ostream& operator<<(std::ostream&, const SwdWldData&);

public:
    SwdWldData(const IOBuffer&);

private:
    auto readString(int begin_offset, int end_offset) const;
    void readHqPositions();
    void readPassableAreas();
    void readBlocks();
    void readBlock(std::string name, int n);

    Buffer data;

    std::string file_format_identification;
    // u16 ui_width;
    // u16 ui_height;
    std::string title;
    TerrainType terrain;
    u8 player_count;
    std::string author;
    std::array<Position2D<u16>, max_player_count> hq_pos;
    bool playable;
    std::array<PlayerFace, max_player_count> player_faces;
    std::vector<PassableArea> passable_areas;
    u16 map_file_identification;
    std::array<Byte, 4> short_block_headers;
    u16 width;
    u16 height;
    u32 map_data_size;
    std::map<std::string, Block> blocks;
    Buffer footer;
};
