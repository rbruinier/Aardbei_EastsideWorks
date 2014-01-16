#include "Main.h"

#define KEY_AANTAL 22

float keys[][7] =
{
	{    0,  0,  0,-10,  0,  0, -1},
	{    0,  0,  0, 10,  0,  0,  1},

	{    1,-10,  1,  0, -1,  1,  0},
	{    1, 10,  1,  0,  1,  1,  0},
	{    1,  0,  1,-10,  0,  1, -1},
	{    1,  0,  1, 10,  0,  1,  1},

	{    2,-10, -1,  0, -1, -1,  0},
	{    2, 10, -1,  0,  1, -1,  0},
	{    2,  0, -1,-10,  0, -1, -1},
	{    2,  0, -1, 10,  0, -1,  1},

	{    3,-10,  1,-10, -1,  1, -1},
	{    3,-10,  1, 10, -1,  1,  1},
	{    3, 10,  1,-10,  1,  1, -1},
	{    3, 10,  1, 10,  1,  1,  1},

	{    4,-10, -1,-10, -1, -1, -1},
	{    4,-10, -1, 10, -1, -1,  1},
	{    4, 10, -1,-10,  1, -1, -1},
	{    4, 10, -1, 10,  1, -1,  1},

	{    5,  0,-10,  0,  0, -1,  0},
	{    5,  0, 10,  0,  0,  1,  0},
	{    5,-10,  0,  0, -1,  0,  0},
	{    5, 10,  0,  0,  1,  0,  0},

//	{    1,  0,  0,  0,  0,  0,  0},
};


bool Cubes02::Init() 
{
	cube02StartTime = 0;
	currentKey = -1;

	bend = stretch = explode = false;

	scene = new Scene();

	oldObject = genCube(3, 1, NULL);

	scene->ambient = 0x000000;

	scene->addLight(new Light(1.0f, 1.0f, 1.0f, 1));

	// eerste fase
	scene->addObject(genCube(3, 1, "brick01"));
	scene->object[0]->transMode = UNI_ALPHA;

	// tweede fase
	for (int i = 0; i < KEY_AANTAL; i++)
	{
		scene->addObject(genCube(3, 1, "brick01"));

		scene->object[i + 1]->transMode = UNI_ALPHA;
	}

	for (i = 0; i < scene->nrObjects; i++)
	{
		scene->object[i]->finish(true);
	}

	scene->camera->aspect = 0.65f;

	scene->camera->fov = 0.95f;

	return true;
}   

void Cubes02::Do(dword timer) 
{	
	int i;

	if (currentKey == -1)
	{
		if (timer < 2000)
		{
			scene->object[0]->setLoc(0, 10 - (sin((timer / 2000.f) * (_PI / 2.f)) * 10.f), 0);
		}
		else
		{
			scene->object[0]->setLoc(0, 0, 0);
		}
	}

	scene->camera->setLoc(sin(timer / 2000.f) * 3.f, cos(timer / 2000.f) * 3.0f, -5);

	scene->light[0]->setLoc(scene->camera->xLoc + 1,
		                    scene->camera->yLoc + 2,
							scene->camera->zLoc + 2);

	
	// keyframen
	float timeDif = (timer - cube02StartTime) / 500.f;

	int index = 1;

	for (i = 0; i < KEY_AANTAL; i++)
	{
		if ((int)keys[i][0] < currentKey)
		{
			scene->object[index]->setLoc(keys[i][4], keys[i][5], keys[i][6]);
			scene->object[index]->setDiffuse(1, 1, 1, 1);
		}
		else if ((int)keys[i][0] == currentKey)
		{
			if (timeDif < 1)
			{
				float x = keys[i][1] + ((keys[i][4] - keys[i][1]) * timeDif);
				float y = keys[i][2] + ((keys[i][5] - keys[i][2]) * timeDif);
				float z = keys[i][3] + ((keys[i][6] - keys[i][3]) * timeDif);

				scene->object[index]->setLoc(x,
					                         y,
										     z);

				scene->object[index]->setDiffuse(1, 1, 1, timeDif);
			}
			else
			{
				scene->object[index]->setLoc(keys[i][4], keys[i][5], keys[i][6]);
				scene->object[index]->setDiffuse(1, 1, 1, 1);
			}
		}
		else
		{
				scene->object[index]->setLoc(keys[i][1], keys[i][2], keys[i][3]);
				scene->object[index]->setDiffuse(1, 1, 1, 0);
		}

		index++;
	}

	// benden
	if (bend)
	{
		float amp = 1;// = (timer - cube02StartTime) / 2000.f;
		if ((timer - cube02StartTime) < 2000)
		{
			amp = 0.5f - cos(((timer - cube02StartTime) / 2000.f) * _PI) * 0.5f;
		}
		if (amp > 1)
		{
			amp = 1;
		}
		if (stretch)
		{
			amp = 1;
		}
		D3DMATRIX rotate;
		for (i = 0; i < scene->nrObjects; i++)
		{
			for (int j = 0; j < scene->object[i]->nrVertices; j++)
			{
				float x = oldObject->vertex[j].x + scene->object[i]->xLoc;
				float y = oldObject->vertex[j].y + scene->object[i]->yLoc;
				float z = oldObject->vertex[j].z + scene->object[i]->zLoc;

				float xrot = 0, yrot = 0, zrot = 0;

				float scale = sin((x * 2.3f) + (timer / 560.f)) +
					          cos((y * 2.0f) + (timer / 900.f)) +
							  sin((z * 1.7f) + (timer / 400.f));

				scale = ((scale / 8.f) * amp) + 1.0f;

				xrot = sin((timer / 800.f) + (x * 0.4f)) * amp;
				yrot = cos((timer / 900.f) + (y * 0.4f)) * amp;
				zrot = sin((timer / 600.f) + (z * 0.5f)) * amp;

				uniMatrixRotate(rotate, xrot, yrot, zrot);

				D3DVECTOR point = {x, y, z};
				uniMatrixMultiplyVector(point, point, rotate);

				scene->object[i]->vertex[j].x = point.x * scale;
				scene->object[i]->vertex[j].y = point.y * scale;
				scene->object[i]->vertex[j].z = point.z * scale;			
			}
			scene->object[i]->setLoc(0, 0, 0);
		}

	}

	// stretch
	if (stretch)
	{
		float scale = 5;
		if ((timer - cube02StartTime) < 1000)
		{
			scale = sin(((timer - cube02StartTime) / 1000.f) * (_PI / 2.f)) * 2.f;
		}

		index = 1;
		for (i = 0; i < KEY_AANTAL; i++)
		{
			float x = keys[i][4];
			float y = keys[i][5];
			float z = keys[i][6];

			float dist = sqrt((x * x) + (y * y) + (z * z));

			x /= dist;
			y /= dist;
			z /= dist;

		
			scene->object[index]->setLoc(x * scale, y * scale, z * scale);

			scene->object[index]->setDiffuse(1, 1, 1, 1.0f - (scale / 2.f));

			index++;
		}
		if (explode)
		{
			scene->object[0]->setDiffuse(1, 1, 1, 1.0f - (scale / 2.f));
		}
	}


	scene->render();

}

void Cubes02::Receive(dword Message, dword timer)
{
	switch (Message)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		cube02StartTime = timer;
		currentKey = Message;
		break;
	case 6:
		cube02StartTime = timer;
		currentKey = 6;
		bend = true;
		break;
	case 7:
		cube02StartTime = timer;
		stretch = true;
		break;
	case 8:
		cube02StartTime = timer;
		explode = true;
		break;
	}
}

void Cubes02::DeInit() 
{
	delete scene;
}
