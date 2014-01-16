#include "Main.h"
/*
int colorTab[] =
{
	0x000000,
	0xda5a20,
	0xdfdb20,
	0x23df20,
	0x2334d9,
	0x9026d9,
	0xd9266d
};
*/
int colorTab[] =
{
	0x000000,
	0x171091,
	0x911017,
	0x109117,
};
		
bool Background05::Init()
{
	currentColor = 0;
	fadeTimer = 0;


	return true;
}
 
void Background05::Do(dword timer)
{
	if (currentColor == 0)
	{
		return;
	}

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	uniSetTexture(NULL);

	sd->Start(UNI_DRAW);

	timer = timer - fadeTimer;

	int color1 = calcColor(colorTab[currentColor - 1], colorTab[currentColor], timer / 1000.f);
	int color2 = calcColor(colorTab[currentColor - 1], colorTab[currentColor], ((float)timer - 500) / 1000.f);

	float x1, y1, x2, y2;

	for (int i = 0; i < 440; i += 2)
	{
		x1 = 0;
		x2 = 800;
		y1 = 80 + i;
		y2 = y1 + 1;

		sd->Draw2D(x1, y1, 0, 0, color1,
			       x2, y1, 0, 0, color2,
				   x1, y2, 0, 0, color1,
		           x2, y2, 0, 0, color2);
	}

	sd->Stop();
}

void Background05::Receive(dword Message, dword timer)
{
	fadeTimer = timer;
	currentColor++;
}


void Background05::DeInit()
{
}