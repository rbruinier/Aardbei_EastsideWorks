#ifndef __CUBES_H__
#define __CUBES_H__

class Cubes: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	Scene	*scene;
};

#endif