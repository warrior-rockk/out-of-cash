/********************************************************************
* PC-Speaker Allegro DOS Driver
*
* 09/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/

#ifndef _H_PCSPEAKER_
#define _H_PCSPEAKER_
//#include <stdint.h>

long pc_speaker_song_pos;

//inits the pc speaker interrupt (timeResolution on ms)
void pc_speaker_init(long timeResolution);
//plays song on pc speaker (loops n times or 0: infinite)
void pc_speaker_play_song(int8_t *notes, uint16_t *durations, uint8_t loop);
//stops song on pc speaker
void pc_speaker_stop_song();
//pauses song on pc speaker
void pc_speaker_pause_song();
//resumens song paused on pc speaker
void pc_speaker_resume_song();
//seeks song to position
void pc_speaker_seek_song(int position);

void pc_speaker_play_sfx(int8_t *sfx_notes, uint16_t *sfx_durations);

#endif