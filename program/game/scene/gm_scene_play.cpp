#include "../gm_manager.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "../model/gm_airplane.h"
#include "../model/gm_tank.h"
#include "../model/gm_wall.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"

tnl::Quaternion	fix_rot;

ScenePlay::~ScenePlay() {
	delete camera_;
	for (auto box : wall_boxs_) delete box;
}

void ScenePlay::initialzie() {
	camera_ = new GmCamera();
	camera_->target_distance_ = 500;

	//�n��
	ground = dxe::Mesh::CreatePlane({ 1000,1000,0 });
	ground->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	ground->rot_q_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	//��ԁH
	tank = MdlTank::Create("graphics/blue1.bmp");
	tank->pos_ = { 0,12,0 };
	tankE1 = MdlTank::Create("graphics/red1.bmp");
	tankE1->pos_ = { 100,12,100 };

	//------------------------------------
	// ���Ɣz�z�T���v���̓]�p
		// �g�p����e�N�X�`�������O���[�h
	Shared<dxe::Texture> texs[3];
	texs[0] = dxe::Texture::CreateFromFile("graphics/blue2.bmp");
	texs[1] = dxe::Texture::CreateFromFile("graphics/blue1.bmp");
	texs[2] = dxe::Texture::CreateFromFile("graphics/red2.box.bmp");

	// �{�b�N�X�R��ނ����炩���ߍ쐬
	dxe::Mesh* origin_boxs[3];
	for (int i = 0; i < 3; ++i) {
		origin_boxs[i] = dxe::Mesh::CreateBoxMV(WALL_SIZE);
		origin_boxs[i]->setTexture(texs[i]);
	}

	// csv ����t�B�[���h����ǂݍ���ł��炩���ߍ쐬���Ă���
	// �{�b�N�X���N���[�����Đ������邱�ƂŐ������x�A�b�v
	std::vector<std::vector<std::string>> csv = tnl::LoadCsv("map.csv");
	for (int i = 0; i < csv.size(); ++i) {
		for (int k = 0; k < csv[i].size(); ++k) {
			int n = std::atoi(csv[i][k].c_str());
			// 0 �͒n�ʈ����Ƃ��Ĕ�΂�
			if (0 == n) continue;
			dxe::Mesh* mesh = origin_boxs[n - 1]->createClone();
			mesh->pos_ = { SX + k * WALL_SIZE, 25, SZ - i * WALL_SIZE };
			wall_boxs_.emplace_back(mesh);
		}
	}

	//�J�[�\��
	target = dxe::Mesh::CreateDome(1);
	target->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
}

