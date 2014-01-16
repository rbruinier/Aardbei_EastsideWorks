#ifndef __SPRITES01_H__
#define __SPRITES01_H__

struct SpriteInfo
{
	float x, y;
	float size;
	float speed;
	int flits;
};

class Sprites01: public Effect 
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