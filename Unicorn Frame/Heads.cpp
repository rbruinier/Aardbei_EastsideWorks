#include "Main.h"

bool Heads::Init() 
{
	current = 0;

	move = false;

//	Receive(0, 0);

	return true;
}   

void Heads::Do(dword timer) 
{	
	char *textures[] = {"gif_rob", "gif_jgi", "gif_oys"};
	int yadds[] = {0, 15, 10};
	int xadds[] = {-15, 0, 0};

	float x1, y1, x2, y2;

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	sd->Start(UNI_ADD);

	x1 = -10;

	bool rotate = true;
/*
	if (timer < 1000)
	{
		x1 = 800 - sin((timer / 1000.f) * (_PI / 2.f)) * 810.f;
		rotate = false;
		fadeTimer = timer;
	}

	if (move)
	{
		if ((timer - moveTimer) < 1000)
		{
			x1 = -800 + cos(((timer - moveTimer) / 1000.f) * (_PI / 2.f)) * 810.f;
		}
		else
		{
			x1 = -800;
		}
		rotate = false;
		fadeTimer = timer;
	}
*/
	x2 = x1 + 256;

	y1 = 174; 
	y2 = y1 + 256;


	for (int i = 0; i < 3; i++)
	{
		uniSetTexture(textures[i]);

		int fade = 200 - ((timer - fadeTimer) / 250.f) * 200.f;

		if (fade < 0)
			fade = 0;

		int color = (fade << 16) | (fade << 8) | fade;

		if (rotate)
		{
			switch (current)
			{
			case 0:
				sd->Draw2D(x1 + xadds[i], y1 + yadds[i], 0, 0, color,
					       x2 + xadds[i], y1 + yadds[i], 1, 0, color,
						   x1 + xadds[i], y2 + yadds[i], 0, 1, color,
						   x2 + xadds[i], y2 + yadds[i], 1, 1, color);
				break;
			case 1:
				sd->Draw2D(x1 - xadds[i], y1 - yadds[i], 1, 1, color,
					       x2 - xadds[i], y1 - yadds[i], 0, 1, color,
						   x1 - xadds[i], y2 - yadds[i], 1, 0, color,
						   x2 - xadds[i], y2 - yadds[i], 0, 0, color);
				break;
			case 2:
				sd->Draw2D(x1 + yadds[i], y1 - xadds[i], 1, 0, color,
					       x2 + yadds[i], y1 - xadds[i], 1, 1, color,
						   x1 + yadds[i], y2 - xadds[i], 0, 0, color,
						   x2 + yadds[i], y2 - xadds[i], 0, 1, color);
				break;
			case 3:
				sd->Draw2D(x1 - yadds[i], y1 + xadds[i], 0, 1, color,
						   x2 - yadds[i], y1 + xadds[i], 0, 0, color,
					       x1 - yadds[i], y2 + xadds[i], 1, 1, color,
					       x2 - yadds[i], y2 + xadds[i], 1, 0, color);
				break;
			}
		}
		else
		{
			sd->Draw2D(x1 + xadds[i], y1 + yadds[i], 0, 0, color,
				       x2 + xadds[i], y1 + yadds[i], 1, 0, color,
					   x1 + xadds[i], y2 + yadds[i], 0, 1, color,
					   x2 + xadds[i], y2 + yadds[i], 1, 1, color);
		}

		x1 += 280; 
		x2 += 280;
	}

	sd->Stop();
}

void Heads::Receive(dword Message, dword timer)
{
	if (Message == 0)
	{
		move = true;
		moveTimer = timer;
	}
	else
	{
		fadeTimer = timer;
		current = (current + 1) % 4;
	}
}

void Heads::DeInit() 
{
}
