#ifndef __LINKIN_H__
#define __LINKIN_H__

class Linkin: public Effect 
{
public:
	bool	Init();
	void	Do(dword);
	void	DeInit();
	void	Receive(dword Message, dword timer);


private:
	void	bendTentacle(Vertex *vertex, int nrSegmentsX, int nrSegmentsY, float radius, float yScale, dword timer);

	Scene	*scene;
	Scene   *scene2;
	D3DVECTOR *source;

	dword	oldTimer;
	int		current;

	dword   punkTimer;
	dword   fadeTimer;

	bool fadeOut;
};

#endif