//�X�V
void ScenePlay::update(float delta_time)
{
	//�Q�[���}�l�[�W���[�̃C���X�^���X�𐶐�/�擾
	GameManager* mgr = GameManager::GetInstance();

	//------------------------------------------------------------------
	//
	// �ړ�����
	//
	int t = tnl::GetXzRegionPointAndOBB(
		camera_->pos_
		, tank->pos_
		, { 32, 48, 32 }
	, tank->rot_);

	tnl::Vector3 move_v = { 0,0,0 };
	tnl::Vector3 prev_pos = tank->pos_;

	tnl::Vector3 dir[4] = {
		camera_->front().xz(),
		camera_->right().xz(),
		camera_->back().xz(),
		camera_->left().xz(),
	};
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		move_v += dir[idx];
		}, eKeys::KB_W, eKeys::KB_D, eKeys::KB_S, eKeys::KB_A);
	if (tnl::Input::IsKeyDown(eKeys::KB_W, eKeys::KB_D, eKeys::KB_S, eKeys::KB_A)) {
		move_v.normalize();
		tank->rot_.slerp(tnl::Quaternion::LookAtAxisY(tank->pos_, tank->pos_ + move_v), 0.3f);
		tank->pos_ += move_v * 2.0f;
	}

	//------------------------------------------------------------------
	//
	// �J��������
	//
	//��]
	/*tnl::Vector3 rot[4] = {
		{ 0, tnl::ToRadian(1.0f), 0 },
		{ 0, -tnl::ToRadian(1.0f), 0 },
		{ tnl::ToRadian(1.0f), 0, 0 },
		{ -tnl::ToRadian(1.0f), 0, 0 } };
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		camera_->free_look_angle_xy_ += rot[idx];
		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);*/
		//�Y�[���C���E�A�E�g
	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		camera_->target_distance_ += 1.0f;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		camera_->target_distance_ -= 1.0f;
	}

	//�C��(��)
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && bullets.size() < 3) {
		auto bullet = MdlBullet::Create(tank->pos_, tank->dir_z);
		bullets.emplace_back(bullet);
	}
	camera_->target_ = tank->pos_;//{ 0,0,0 };

	for (auto bullet : bullets)
	{
		bullet->move();
		bullet->update(delta_time);
	}

	tank->update(delta_time);
	tankE1->update(delta_time);
	// ---------------------------------
	// ���Ɣz�z�T���v���̓]�p
		// �Փ˔���ƕ␳
		//
	tnl::Vector3 boxSize = { WALL_SIZE, WALL_SIZE, WALL_SIZE };
	//��ԑΕ�
	// ����@�̂ɋ߂����Ƀ\�[�g
	wall_boxs_.sort([&](const dxe::Mesh* l, const dxe::Mesh* r) {
		float ld = (tank->pos_ - l->pos_).length();
	float rd = (tank->pos_ - r->pos_).length();
	return ld < rd;
		});
	for (auto box : wall_boxs_) {
		if (tnl::IsIntersectAABB(tank->pos_, tank->size, box->pos_, boxSize)) {
			int n = tnl::GetCorrectPositionIntersectAABB(prev_pos, tank->size, box->pos_, boxSize, tank->pos_);
			// �{�b�N�X�̏�ɕ␳���ꂽ��W�����v�̓��Z�b�g
			// ��U�W�����v�͂Ȃ�
			//if (2 == n) jump_vel_ = 0;
		}
	}
	//��ԑΐ��
	if (tnl::IsIntersectAABB(tank->pos_, tank->size, tankE1->pos_, tankE1->size)) {
		int n = tnl::GetCorrectPositionIntersectAABB(prev_pos, tank->size, tankE1->pos_, tankE1->size, tank->pos_);
	}
	// �C�e�ɋ߂����Ƀ\�[�g
	for (auto bullet : bullets) {
		wall_boxs_.sort([&](const dxe::Mesh* l, const dxe::Mesh* r) {
			float ld = (bullet->pos_ - l->pos_).length();
		float rd = (bullet->pos_ - r->pos_).length();
		return ld < rd;
			});
		for (auto box : wall_boxs_) {
			if (tnl::IsIntersectAABB(bullet->pos_, bullet->size, box->pos_, boxSize)) {
				//int n = tnl::GetCorrectPositionIntersectAABB(prev_pos, bullet->size, box->pos_, boxSize, bullet->pos_);
				bullet->isAlive = false;
			}
		}
		//�C�e�ΐ��
		if (tnl::IsIntersectAABB(bullet->pos_, bullet->size, tankE1->pos_, tankE1->size)) {
			bullet->isAlive = false;
		}
		for (auto obj : bullets) {
			obj->update(delta_time);
		}
	}

	//�V�[�������U���g�ɐ؂�ւ���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}
}

//�`��֘A
void ScenePlay::render()
{
	camera_->update();

	//�I�u�W�F�N�g�����̕`��
	/*if (bullets.size() != 0) {
		for (auto bullet : bullets)
		{
			bullet->render(camera_);
		}
	}*/
	auto it = bullets.begin();
	while (it != bullets.end()) {
		if (!(*it)->isAlive) {
			delete (*it);
			it = bullets.erase(it);
			continue;
		}
		(*it)->render(camera_);
		it++;
	}

	ground->render(camera_);
	for (auto box : wall_boxs_) box->render(camera_);
	tankE1->render(camera_);
	tank->render(camera_);
	target->render(camera_);

	DrawLine3D({ tank->pos_.x,tank->pos_.y,tank->pos_.z },
		{ tankE1->pos_.x,tankE1->pos_.y,tankE1->pos_.z }, 0xffff0000);

	//DrawOBB(camera_, tank->pos_, tank->rot_, { 32, 48, 32 });//�L�������͂ޒ����̘g
	//�}�E�X�|�C���^�[���烌�C���΂��n�\�Ƃ̌�_��T��
	/*tnl::Vector3 msv = tnl::Input::GetMousePosition();
	tnl::Vector3 ray = tnl::Vector3::CreateScreenRay(
		msv.x
		, msv.y
		, camera_->screen_w_
		, camera_->screen_h_
		, camera_->view_
		, camera_->proj_);
	tnl::Vector3 hit;

	if (tnl::IsIntersectLinePlane(camera_->pos_, camera_->pos_ + (ray * 10000.0f), { 10, 0, 10 }, { 0, 1, 0 }, &hit)) {
		target->pos_ = hit;
	}*/

	//�i�q�̂��
	DrawGridGround(camera_, 50, 20);

	DrawStringEx(50, 50, -1, "scene play");
	DrawStringEx(50, 70, -1, "�ړ� [ �� : A ] [ �� : W ] [ �� : D ] [ �� : S ]");
	/*DrawStringEx(50, 90, -1, "camera [ �� : Z ] [ �� : X ] ");
	DrawStringEx(50, 120, -1, "character [ �� : �� ] [ �� : �� ] [ �E : �� ] [ ��O : �� ] ");*/
}
