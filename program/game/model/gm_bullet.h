#pragma once
#include "../gm_main.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_model.h"

class MdlBullet :public Model
{
public:
	MdlBullet();
	MdlBullet(tnl::Vector3,tnl::Vector3);

	dxe::Mesh* bulMesh = nullptr;
	float speed = 5;
	tnl::Vector3 dir_;

	tnl::Vector3 size = { 3,3,3 };
	void move();
	static MdlBullet* Create(tnl::Vector3,tnl::Vector3);
};