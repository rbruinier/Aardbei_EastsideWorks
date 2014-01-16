#include "Main.h"

#define TENT_SEGX 20
#define TENT_SEGY 180

#define LINKIN_MULTIPASS

void genTentacleShape(Vertex *vertex, int nrSegmentsX, int nrSegmentsY)
{
	int timer = uniTimer();

	int index = 0;

	float yMul = 1.f / nrSegmentsY;
	float xMul = (2.f * _PI) / nrSegmentsX;
	float uStp = 1.f / nrSegmentsX;
	float vStp = 1.f / nrSegmentsY;

	for (int y = 0; y < nrSegmentsY + 1; y++)
	{
		float rr = sin((y + (timer / 80.f))* (_PI / TENT_SEGY) * 22.f) * 0.3f + 1.2f;
		float yy = y * yMul;
		float vv = y * vStp;
		for (int x = 0; x < nrSegmentsX + 1; x++)
		{
			float xx, zz, uu;

			xx = sin(x * xMul) * rr;
			zz = cos(x * xMul) * rr;
			uu = x * uStp;

			vertex[index].x = xx;
			vertex[index].y = yy;
			vertex[index].z = zz;
			vertex[index].tu1 = uu;
			vertex[index].tv1 = vv * 10.f;

			index++;
		}
	}
}

Object *genTentacle(int nrSegmentsX, int nrSegmentsY, char *texture)
{
	Object *obj = 
		new Object((nrSegmentsX + 1) * (nrSegmentsY + 1), nrSegmentsX * nrSegmentsY * 2, texture);

	genTentacleShape(obj->vertex, nrSegmentsX, nrSegmentsY);
	
	int index = 0;

	for (int j = 0; j < nrSegmentsY; j++)
	{
		for (int i = 0; i < nrSegmentsX; i++)
		{
			int e = j * (nrSegmentsX + 1);
			int a = e + i;
			int b = a + 1;
			int c = a + nrSegmentsX + 1;
			int d = c + 1;

			obj->face[index].a = a;
			obj->face[index].b = c;
			obj->face[index].c = b;

			index++;

			obj->face[index].a = b;
			obj->face[index].b = c;
			obj->face[index].c = d;

			index++;
		}
	}

	return obj;
}

void Linkin::bendTentacle(Vertex *vertex, int nrSegmentsX, int nrSegmentsY, float radius, float yScale, dword timer)
{
	int index = 0;

	float xRot = 0;
	float yRot = 0;
	float zRot = 0;

	float curLocX = 0;
	float curLocY = 0;
	float curLocZ = 0;
		
	for (int y = 0; y < nrSegmentsY + 1; y++)
	{
		D3DMATRIX rotate;
		uniMatrixRotate(rotate, xRot * _PI / 180.f, yRot * _PI / 180.f, zRot * _PI / 180.f);
		float rr = sin((y + (timer / 80.f))* (_PI / TENT_SEGY) * 22.f) * 0.4f + 0.8f;
		for (int x = 0; x < nrSegmentsX + 1; x++)
		{
			float rrr = rr;// + ((sin(y * 3.5f) * 0.3f) + 0.3f);

			if (y & 2)
			{
				if (x & 2)
				{
					rrr += 2.f;
					if ((timer - punkTimer) < 500)
					{
						rrr += sin(((timer - punkTimer) / 500.f) * _PI) * 4.f;
					}

				}
			}

			float xx = source[x].x * rrr;
			float yy = source[x].y;
			float zz = source[x].z * rrr;

			D3DVECTOR point = {xx, yy, zz};
			uniMatrixMultiplyVector(point, point, rotate);

			xx = point.x + curLocX;
			yy = point.y + curLocY;
			zz = point.z + curLocZ;
			
			vertex[index].x = xx + 18.f;
			vertex[index].y = yy;
			vertex[index].z = zz;

			index++;
		}

		D3DVECTOR dir = {0, yScale / nrSegmentsY, 0};
		D3DMATRIX dirMatrix;
		uniMatrixRotate(dirMatrix, xRot * _PI / 180.f, yRot * _PI / 180.f,  zRot * _PI / 180.f);
		uniMatrixMultiplyVector(dir, dir, dirMatrix);

		curLocX += dir.x; 
		curLocY += dir.y; 
		curLocZ += dir.z; 

		zRot += 3.5f;
		yRot += 4;
		zRot += 2.5f;
	}
}


