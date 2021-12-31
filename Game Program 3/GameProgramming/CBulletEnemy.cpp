#include "CBulletEnemy.h"
#include "CTexture.h"
#include"CPlayer.h"
#define ANICNT 30


//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
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
	//mEnabled��false�Ȃ�߂�
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
	//60�t���[����1�񔭎�
	if (mFireCount > 0) {
		mFireCount--;
	}
	else {
		//�e��4���l���֔��˂���
		for (int i = 0; i < 2; i++) {
			CBullet* EBullet = new CBullet();
			//���W�ݒ�
			EBullet->x = x;
			EBullet->y = y;
			//�ړ��ʐݒ�
			EBullet->mFx = (i - 2) % 2 * 2;
			EBullet->mFy = (i - 1) % 2 * 2;
			//�L���ɂ���
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
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CBulletEnemy::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			int mx, my;
			if (CRectangle::Collision(&r, &mx, &my)) {
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��x�����ړ�����
					x += mx;
					//�Փ˂��Ă���Δ��]
					mFx *= -1;
				}
				else {
					//Rect��y�����ړ�����
					y += my;
				}
			}
		case EINVISIBLEBLOCK:
			if (CRectangle::Collision(&r, &mx, &my)) {
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��x�����ړ�����
					x += mx;
					//�Փ˂��Ă���Δ��]
					mFx *= -1;
				}
				else {
					//Rect��y�����ړ�����
					y += my;
				}
			}



			//mFy *= -1;
			break;
		case EKEYBLOCK:
			if (CRectangle::Collision(&r, &mx, &my)) {
				//abs(x) x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��x�����ړ�����
					x += mx;
					//�Փ˂��Ă���Δ��]
					mFx *= -1;
				}
				else {
					//Rect��y�����ړ�����
					y += my;
				}
			}



			//mFy *= -1;
			break;

		case EPLAYERBULLET:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
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