#include "Main.h"

float randomTable[256];

bool Background03::Init() 
{
	lights = false;

	move1  = true;
	move2  = false;
	move3  = false;

	fadeout = false;

	title = false;

	fadeTimer = 0;

	moveTime = 0;

	yadd = -50;

	for (int i = 0; i < 256; i++)
	{
		randomTable[i] = uniRand();
	}

	current = 0;

	return true;
}   

void Background03::Do(dword timer) 
{	
	int i, j;

	clearColor = 0x000000;

	if (move1)
	{
		yadd = -50 + ((timer - moveTime) / 1000.f) * 25.f;
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
 
	float x1, y1, x2, y2;

	uniSetTexture(NULL);

	sd->Start(UNI_DRAW);

	int addFade = 60 - ((timer - fadeTimer) / 4);

	if (addFade < 0)
	{
		addFade = 0;
	}

	for (i = 0; i < 20; i++)
	{
		x1 = (i * 40.f) + 1;
		y1 = 80 + yadd;

		x2 = x1 + 39.0f;
		y2 = y1 + 41.0f;

		if (i == 0)
		{
			x1 -= 1;
			x2 += 0;
		}

		float period = (randomTable[i] * 3000.f) + 1000.f;
		int fade = sin(fmod(timer, period) / period * _PI2) * 100.f + 128.f + addFade;
		if (fade > 255)
		{
			fade = 255;
		}

		int color = ((int)(fade * 0.8f) << 16) | ((int)(fade * 0.8f) << 8) | fade;

		sd->Draw2D(x1, y1, 0, 0, color,
			       x2, y1, 0, 0, color,
				   x1, y2, 0, 0, color,
		           x2, y2, 0, 0, color);

		sd->Draw2D(x2, y1, 0, 0, 0,
			       x2 + 1, y1, 0, 0, 0,
				   x2, y2, 0, 0, 0,
		           x2 + 1, y2, 0, 0, 0);
	}

	for (i = 0; i < 20; i++)
	{
		x1 = (i * 40.f) + 1;
		y1 = 481.1f - yadd;

		x2 = x1 + 39.0f;
		y2 = y1 + 40.0f;

		if (i == 0)
		{
			x1 -= 1;
			x2 += 0;
		}

		float period = (randomTable[i + 20] * 3000.f) + 1000.f;
		int fade = sin(fmod(timer, period) / period * _PI2) * 100.f + 128.f + addFade;
		if (fade > 255)
		{
			fade = 255;
		}

		int color = ((int)(fade * 0.8f) << 16) | ((int)(fade * 0.8f) << 8) | fade;

		sd->Draw2D(x1, y1, 0, 0, color,
			       x2, y1, 0, 0, color,
				   x1, y2, 0, 0, color,
		           x2, y2, 0, 0, color);

		sd->Draw2D(x2, y1, 0, 0, 0,
			       x2 + 1, y1, 0, 0, 0,
				   x2, y2, 0, 0, 0,
		           x2 + 1, y2, 0, 0, 0);
	}

	sd->Stop();

	if (title)
	{
		int timerrr = timer - titleTimer;

		uniSetTexture("title");

		int fade = (timerrr) / 16.f;

		if (timerrr > 10000)
		{
			fade = 255 - ((timerrr - 10000) / 8.f);
		}

		if (fade > 255)
		{
			fade = 255;
		}

		if (fade < 0)
		{
			fade = 0;
		}

		int color = (fade << 16) | (fade << 8) | fade;

		sd->Start(UNI_ADD);

		x1 = 250;
		y1 = 200;

		x2 = x1 + 512;
		y2 = y1 + 256;

		if (color != 0)
		{
			sd->Draw2D(x1, y1, 0, 0, color,
				       x2, y1, 1, 0, color,
					   x1, y2, 0, 1, color,
					   x2, y2, 1, 1, color);
		}

		sd->Stop();
	}

	if (credits)
	{
		uniSetTexture("credits");

		sd->Start(UNI_ADD);

		int fade = addFade * 2;

		int color = (fade << 16) | (fade << 8) | fade;

		if ((color != 0 && current == 0))
		{
			x1 = 10;
			y1 = 260;

			y2 = y1 + 128;
			x2 = x1 + 109;

			sd->Draw2D(x1, y1, 0, 0, color,
				       x2, y1, 0.212f, 0, color,
					   x1, y2, 0, 0.5f, color,
					   x2, y2, 0.212f, 0.5f, color);
		}

		if ((color != 0 && current == 1))
		{
			x1 = 327;
			y1 = 260;

			x2 = x1 + 147;
			y2 = y1 + 128;

			sd->Draw2D(x1, y1, 0.686f, 0, color,
				       x2, y1, 0.972f, 0, color,
					   x1, y2, 0.686f, 0.5f, color,
					   x2, y2, 0.972f, 0.5f, color);
		}
		
		if ((color != 0 && current == 2))
		{
			x1 = 573;
			y1 = 260;

			x2 = x1 + 217;
			y2 = y1 + 128;

			sd->Draw2D(x1, y1, 0.240f, 0, color,
				       x2, y1, 0.664f, 0, color,
					   x1, y2, 0.240f, 0.5f, color,
					   x2, y2, 0.664f, 0.5f, color);
		}
	
		sd->Stop();
	}
}

void Background03::Receive(dword Message, dword timer)
{
	switch (Message)
	{
	case 1:
		moveTime = timer;
		move1 = true;
		move2 = false;
		break;
	case 2:
		moveTime = timer;
		move1  = false;
		move2  = true;
		break;
	case 3:
		fadeTimer = timer;
		break;
	case 10:
		title = true;
		titleTimer = timer;
		break;
	case 11:
		credits = true;
		break;
	case 12:
		credits = false;
		break;
	case 20:
		current = (current + 1) % 4;
		break;
	}
}


void Background03::DeInit() 
{
}

