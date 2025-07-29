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

static tSfx sfx[SFX_NUM_VOICES];

//pc speaker songs to array
int8_t* songs_notes[] = {
    _Foxtrot_notes , 
    _intro_notes , 
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
    _intro_durations , 
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

//function to init sfx sound system
void sfx_init()
{
    //init all sfx voices
    for (int i = 0; i < SFX_NUM_VOICES; i++)
    {
        //get soundcard voice (reallocate if exists)
        if (!voice_check(i))
        {
            int voice = allocate_voice((SAMPLE*)soundDataFile[sd_take].dat);
            TRACE("SFX voice %i allocated to soundcard voice %i\n", i, voice);
        }
        else
            reallocate_voice(i, (SAMPLE*)soundDataFile[sd_take].dat);

        sfx[i].sampleId = sd_take;

        //init channel flags
        sfx[i].playing     = false;
        sfx[i].paused      = false;
        sfx[i].pause       = false;
        sfx[i].stop        = false;
        sfx[i].finished    = false;
        sfx[i].position    = -1;
    }

    TRACE("SFX system initialized\n");
}

//function to destroy sfx system (free resources)
void sfx_destroy()
{
    TRACE("Destroy SFX system\n");
    
    //free all sfx voices
    for (int i = 0; i < SFX_NUM_VOICES; i++)
    {
        //get soundcard voice (reallocate if exists)
        if (!voice_check(i))
            deallocate_voice(i);
    }

    TRACE("SFX system destroyed\n");
}

//function to update sfx sound system
void sfx_update()
{
    for (int i = 0; i < SFX_NUM_VOICES; i++)
    {
        //handles sound pause
        if (sfx[i].pause)
        {
            if (sfx[i].playing)
            {
                //do the stop/pause
                voice_stop(i);
                //set flag
                sfx[i].paused = true;
            }
            else
                //clear flag
                sfx[i].pause = false;
        }
    
        //handles sound resume
        if (!sfx[i].pause && sfx[i].paused)
        {
            //resume sound if was started
            if (sfx[i].position >= 0)
                voice_start(i);
            //clear flag
            sfx[i].paused = false;
        }
    
        //handles sound stop
        if (sfx[i].stop)
        {
            if (sfx[i].playing)
                //do sound stop
                voice_stop(i);
            //clear flag
            sfx[i].stop = false;
            //set flag
            sfx[i].finished = true;
        }
    
        //handles clear sound playing flag
        if (sfx[i].playing && !sfx[i].paused)
        {
            //stores sound position
            switch (soundMode)
            {
                case SB_SND_MODE:
                    sfx[i].position = voice_get_position(i);
                break;
                case PC_SPEAKER_SND_MODE:
                    sfx[i].position = (int)pc_speaker_song_pos;
                break;
            }
            
            //clear flag when sound finished
            if (sfx[i].position == -1)
            {
                sfx[i].playing = false;
                sfx[i].finished = true;
            }
        }
    }
}

//function to play a sound
void sfx_play(uint16_t soundId, uint8_t voice, bool rndFreq)
{
    ASSERT(voice < SFX_NUM_VOICES);
    ASSERT(soundId < sd_COUNT);

    sfx[voice].sampleId = soundId;
    
    switch (soundMode)
    {
        case SB_SND_MODE:
            //reallocate the sample on select voice of selected channel
            reallocate_voice(voice, (SAMPLE*)soundDataFile[soundId].dat);

            //randomize frequency
            if (rndFreq)
            {
                //get a random percent variation from twice of SFX_FREQ_RND_PERCENT (half for negative, half for positive)
                int freqVariation = (rand() % (SFX_FREQ_RND_PERCENT * 2));

                //get sample original frequency
                int sampleFreq = voice_get_frequency(voice);
                TRACE("Original freq: %iHz | ", sampleFreq);

                //calculate new frequency
                fixed newFreq;
                //if variation is below half
                if (freqVariation < SFX_FREQ_RND_PERCENT)
                {
                    //sub the percentage variation to original freq
                    newFreq = itofix(sampleFreq) - fixmul(itofix(sampleFreq),(fixdiv(itofix(freqVariation),itofix(100))));
                    TRACE("Variation: -%i%% | ", freqVariation);
                }
                else
                {
                    //add the percentage variation to original freq
                    newFreq = fixmul(itofix(sampleFreq), fixdiv(itofix(freqVariation - SFX_FREQ_RND_PERCENT), itofix(100.0))) + itofix(sampleFreq);
                    TRACE("Variation: +%i%% | ", (freqVariation - SFX_FREQ_RND_PERCENT));
                }

                //set the new frequency
                voice_set_frequency(voice, fixtoi(newFreq));
                TRACE("New freq: %iHz\n", fixtoi(newFreq));
                
            }
            
            //start sample allocated on voice channel
            voice_start(voice);
        break;
        case PC_SPEAKER_SND_MODE:
            pc_speaker_play_sfx(_sfx_notes, _sfx_durations);
        break;
    }

    //set flag
    sfx[voice].playing = true;
    sfx[voice].finished = false;
}

void sfx_stop(uint8_t voice)
{
    sfx[voice].stop = true;
}

void sfx_pause(uint8_t voice)
{
    sfx[voice].pause = true;
}

void sfx_resume(uint8_t voice)
{
    sfx[voice].pause = false;
}

tSfx sfx_get_voice_data(uint8_t voice)
{
    return sfx[voice];
}

void sfx_set_voice_data(uint8_t voice, tSfx voiceData)
{
    sfx[voice] = voiceData;
}

bool sfx_voice_is_playing(uint8_t voice)
{
    return sfx[voice].playing;
}

bool sfx_voice_finished(uint8_t voice)
{
    return sfx[voice].finished;
}

int sfx_get_voice_sample_id(uint8_t voice)
{
    return sfx[voice].sampleId;
}

void sfx_voice_clear_finished(uint8_t voice)
{
    sfx[voice].finished = false;    
}

void sfx_voice_reallocate(uint8_t voice)
{
    reallocate_voice(voice, (SAMPLE*)soundDataFile[sfx[voice].sampleId].dat);
}

void sfx_voice_set_position(uint8_t voice, int position)
{
    voice_set_position(voice, position);
}
