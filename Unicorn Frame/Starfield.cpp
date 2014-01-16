#include "Main.h"

#define STARFIELD_NRSTARS   6000
#define STARFIELD_STARSPEED    0.01f


bool Starfield::Init() 
{
	scene = new Scene();

	scene->fogSprites = true;

	scene->addSpriteGroup(new SpriteGroup(STARFIELD_NRSTARS, 0.14f, 0x1a1a1a, "sprite01"));
	for (int i = 0; i < STARFIELD_NRSTARS; i++) {
		scene->spriteGroup[0]->sprite[i].setLoc((uniRand() * 20.f) - 10.f,
								                (uniRand() * 20.f) - 10.f,
												(uniRand() * 30.f) - 5.f);
	}

	oldTimer = 0;

	mode = 1;

	return true;
}   

void Starfield::Do(dword timer) 
{	
	float timing = timer - oldTimer;
	oldTimer = timer;

	int fade = (timer / 1000.f) * 5.f;
	if (fade > 30)
	{
		fade = 30;
	}
	int color = (fade << 16) | (fade << 8) | (fade);
	for (int i = 0; i < STARFIELD_NRSTARS; i++) {
		float x = scene->spriteGroup[0]->sprite[i].x;
		float y = scene->spriteGroup[0]->sprite[i].y;
		float z = scene->spriteGroup[0]->sprite[i].z;

		scene->spriteGroup[0]->sprite[i].setLoc(x, y, z - (timing * STARFIELD_STARSPEED));
		if (z < -5.0f) {
			float p = uniRand() * _PI2;
//			x = sin(p) * (uniRand() * 0.4f + 1.2f + (sin(timer / 1000.f) * 0.4f));
//			y = cos(p) * (uniRand() * 0.4f + 1.2f + (cos(timer / 1300.f) * 0.4f));
//			z = 25 + (uniRand() * 4.f);
			if (mode == 1)
			{
				x = (uniRand() * 20.f) - 10.f;
				y = (uniRand() * 20.f) - 10.f;
			}
			else
			{
				x = sin(p) * (uniRand() * 0.4f + 1.2f + (sin(timer / 1000.f) * 0.4f));
				y = cos(p) * (uniRand() * 0.4f + 1.2f + (cos(timer / 1300.f) * 0.4f));
			}
			z = 25 + (uniRand() * 4.f);


			
			scene->spriteGroup[0]->sprite[i].setLoc(x, y, z);
		}

		scene->spriteGroup[0]->sprite[i].diffuse = color;
	}

	scene->fog = true;
	scene->fogEnd = 30.f;

	scene->camera->setRoll(sin(timer / 5000.f) * 20.f);


	uniSetRenderState(D3DRS_RANGEFOGENABLE, TRUE);

	scene->render();

	uniSetRenderState(D3DRS_RANGEFOGENABLE, FALSE);
}

void Starfield::Receive(dword Message, dword timer)
{
	mode = Message;
}

void Starfield::DeInit() 
{
	delete scene;
}
