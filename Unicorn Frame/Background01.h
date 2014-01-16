#ifndef __BACKGROUND01_H__
#define __BACKGROUND01_H__

class Background01: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	Receive(dword Message, dword timer);
	void	DeInit();

private:
	SpriteDrawer *spriteDrawer;

	float yadd;
	bool move1;
	bool move2;
	bool move3;
	dword moveTime;
	bool greet;
	dword greetTime;
	bool lights;
	bool fadeout;
	dword fadeTimer;

	int current;
};

#endif