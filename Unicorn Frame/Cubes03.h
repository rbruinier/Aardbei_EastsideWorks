#ifndef __CUBES03_H__
#define __CUBES03_H__

class Cubes03: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	Scene	*scene;

	dword	oldTimer;
	int		current;

	dword   fadeTimer;
	bool fadeOut;
};

#endif