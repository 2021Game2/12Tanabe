#include "CAttack.h"
#include "CTexture.h"

CTexture TextureAttack;

//デフォルトコンストラクタ
CAttack::CAttack()
	: mFx(0), mFy(0),mCount(30)
{
	mEnabled = false;
	w = 20;	//幅設定
	h = 20;	//高さ設定

	if (TextureAttack.mId == 0) {
		TextureAttack.Load("effect.tga");
	}
}

//更新処理
void CAttack::Update() {

	//有効な時
	mCount--;
	if (mCount < 0) {
		mEnabled = false;
	}

}

//描画処理
void CAttack::Render() {
	//有効な時
	if (mEnabled) {
		//親の描画メソッドを呼ぶ
		CRectangle::Render(TextureAttack, 0, 28, 96, 64);
	}
}

void CAttack::Collision(CRectangle* i, CRectangle* y) {
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EATTACK && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EATTACK && y->mTag == EBREAKABLEWALL) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
	}
}