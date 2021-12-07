#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#include "CTexture.h"
#include "CAttack.h"
#include "CSearch.h"
#include "CPlayer.h"
#include"CClearItem.h";

#define G  1
#define VJ0 18
#define ANICNT 30

//extern：他のソースファイルの外部変数にアクセスする宣言
CTexture TexturePlayer;
extern int CountEnemy;
extern int CountItem;
extern int CountKeyBlock;
extern int CountKeyItem;
//extern int GetClearItem;
int mLife = 3;

CPlayer* CPlayer::spInstance = 0;
CPlayer::CPlayer()
	: mFx(1.0f), mFy(0.0f)
	, FireCount(0)
	, mVj(0)
	, mJump(0)
	, mMuteki(0)
	, mGameover(false)
	, mGameclear(false)
	, mClearPoint(false)
	//, SearchCount(0)
{
	mTag = EPLAYER;
	spInstance = this;
	if (TexturePlayer.mId == 0) {
		TexturePlayer.Load("player1.tga");
	 }
}

void CPlayer::Update() {
	if (mGameover) {
		return;
	}
	if (mGameclear) {
		return;
	}
	if (mMuteki > 0) {
		mMuteki--;
	}

	//staticメソッドはどこからでも呼べる
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
		if (x - w < -400) {
			x = -400 + w;
		}
	}

	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
		//if (x + w > 400) {
			//x = 400 - w;
		//}
	}

	if (CKey::Push('S')) {
		y -= 3;
		//mFx = 0;
		//mFy = -1;
		if (y - h < -300) {
			y = -300 + h;
		}
	}

	//if (SearchCount > 0) {
	//	SearchCount--;
	//}
	//else if (SearchCount == 0 && CKey::Once('W')) {
	//	CSearch* Search = new CSearch();
	//	Search->y = y;
	//	Search->mEnabled = true;
	//	Search->mTag = CRectangle::ESEARCH;
	//	SearchCount = 10;
	//}

	if (FireCount > 0) {
		FireCount--;
	}
	//FireContが0で、かつ、スペースキーで弾発射
	else if (FireCount==0 && CKey::Once(' ')) {
		CAttack* Attack = new CAttack();
		//発射位置の設定
		Attack->x = x + (w + 10) * mFx;
		Attack->y = y;
		//有効にする
		Attack->mEnabled = true;
		//プレイヤーの弾を設定
		Attack->mTag = CRectangle::EATTACK;
		FireCount = 10;
	}

	//ジャンプ可能か
	if (mJump == 0 && CKey::Push('J')) {
		mVj = VJ0;
		mJump++;
	}



	//速度に重力加速度計算
	mVj -= G;
	y += mVj;
	if (y - h < -300) {
		mGameover = true;
	}

	else if (mMuteki >= 0) {
		mGameover = false;
	}

	if (CountItem == 0) {
		mGameclear = true;
	}

	//if (GetClearItem >= 1) {
	//	mGameclear = true;
	//}

}

void CPlayer::Render() {
	if (mGameover) {
		return;
	}
	//Texture.Load("player.tga");
	mAniCnt++;
	mAniCnt %= ANICNT;
	//	CRectangle::Render(Texture, 146 - 16, 146 + 16, 146 + 16, 146 - 16);
	if (mMuteki % 20 > 10) {
		return;
	}
	if (mAniCnt < ANICNT / 2) {
		if (mFx >= 0) {
			CRectangle::Render(TexturePlayer, 130, 162, 162, 130);
		}
		else
		{
			CRectangle::Render(TexturePlayer, 162, 130, 162, 130);
		}
	}
	else
	{
		if (mFx >= 0) {
			CRectangle::Render(TexturePlayer, 162, 194, 162, 130);
		}
		else
		{
			CRectangle::Render(TexturePlayer, 194, 162, 162, 130);
		}
	}
}


void CPlayer::Collision(CRectangle* ri, CRectangle* ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my)) {
				//Rectをxだけ移動する
				x += mx;
			}
			else {
				//Rectをyだけ移動する
				y += my;
				//着地
				mVj = 0;
				if (my > 0) {
					//ジャンプ可能
					mJump = 0;
				}
			}
		}
	}
	else if (ry->mTag == EENEMY)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			if (mLife <= 0) {
				mGameover = true;
			}
			else if (mMuteki <= 0) {
				mMuteki = 2 * 60;
				mLife -= 1;
			}

		}

	}
	else if (ry->mTag == EBULLETENEMY)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			if (mLife <= 0) {
				mGameover = true;
			}
			else if (mMuteki <= 0) {
				mMuteki = 2 * 60;
				mLife -= 1;
			}

		}

	}

	else if (ry->mTag == EENEMYBULLET)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			if (mLife <= 0) {
				mGameover = true;
			}
			else if (mMuteki <= 0) {
				mMuteki = 2 * 60;
				mLife -= 1;
			}

		}

	}
	else if (ry->mTag == EKEYENEMYBULLET)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			if (mLife <= 0) {
				mGameover = true;
			}
			else if (mMuteki <= 0) {
				mMuteki = 2 * 60;
				mLife -= 1;
			}

		}

	}
	else if (ry->mTag == EKEYBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my)) {
				//Rectをxだけ移動する
				x += mx;
			}
			else {
				//Rectをyだけ移動する
				y += my;
			}
		}
	}
}

