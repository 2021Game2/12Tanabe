#ifndef CMODELX_H
#define CMODELX_H
#include<vector>
#include"CMatrix.h"
#include"CVector.h"
class CModelX;

#define MODEL_FILE "���O�i.x"
//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRY_SIZE(a)(sizeof(a)/sizeof(a[0]))

//�N���X�̐錾
class CMaterial;

class CSkinWeights{
public:
	char*mpFrameName;
	int mFrameIndex;
	int mIndexNum;
	int*mpIndex;
	float*mpWeight;
	CMatrix mOffset;

	CSkinWeights::CSkinWeights(CModelX*model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}

};

class CAnimationKey{
public:
	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};
class CAnimation{
public:
	char *mpFrameName;//���O
	int mFrameIndex;//�ԍ�
	int mKeyNum;//�L�[�̐�(����)
	CAnimationKey*mpKey;//�L�[�̔z��

	CAnimation(CModelX*model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

class CAnimationSet{
public:
	//�A�j���[�V�����Z�b�g��
	char *mpName;
	float mTime; //���ݎ���
	float mWeight; //�d��
	float mMaxTime; //�ő厞��
		//�A�j���[�V����
	std::vector<CAnimation*>mAnimation;

	CAnimationSet(CModelX*model);

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for(int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}
};

class CMesh{
public:
	int mVertexNum; //���_��
	CVector*mpVertex; //���_�f�[�^
	int mFaceNum; //�ʐ�
	int *mpVertexIndex; //�ʂ��\�����钸�_�ԍ�
	int mNormalNum; //�@����
	CVector *mpNormal;
	CVector*mpAnimateVertex; //�A�j���[�V�����p���_
	CVector*mpAnimateNormal; //�A�j���[�V�����p�@��

	int mMaterialNum;//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ��i�ʐ�)
	int *mpMaterialIndex;//�}�e���A���ԍ�
	std::vector<CMaterial*>mMaterial;//�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*>mSkinWeights;
	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(0)
	    ,mFaceNum(0)
	    ,mpVertexIndex(nullptr)
		,mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		,mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
		, mpAnimateVertex(nullptr)
		, mpAnimateNormal(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
	}
	void Init(CModelX*model);
	void AnimateVertex(CModelX*model);
	void Render();
};

class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild;
	CMatrix mTransformMatrix;
	CMatrix mCombinedMatrix;  //�����s��
	char* mpName;
	int mIndex;
	//Mesh�f�[�^
	CMesh mMesh;
	//�R���X�g���N�^
	CModelXFrame(CModelX*model);
	//�f�X�g���N�^
	~CModelXFrame(){
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete *itr;
		}
		SAFE_DELETE_ARRAY(mpName);
	}
	void AnimateCombined(CMatrix*parent);
	void Render();
};


class CModelX{
public:
	char*mpPointer;
	char mToken[1024];
	CModelXFrame*FindFrame(char*name);
	//�}�e���A���̌���
	CMaterial*FindMaterial(char*name);
	std::vector<CModelXFrame*>mFrame;
	std::vector<CAnimationSet*>mAnimationSet;
	std::vector<CMaterial*>mMaterial;	//�}�e���A���z��
	
	CModelX() :mpPointer(0)
	{}
	~CModelX(){
		if (mFrame.size() > 0){
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
			//�}�e���A���̊J��
			for (int i = 0; i < mMaterial.size(); i++){
				delete mMaterial[i];
			}
		}
	}
	void Load(char*file);
	void GetToken();
	void CModelX::AnimateFrame();
	void SetSkinWeightFrameIdex();
	void AnimateVertex(); //���_�ɃA�j���[�V������K�p

	//���������_�f�[�^�̎擾
	float GetFloatToken();
	void SkipNode();
	//�����f�[�^�̎擾
	int CModelX::GetIntToken(){
		GetToken();
		return atoi(mToken);
	}
	void Render();
};




#endif