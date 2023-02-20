#include "gm_tank.h"
#include "gm_bullet.h"

MdlTank::MdlTank() {
	
}
MdlTank* MdlTank::Create(const char* texture) {
	MdlTank* mdl = new MdlTank();
	mdl->parts_.resize(e_parts_max);

	//ŽÔ‘Ì
	Parts* body = new Parts();
	body->mesh_ = dxe::Mesh::CreateBox(24);
	body->mesh_->setTexture(dxe::Texture::CreateFromFile(texture));
	body->ofs_rot_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));
	mdl->parts_[e_body] = body;

	//–C“ƒ
	Parts* turret = new Parts();
	turret->mesh_ = dxe::Mesh::CreateCylinder(8, 12);
	turret->mesh_->setTexture(dxe::Texture::CreateFromFile(texture));
	turret->ofs_pos_ = { 0,18,0 };
	mdl->parts_[e_turret] = turret;

	//–Cg
	Parts* gunbarrel = new Parts();
	gunbarrel->mesh_ = dxe::Mesh::CreateCylinder(4, 30);
	gunbarrel->mesh_->setTexture(dxe::Texture::CreateFromFile(texture));
	gunbarrel->ofs_pos_ = { 0,20,12 };
	gunbarrel->ofs_rot_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(80));
	mdl->parts_[e_gunbarrel] = gunbarrel;

	mdl->update(0);

	return mdl;
}

void MdlTank::bomberdment() {
	/*bullet = dxe::Mesh::CreateSphere(10);
	b->bulMesh->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
	b->bulMesh->pos_ = {0,10,0};
	bullets.push_back(*b);*/
}

void MdlTank::update(float delta_time) {
	/*tnl::Quaternion rot = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(10));
	rot_ *= rot;*/
	dir_z = tnl::Vector3::TransformCoord(dir_z_init, rot_);
	Model::update(delta_time);
}