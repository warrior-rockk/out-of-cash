/********************************************************************
* PC-Speaker Allegro DOS Driver
*
* 09/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/

#include <pc.h>
#include <stdint.h>

#include "allegro.h"
#include "pcspeaker.h"

#define _TIME_OFFSET 1 //ms

//internal vars
static int _music_pos = 0;
static int _prev_note = 0;
static int _music_duration = 0;
static uint8_t _loop = 0;
static uint8_t _play = 0;
static long _timeResolution = 0;

static int _saved_pos = 0;
static int _saved_prev_note = 0;
static int _saved_duration = 0;

static uint8_t _sfx_play = 0;

//pointer to song data
int8_t *_notes;
uint16_t *_durations;
//pointer to saved song data
int8_t *_saved_notes;
uint16_t *_saved_durations;

//frequency notes 
static uint16_t _freqList[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2218, 2349, 2489, };

//restore song data after sfx play
void restore_song_data()
{
    _sfx_play = 0;
 
    _notes = _saved_notes;
    _durations = _saved_durations;

    _music_pos = _saved_pos;
    _prev_note = _saved_prev_note;
    _music_duration = _saved_duration;

    _play = 1;
}

//update music timer callback
static void pc_speaker_update()
{
    if (_play)
    {
        if (_notes[_music_pos] >= 0)  //not end of song
        {
            //check note
            if (_notes[_music_pos] > 0)   //if note <> silence
            {
                if (_notes[_music_pos] != _prev_note)
                {
                    sound(_freqList[_notes[_music_pos]]);               
                    _prev_note = _notes[_music_pos];
                }            
            }
            else
            {
                //silence
                nosound();
                _prev_note = _notes[_music_pos];
            }

            //check duration
            if (_music_duration >= _durations[_music_pos])
                {
                    _music_pos++;
                    if (_notes[_music_pos] == _prev_note)
                    {
                        nosound();
                        _prev_note = 0;
                    }
                    //prev_note = notes[music_pos];
                    _music_duration = 0;
                }
                else
                    _music_duration += _timeResolution + _TIME_OFFSET;
        }
        else
        {
            //end of song
            nosound(); 
            //check loop
            if (_loop)
            {
                //reset song
                _music_pos = 0;
                _prev_note = 0;
                _music_duration = 0;   
                //if (_sfx_play)
                    restore_song_data();
            }
            else
            {
                pc_speaker_song_pos = -1;
                //if (_sfx_play)
                    restore_song_data();
            }
        }
    }
    else
        nosound();
}
END_OF_FUNCTION(pc_speaker_update);

void pc_speaker_init(long timeResolution)
{
    _timeResolution = timeResolution;
    LOCK_FUNCTION(pc_speaker_update);
    install_int(pc_speaker_update, _timeResolution);   
}

void pc_speaker_play_song(int8_t *notes, uint16_t *durations, uint8_t loop)
{
    //load song
    _notes = notes;
    _durations = durations;
    
    _music_pos = 0;
    _prev_note = 0;
    _music_duration = 0;

    _loop = loop;
    _play = 1;    
    
    pc_speaker_song_pos = 0;
}

void pc_speaker_stop_song()
{
    nosound();
    _play = 0;
    _music_pos = 0;
    _prev_note = 0;
    _music_duration = 0;
}

void pc_speaker_pause_song()
{
    nosound();
    _play = 0;    
}

void pc_speaker_resume_song()
{
    _play = 1;    
}

void pc_speaker_seek_song(int position)
{
    _music_pos = position;
}

void pc_speaker_play_sfx(int8_t *sfx_notes, uint16_t *sfx_durations)
{
    //if playing song, save notes and durations
    if (_play)
    {
        _saved_notes = _notes;
        _saved_durations = _durations;

        _saved_pos = _music_pos;
        _saved_prev_note = _prev_note;
        _saved_duration = _music_duration;
    }

    //load sfx
    _notes = sfx_notes;
    _durations = sfx_durations;

    _music_pos = 0;
    _prev_note = 0;
    _music_duration = 0;
    _loop = -1;
    _play = 1;    
    _sfx_play = 1;
}