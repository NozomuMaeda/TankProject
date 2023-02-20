#include "gm_scene_base.h"

class GmCamera;
class AnimSprite3D;
class MdlAirPlane;
class MdlTank;
class MdlWall;
class MdlBullet;
class Model;
class ScenePlay : public SceneBase {
public:
	ScenePlay() {}
	~ScenePlay();

	
	GmCamera* camera_ = nullptr;//�J����
	//std::list<Model*> objects;
	MdlTank* tank = nullptr;	//���@������
	MdlTank* tankE1 = nullptr;	//�G�@������
	std::list<MdlBullet*> bullets;	//�C�e(��)

	const float WALL_SIZE = 50;//�ǃI�u�W�F�N�g�̃T�C�Y
	const float SX = -475;
	const float SZ = 475;
	std::list<dxe::Mesh*> wall_boxs_;//�ǃI�u�W�F�N�g�̃��b�V��
	dxe::Mesh* ground = nullptr;//��
	dxe::Mesh* target = nullptr;//�Ə��H

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

};