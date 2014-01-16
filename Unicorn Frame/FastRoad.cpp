#include "Main.h"

bool FastRoad::Init() 
{
	scene = new Scene();

	scene->addObject(genPlane(39, 100, "road01"));

	Object *obj = scene->object[0];

	int index = 0;
	for (int z = 0; z < 40; z++)
	{
		for (int x = 0; x < 40; x++)
		{
			obj->vertex[index].y = (sin(z / 10.f) * 7.f) + ((sin(x / 10.f) * 2.f) - 2.f);
			obj->vertex[index].z *= 3.f;
			index++;
		}		
	}

	obj->transMode = UNI_ADD;

	//obj->setDiffuse(0.15f, 0.15f, 0.15f);

	obj->writeZBuffer = false;


	scene->object[0]->finish(true);

	scene->ambient = 0x202020;

	scene->addLight(new Light(1, 1, 1, 1));

	fadeOut = false;
	
	return true;
}   


void FastRoad::Do(dword timer) 
{
	float diffuse = (timer / 1000.f) * 0.10f;

	if (diffuse > 0.45f)
	{
		diffuse = 0.45f;
	}

	if (fadeOut)
	{
		diffuse = 0.45f - ((timer - fadeTimer) / 1000.f) * 0.22f;
	}

	if (diffuse < 0)
	{
		diffuse = 0;
	}

	Object *obj = scene->object[0];

	obj->setDiffuse(diffuse, diffuse, diffuse); 
	obj->setAmbient(diffuse, diffuse, diffuse);

	int index = 0;
	for (int v = 0; v < 40; v++)
	{
		float vcord = (float)v / 40.f * 2.f + (fmod((timer) / 400.f, 1));
		for (int u = 0; u < 40; u++)
		{
			obj->vertex[index].tu1 = (float)u / 40.f;
			obj->vertex[index].tv1 = vcord;
			index++;
		}		
	}
		
	float x, y;

	x = sin(timer / 4000.f) * sin(timer / 5000.f) * 20.f;
	y = sin(timer / 3000.f) * sin(timer / 4100.f)  * 1.f;

	scene->camera->setLoc(x, 14 + y, -100);

	timer += 3000.f;

	x = sin(timer / 4000.f) * sin(timer / 5000.f) * 20.f;

	scene->camera->setTar(x, 0, 0);

	scene->camera->fov = 1.1f;
	scene->light[0]->setLoc(0, 14, -90);

	scene->fog = true;
	scene->fogEnd = 190;

	scene->render();
}

void FastRoad::Receive(dword Message, dword timer)
{
	fadeOut = true;
	fadeTimer = timer;
}

void FastRoad::DeInit() 
{
	delete scene;
};
