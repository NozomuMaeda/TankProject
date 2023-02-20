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

	
	GmCamera* camera_ = nullptr;//カメラ
	//std::list<Model*> objects;
	MdlTank* tank = nullptr;	//自機たる戦車
	MdlTank* tankE1 = nullptr;	//敵機たる戦車
	std::list<MdlBullet*> bullets;	//砲弾(仮)

	const float WALL_SIZE = 50;//壁オブジェクトのサイズ
	const float SX = -475;
	const float SZ = 475;
	std::list<dxe::Mesh*> wall_boxs_;//壁オブジェクトのメッシュ
	dxe::Mesh* ground = nullptr;//床
	dxe::Mesh* target = nullptr;//照準？

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

};