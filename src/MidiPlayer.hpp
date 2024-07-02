#pragma once

#include <array>
#include <tools/Typedefs.hpp>

class MidiPlayer
{
public:
    MidiPlayer();
    ~MidiPlayer();

    void playNextTrack();

private:
    static constexpr auto track_count = 14;

    std::array<struct _Mix_Music*, track_count> tracks;
    u8 current_track = 0;
};
