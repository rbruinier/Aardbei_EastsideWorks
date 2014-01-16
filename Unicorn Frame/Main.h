#ifndef __MAIN_H_
#define __MAIN_H_

// system
#include "..\Unicorn System\Unicorn.h"
#include "..\Unicorn Engine\Engine.h"

// extra system stuff
#include "Ats.h"
#include "Common.h"

// effects
#include "Sphery03.h"
#include "Cubes.h"
#include "Cubes02.h"
#include "Cubes03.h"
#include "Starfield.h"
#include "FastRoad.h"
#include "Heads.h"
#include "Sprites01.h"
#include "Sprites02.h"
#include "Linkin.h"
#include "Background01.h"
#include "Background02.h"
#include "Background03.h"
#include "Background04.h"
#include "Background05.h"
#include "Blurs.h"

// data
#include "Textures.h"

// effecten die overal gebruikt mogen worden
extern BlurMotion	   *blurMotion;
extern BlurRadial	   *blurRadial;
extern BlurHorizontal  *blurHorizontal;

extern Effect *flashWhite;
extern Effect *flashBlack;
extern Effect *fadeWhite;
extern Effect *fadeBlack;
extern Effect *flashWhiteFast; 
extern Effect *flashBlackFast;
extern Effect *fadeWhiteFast;
extern Effect *fadeBlackFast;
extern Effect *clearBuffers;
extern Effect *noise01;

extern dword clearColor;

extern dword calcColor(dword color1, dword color2, float pos);


#endif