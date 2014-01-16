#include "Main.h"
		
bool Background04::Init()
{
	yadd = -60;
	move1  = false;
	move2  = false;
	move3  = false;
	lights = false;
	fadeout = false;

	Receive(1, 0);
//	Receive(4, 0);
//	Receive(2, 0);

	return true;
}
 
void Background04::Do(dword timer)
{
	int i;
	float x1, y1, x2, y2;

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
		yadd = ((timer - moveTime) / 1000.f) * 25.f;
		if (yadd > 65)
		{
			yadd = 65;
		}
	}

	if (move3)
	{
		yadd = 65 - ((timer - moveTime) / 1000.f) * 25.f;
	}

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	uniSetTexture("hello");

	sd->Start(UNI_ADD);

	for (i = 0; i < 17; i++) 
	{
		x1 = i * 50 + fmod(timer / 15.f, 50) - 50;
		y1 = 70 + yadd;
	
		x2 = x1 + 50;
		y2 = y1 + 50;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}

	for (i = 0; i < 22; i++) 
	{
		x1 = i * 38.1f + fmod(timer / 20.f, 38.1f) - 38.1f;
		y1 = 100 + yadd;
	
		x2 = x1 + 38.1f;
		y2 = y1 + 38.1f;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}

	for (i = 0; i < 27; i++) 
	{
		x1 = i * 30.8f + fmod(timer / 25.f, 30.8f) - 30.8f;
		y1 = 122 + yadd;
	
		x2 = x1 + 30.8f;
		y2 = y1 + 30.8f;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}

	for (i = 0; i < 32; i++) 
	{
		x1 = i * 25.8f + fmod(timer / 30.f, 25.8f) - 25.8f;
		y1 = 140 + yadd;
	
		x2 = x1 + 25.8f;
		y2 = y1 + 25.8f;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}


	///////////////////////////////////////////

	for (i = 0; i < 17; i++) 
	{
		x1 = i * 50 + fmod(timer / 15.f, 50) - 50;
		y1 = 483 - yadd;
	
		x2 = x1 + 50;
		y2 = y1 + 50;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}

	for (i = 0; i < 22; i++) 
	{
		x1 = i * 38.1f + fmod(timer / 20.f, 38.1f) - 38.1f;
		y1 = 465 - yadd;
	
		x2 = x1 + 38.1f;
		y2 = y1 + 38.1f;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}

	for (i = 0; i < 27; i++) 
	{
		x1 = i * 30.8f + fmod(timer / 25.f, 30.8f) - 30.8f;
		y1 = 449 - yadd;
	
		x2 = x1 + 30.8f;
		y2 = y1 + 30.8f;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}

	for (i = 0; i < 32; i++) 
	{
		x1 = i * 25.8f + fmod(timer / 30.f, 25.8f) - 25.8f;
		y1 = 435 - yadd;
	
		x2 = x1 + 25.8f;
		y2 = y1 + 25.8f;

		sd->Draw2D(x1, y1, 0, 0, 0xffffff,
			       x2, y1, 1, 0, 0xffffff,
				   x1, y2, 0, 1, 0xffffff,
				   x2, y2, 1, 1, 0xffffff);			       
	}
	
	
	//////////////////////////////////////

	if (lights)
	{
		for (i = -2; i < 2; i++)
		{
			int fade = 255 - (timer % 500);
			if (fade > 0)
			{
				int color = (fade << 16) | (fade << 8) | fade;

				x1 = 400 + (i  * 200) + 36;
				y1 = 236;
	
				x2 = x1 + 128;
				y2 = y1 + 128;

				sd->Draw2D(x1, y1, 0, 0, color,
					       x2, y1, 1, 0, color,
						   x1, y2, 0, 1, color,
						   x2, y2, 1, 1, color);
			}
		}
	}

	sd->Stop();
}

void Background04::Receive(dword Message, dword timer)
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
		greetTime = timer;
		greet = true;
		break;
	case 5:
		moveTime = timer;
		move1  = false;
		move2  = false;
		move3  = true;
		break;
	case 6:
		fadeTimer = timer;
		fadeout = true;
		break;
	}
}


void Background04::DeInit()
{
}