#include "CAttack.h"

CAttack::CAttack()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EATTACK;
	mEnabled = false;
	w = 10;	//���ݒ�
	h = 10;	//�����ݒ�
}

void CAttack::Update()
{
	if (mEnabled) {

	}
}

void CAttack::Render()
{
}
