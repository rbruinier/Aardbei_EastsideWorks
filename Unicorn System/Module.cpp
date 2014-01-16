/*

	Pyramid DX8 System - HTML Log Code (source file)


	(c) 2001, Robert Jan Bruinier

*/


#include "Unicorn.h"

#ifdef UNI_TINY_FMOD

#include "..\Unicorn Music\lib\minifmod.h"

FMUSIC_MODULE	*fmodMod;
void			*fmodData;
int				fmodLength;
int				fmodPos;
unsigned char	fmodMusic;

unsigned int memopen(char * name) {
	fmodPos    = 0;
	return 1;
}

void memclose(unsigned int handle) {
}

int memread(void *buffer, int size, unsigned int handle) {
	if (fmodPos + size >= fmodLength)
		size = fmodLength - fmodPos;

	memcpy(buffer, (char *)fmodData+fmodPos, size);
	fmodPos += size;
	
	return size;
}

void memseek(unsigned int handle, int pos, signed char mode) {
	if (mode == SEEK_SET) 
		fmodPos = pos;
	else if (mode == SEEK_CUR) 
		fmodPos += pos;
	else if (mode == SEEK_END)
		fmodPos = fmodLength;

	if (fmodPos > fmodLength)
		fmodPos = fmodLength;
}
 
int memtell(unsigned int handle) {
	return fmodPos;
}

void fmodLoadMod(void *data, int length) {
	fmodData   = data;
	fmodLength = length;

	FSOUND_File_SetCallbacks(memopen, memclose, memread, memseek, memtell);

	if (!FSOUND_Init(44100, 0)) 
	{
		uniQuit("Your soundcard is... gone?!");
	}

	fmodMod = FMUSIC_LoadSong("", NULL);

	if (!fmodMod) 
	{
		uniQuit("Unable to load XM");
	}
}

void fmodPlay(int iOrder) {
	FMUSIC_PlaySong(fmodMod, iOrder);
}

void fmodStop() {
	FMUSIC_FreeSong(fmodMod);
	FSOUND_Close();
}

void fmodGetInfo(int &order, int &row, int &sync) {
	order = FMUSIC_GetOrder(fmodMod);
	row   = FMUSIC_GetRow(fmodMod);
	sync  = FMUSIC_GetTime(fmodMod);
}

/*
// for no music (but timing)
unsigned int fakeMusicTimer;
unsigned int playerStartPos;

void fmodLoadMod(void *data, int length) 
{
}

void fmodPlay(int iOrder) 
{
	fakeMusicTimer = timeGetTime();
	playerStartPos = iOrder;
}

void fmodStop() 
{
}

void fmodGetInfo(int &order, int &row, int &sync) 
{
	float sec = (timeGetTime() - fakeMusicTimer) / 1000.f;

	order  = (int)floor(sec / 6);
	row    = ((sec - (order * 6)) / 6.f) * 64.f;
	sync   = sec;
	order += playerStartPos;
}
*/

#endif