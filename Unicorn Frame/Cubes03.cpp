#include "Main.h"

#define CUBEPOS_NR 35

float cubePos[][3] =
{
	{ 0, 0, 0},

	{-1, 1, 1},
	{ 1, 1, 1},
	{-1, 1,-1},
	{ 1, 1,-1},

	{-1,-1, 1},
	{ 1,-1, 1},
	{-1,-1,-1},
	{ 1,-1,-1},

	{-2, 2, 2},
	{ 0, 2, 2},
	{ 2, 2, 2},

	{-2, 0, 2},
	{ 0, 0, 2},
	{ 2, 0, 2},

	{-2,-2, 2},
	{ 0,-2, 2},
	{ 2,-2, 2},

	{-2, 2,-2},
	{ 0, 2,-2},
	{ 2, 2,-2},

	{-2, 0,-2},
	{ 0, 0,-2},
	{ 2, 0,-2},

	{-2,-2,-2},
	{ 0,-2,-2},
	{ 2,-2,-2},

	{-2, 2, 0},
	{ 0, 2, 0},
	{ 2, 2, 0},

	{-2,-2, 0},
	{ 0,-2, 0},
	{ 2,-2, 0},

	{-2, 0, 0},
	{ 2, 0, 0}
};

bool Cubes03::Init() 
{
	current = 0;

	fadeOut = false;

	int width, height;

	dword *data = loadATSFromMem(ATS_BRICK02, width, height);

	int index = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (data[index] & 0xff)
			{
				data[index] = data[index] | (0xff << 24);
			}
			else
			{
				data[index] = data[index] & 0x00ffffff;
			}

			index++;			
		}
	}

	uniTextureCreate("brick02", data, width, height, UNI_NONE);

	scene = new Scene();

	for (int i = 0; i < CUBEPOS_NR; i++)
	{
		Object *obj = genCube(1, 2.f, "brick02");
		obj->cull = CULL_NONE;
		obj->alphatest = true;
		for (int j = 0; j < obj->nrVertices; j++)
		{
			obj->vertex[j].x += cubePos[i][0];
			obj->vertex[j].y += cubePos[i][1];
			obj->vertex[j].z += cubePos[i][2];
		}
		scene->addObject(obj);
	}

	
	//	scene->ambient = 0x000000;

//	scene->addLight(new Light(1.0f, 1.0f, 1.0f, 1));

	scene->camera->nearPlane = 0.001f;

	scene->camera->fov = 1;


	return true;
}   

void Cubes03::Do(dword timer) 
{	
	float radiusx = 0.9f;
	float radiusz = 1.7f;

	if (timer < 3000)
	{
		radiusx = 15.f - sin((timer / 3000.f) * (_PI / 2.f)) * 14.1f;
		radiusz = 15.f - sin((timer / 3000.f) * (_PI / 2.f)) * 13.3f;
		for (int i = 0; i < CUBEPOS_NR; i++)
		{
			scene->object[i]->transMode = UNI_ALPHA;
			scene->object[i]->setDiffuse(1, 1, 1, timer / 3000.f);
		}
	}
	else
	{
		for (int i = 0; i < CUBEPOS_NR; i++)
		{
			scene->object[i]->transMode = UNI_NONE;
		}
	}

	if (fadeOut)
	{
		float alpha = (timer - fadeTimer) / 900.f;
		if (alpha > 1)
		{
			alpha = 1;
		}
		for (int i = 0; i < CUBEPOS_NR; i++)
		{
			scene->object[i]->transMode = UNI_ALPHA;
			scene->object[i]->setDiffuse(1, 1, 1, 1.f - alpha);
		}
	}



//	scene->light[0]->setLoc(0, 0, 0);

/*
	scene->camera->setTar(sin(timer / 1500.f) * 0.5f, cos((timer + 300) / 3000.f) * 1.5f, cos(timer / 1500.f) * 1.7f);

	timer -= 2000;
	scene->camera->setLoc(sin(timer / 1500.f) * radiusx, cos((timer + 300) / 3000.f) * 1.5f, cos(timer / 1500.f) * radiusz);

	scene->camera->setRoll(30 + sin(timer / 3000.f) * 10.f + cos(timer / 1900.f) * 5.f);
*/
	timer += 2000;
	scene->camera->setTar(sin(timer / 1000.f) * 0.5f, cos((timer + 300) / 2000.f) * 1.5f, cos(timer / 1000.f) * 1.7f);

	timer -= 2000;
	scene->camera->setLoc(sin(timer / 1000.f) * radiusx, cos((timer + 300) / 2000.f) * 1.5f, cos(timer / 1000.f) * radiusz);

//	scene->camera->setRoll(30 + sin(timer / 3000.f) * 10.f + cos(timer / 1900.f) * 5.f);
//	scene->camera->setRoll((timer / 1000.f) * 20.f);

	float timeDif = (timer - oldTimer) / 1000.f;

	switch (current)
	{
	case 0:
		scene->camera->roll += 40.f * timeDif;
		break;
	case 1:
		scene->camera->roll += -40.f * timeDif;
		break;
	};

	oldTimer = timer;


	scene->render();
}

void Cubes03::Receive(dword Message, dword timer)
{
	/*
	if ((Message == 10))
	{
		punkTimer = timer;
	}
	else
	{
		current = Message;
	}
*/
	current = Message;

	if (Message == 8)
	{
		fadeTimer = timer;
		fadeOut = true;
	}

}

void Cubes03::DeInit() 
{
	delete scene;
}
