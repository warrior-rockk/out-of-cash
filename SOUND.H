/********************************************************************
* Sound system
*
* 26/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/
#ifndef _H_SOUND_
#define _H_SOUND_

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
#endif