#include "Main.h"

#include <olectl.h>

struct texture
{
	char *name;
	unsigned char *source;
	int	 flags;
	bool toMem;
};

#define TEXTURELOAD_NR 1

texture texturesToLoad[] =
{
	{"sprite01",	ATS_SPRITE01,		UNI_NONE,	true},		// background01 
	{"env03",		ATS_ENV03,			UNI_MIPMAP,	true},		// sphery03
	{"greets",		ATS_GREETS,			UNI_NONE,	true},		// greets
	{"road01",		ATS_ROAD01,			UNI_MIPMAP,	true},		// road
	{"sprite02",	ATS_SPRITE02,		UNI_NONE,	true},		// background01 
	{"texture01",	ATS_TEXTURE01,		UNI_MIPMAP,	true},		// linkin
	{"brick01",		ATS_BRICK,			UNI_MIPMAP,	true},		// cubes02

	{"credits",		ATS_CREDITS,		UNI_NONE,	true},		// background01 
	{"title",		ATS_TITLE,			UNI_NONE,	true},		// background01 

	{"hello",		ATS_HELLO,			UNI_NONE,	true},		// background04

	{"distort01",	ATS_DISTORT01,		UNI_NONE,	true},		// distort
	{"distort02",	ATS_DISTORT02,		UNI_NONE,	true},		// distort

	{NULL,			NULL,				NULL,		NULL}
};


void LoadAllTextures()
{
	unsigned char *currentTexture;
	int width, height;
	int index = 0;
	int extraIndex = 0;
	while ((currentTexture = texturesToLoad[index].source) != NULL)
	{
  		MSG  msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		if (msg.message == WM_QUIT)
		{
			uniQuit();
		}

		dword *data = loadATSFromMem(currentTexture, width, height);
		if (texturesToLoad[index].toMem)
		{
			uniTextureCreate(texturesToLoad[index].name, data, width, height, texturesToLoad[index].flags);
		}

		index++;

		_sleep(20); 
	}
}

// COMMON EFFECTS

void ClearBuffers::Do(dword timer) 
{
	uniClearBuffers(UNI_BBF | UNI_ZBF, clearColor);
}

void ClearBuffers::Receive(dword message, dword timer) 
{
	clearColor = message; 
}


void CameraKick::Do(dword timer) 
{
	kickamp = 0.1f - (timer / 4000.f);
	if (kickamp < 0)
		kickamp = 0;
}

bool Noise01::Init() 
{
	return true;
}

void Noise01::Do(dword timer) 
{
	int pos, row, sync;
	fmodGetInfo(pos, row, sync);

	if (pos < 12)
	{
		uniSetTexture("distort01");
	}
	else
	{
		uniSetTexture("distort02");
	}

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;

	float u1, v1, u2, v2;

	u1 = 0;
	v1 = 0;
	u2 = 12.5f;
	v2 = 6.875f;

	int a = 0xAA - (timer / 1);
	int c = (a << 16) | (a << 8) | a;
	if (a >= 0) 
	{
		float distu = 0;
		float distv = 0;
		sd->Start(UNI_ADD);
		sd->Draw2D(x1, y1, u1, v1, c,
				   x2, y1, u2, v1, c,
  				   x1, y2, u1, v2, c,
				   x2, y2, u2, v2, c);
		sd->Stop();
	}
}

void Noise01::DeInit() 
{
}

bool Noise02::Init() 
{
	noise = new dword[512 * 256];
	for (int i = 0; i < 512 * 256; i++)
	{
		int fade = rand() % 255;
		noise[i] = (fade << 16) | (fade << 8) | (fade) | (0xff << 24);
//		noise[i] = fade << 24;
//		noise[i] = ((rand() % 255) << 16) | ((rand() % 255) << 8) | ((rand() % 255)) | (0xff << 24);
	}

	uniTextureCreate("noise02", noise, 512, 256, 0);

	return true;
}

