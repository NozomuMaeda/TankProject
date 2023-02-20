#pragma once
#include "gm_model.h"
#include "gm_bullet.h"

class MdlTank :public Model {
public:
	enum
	{
		e_body,
		e_turret,
		e_gunbarrel,
		e_parts_max
	};
	float gunbarrel_angle = 0;
	MdlTank();
	tnl::Vector3 size = { 24,40,24 };
	tnl::Vector3 dir_z_init = { 0,0,1 };
	tnl::Vector3 dir_z = { 0,0,1 };
	//std::list<MdlBullet> bullets = {};
	//MdlBullet bullet;
	void update(float delta_time) override;
	void bomberdment();
	static MdlTank* Create(const char*);
};