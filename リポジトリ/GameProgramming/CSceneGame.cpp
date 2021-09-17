#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
#include "CRes.h"
#include "CKey.h"
#include "CModelX.h"
#include "CMaterial.h"
#include "glut.h"
#include <Windows.h>

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	CRes::sModelX.Load(MODEL_FILE);
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
}


void CSceneGame::Update() {
	//�ŏ��̃A�j���[�V�����̌��ݎ�����45�ɂ���
	//CRes::sModelX.mAnimationSet[0]->mTime = 0;
	CRes::sModelX.mAnimationSet[0]->mTime += 1.0f;
	CRes::sModelX.mAnimationSet[0]->mTime =
		(int)CRes::sModelX.mAnimationSet[0]->mTime %
		(int)(CRes::sModelX.mAnimationSet[0]->mMaxTime + 1);
	//�ŏ��̃A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	CRes::sModelX.AnimateFrame();
	//�t���[���̍����s����v�Z����
	CRes::sModelX.mFrame[0]->AnimateCombined(&Matrix);
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f,2.0f,10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����̐ݒ�
	//Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.Set(e, c, u);
	Camera.Render();

	//��]
	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	if (CKey::Push('I')){
		Matrix = Matrix*CMatrix().RotateX(-1);
	}
	if (CKey::Push('J')){
		Matrix = Matrix*CMatrix().RotateY(-1);
	}
	//�s��ݒ�
	glMultMatrixf(Matrix.mF);
	//���_�ɃA�j���[�V������K�p����
	CRes::sModelX.AnimateVertex();
	//���f���`��
	CRes::sModelX.Render();
	//�e�N�X�`���e�X�g
	CRes::sModelX.mMaterial[0]->mTexture.DrawImage(-5, 5, -5, 5, 128, 128, 0);


	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�`��I��
	End2D();

	return;

}

