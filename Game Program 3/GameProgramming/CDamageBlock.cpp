#include"CDamageBlock.h"
#include"CTexture.h"
#include"CPlayer.h"

extern CTexture Texture;

extern int Score;
extern int CountKeyItem;
extern int KeyItem;
extern int CountKeyBlock;
extern int mLife;

CDamageBlock::CDamageBlock()
:mFx(1.0f)
, mFy(0.0f)
{
	mTag = EDAMAGEBLOCK;
	w = 50;
	h = 50;
}
void CDamageBlock::Render(){
	if (mEnabled){
		CRectangle::Render(Texture, 226 - 1, 239 + 1, 15 + 1, 33 - 1);
	}
}
bool CDamageBlock::Collision(CRectangle &r){
	if (!mEnabled) return false;
	
}
void CDamageBlock::Collision(CRectangle *i, CRectangle *y){
	Collision(*y);
}