#ifndef __SPRITES02_H__
#define __SPRITES02_H__

struct SpriteInfo;

class Sprites02: public Effect 
{
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	int nrSprites;
	SpriteInfo *sprites;

	int oldTime;

	bool fadeOut;
	dword fadeTimer;
};

#endif