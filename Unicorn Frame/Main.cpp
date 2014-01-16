#include "Main.h"

#define PLAY_WITH_MUSIC
#define PLAY_WITH_SCRIPT

extern unsigned char script_usc[];

#ifdef PLAY_WITH_SCRIPT
#ifndef PLAY_WITH_MUSIC
#define PLAY_WITH_MUSIC
#endif
#endif

extern unsigned char XM_SJA[178463];

 
Effect *sphery03;
Effect *cubes;
Effect *cubes02;
Effect *cubes03;
Effect *starfield;
Effect *fastroad;
Effect *heads;
Effect *sprites01;
Effect *sprites02;
Effect *linkin;
Effect *background01;
Effect *background02;
Effect *background03;
Effect *background04;
Effect *background05;

Effect * cameraKick;

Effect *flashWhite;
Effect *flashBlack;
Effect *fadeWhite;
Effect *fadeBlack;
Effect *flashWhiteFast; 
Effect *flashBlackFast;
Effect *fadeWhiteFast;
Effect *fadeBlackFast;
Effect *clearBuffers;
Effect *noise01;

BlurMotion	   *blurMotion;
BlurRadial	   *blurRadial;

#define EFFECT_SPHERY03			10
#define EFFECT_CUBES01 			11
#define EFFECT_CUBES02 			12
#define EFFECT_STARFIELD		13
#define EFFECT_FASTROAD			14
#define EFFECT_HEADS			15
#define EFFECT_SPRITES01		16
#define EFFECT_LINKIN   		17
#define EFFECT_SPRITES02		18
#define EFFECT_CUBES03 			19

#define EFFECT_BACKGROUND01		20
#define EFFECT_BACKGROUND02		21
#define EFFECT_BACKGROUND03		22
#define EFFECT_BACKGROUND04		23
#define EFFECT_BACKGROUND05		24

#define EFFECT_WHITEFL			50	
#define EFFECT_BLACKFL			51
#define EFFECT_WHITEFD			52
#define EFFECT_BLACKFD			53
#define EFFECT_WHITEFLFAST		54
#define EFFECT_BLACKFLFAST		55
#define EFFECT_WHITEFDFAST		56
#define EFFECT_BLACKFDFAST		57

#define EFFECT_NOISECONST		58
#define EFFECT_NOISEFL			59

#define EFFECT_CLEARBUFFERS		60

#define	EFFECT_CAMERAKICK		70

dword calcColor(dword color1, dword color2, float pos)
{
	if (pos < 0)
	{
		return color1;
	}
	
	if (pos > 1)
	{
		return color2;
	}

	int a1 = (color1 >> 24) & 255;
	int r1 = (color1 >> 16) & 255;
	int g1 = (color1 >>  8) & 255;
	int b1 = (color1 >>  0) & 255;

	int a2 = (color2 >> 24) & 255;
	int r2 = (color2 >> 16) & 255;
	int g2 = (color2 >>  8) & 255;
	int b2 = (color2 >>  0) & 255;

	a1 = a1 + ((a2 - a1) * pos);
	r1 = r1 + ((r2 - r1) * pos);
	g1 = g1 + ((g2 - g1) * pos);
	b1 = b1 + ((b2 - b1) * pos);

	return (a1 << 24) | (r1 << 16) | (g1 << 8) | b1;
}


dword clearColor = 0x000000;

