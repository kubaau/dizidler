#pragma once

#include <tools/Typedefs.hpp>

class WorldDatData
{
    friend std::ostream& operator<<(std::ostream&, const WorldDatData&);

public:
    WorldDatData(const IOBuffer&);

private:
    Buffer data;

    u16 map_file_identification;
    bool compressed;
    u16 width;
    u16 height;
};
