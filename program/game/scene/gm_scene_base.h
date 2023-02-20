#pragma once

class SceneBase {
public :
	SceneBase(){}
	virtual ~SceneBase(){}
	virtual void initialzie() = 0;//ƒˆ‰¼‘zŠÖ”
	virtual void update( float delta_time ) {}//X‚Æ•Ï‰»‚·‚éó‹µA‰‰Z
	virtual void render(){}//•`‰æ
};

