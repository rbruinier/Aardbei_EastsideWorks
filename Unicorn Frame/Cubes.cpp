#include "Main.h"

#define CUBES_RESX 8
#define CUBES_RESY 8
#define CUBES_RESZ 8

bool Cubes::Init() 
{
	scene = new Scene();


	scene->ambient = 0x000000;

	int index = 0;
	for (int z = 0; z < CUBES_RESZ; z++)
	{
		for (int y = 0; y < CUBES_RESY; y++)
		{
			for (int x = 0; x < CUBES_RESX; x++)
			{
				scene->addObject(genCube(1, 0.5f, "env03"));

				scene->object[index]->setLoc(-((CUBES_RESX / 2) * 0.5f) + (x * 0.5f), 
					                         -((CUBES_RESY / 2) * 0.5f) + (y * 0.5f), 
											 -((CUBES_RESZ / 2) * 0.5f) + (z * 0.5f));

				scene->object[index]->transMode = UNI_ADD;

				scene->object[index]->setDiffuse(0.2f, 0.2f, 0.2f);

				scene->object[index]->finish(false);

				index++;
			}
		}
	}

	scene->addLight(new Light(1, 1, 1, 1));


	scene->camera->aspect = 0.65f;



	return true;
}   

void Cubes::Do(dword timer) 
{	
	float fade = (timer / 1000.f) * 0.02f;
	if (fade > 0.5f)
	{
		fade = 0.5f;
	}

	for (int i = 0; i < scene->nrObjects; i++)
	{
		float x = scene->object[i]->xLoc;
		float y = scene->object[i]->yLoc;
		float z = scene->object[i]->zLoc;

		float scale = sin((x * 10.2f) + (timer / 500.f)) * 
			          cos((y * 18.32f) + (timer / 800.f)) * 
					  sin((z * 14.25f) + (timer / 600.f)) * 1.0f + 0.0f;

		if (scale < 0)
			scale = 0;

		scene->object[i]->setScl(scale, scale, scale);

		scene->object[i]->setDiffuse(fade, fade, fade);

	}

	scene->camera->setLoc(sin(timer / 7000.f) * 3.f, cos(timer / 7000.f) * 3.f, -sin(timer / 9400.f) * 3.f);
	scene->camera->setRoll(sin(timer / 12000.f) * 360.f);

	scene->light[0]->setLoc(sin(timer / 7000.f) * 3.f, cos(timer / 7000.f) * 3.f, -sin(timer / 9400.f) * 3.f); 

	scene->render();
}

void Cubes::Receive(dword Message, dword timer)
{
}

void Cubes::DeInit() 
{
	delete scene;
}
