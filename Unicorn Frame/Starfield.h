#ifndef __STARFIELD_H__
#define __STARFIELD_H__

class Starfield: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	Scene	*scene;
	dword	oldTimer;

	int mode;

};

#endif