void Noise02::Do(dword timer) 
{
	uniSetTexture("noise02");

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;

    int c = 0xffffff;
	int a = 0xff - (timer / 3);
	if (a >= 0) 
	{
		float dist = uniRand() * 2.f;
		c += a << 24;
		sd->Start(UNI_ALPHA);
		sd->Draw2D(x1, y1, 0 + dist, 0 + dist, c,
				  x2, y1, 1 + dist, 0 + dist, c,
  				  x1, y2, 0 + dist, 1 + dist, c,
				  x2, y2, 1 + dist, 1 + dist, c);
		sd->Stop();
	}
}

void Noise02::DeInit() 
{
	delete [] noise;
}


void FlashWhite::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0xffffff;
	int a = 0xff - (timer / 5);
	if (a >= 0) {
		c += a << 24;
		sd->Start(UNI_ALPHA);
		sd->Draw2D(x1, y1, 0, 0, c,
				  x2, y1, 0, 0, c,
  				  x1, y2, 0, 0, c,
				  x2, y2, 0, 0, c);
		sd->Stop();
	}
}

void FlashBlack::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0x0;
	int a = 0xff - (timer / 7);
	if (a >= 0) {
		c += a << 24;
		sd->Start(UNI_ALPHA);
		sd->Draw2D(x1, y1, 0, 0, c,
				  x2, y1, 0, 0, c,
  				  x1, y2, 0, 0, c,
				  x2, y2, 0, 0, c);
		sd->Stop();
	}
}

void FadeWhite::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0xffffff;
	int a = 0x0 + (timer / 7);
	if (a > 255)
		a = 255;
	c += a << 24;

	sd->Start(UNI_ALPHA);
	sd->Draw2D(x1, y1, 0, 0, c,
			  x2, y1, 0, 0, c,
			  x1, y2, 0, 0, c,
			  x2, y2, 0, 0, c);
	sd->Stop();
}


void FadeBlack::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0x0;
	int a = 0x0 + (timer / 7);
	if (a > 255) 
		a = 255;
	c += a << 24;

	sd->Start(UNI_ALPHA);
	sd->Draw2D(x1, y1, 0, 0, c,
			  x2, y1, 0, 0, c,
			  x1, y2, 0, 0, c,
			  x2, y2, 0, 0, c);
	sd->Stop();
}

bool FlashWhiteFast::Init()
{
	mode = 2;
	return true;
}

void FlashWhiteFast::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0xffffff;
	int a = 0xff - (timer / 2);
	if (mode == 2)
	{
		a = 0x77 - (timer / 1);
	}
	if (a >= 0) {
		c += a << 24;
		sd->Start(UNI_ALPHA);
		sd->Draw2D(x1, y1, 0, 0, c,
				  x2, y1, 0, 0, c,
  				  x1, y2, 0, 0, c,
				  x2, y2, 0, 0, c);
		sd->Stop();
	}
}

void FlashWhiteFast::Receive(dword message, dword timer) 
{
	mode = message & 255; 
}

void FlashBlackFast::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0x0;
	int a = 0xff - (timer / 1.5);
	if (a >= 0) {
		c += a << 24;
		sd->Start(UNI_ALPHA);
		sd->Draw2D(x1, y1, 0, 0, c,
				  x2, y1, 0, 0, c,
  				  x1, y2, 0, 0, c,
				  x2, y2, 0, 0, c);
		sd->Stop();
	}
}

void FadeWhiteFast::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0xffffff;
	int a = 0x0 + (timer / 2);
	if (a > 255)
		a = 255;
	c += a << 24;

	sd->Start(UNI_ALPHA);
	sd->Draw2D(x1, y1, 0, 0, c,
			  x2, y1, 0, 0, c,
			  x1, y2, 0, 0, c,
			  x2, y2, 0, 0, c);
	sd->Stop();
}

