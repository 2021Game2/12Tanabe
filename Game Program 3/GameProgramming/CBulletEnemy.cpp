#include "CBulletEnemy.h"
#include "CTexture.h"
#include"CPlayer.h"
#define ANICNT 30


//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
extern int Score;
extern int CountEnemy;
CTexture TextureBulletEnemy;

CBulletEnemy::CBulletEnemy()
	: mFx(1.0f)
	, mFy(0.0f)
	, mFireCount(60)
{
	mTag = EBULLETENEMY;
	w = 25;
	h = 25;
	if (TextureBulletEnemy.mId == 0) {
		TextureBulletEnemy.Load("BulletEnemy.tga");
	}
}


void CBulletEnemy::Update() {
	//mEnabledがfalseなら戻る
	if (CPlayer::spInstance->mGameover) {
		return;
	}
	if (CPlayer::spInstance->mGameclear) {
		return;
	}
	if (!mEnabled) return;
	if (CPlayer::spInstance->mGameover) {
		Score = 0;
	}
	if (CPlayer::spInstance->mGameclear) {
		Score = 0;
	}
	//60フレームに1回発射
	if (mFireCount > 0) {
		mFireCount--;
	}
	else {
		//弾を4発四方へ発射する
		for (int i = 0; i < 2; i++) {
			CBullet* EBullet = new CBullet();
			//座標設定
			EBullet->x = x;
			EBullet->y = y;
			//移動量設定
			EBullet->mFx = (i - 2) % 2 * 2;
			EBullet->mFy = (i - 1) % 2 * 2;
			//有効にする
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		mFireCount = 200;
	}
	mFy = -1;
	x += mFx;
	y += mFy;
}

/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CBulletEnemy::Collision(CRectangle& r) {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			int mx, my;
			if (CRectangle::Collision(&r, &mx, &my)) {
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//Rectをxだけ移動する
					x += mx;
					//衝突していれば反転
					mFx *= -1;
				}
				else {
					//Rectをyだけ移動する
					y += my;
				}
			}
		case EINVISIBLEBLOCK:
			if (CRectangle::Collision(&r, &mx, &my)) {
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//Rectをxだけ移動する
					x += mx;
					//衝突していれば反転
					mFx *= -1;
				}
				else {
					//Rectをyだけ移動する
					y += my;
				}
			}



			//mFy *= -1;
			break;
		case EKEYBLOCK:
			if (CRectangle::Collision(&r, &mx, &my)) {
				//abs(x) xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//Rectをxだけ移動する
					x += mx;
					//衝突していれば反転
					mFx *= -1;
				}
				else {
					//Rectをyだけ移動する
					y += my;
				}
			}



			//mFy *= -1;
			break;

		case EPLAYERBULLET:
			//プレイヤーの弾に当たると、無効にする
			mEnabled = false;
			Score += 300;
			CountEnemy--;
			break;
			//case EPLAYER:
			//	mEnabled = false;
			//	break;
		}
		return true;
	}
	return false;
}

void CBulletEnemy::Render() {
	if (mEnabled) {
		//CRectangle::Render(Texture, 146 - 16, 146 + 16, 178 + 16, 178 - 16);
		mAniCnt++;
		mAniCnt %= ANICNT;
		if (mAniCnt < ANICNT / 2) {
			if (mFx >= 0) {
				CRectangle::Render(TextureBulletEnemy, 32, 64, 96, 64);
			}
			else
			{
				CRectangle::Render(TextureBulletEnemy, 64, 32, 96, 64);
			}
		}
		else
		{
			if (mFx >= 0) {
				CRectangle::Render(TextureBulletEnemy, 64, 96, 96, 64);
			}
			else
			{
				CRectangle::Render(TextureBulletEnemy, 96, 64, 96, 64);
			}
		}
	}
}

void CBulletEnemy::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}