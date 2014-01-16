#ifndef __BACKGROUND05_H__
#define __BACKGROUND05_H__

class Background05: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	Receive(dword Message, dword timer);
	void	DeInit();

private:
	int currentColor;
	dword fadeTimer;
};

#endif