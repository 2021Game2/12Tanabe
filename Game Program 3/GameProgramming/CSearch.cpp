#include "CSearch.h"
#include "CTexture.h"

CTexture TextureSearch;

CSearch::CSearch()
	: mFx(0), mFy(0), mCount(30)
{
	mEnabled = false;
	w = 10;	//���ݒ�
	h = 10;	//�����ݒ�

	if (TextureSearch.mId == 0) {
		TextureSearch.Load("effect.tga");
	}
}

void CSearch::Update()
{
	//�L���Ȏ�
	mCount--;
	if (mCount < 0) {
		mEnabled = false;
	}

}

void CSearch::Render()
{
	//�L���Ȏ�
	if (mEnabled) {
		//�e�̕`�惁�\�b�h���Ă�
		CRectangle::Render(TextureSearch, 192, 207, 112, 97);
	}
}

void CSearch::Collision(CRectangle* i, CRectangle* y) {
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EATTACK && y->mTag == ESEARCHPOINT) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
	}
}