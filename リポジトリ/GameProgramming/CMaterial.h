#ifndef CMATERIAL_H
#define CMATERIAL_H
//�e�N�X�`���N���X�̃C���N���[�h
#include "CTexture.h"
#include"CModelX.h"
//shared_ptr�̃C���N���[�h
#include <memory>
/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial {
public:
	//�}�e���A����
	char mName[64];
	//�g�U���̐FRGBA
	float mDiffuse[4];
	//�e�N�X�`���̃X�}�[�g�|�C���^
	std::shared_ptr<CTexture> mpTexture;
	//�}�e���A�����̒��_��
	int mVertexNum;
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char*mpTextureFilename;

	CMaterial(CModelX*model);
	~CMaterial(){
		if (mpTextureFilename){
			delete[]mpTextureFilename;
		}
		mpTextureFilename = nullptr;
	}

	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	
};

#endif
