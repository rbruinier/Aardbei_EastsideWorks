#ifndef __CUBES02_H__
#define __CUBES02_H__

class Cubes02: public Effect {
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	Scene	*scene;
	Object  *oldObject;

	float cube02StartTime;
	int currentKey;

	bool bend;
	bool stretch;
	bool explode;
};

#endif