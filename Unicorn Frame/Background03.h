#ifndef __BACKGROUND03_H__
#define __BACKGROUND03_H__

class Background03: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	Scene	*scene;

	bool lights;

	float yadd;
	bool move1;
	bool move2;
	bool move3;
	dword moveTime;

	bool fadeout;
	dword fadeTimer;

	bool title;
	dword titleTimer;

	bool credits;

	int current;
};

#endif