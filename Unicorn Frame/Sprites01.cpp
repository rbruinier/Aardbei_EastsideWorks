#include "Main.h"

bool Sprites01::Init() 
{
	nrSprites = 1500;

	sprites = new SpriteInfo[nrSprites];

	for (int i = 0; i < nrSprites; i++)
	{
		sprites[i].x = uniRand() * 800.f;
		sprites[i].y = uniRand() * 550.f + 80.f;
		sprites[i].speed = uniRand() * 25.f + 5.f;
		sprites[i].size = sprites[i].speed;
		sprites[i].flits = uniRand() * 20000.f + 5000.f;
	}

	oldTime = 0;

	fadeOut = false;

	return true;
}   

void Sprites01::Do(dword timer) 
{	
	float timeDif = (timer - oldTime) / 1000.f;

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	uniSetTexture("sprite01");

	sd->Start(UNI_SUB);

	int fade = timer / 200;

	if (fadeOut)
	{
		fade = 0x10 - ((timer - fadeTimer) / 160.f);
	}

	if (fade > 0x10)
	{
		fade = 0x10;
	}

	if (fade < 0)
	{
		fade = 0;
	}

	int color = (fade << 16) | (fade << 8) | fade;

	for (int i = 0; i < nrSprites; i++)
	{
		sprites[i].y -= sprites[i].speed * timeDif;

		if (sprites[i].y < 0)
		{
			sprites[i].y = 600;
		}

		float size = sprites[i].size;

		int timerr = timer + 20000;

		if ((timerr % sprites[i].flits) < 600)
		{
			size += sin(((timerr % sprites[i].flits) / 600.f) * _PI) * 50.f;
		}

		float x1 = sprites[i].x - (size / 2.f);
		float x2 = x1 + size;

		float y1 = sprites[i].y - (size / 2.f);
		float y2 = y1 + size;

		sd->Draw2D(x1, y1, 0, 0, color,
			       x2, y1, 1, 0, color,
				   x1, y2, 0, 1, color,
				   x2, y2, 1, 1, color);
	}


	sd->Stop();

	oldTime = timer;
}

void Sprites01::Receive(dword Message, dword timer)
{
	if (Message == 1)
	{
		fadeOut = true;
		fadeTimer = timer;
	}
}

void Sprites01::DeInit() 
{
	delete [] sprites;
}
