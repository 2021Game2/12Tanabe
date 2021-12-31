#include"CKeyItem.h"
#include"CTexture.h"
#include"CPlayer.h"

CTexture TextureKeyItem;
extern int Score;
extern int CountKeyItem;
extern int CountKeyBlock;
int KeyItem = 0;

CKeyItem::CKeyItem()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EKEYITEM;
	w = 20;
	h = 20;

	if (TextureKeyItem.mId == 0) {
		TextureKeyItem.Load("KeyItem.tga");
	}
}
void CKeyItem::Update() {
	if (!mEnabled) return;
	if (CPlayer::spInstance->mGameover) {
		Score = 0;
	}
	if (CPlayer::spInstance->mGameclear) {
		Score = 0;
	}
}
void CKeyItem::Render() {
	if (mEnabled) {
		CRectangle::Render(TextureKeyItem, 64, 96, 126, 96);
	}
}
bool CKeyItem::Collision(CRectangle& r) {
	if (!mEnabled) return false;
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			mEnabled = false;
			Score += 100;
			CountKeyBlock--;
			KeyItem++;
			break;
		}
		return true;
	}
	return false;
}
void CKeyItem::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}