void mainInit() {
	uniInitSystem(800, 600, 32, 32, UNI_TNL);

	uniSetViewport(0, 80, 800, 520);

//	TGALoadAndSave = true;

	LoadAllTextures();

	dword *texture;

	texture = (dword*)uniLoadJPG(GIF_ROB, 1346);
	uniTextureCreate("gif_rob", texture, 256, 256, UNI_NONE);

	texture = (dword*)uniLoadJPG(GIF_JGI, 1642);
	uniTextureCreate("gif_jgi", texture, 256, 256, UNI_NONE);

	texture = (dword*)uniLoadJPG(GIF_OYS, 1382);
	uniTextureCreate("gif_oys", texture, 256, 256, UNI_NONE);

	sphery03  = new Sphery03();
	cubes	  = new Cubes();
	cubes02	  = new Cubes02();
	cubes03	  = new Cubes03();
	starfield = new Starfield();
	fastroad  = new FastRoad();
	heads     = new Heads();
	sprites01 = new Sprites01();
	sprites02 = new Sprites02();
	linkin    = new Linkin();
	background01 = new Background01();
	background02 = new Background02();
	background03 = new Background03();
	background04 = new Background04();
	background05 = new Background05();

	flashWhite		= new FlashWhite();
	flashBlack		= new FlashBlack();
	fadeWhite		= new FadeWhite();
	fadeBlack		= new FadeBlack();
	flashWhiteFast	= new FlashWhiteFast();
	flashBlackFast	= new FlashBlackFast();
	fadeWhiteFast	= new FadeWhiteFast();
	fadeBlackFast	= new FadeBlackFast();
	clearBuffers    = new ClearBuffers();
	noise01         = new Noise01();

	cameraKick		= new CameraKick();

	blurMotion     = new BlurMotion();
	blurRadial     = new BlurRadial();
	
	srand(1);

//	blurRadial->Init();
//	blurMotion->Init();
	noise01->Init();

#ifndef PLAY_WITH_SCRIPT

	sphery03->Init();
	cubes->Init();
	cubes02->Init();
	cubes03->Init();
	starfield->Init();
	fastroad->Init();
	heads->Init();
	sprites01->Init();
	sprites02->Init();
	linkin->Init();

	background01->Init();
	background02->Init();
	background03->Init();
	background04->Init();
	background05->Init();

#else

	scriptRegisterEffect(sphery03,		EFFECT_SPHERY03);
	scriptRegisterEffect(cubes,			EFFECT_CUBES01);
	scriptRegisterEffect(cubes02,		EFFECT_CUBES02);
	scriptRegisterEffect(starfield,		EFFECT_STARFIELD);
	scriptRegisterEffect(fastroad,		EFFECT_FASTROAD);
	scriptRegisterEffect(heads,			EFFECT_HEADS);
	scriptRegisterEffect(sprites01,		EFFECT_SPRITES01);
	scriptRegisterEffect(sprites02,		EFFECT_SPRITES02);
	scriptRegisterEffect(linkin,		EFFECT_LINKIN);
	scriptRegisterEffect(cubes03,		EFFECT_CUBES03);

	scriptRegisterEffect(cameraKick,	EFFECT_CAMERAKICK);

	scriptRegisterEffect(background01,	EFFECT_BACKGROUND01);
	scriptRegisterEffect(background02,	EFFECT_BACKGROUND02);
	scriptRegisterEffect(background03,	EFFECT_BACKGROUND03);
	scriptRegisterEffect(background04,	EFFECT_BACKGROUND04);
	scriptRegisterEffect(background05,	EFFECT_BACKGROUND05);

	scriptRegisterEffect(flashWhite,	EFFECT_WHITEFL);
	scriptRegisterEffect(flashBlack,	EFFECT_BLACKFL);
	scriptRegisterEffect(fadeWhite,		EFFECT_WHITEFD);
	scriptRegisterEffect(fadeBlack,		EFFECT_BLACKFD);
	scriptRegisterEffect(flashWhiteFast,EFFECT_WHITEFLFAST);
	scriptRegisterEffect(flashBlackFast,EFFECT_BLACKFLFAST);
	scriptRegisterEffect(fadeWhiteFast,	EFFECT_WHITEFDFAST);
	scriptRegisterEffect(fadeBlackFast,	EFFECT_BLACKFDFAST);
	scriptRegisterEffect(noise01,		EFFECT_NOISEFL);
	scriptRegisterEffect(clearBuffers,  EFFECT_CLEARBUFFERS);

	scriptInitEffects();

//	scriptInitFile("script.usc");
	scriptInitMXM(script_usc);
#endif

#ifdef PLAY_WITH_MUSIC

	fmodLoadMod(XM_SJA, 178463);
#ifndef PLAY_WITH_SCRIPT 
	fmodPlay(0); 
#endif
#endif

	uniTextureUnSwapAll();
	uniTextureUnSwapAll();
	uniTextureUnSwapAll();

	_sleep(1000);


	uniTimerReset(); 
}


void mainRender(dword timer) {
#ifndef PLAY_WITH_SCRIPT
	uniClearBuffers(UNI_BBF | UNI_ZBF, clearColor);

//	background01->Do(timer);
//	background02->Do(timer);
//	background03->Do(timer);
//	background04->Do(timer);
	//background05->Do(timer);

//	fastroad->Do(timer);
//	cubes->Do(timer);

//	uniClearBuffers(UNI_ZBF, clearColor);

//	sprites01->Do(timer);

//	starfield->Do(timer);
//	heads->Do(timer);

//	linkin->Do(timer);

	//cubes02->Do(timer);

//	flashWhiteFast->Do(timer % 1000);

//	sphery03->Do(timer);

	cubes03->Do(timer);

	int pos, row, sync;

	fmodGetInfo(pos, row, sync);

	//cameraKick->Do(row * 80);


#else
	scriptRunMXM();
#endif
}

void mainExit() {
#ifdef PLAY_WITH_MUSIC
	fmodStop();
#endif

#ifndef PLAY_WITH_SCRIPT
	cubes->DeInit();
	cubes02->DeInit();
	cubes03->DeInit();
	sphery03->DeInit();
	starfield->DeInit();
	heads->DeInit();
	sprites01->DeInit();
	sprites02->DeInit();
	linkin->DeInit();

	background01->DeInit();
	background02->DeInit();
	background03->DeInit();
	background04->DeInit();
	background05->DeInit();

//	blurMotion->DeInit();
//	blurRadial->DeInit();

	noise01->DeInit();

	delete sphery03;
	delete cubes;
	delete cubes02;
	delete cubes03;
	delete starfield;
	delete fastroad;
	delete heads;
	delete sprites01;
	delete sprites02;
	delete linkin;
	delete background01;
	delete background02;
	delete background03;
	delete background04;
	delete background05;

	delete blurMotion;
	delete blurRadial;
	delete noise01;	

	delete cameraKick;
#endif
}


