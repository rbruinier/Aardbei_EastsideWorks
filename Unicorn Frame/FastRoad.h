#ifndef __FASTROAD_H__
#define __FASTROAD_H__

class FastRoad: public Effect 
{
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);

private:
	Scene	*scene;

	bool fadeOut;
	dword fadeTimer;
};

#endif