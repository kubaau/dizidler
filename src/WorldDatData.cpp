#include "WorldDatData.hpp"

#include <tools/As.hpp>
#include <tools/ThreadSafeLogger.hpp>

using namespace std;

namespace Offset
{
    constexpr auto map_file_identification = 0;
    auto compress_bump = 0;
    constexpr auto width = map_file_identification + 6;
    constexpr auto height = width + 2;
    constexpr auto map_data = height + 2;
}

namespace MapDataOffset
{
    constexpr auto map_data_size = 0;
    constexpr auto map_data = map_data_size + 4;
}

ostream& operator<<(ostream& os, const WorldDatData& data)
{
    return os //<< "\nMap file identification: " << hex << data.map_file_identification
        << "\nCompressed: " << boolalpha << data.compressed << "\nWidth: " << data.width << "\nHeight: " << data.height;
}

template <typename It>
auto decompressRLE(It begin, It end)
{
    Buffer out;
    DEBUG_LOG << end - begin;
    return out;
}

WorldDatData::WorldDatData(const IOBuffer& d) : data(cbegin(d), cend(d))
{
    map_file_identification = as<u16>(data, Offset::map_file_identification);
    compressed = data[2];
    if (compressed)
        Offset::compress_bump = 4;
    width = as<u16>(data, Offset::width + Offset::compress_bump);
    height = as<u16>(data, Offset::height + Offset::compress_bump);

    if (compressed)
    {
        const auto begin = cbegin(data) + Offset::map_data + Offset::compress_bump + MapDataOffset::map_data;
        decompressRLE(begin,
                      begin + as<u32>(data, Offset::map_data + Offset::compress_bump + MapDataOffset::map_data_size));
    }
}
