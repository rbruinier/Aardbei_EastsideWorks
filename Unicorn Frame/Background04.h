#ifndef __BACKGROUND04_H__
#define __BACKGROUND04_H__

class Background04: public Effect {
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
};

#endif