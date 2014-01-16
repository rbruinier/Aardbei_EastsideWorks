#ifndef __BACKGROUND02_H__
#define __BACKGROUND02_H__

class Background02: public Effect {
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


};

#endif