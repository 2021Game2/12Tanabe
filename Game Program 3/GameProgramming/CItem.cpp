#include"CItem.h"
#include"CTexture.h"
#include"CPlayer.h"

CTexture TextureItem;
extern int Score;
extern int CountItem;

CItem::CItem()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EITEM;
	w = 25;
	h = 25;

	if (TextureItem.mId == 0) {
		TextureItem.Load("Item.tga");
	}
}
void CItem::Update() {
	if (!mEnabled) return;
	if (CPlayer::spInstance->mGameover) {
		Score = 0;
	}
	if (CPlayer::spInstance->mGameclear) {
		Score = 0;
	}
}
void CItem::Render() {
	if (mEnabled) {
		CRectangle::Render(TextureItem, 64, 96, 126 , 96 );
	}
}
bool CItem::Collision(CRectangle& r) {
	if (!mEnabled) return false;
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			mEnabled = false;
			Score += 100;
			CountItem--;
			break;
		}
		return true;
	}
	return false;
}
void CItem::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}
