#include "Main.h"

bool Sphery03::Init() 
{
	scene = new Scene();

	scene->addObject(genSphere(37, 2.f, "env03"));
/*
	scene->addSpriteGroup(new SpriteGroup(scene->object[0]->nrVertices / 12, 0.03f, 0xcccccc, "sprite01"));

	for (int i = 0; i < scene->object[0]->nrVertices / 24; i++)
	{
		scene->spriteGroup[0]->sprite[i].diffuse = 0x505050;
	}

*/
	oldObject = genSphere(37, 2.f, NULL);

	scene->object[0]->finish(true);

	scene->ambient = 0x202020;

	scene->addLight(new Light(1.3f, 1.3f, 1.3f, 1));

	scene->object[0]->transMode = UNI_ADD;
	scene->object[0]->setDiffuse(0.8f, 0.8f, 0.8f);

	return true;
}   

void Sphery03::Do(dword timer) 
{	

	timer += 0;
	Vertex *src = oldObject->vertex;
	float timer1 = timer / 1000.f;
	float timer2 = timer / 2700.f;
	float timer3 = timer / 2100.f;
	for (int i = 0; i < oldObject->nrVertices; i++)
	{
		float x = src[i].x;
		float y = src[i].y;
		float z = src[i].z;

		float scale;

		float scale2 = x + 0.5;
		if (scale2 < 0)
		{
			scale2 = 0;
		}

		scale = 1.0f + ((cos(x * 12.f) * scale2 * 
   		                 cos((z * 10.5f) + (timer / 2000.f)) * 
					     sin((y * 14.5f) + (timer / 1700.f))) * 0.7f);

		x *= scale;
		y *= scale;
		z *= scale;

		float dist = 2.5f - scale;

		float yrot = 3;

		if (fmod(timer / 2050.f, _PI2) < _PI)
		{
			yrot = 0;
		}

		D3DMATRIX rotate;
		uniMatrixRotate(rotate, sin((timer1) + (dist * 0.3f)) * 2.0f, 
			                    yrot, 
								sin((timer3) + (dist * 0.3f)) * 0.0f);

		D3DVECTOR point = {x, y, z};
		uniMatrixMultiplyVector(point, point, rotate);

		scene->object[0]->vertex[i].x = point.x + (cos((timer / 3050.f) + (dist * 0.09f)) * 8.5f) + (sin((timer / 300.f) + (dist * 1.5f)) * 0.6f);
		scene->object[0]->vertex[i].y = point.y;
		scene->object[0]->vertex[i].z = point.z;
	}
/*
	for (i = 0; i < scene->object[0]->nrVertices / 12; i++)
	{
		scene->spriteGroup[0]->sprite[i].setLoc(scene->object[0]->vertex[i * 12].x,
			                                    scene->object[0]->vertex[i * 12].y,
												scene->object[0]->vertex[i * 12].z);

	}
*/
	scene->light[0]->setLoc(scene->camera->xLoc,
		                    scene->camera->yLoc,
							scene->camera->zLoc);

//	float scale = 1.2f - (((timer % 500) / 500.f) * 0.4f);
//	scene->object[0]->setScl(scale, scale, scale);

	scene->camera->aspect = 0.6f;
	scene->camera->fov = 0.95f;

	scene->render();
}

void Sphery03::Receive(dword Message, dword timer)
{
	switch (Message)
	{
	case 0:
		scene->camera->roll = -40;
		break;
	case 1:
		scene->camera->roll = 40;
	}
}

void Sphery03::DeInit() 
{
	delete scene;
	delete oldObject;
}
