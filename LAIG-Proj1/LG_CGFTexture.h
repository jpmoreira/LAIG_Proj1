#pragma once
#include "CGFtexture.h"
class LG_CGFTexture :
	public CGFtexture
{
public:
	LG_CGFTexture(string t);
	~LG_CGFTexture();
	unsigned int getId();
};

