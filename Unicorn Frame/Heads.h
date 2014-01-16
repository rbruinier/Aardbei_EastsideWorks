#ifndef __HEADS_H__
#define __HEADS_H__

class Heads: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	int current;
	int fadeTimer;
	bool move;
	int moveTimer;
};

#endif