void FadeBlackFast::Do(dword timer) {
//	uniSetTexture(NULL);
//	uniSetTexture(NULL, 1);
	uniSetTexture("null");
	uniSetTexture("null", 1);

	SpriteDrawer *sd = uniSystem->spriteDrawer;

	float x1 = uniSystem->viewportX1;
	float y1 = uniSystem->viewportY1;
	float x2 = uniSystem->viewportX2;
	float y2 = uniSystem->viewportY2;
 
    int c = 0x0;
	int a = 0x0 + (timer / 1.5);
	if (a > 255) 
		a = 255;
	c += a << 24;

	sd->Start(UNI_ALPHA);
	sd->Draw2D(x1, y1, 0, 0, c,
			  x2, y1, 0, 0, c,
			  x1, y2, 0, 0, c,
			  x2, y2, 0, 0, c);
	sd->Stop();
}

 

// ATS CRAP

#define ATS_FILLALPHA

bool TGALoadAndSave = false;
//char *TGAFilename = "texmap000.tga";
char TGAFilename[] = {'t', 'e', 'x', 'm', 'a', 'p', '0', '0', '0', '.', 't', 'g', 'a', '\0'};


class MemFileSys
{
public:
	MemFileSys(byte *pData)
	{
		data = pData;
		pos  = 0;
	}
	~MemFileSys()
	{
	}

	void Read(void *target, int size)
	{
		memcpy(target, data + pos, size);
		pos += size;
	}

	int GetOffset()
	{
		return pos;
	}

	void SetOffset(int iPos)
	{
		pos = iPos;
	}

private:	
	byte *data;
	int pos;
};

#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>

dword *loadTGAFromFile(char *filename, unsigned short &width, unsigned short &height)
{
    int handle;

    if ((handle = open(filename, O_RDONLY | O_BINARY, S_IREAD)) == -1)
    {
		return NULL;
    }

    unsigned short bpp;

    char h[12];

    read(handle, h, 12);

    read(handle, &width, 2);
    read(handle, &height, 2);
    read(handle, &bpp, 2);

	dword *target = new dword[width * height];

	unsigned char *tempmap = new unsigned char[width * height * 3];
	read(handle, tempmap, width * height * 3);

    int index = 0;
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
			unsigned char b = tempmap[index++];
			unsigned char g = tempmap[index++];
			unsigned char r = tempmap[index++];
            target[x + (y * width)] = ((int)r << 16) | ((int)g << 8) | (int)b;
        }
    }

    close(handle);

	delete [] tempmap;

#ifdef ATS_FILLALPHA
	for (int i = 0; i < width * height; i++)
	{
		target[i] |= 0xff << 24;
	}
#endif

	return target;
}

void saveTGAToFile(char *filename, dword *source, unsigned short width, unsigned short height)
{
    int handle;

    if ((handle = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, S_IWRITE)) == -1)
    {
        uniQuit("Error saving TGA");
    }

    unsigned short bpp = 24;

    char h[] = "\0\0\2\0\0\0\0\0\0\0\0\0";

    write(handle, h, 12);

    write(handle, &width, 2);
    write(handle, &height, 2);
    write(handle, &bpp, 2);

    char *tempmap = new char[width * height * 3];
    int index = 0;
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            int col = source[x + (y * width)];
            char r = (col >> 16) & 255;
            char g = (col >> 8) & 255;
            char b = (col) & 255;
            tempmap[index++] = b;
            tempmap[index++] = g;
            tempmap[index++] = r;
        }
    }

    write(handle, tempmap, width * height * 3);

    close(handle);

	delete [] tempmap;
}

