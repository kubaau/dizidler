#include "MidiPlayer.hpp"

#include <SDL_mixer.h>

#include <tools/IoTypedefs.hpp>

#include "Constants.hpp"

using namespace std;

namespace
{
    auto sdlLoadMusic(Filename file)
    {
        static const auto midi_folder = asset_folder + "DATA/SOUNDDAT/SNG/";
        return Mix_LoadMUS((midi_folder + file).c_str());
    }
}

MidiPlayer::MidiPlayer()
{
    tracks[0] = sdlLoadMusic("SNG_0001.MID");
    tracks[1] = sdlLoadMusic("SNG_0002.MID");
    tracks[2] = sdlLoadMusic("SNG_0003.MID");
    tracks[3] = sdlLoadMusic("SNG_0004.MID");
    tracks[4] = sdlLoadMusic("SNG_0005.MID");
    tracks[5] = sdlLoadMusic("SNG_0006.MID");
    tracks[6] = sdlLoadMusic("SNG_0007.MID");
    tracks[7] = sdlLoadMusic("SNG_0008.MID");
    tracks[8] = sdlLoadMusic("SNG_0009.MID");
    tracks[9] = sdlLoadMusic("SNG_0010.MID");
    tracks[10] = sdlLoadMusic("SNG_0011.MID");
    tracks[11] = sdlLoadMusic("SNG_0012.MID");
    tracks[12] = sdlLoadMusic("SNG_0013.MID");
    tracks[13] = sdlLoadMusic("SNG_0014.MID");
    playNextTrack();
}

MidiPlayer::~MidiPlayer()
{
    Mix_HaltMusic();
    for (auto track : tracks)
        Mix_FreeMusic(track);
    Mix_CloseAudio();
}

void MidiPlayer::playNextTrack()
{
    Mix_HaltMusic();
    Mix_PlayMusic(tracks[current_track], -1);

    if (++current_track >= track_count)
        current_track = 0;
}
