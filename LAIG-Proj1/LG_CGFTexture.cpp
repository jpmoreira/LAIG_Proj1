#include "LG_CGFTexture.h"


LG_CGFTexture::LG_CGFTexture(string t)
{
	CGFtexture::CGFtexture(t);
}


LG_CGFTexture::~LG_CGFTexture()
{
	CGFtexture::~CGFtexture();
}


unsigned int LG_CGFTexture::getId(){
	return this->texID;
}