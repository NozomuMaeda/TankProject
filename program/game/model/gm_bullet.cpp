#include "gm_bullet.h"
#include "gm_tank.h"

MdlBullet::MdlBullet() {
}
MdlBullet::MdlBullet(tnl::Vector3 pos, tnl::Vector3 dir) {
	pos_ = pos;
	dir_ = dir;
}
MdlBullet* MdlBullet::Create(tnl::Vector3 pos, tnl::Vector3 dir) {
	MdlBullet* mdl = new MdlBullet(pos,dir);
	mdl->parts_.resize(1);

	//’eŠÛ
	Parts* body = new Parts();
	body->mesh_ = dxe::Mesh::CreateSphere(3);
	body->mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/blue1.bmp"));
	body->ofs_rot_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));
	mdl->parts_[0] = body;

	mdl->update(0);

	return mdl;
}
void MdlBullet::move() {
	pos_ += dir_*speed;
}