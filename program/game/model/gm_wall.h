#pragma once
#include "../gm_main.h"
#include "../../dxlib_ext/dxlib_ext.h"

class MdlWall
{
private:
	dxe::Mesh* wall = nullptr;
public:
	void CreateWall(float x, float z, float size) {
		wall = dxe::Mesh::CreateBox(size);
		wall->setTexture(dxe::Texture::CreateFromFile("graphics/blue1.bmp"));
		wall->pos_ = { x,size/2.0f,z };
	}
};

