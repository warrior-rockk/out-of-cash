/********************************************************************
* Sound system
*
* 26/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/
#include <stdint.h>

#include "sound.h"
#include "pcspeaker.h"
#include "game.h"
#include "SPSONGS.H"

//sound mode configured
static uint8_t soundMode;

//pc speaker songs to array
int8_t* songs_notes[] = {
    _Foxtrot_notes , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    _warcom_notes ,
    _title2_notes,
    NULL
};

//pc speaker song durations to array
uint16_t* songs_durations[] = {
    _Foxtrot_durations, 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    NULL , 
    _warcom_durations ,
    _title2_durations,
    NULL
};

//inits sound system
int sound_init()
{
    switch(soundMode)
    {
        case SB_SND_MODE:
            TRACE("Sound Blaster sound system init\n");
            return install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);            
        break;
        case PC_SPEAKER_SND_MODE:
            pc_speaker_init(10);
            TRACE("PC Speaker sound system init\n");
            return 0;
        break;
        case NO_SOUND_SND_MODE:
            TRACE("No sound configured init\n");
            return 0;
        break;
        default:
            return -1;
        break;
    }
}

//sets sound system mode
void sound_set_mode(enum soundModes _soundMode)
{
    soundMode = _soundMode;
}

//gets sound system mode
enum soundModes sound_get_mode()
{
    return soundMode;
}

//function to play music
void play_music(uint16_t musicId, int loop)
{
    //stop actual music
    stop_music();

    if (soundMode == SB_SND_MODE)
    {
        //load index music index
        TRACE("Load music data file object\n");
        actualRoom.musicDataFile  = load_datafile_object_indexed(actualRoom.musicDataFileIndex, musicId);

        //play midi
        TRACE("Play midi music\n");
        play_midi((MIDI *)actualRoom.musicDataFile[0].dat, loop);
    }
    else if(soundMode == PC_SPEAKER_SND_MODE)
    {
        if (songs_notes[musicId] && songs_durations[musicId])
        {
            //play pcspeaker
            TRACE("Play pc speaker music\n");
            pc_speaker_play_song(songs_notes[musicId], songs_durations[musicId], loop); 
        }
    }
}

//function to stop midi music
void stop_music()
{
    //stop actual music
    TRACE("Stopping midi\n");
    if (soundMode == SB_SND_MODE)
        stop_midi();
    else if (soundMode == PC_SPEAKER_SND_MODE)
        pc_speaker_stop_song();
}

//function to pause music
void pause_music()
{
    if (soundMode == SB_SND_MODE)
        midi_pause();
    else if (soundMode == PC_SPEAKER_SND_MODE)
        pc_speaker_pause_song();
}

//function to resume music
void resume_music()
{
    if (soundMode == SB_SND_MODE)
        midi_resume();
    else if (soundMode == PC_SPEAKER_SND_MODE)
        pc_speaker_resume_song();
}

//returns music position
long music_get_pos()
{
    if (soundMode == SB_SND_MODE)
        return midi_pos;
    else if (soundMode == PC_SPEAKER_SND_MODE)
        return pc_speaker_song_pos;
}

//seeks music to position
void music_seek(int position)
{
    if (soundMode == SB_SND_MODE)
        midi_seek(position);
    else if (soundMode == PC_SPEAKER_SND_MODE)
        pc_speaker_seek_song(position);
}