dword *loadATSFromMem(byte *atsMem, int &width, int &height)
{
	unsigned short nrFilters;
	unsigned short textureWidth;
	unsigned short textureHeight;

	if (TGALoadAndSave)
	{
		dword *target = loadTGAFromFile(TGAFilename, textureWidth, textureHeight);

		if (target != NULL)
		{
			TGAFilename[8]++;
			if (TGAFilename[8] == ':') 
			{
				TGAFilename[8] = '0';
				TGAFilename[7]++;
			}

			width  = textureWidth;
			height = textureHeight;

			return target;
		}
	}

	MemFileSys fileSys(atsMem);

    char header[5] = {'0','0','0','0','\0'};

	fileSys.Read(header, 4);
    
    if (strcmp(header, TEXGEN_HEADER1) == 0)
    {
		uniQuit("Sorry, cant read this old ATS file");
    }
    else
    if (strcmp(header, TEXGEN_HEADER2) != 0)
    {
		uniQuit("Not a valid Aardbei Texture Studio file");
        return NULL;
    }


    fileSys.Read(&nrFilters, 2);

    fileSys.Read(&textureWidth, 2);
    fileSys.Read(&textureHeight, 2);

    TextureGenerator *generator = new TextureGenerator(textureWidth, textureHeight);

	generator->AddLayer();

    for (int i = 0; i < nrFilters; i++)
    {
        unsigned char command;
        long offset = fileSys.GetOffset();
		fileSys.Read(&command, 1);
		fileSys.SetOffset(offset);
        if (command == TEXGEN_NEWLAYER)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
			generator->AddLayer();
        }
        if (command == TEXGEN_CHANGELAYER)
        {
            FilterChangeLayer *filter = new FilterChangeLayer();
            fileSys.Read(filter, sizeof(FilterChangeLayer));
			generator->layerActive = generator->layers[filter->layerNr];
        }
        if (command == TEXGEN_COPY)
        {
            FilterCopy *filter = new FilterCopy();
            fileSys.Read(filter, sizeof(FilterCopy));
            generator->FilterCopy(generator->layerActive,
                                  generator->layers[filter->sourceNr],
                                  filter->channel);
        }
        if (command == TEXGEN_ADD)
        {
            FilterAdd *filter = new FilterAdd();
            fileSys.Read(filter, sizeof(FilterAdd));
            generator->FilterAdd(generator->layerActive,
                                 generator->layers[filter->sourceNr],
                                 filter->channel);
        }
        if (command == TEXGEN_SUB)
        {
            FilterSub *filter = new FilterSub();
            fileSys.Read(filter, sizeof(FilterSub));
            generator->FilterSub(generator->layerActive,
                                 generator->layers[filter->sourceNr],
                                 filter->channel);
        }
        if (command == TEXGEN_MUL)
        {
            FilterMul *filter = new FilterMul();
            fileSys.Read(filter, sizeof(FilterMul));
            generator->FilterMul(generator->layerActive,
                                 generator->layers[filter->sourceNr],
                                 filter->channel);
        }
        if (command == TEXGEN_NOTNULLCOPY)
        {
            FilterNotNull *filter = new FilterNotNull();
            fileSys.Read(filter, sizeof(FilterNotNull));
            generator->FilterNotNullCopy(generator->layerActive,
                                         generator->layers[filter->sourceNr],
                                         filter->channel);
        }
        if (command == TEXGEN_MIX)
        {
            FilterMix *filter = new FilterMix();
            fileSys.Read(filter, sizeof(FilterMix));
            generator->FilterMix(generator->layerActive,
                                 generator->layers[filter->sourceNr],
                                 filter->alpha,
                                 filter->channel);
        }
        if (command == TEXGEN_SHADE)
        {
            FilterShade *filter = new FilterShade();
            fileSys.Read(filter, sizeof(FilterShade));
            generator->FilterShade(generator->layerActive,
                                   generator->layers[filter->sourceNr],
                                   filter->lightning,
                                   filter->channel);
        }
        if (command == TEXGEN_PLASMA)
        {
            FilterPlasma *filter = new FilterPlasma();
            fileSys.Read(filter, sizeof(FilterPlasma));
            generator->FilterPlasma(filter->aantalX,
                                    filter->aantalY,
                                    filter->shiftX,
                                    filter->shiftY,
                                    filter->channel,
                                    filter->method);
        }
        if (command == TEXGEN_FRACTALPLASMA)
        {
            FilterFractalPlasma *filter = new FilterFractalPlasma();
            fileSys.Read(filter, sizeof(FilterFractalPlasma));
            generator->FilterFractalPlasma(filter->factor,
                                           filter->seed,
                                           filter->channel,
                                           filter->method);
        }
        if (command == TEXGEN_CELLS)
        {
            FilterCells *filter = new FilterCells();
            fileSys.Read(filter, sizeof(FilterCells));
            generator->FilterCells(filter->density,
                                   filter->strength,
                                   filter->seed,
                                   filter->channel,
                                   filter->method);
        }
        if (command == TEXGEN_TEXT)
        {
            FilterText *filter = new FilterText();
            fileSys.Read(filter, sizeof(FilterText));
            generator->FilterText(filter->text,
                                  filter->font,
                                  filter->color,
                                  filter->size,
                                  filter->x,
                                  filter->y,
                                  filter->aa,
                                  filter->style,
                                  filter->clip,
                                  filter->method);
        }
        if (command == TEXGEN_BRUSH)
        {
            FilterBrush *filter = new FilterBrush();
            fileSys.Read(filter, sizeof(FilterBrush));
            generator->FilterBrush(filter->x,
                                    filter->y,
                                    filter->size,
                                    filter->density,
                                    filter->hardness,
                                    filter->opacity,
                                    filter->color);
        }
        if (command == TEXGEN_NOISE)
        {
            FilterNoise *filter = new FilterNoise();
            fileSys.Read(filter, sizeof(FilterNoise));
            generator->FilterNoise(filter->strength,
                                   filter->uniform,
                                   filter->multi,
                                   filter->seed,
                                   filter->channel,
                                   filter->method);
        }
        if (command == TEXGEN_RECTANGLE)
        {
            FilterRectangle *filter = new FilterRectangle();
            fileSys.Read(filter, sizeof(FilterRectangle));
            generator->FilterRectangle(filter->x1,
                                       filter->y1,
                                       filter->x2,
                                       filter->y2,
                                       filter->color,
                                       filter->method);
        }
        if (command == TEXGEN_GAUSSIANBLUR)
        {
            FilterGaussianBlur *filter = new FilterGaussianBlur();
            fileSys.Read(filter, sizeof(FilterGaussianBlur));
            generator->FilterGaussianBlur(filter->radius);
        }
        if (command == TEXGEN_MOTIONBLUR)
        {
            FilterMotionBlur *filter = new FilterMotionBlur();
            fileSys.Read(filter, sizeof(FilterMotionBlur));
            generator->FilterMotionBlur(filter->angle,
                                        filter->radius);
        }
        if (command == TEXGEN_DIRBLUR)
        {
            FilterDirBlur *filter = new FilterDirBlur();
            fileSys.Read(filter, sizeof(FilterDirBlur));
            generator->FilterDirBlur(generator->layers[filter->sourceNr],
                                     filter->aantal,
                                     filter->channel);
        }
        if (command == TEXGEN_BOXBLUR)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
            generator->FilterBoxBlur();
        }
        if (command == TEXGEN_EMBOSS)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
            generator->FilterEmboss();
        }
        if (command == TEXGEN_SOBEL)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
            generator->FilterSobel();
        }
        if (command == TEXGEN_EDGE)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
            generator->FilterEdge();
        }
        if (command == TEXGEN_TOPLEFT)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
            generator->FilterTopLeft();
        }
        if (command == TEXGEN_HSV)
        {
            FilterHsv *filter = new FilterHsv();
            fileSys.Read(filter, sizeof(FilterHsv));
            generator->FilterHsv(filter->rotation,
                                 filter->saternation);
        }
        if (command == TEXGEN_INVERT)
        {
            Filter *filter = new Filter();
            fileSys.Read(filter, sizeof(Filter));
            generator->FilterInvert();
        }
        if (command == TEXGEN_CONTRAST)
        {
            FilterContrast *filter = new FilterContrast();
            fileSys.Read(filter, sizeof(FilterContrast));
            generator->FilterContrast(filter->strength);
        }
        if (command == TEXGEN_BRIGHTNESS)
        {
            FilterBrightness *filter = new FilterBrightness();
            fileSys.Read(filter, sizeof(FilterBrightness));
            generator->FilterBrightness(filter->strength);
        }
        if (command == TEXGEN_SINEDISTORT)
        {
            FilterSineDistort *filter = new FilterSineDistort();
            fileSys.Read(filter, sizeof(FilterSineDistort));
            generator->FilterSineDistort(filter->nrX,
                                         filter->nrY,
                                         filter->ampX,
                                         filter->ampY,
                                         filter->shiftX,
                                         filter->shiftY);
        }
        if (command == TEXGEN_TILE)
        {
            FilterTile *filter = new FilterTile();
            fileSys.Read(filter, sizeof(FilterTile));
            generator->FilterTile(filter->repX,
                                  filter->repY);
        }
    }

	dword *target = new dword[textureWidth * textureHeight];

	memcpy(target, generator->layerActive, textureWidth * textureHeight * 4);

	width  = textureWidth;
	height = textureHeight;

