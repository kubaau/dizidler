#include "Loading.hpp"

#include <tools/ReadFile.hpp>
#include <tools/ThreadSafeLogger.hpp>

#include "SwdWldData.hpp"
#include "WorldDatData.hpp"

using namespace std;

void load()
{
    SwdWldData swd_wld_data{readBinaryFile(asset_folder + "DATA/MAPS/MISS200.WLD")};
    DEBUG_LOG << swd_wld_data;

    WorldDatData world_dat_data{readBinaryFile(asset_folder + "SAVE/WORLD900.DAT")};
    DEBUG_LOG << world_dat_data;
}
