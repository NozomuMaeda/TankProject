#pragma once

class SceneBase {
public :
	SceneBase(){}
	virtual ~SceneBase(){}
	virtual void initialzie() = 0;//�������z�֐�
	virtual void update( float delta_time ) {}//���X�ƕω�����󋵁A���Z
	virtual void render(){}//�`��
};

