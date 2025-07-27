/********************************************************************
* Sound system
*
* 26/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/
#ifndef _H_SOUND_
#define _H_SOUND_

#include <stdbool.h>

//Sfx
#define SFX_FREQ_RND_PERCENT    20 //(+/- % freq variation)
#define SFX_GAME_VOICE          0
#define SFX_ROOM_VOICE          1
#define SFX_NUM_VOICES          2

//sfx voices structure
typedef struct tSfx
{
    int position;
    int sampleId;
    bool playing;
    bool paused;
    bool finished;
    bool stop;
    bool pause;
} tSfx;

enum soundModes{
    SB_SND_MODE = 0,
    PC_SPEAKER_SND_MODE,
    NO_SOUND_SND_MODE
};

//inits sound system
int sound_init();
//sets sound mode
void sound_set_mode(enum soundModes _soundMode);
//get sound mode
enum soundModes sound_get_mode();

//plays game music
void play_music(uint16_t musicId, int loop);
//stops game music
void stop_music();
//pauses game music
void pause_music();
//resume game music
void resume_music();
//get music position
long music_get_pos();
//seeks music to position
void music_seek(int position);

void sfx_init();
void sfx_destroy();
void sfx_update();
void sfx_play(uint16_t soundId, uint8_t voice, bool rndFreq);
void sfx_stop(uint8_t voice);
void sfx_pause(uint8_t voice);
void sfx_resume(uint8_t voice);
tSfx sfx_get_voice_data(uint8_t voice);
void sfx_set_voice_data(uint8_t voice, tSfx voiceData);
bool sfx_voice_is_playing(uint8_t voice);
bool sfx_voice_finished(uint8_t voice);
void sfx_voice_clear_finished(uint8_t voice);
int sfx_get_voice_sample_id(uint8_t voice);

void sfx_voice_reallocate(uint8_t voice);
void sfx_voice_set_position(uint8_t voice, int position);
#endif