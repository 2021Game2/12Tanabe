#include "CAttack.h"
#include "CTexture.h"

CTexture TextureAttack;

//�f�t�H���g�R���X�g���N�^
CAttack::CAttack()
	: mFx(0), mFy(0),mCount(30)
{
	mEnabled = false;
	w = 20;	//���ݒ�
	h = 20;	//�����ݒ�

	if (TextureAttack.mId == 0) {
		TextureAttack.Load("effect.tga");
	}
}

//�X�V����
void CAttack::Update() {

	//�L���Ȏ�
	mCount--;
	if (mCount < 0) {
		mEnabled = false;
	}

}

//�`�揈��
void CAttack::Render() {
	//�L���Ȏ�
	if (mEnabled) {
		//�e�̕`�惁�\�b�h���Ă�
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