#ifdef ATS_FILLALPHA
	for (i = 0; i < width * height; i++)
	{
		target[i] |= 0xff << 24;
	}
#endif

	if (TGALoadAndSave)
	{
		saveTGAToFile(TGAFilename, target, width, height);

		TGAFilename[8]++;
		if (TGAFilename[8] == ':') 
		{
			TGAFilename[8] = '0';
			TGAFilename[7]++;
		}
	}

	delete generator;

	return target;
}

// loads jpg/gif/bmp/ico/emf/wmf (sick indeed :)
DWORD * uniLoadJPG(unsigned char * data, int size) {
	static HDC hdcnull = GetDC(NULL);
	static LPPICTURE gpPicture;
	
	LPVOID pvData = NULL;

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, size);

	pvData = GlobalLock(hGlobal);
	memcpy(pvData, data, size);

	GlobalUnlock(hGlobal);

	LPSTREAM pstm = NULL;
	HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);

	if (gpPicture) gpPicture->Release();

	hr = ::OleLoadPicture(pstm, size, FALSE, IID_IPicture, (LPVOID *)&gpPicture);
	pstm->Release();

	long hmWidth;
	long hmHeight;
	gpPicture->get_Width(&hmWidth);
	gpPicture->get_Height(&hmHeight);

	HDC hdc = CreateCompatibleDC( hdcnull );

	int nWidth	= MulDiv( hmWidth, GetDeviceCaps(hdc,LOGPIXELSX), 2540 );
	int nHeight	= MulDiv( hmHeight, GetDeviceCaps(hdc,LOGPIXELSY), 2540 );

	HBITMAP bmp = CreateCompatibleBitmap( hdcnull, nWidth, nHeight);
	SelectObject(hdc, bmp);

	int pixel1 = (1 * 2540) / GetDeviceCaps(hdc, LOGPIXELSY);
	RECT rc = {0,0,nWidth,nHeight};
	gpPicture->Render( hdc, 0, -1, nWidth, nHeight+1, 0, 0, hmWidth, hmHeight+pixel1, NULL);

	BITMAPINFOHEADER lpbi;
	ZeroMemory(&lpbi,sizeof(BITMAPINFOHEADER));
	lpbi.biSize = sizeof(BITMAPINFOHEADER);
	lpbi.biWidth = nWidth;
	lpbi.biHeight = nHeight;
	lpbi.biPlanes = 1;
	lpbi.biBitCount = 32;
	lpbi.biCompression = BI_RGB;

	DWORD *ret = new DWORD[ nWidth * nHeight ];
	for( int i=0; i<nHeight; i++ )
		GetDIBits( hdc, bmp, i, 1, &ret[i*nWidth], (LPBITMAPINFO)&lpbi, DIB_RGB_COLORS );

	return ret;
}
