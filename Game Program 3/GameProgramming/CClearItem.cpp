#include "CClearItem.h"
#include"CTexture.h"
#include"CPlayer.h"

CTexture TextureClearItem;
extern int Score;
int GetClearItem = 0;

CClearItem::CClearItem()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = ECLEARITEM;
	w = 20;
	h = 20;

	if (TextureClearItem.mId == 0) {
		TextureClearItem.Load("ClearItem.tga");
	}
}

void CClearItem::Update()
{
	if (!mEnabled) return;
	if (CPlayer::spInstance->mGameover) {
		Score = 0;
	}
	if (CPlayer::spInstance->mGameclear) {
		Score = 0;
	}
}

void CClearItem::Render()
{
	if (mEnabled) {
		//親の描画メソッドを呼ぶ
		CRectangle::Render(TextureClearItem, 192, 207, 112, 97);
	}
}

bool CClearItem::Collision(CRectangle& r)
{
	if (!mEnabled) return false;
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			mEnabled = false;
			Score += 500;
			GetClearItem += 1;
			break;
		}
		return true;
	}
	return false;
}

void CClearItem::Collision(CRectangle* i, CRectangle* y)
{
	Collision(*y);
}