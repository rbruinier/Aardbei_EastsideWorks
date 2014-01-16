#include "Main.h"

bool Sprites02::Init() 
{
	nrSprites = 2000;

	sprites = new SpriteInfo[nrSprites];

	for (int i = 0; i < nrSprites; i++)
	{
		sprites[i].x = (uniRand() * 1000.f) - 100.f;
		sprites[i].y = uniRand() * 550.f + 80.f;
		sprites[i].speed = uniRand() * 15.f + 5.f;
		sprites[i].size = sprites[i].speed * 1.5f;
	}

	oldTime = 0;

	fadeOut = false;

	return true;
}   

void Sprites02::Do(dword timer) 
{	
	float timeDif = (timer - oldTime) / 1000.f;

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	uniSetTexture("sprite01");

	sd->Start(UNI_ADD);

	int fade = timer / 200;

	if (fadeOut)
	{
		fade = 0x08 - ((timer - fadeTimer) / 200.f);
	}

	if (fade > 0x08)
	{
		fade = 0x08;
	}

	if (fade < 0)
	{
		fade = 0;
	}

	int color = (fade << 16) | (fade << 8) | fade;

	for (int i = 0; i < nrSprites; i++)
	{
		float x = sprites[i].x;
		float y = sprites[i].y;

		x = x + ((((sin(y / 50.f) * 0.6f) + (sin(y / 37.f) * 0.4f)) * 0.8f) * timeDif * sprites[i].speed);
		y = y + ((((cos(x / 62.f) * 0.5f) + (sin(x / 52.f) * 0.5f)) * 0.8f) * timeDif * sprites[i].speed);

		sprites[i].x = x;
		sprites[i].y = y;

		float size = sprites[i].size;

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

void Sprites02::Receive(dword Message, dword timer)
{
	if (Message == 1)
	{
		fadeOut = true;
		fadeTimer = timer;
	}
}

void Sprites02::DeInit() 
{
	delete [] sprites;
}
