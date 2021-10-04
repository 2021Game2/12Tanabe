#include"CKeyItem.h"
#include"CTexture.h"
#include"CPlayer.h"

extern CTexture Texture;
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
		CRectangle::Render(Texture, 243 - 2, 253 + 2, 15 + 2, 3 - 2);
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
