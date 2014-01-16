#include "Main.h"

bool Background02::Init() 
{
	lights = false;

	move1  = true;
	move2  = false;
	move3  = false;

	fadeout = false;

	yadd = -90;

	moveTime = 0;

	return true;
}   

void Background02::Do(dword timer) 
{	
	int i, j;

	clearColor = 0x000000;

	if (move1)
	{
		yadd = -90 + ((timer - moveTime) / 1000.f) * 25.f;
		if (yadd > 0)
		{
			yadd = 0;
		}
	}

	if (move2)
	{
		yadd = -((timer - moveTime) / 1000.f) * 25.f;
	}

	SpriteDrawer *sd = uniSystem->spriteDrawer;
 
	float x1, y1, x2, y2, x3;

	uniSetTexture(NULL);

	sd->Start(UNI_ADD);


	int fade = 60 - ((timer % 500) / 500.f) * 40;

	for (j = 0; j < 3; j++)
	{
		int aantal = 5 + (j * 4);
		float fullSize = 160.f;
		float halfSize = fullSize / 2.f;
		float height   = 120 - (j * 34);
		for (i = 0; i < aantal + 1; i++)
		{
			float size1 = 800.f / aantal;
			float size2 = size1 / 2.f;

			x1 = size2 + i * size1 + fmod(timer / (15.f + (j * 5)), size1) - size1;
			y1 = 550 - height - yadd;

			y2 = y1 + 90;
			x2 = x1 - halfSize;
			x3 = x1 + halfSize;

			int color = 0x312011;

			sd->Draw2D(x1, y1, 0, 0, color,
				       x1, y1, 0, 0, color,
					   x2, y2, 0, 0, color,
			           x3, y2, 0, 0, color);
		}
	}


	for (j = 0; j < 3; j++)
	{
		int aantal = 5 + (j * 4);
		float fullSize = 160.f;
		float halfSize = fullSize / 2.f;
		float height   = 120 - (j * 34);
		for (i = 0; i < aantal + 1; i++)
		{
			float size1 = 800.f / aantal;
			float size2 = size1 / 2.f;

			x1 = size2 + i * size1 + fmod(timer / (15.f + (j * 5)), size1) - size1;
			y1 = 50 + height + yadd;

			y2 = y1 - 90;
			x2 = x1 - halfSize;
			x3 = x1 + halfSize;

			int color = 0x312011;

			sd->Draw2D(x2, y2, 0, 0, color,
				       x3, y2, 0, 0, color,
					   x1, y1, 0, 0, color,
			           x1, y1, 0, 0, color);
		}
	}

	if (lights)
	{
		bool onder = true;
		if ((timer / 500) & 1)
		{
			onder = false;
		}
		for (i = -2; i < 2; i++)
		{
			int fade = 255 - (timer % 500);
			if (fade > 0)
			{
				int color = ((int)((fade / 255.f) * 0x31) << 16) |
					        ((int)((fade / 255.f) * 0x20) << 8) |
							((int)((fade / 255.f) * 0x11));

				x1 = 400 + (i  * 200) + 36 + 64;
				y1 = 236;

				y2 = y1 + 128;
				x2 = x1 - 64;
				x3 = x1 + 64;

				if (onder)
				{
					if ((i == -2 || i == 1))
					{
						sd->Draw2D(x1, y1, 0, 0, color,
							       x1, y1, 0, 0, color,
								   x2, y2, 0, 0, color,
								   x3, y2, 0, 0, color);
					}
					else
					{
						sd->Draw2D(x2, y1, 0, 0, color,
							       x3, y1, 0, 0, color,
								   x1, y2, 0, 0, color,
								   x1, y2, 0, 0, color);
					}
				}
				else
				{
					if ((i == -2 || i == 1))
					{
						sd->Draw2D(x2, y1, 0, 0, color,
							       x3, y1, 0, 0, color,
								   x1, y2, 0, 0, color,
								   x1, y2, 0, 0, color);
					}
					else
					{
						sd->Draw2D(x1, y1, 0, 0, color,
							       x1, y1, 0, 0, color,
								   x2, y2, 0, 0, color,
								   x3, y2, 0, 0, color);
					}
				}
			}
		}
	}
	
	sd->Stop();
}

void Background02::Receive(dword Message, dword timer)
{
	switch (Message)
	{
	case 1:
		moveTime = timer;
		move1 = true;
		move2 = false;
		move3 = false;
		break;
	case 2:
		lights = true;
		break;
	case 3:
		moveTime = timer;
		move1  = false;
		move2  = true;
		move3  = false;
		lights = false;
		break;
	case 4:
		moveTime = timer;
		move1  = false;
		move2  = false;
		move3  = true;
		break;
	case 5:
		fadeTimer = timer;
		fadeout = true;
		break;

	}
}


void Background02::DeInit() 
{
}