bool Linkin::Init() 
{
	current = 0;
	oldTimer = 0;
	punkTimer = 0;

	scene = new Scene();

	Object *obj = genTentacle(TENT_SEGX, TENT_SEGY, "texture01");

	obj->finish(true);
	obj->setSpecular(1, 1, 1, 1, 20.f);

	scene->addObject(obj);


	obj = genTentacle(TENT_SEGX, TENT_SEGY, "texture01");

	obj->finish(true);
	obj->setSpecular(1, 1, 1, 1, 20.f);

	scene->addObject(obj);

	source = new D3DVECTOR[TENT_SEGX + 1];
	for (int i = 0; i < TENT_SEGX + 1; i++)
	{
		source[i].x = obj->vertex[i].x;
		source[i].y = 0;
		source[i].z = obj->vertex[i].z;
	}

	scene->addLight(new Light(1.5f, 1.5f, 1.5f, 1));
	scene->addLight(new Light(1.0f, 1.0f, 1.0f, 1));
	scene->ambient = 0x404040;

	obj = genSphere(10, 80.f, "sprite02");

	scene->camera->fov = 1.0f;


	scene->camera->setLoc(0, 40, -140);

	fadeOut = false;

	return true;
}   



void Linkin::Do(dword timer) 
{
	bendTentacle(scene->object[0]->vertex, TENT_SEGX, TENT_SEGY, 0.5f, 200.f, timer);
	bendTentacle(scene->object[1]->vertex, TENT_SEGX, TENT_SEGY, 0.5f, 200.f, timer);
//	scene->object[0]->setRot(timer / 90.f, timer / 80.f, timer / 120.f);

	float x = sin(timer / 3400.f) * cos(timer / 2460.f) * 20.f;
	float y = cos(timer / 3000.f) * cos(timer / 3460.f) * 10.f;
	float z = sin(timer / 4000.f) * cos(timer / 2060.f) * 20.f;

	scene->object[0]->setLoc(-14, 0, 0);

	scene->object[1]->setLoc( 14, 0, 0);

	scene->object[1]->setRot(90, 0, 0);

	float radiusx = 70.f;
	float radiusz = 50.f;

	if (timer < 1000)
	{
		radiusx = 300.f - sin((timer / 1000.f) * (_PI / 2.f)) * 230.f;
		radiusz = 280.f - sin((timer / 1000.f) * (_PI / 2.f)) * 230.f;
		scene->object[0]->transMode = UNI_ALPHA;
		scene->object[0]->setDiffuse(1, 1, 1, timer / 1000.f);
		scene->object[1]->transMode = UNI_ALPHA;
		scene->object[1]->setDiffuse(1, 1, 1, timer / 1000.f);
	}
	else
	{
		scene->object[0]->transMode = UNI_NONE;
		scene->object[1]->transMode = UNI_NONE;
	}

	float timerr = (timer - punkTimer) / 1000.f;
	if ((timerr < 0.5f) && (timer > 1000))
	{
		float alpha = 0.75f + cos(timerr * _PI2 * 2.f) * 0.25f;
		scene->object[0]->transMode = UNI_ALPHA;
		scene->object[0]->setDiffuse(1, 1, 1, alpha);
		scene->object[1]->transMode = UNI_ALPHA;
		scene->object[1]->setDiffuse(1, 1, 1, alpha);
	}


	if (fadeOut)
	{
		radiusx = 70.f - ((timer - fadeTimer) / 1000.f) * 30.f;
		radiusz = 50.f - ((timer - fadeTimer) / 1000.f) * 20.f;
		float alpha = (timer - fadeTimer) / 1000.f;
		if (alpha > 1)
		{
			alpha = 1;
		}
		scene->object[0]->transMode = UNI_ALPHA;
		scene->object[0]->setDiffuse(1, 1, 1, 1.f - alpha);
		scene->object[1]->transMode = UNI_ALPHA;
		scene->object[1]->setDiffuse(1, 1, 1, 1.f - alpha);
	}


	scene->camera->setLoc(sin(timer / 1000.f) * radiusx, sin(timer / 1400.f) * 20.f, cos(timer / 1000.f) * radiusz);

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


	scene->light[1]->setLoc(scene->camera->xLoc / 1.5f,
						    scene->camera->yLoc / 1.5f,
							scene->camera->zLoc / 1.5f);

	scene->render();

	oldTimer = timer;
}

void Linkin::Receive(dword Message, dword timer)
{
	if ((Message == 10))
	{
		punkTimer = timer;
	}
	else
	{
		current = Message;
	}

	if (Message == 8)
	{
		fadeTimer = timer;
		fadeOut = true;
	}
}

void Linkin::DeInit() 
{
	delete scene;
	delete source;
};

