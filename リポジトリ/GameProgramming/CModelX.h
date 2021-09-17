#ifndef CMODELX_H
#define CMODELX_H
#include<vector>
#include"CMatrix.h"
#include"CVector.h"
class CModelX;

#define MODEL_FILE "ラグナ.x"
//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRY_SIZE(a)(sizeof(a)/sizeof(a[0]))

//クラスの宣言
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
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};
class CAnimation{
public:
	char *mpFrameName;//名前
	int mFrameIndex;//番号
	int mKeyNum;//キーの数(時間)
	CAnimationKey*mpKey;//キーの配列

	CAnimation(CModelX*model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

class CAnimationSet{
public:
	//アニメーションセット名
	char *mpName;
	float mTime; //現在時間
	float mWeight; //重み
	float mMaxTime; //最大時間
		//アニメーション
	std::vector<CAnimation*>mAnimation;

	CAnimationSet(CModelX*model);

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for(int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}
};

class CMesh{
public:
	int mVertexNum; //頂点数
	CVector*mpVertex; //頂点データ
	int mFaceNum; //面積
	int *mpVertexIndex; //面を構成する頂点番号
	int mNormalNum; //法線数
	CVector *mpNormal;
	CVector*mpAnimateVertex; //アニメーション用頂点
	CVector*mpAnimateNormal; //アニメーション用法線

	int mMaterialNum;//マテリアル数
	int mMaterialIndexNum;//マテリアル番号（面数)
	int *mpMaterialIndex;//マテリアル番号
	std::vector<CMaterial*>mMaterial;//マテリアルデータ
	//スキンウェイト
	std::vector<CSkinWeights*>mSkinWeights;
	//コンストラクタ
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
	//デストラクタ
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
	CMatrix mCombinedMatrix;  //合成行列
	char* mpName;
	int mIndex;
	//Meshデータ
	CMesh mMesh;
	//コンストラクタ
	CModelXFrame(CModelX*model);
	//デストラクタ
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
	//マテリアルの検索
	CMaterial*FindMaterial(char*name);
	std::vector<CModelXFrame*>mFrame;
	std::vector<CAnimationSet*>mAnimationSet;
	std::vector<CMaterial*>mMaterial;	//マテリアル配列
	
	CModelX() :mpPointer(0)
	{}
	~CModelX(){
		if (mFrame.size() > 0){
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
			//マテリアルの開放
			for (int i = 0; i < mMaterial.size(); i++){
				delete mMaterial[i];
			}
		}
	}
	void Load(char*file);
	void GetToken();
	void CModelX::AnimateFrame();
	void SetSkinWeightFrameIdex();
	void AnimateVertex(); //頂点にアニメーションを適用

	//浮動小数点データの取得
	float GetFloatToken();
	void SkipNode();
	//整数データの取得
	int CModelX::GetIntToken(){
		GetToken();
		return atoi(mToken);
	}
	void Render();
};




#endif