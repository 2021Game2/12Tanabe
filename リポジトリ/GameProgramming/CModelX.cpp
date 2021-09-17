#include"glut.h"
#include<stdio.h>
#include<string.h>
#include"CModelX.h"
#include"CMaterial.h"

void CModelX::Load(char*file){
	//ファイルサイズの獲得
	FILE*fp;
	fp = fopen(file, "rb");
	if (fp == NULL){
		printf("fopen error:%s\n", file);
		return;
	}
	fseek(fp, 0L, SEEK_END);
	int  size = ftell(fp);
	char*buf = mpPointer = new char[size + 1];
	fseek(fp, 0L, SEEK_SET);
	fread(buf, size, 1, fp);
	buf[size] = '\0';
	//printf(buf);
	fclose(fp);
	while (*mpPointer != '\0'){
		GetToken();
		//template 読み飛ばし
		if (strcmp(mToken, "template") == 0){
			SkipNode();
		}
		//Materialの時
		else if (strcmp(mToken, "Material") == 0){
			new CMaterial(this);
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0){
				new CModelXFrame(this);
				//	printf("%s", mToken);
				//	GetToken();
				//	printf("%s\n", mToken);
			}
		else if (strcmp(mToken, "AnimationSet") == 0){
			new CAnimationSet(this);
		}
			//if (strcmp(mToken, "AnimationSet") == 0){
			//	printf("%s", mToken);
			//GetToken();
			//	printf("%s\n", mToken);
			//}

		}
	SAFE_DELETE_ARRAY(buf);
	SetSkinWeightFrameIdex();
}


void CModelX::GetToken(){
	char* p = mpPointer;
	char* q = mToken;
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p))p++;
	if (*p == '{' || *p == '}'){
		*q++ = *p++;
	}
	else{
		while (*p != '\0' && ! strchr(" \t\r\n,;\"}",*p))
			*q++ = *p++;
	}
	*q = '\0'; 
	mpPointer = p;
	if (!strcmp("//", mToken)){
		while (*p != '\0' && !strchr("\r\n", *p))p++;
		mpPointer = p;
		GetToken();
	}
}


void CModelX::SkipNode(){
	while (*mpPointer != '\0'){
		GetToken();
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	while (*mpPointer !='\0' && count>0){
		GetToken();
		if (strchr(mToken, '{'))count++;
		else if (strchr(mToken, '}'))count--;
	}
}


CModelXFrame::CModelXFrame(CModelX*model){
	mIndex = model->mFrame.size();
	model->mFrame.push_back(this);
	mTransformMatrix.Identity();
	model->GetToken();
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken();
	while (*model->mpPointer != '\0'){
		model->GetToken();
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Frame") == 0){
			mChild.push_back(new CModelXFrame(model));
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0){
			model->GetToken();//{
			for (int i = 0; i < ARRY_SIZE(mTransformMatrix.mF); i++){
				mTransformMatrix.mF[i] = model->GetFloatToken();
			}
			model->GetToken();//}
		}
		else if (strcmp(model->mToken, "Mesh") == 0){
			mMesh.Init(model);
		}
		else {
			model->SkipNode();
		}
	}
//#ifdef _DEBUG
	//printf("%s\n", mpName);
	//mTransformMatrix.Print();
//#endif
}


CModelXFrame*CModelX::FindFrame(char*name){
	//イテレータの作成
	std::vector<CModelXFrame*>::iterator itr;
	//先頭から最後まで繰り返し
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++){
		//名前が一致したかどうか
		if (strcmp(name, (*itr)->mpName) == 0){
		//一致したらアドレスを返す
			return *itr;
		}
	}
	//一致しない場合はNULLを返す
	return NULL;
}


float CModelX::GetFloatToken(){
	GetToken();
	return atof(mToken);
}


void CModelX::AnimateFrame(){
	//アニメーションで適用されるフレームの変換行列をゼロクリアする
	for (int i = 0; i < mAnimationSet.size(); i++){
		CAnimationSet*anim = mAnimationSet[i];
		//重みが0なら飛ばす
		if (anim->mWeight == 0)continue;
		//フレーム分(Animation分)繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++){
			CAnimation*animation = anim->mAnimation[j];
			//該当するフレームの変換行列をゼロクリアする
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix));
		}
	}
	//アニメーションに該当するフレームの変換行列をアニメーションのデータで設定する
	for (int i = 0; i < mAnimationSet.size(); i++){
		CAnimationSet*anim = mAnimationSet[i];
		//重みが0なら飛ばす
		if (anim->mWeight == 0)continue;
		//フレーム分(Animation分)繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++){
			//フレームを取得する
			CAnimation*animation = anim->mAnimation[j];
			CModelXFrame*frame = mFrame[animation->mFrameIndex];
			//キーがない場合は飛ばす
			if (animation->mpKey == 0)continue;
			//時間を取得
			float time = anim->mTime;
			//最初の時間より小さい場合
			if (time<animation->mpKey[0].mTime){
				frame->mTransformMatrix += animation->mpKey[0].mMatrix*anim->mWeight;
			}
			//最後の時間より大きい場合
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime){
				//変換行列を最後のコマの行列で更新
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix*anim->mWeight;
			}
			else{
				//時間の途中の場合
				for (int k = 1; k < animation->mKeyNum; k++){
					if (time < animation->mpKey[k].mTime &&
						animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime){
						float r = (animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix +=
							(animation->mpKey[k - 1].mMatrix*r + animation->mpKey[k].mMatrix*(1 - r))*anim->mWeight;
						break;
					}
				}
			}
		}
	}
//#ifdef _DEBUG
	//for (int i = 0; i < mAnimationSet.size(); i++) {
		//CAnimationSet* anim = mAnimationSet[i];
		//重みが0の時は飛ばす
		//if (anim->mWeight == 0) continue;
		//フレーム分（Animation分）繰り返す
		//for (int j = 0; j < anim->mAnimation.size(); j++) {
			//フレームを取得する
			//CAnimation* animation = anim->mAnimation[j];
			//CModelXFrame* frame = mFrame[animation->mFrameIndex];
			//printf("Frame:%s\n", frame->mpName);
			//frame->mTransformMatrix.Print();
		//}
	//}
//#endif

}


void CMesh::Init(CModelX* model) {
	model->GetToken();
	if (!strchr(model->mToken, '{')) {
		model->GetToken();//{
	}
	mVertexNum = model->GetIntToken();
	mpVertex = new CVector[mVertexNum];
	mpAnimateVertex = new CVector[mVertexNum];
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].mX = model->GetFloatToken();
		mpVertex[i].mY = model->GetFloatToken();
		mpVertex[i].mZ = model->GetFloatToken();
	}
	mFaceNum = model->GetIntToken(); //面数読み込み
	mpVertexIndex = new int[mFaceNum * 3]; //頂点数は1つの面に3つ
	for (int i = 0; i < mFaceNum * 3; i += 3) {
		model->GetToken();
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	while (model->mpPointer != '\0') {
		model->GetToken();
		if (strchr(model->mToken, '}'))
			break;
		if (strcmp(model->mToken, "MeshNormals") == 0) {
			model->GetToken();//{
			//法線データの取得
			mNormalNum = model->GetIntToken();
			//法線データを配列へ
			CVector* pNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i++) {
				pNormal[i].mX = model->GetFloatToken();
				pNormal[i].mY = model->GetFloatToken();
				pNormal[i].mZ = model->GetFloatToken();
			}
			//法線数=面数*3
			mNormalNum = model->GetIntToken() * 3;//FaceNum
			int ni;
			//頂点ごとに法線データを設定
			mpNormal = new CVector[mNormalNum];
			mpAnimateNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3) {
				model->GetToken();//3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];
				ni = model->GetIntToken();
				mpNormal[i + 1] = pNormal[ni];
				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[]pNormal;
			model->GetToken();//}
		}
		else if (strcmp(model->mToken, "MeshMaterialList") == 0) {
			model->GetToken();//{
			//マテリアルの数
			mMaterialNum = model->GetIntToken();
			mMaterialIndexNum = model->GetIntToken();
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//マテリアルデータの作成
			for (int i = 0; i < mMaterialNum; i++) {
				model->GetToken();
				if (strcmp(model->mToken, "Material") == 0) {
					mMaterial.push_back(new CMaterial(model));
				}
				else{
					//{既出
					model->GetToken();	//MaterialName
					mMaterial.push_back(
						model->FindMaterial(model->mToken));
					model->GetToken();	//}
				}
			}
			model->GetToken();	//}//End of MeshMaterialList
		}
		//SkinWeightsの時
		else if (strcmp(model->mToken, "SkinWeights") == 0){
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		else {
			//ノードの読み飛ばし
			model->SkipNode();
		}
	}
}


//#ifdef _DEBUG
	//printf("VertexNum:%d\n",  mVertexNum);
	//for (int i = 0; i < mVertexNum; i++){
	//printf("%10f", mpVertex[i].mX);
	//printf("%10f", mpVertex[i].mY);
	//printf("%10f\n", mpVertex[i].mZ);
	//}

	//printf("FaceNum:%d\n", mFaceNum);
	//for (int i = 0; i < mFaceNum * 3; i += 3){
	//printf("%4d", mpVertexIndex[i]);
	//printf("%4d", mpVertexIndex[i + 1]);
	//printf("%4d\n", mpVertexIndex[i + 2]);
    //}

	//printf("NormalNum:%d\n", mNormalNum);
	//for (int i = 0; i < mNormalNum; i++){
		//printf("%10f", mpNormal[i].mX);
		//printf("%10f", mpNormal[i].mY);
		//printf("%10f\n", mpNormal[i].mZ);
//	}
//#endif


CSkinWeights::CSkinWeights(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mIndexNum(0)
, mpIndex(nullptr)
, mpWeight(nullptr)
{
	model->GetToken();	//{
	model->GetToken();	//FrameName
	//フレーム名エリア確保と設定
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//頂点番号取得
	mIndexNum = model->GetIntToken();
	//頂点番号が0を超えた場合
	if (mIndexNum > 0){
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
	//オフセット行列取得
	for (int i = 0; i < 16; i++){
		mOffset.mF[i] = model->GetFloatToken();
	}
	model->GetToken();	//}

//#ifdef _DEBUG
	//printf("SkinWeights:%s\n", mpFrameName);
	//for (int i = 0; i < mIndexNum; i++) {
		//printf("%d", mpIndex[i]);
		//printf("%10f\n", mpWeight[i]);
//	}
	//mOffset.Print();
//#endif
}


CAnimationSet::CAnimationSet(CModelX*model)
:mpName(nullptr)
, mTime(0)
, mWeight(0)
, mMaxTime(0)
{
	model->mAnimationSet.push_back(this);
	model->GetToken();  // Animation Name
	//アニメーションセット名を退避
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken();//{
	while (*model->mpPointer != '\0'){
		model->GetToken();// } or Animation
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Animation") == 0){
			//Animation要素の読み込み
			mAnimation.push_back(new CAnimation(model));
		}
	}
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
//#ifdef _DEBUG
	//printf("AnimationSet:%s\n", mpName);
//#endif

}


CAnimation::CAnimation(CModelX*model)
:mpFrameName(0)
,mFrameIndex(0)
, mKeyNum(0)
, mpKey(nullptr)
{
	model->GetToken(); // { or Animation Name
	if (strchr(model->mToken, '{')){
		model->GetToken(); // {
	}
	else
	{
		model->GetToken(); // {
		model->GetToken() ;// {
	}
	model->GetToken();//FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex =
		model->FindFrame(model->mToken)->mIndex;
	model->GetToken();//}
	//キーの配列を保存しておく配列
	CMatrix*key[4] = { 0, 0, 0, 0 };
	//時間の配列を保存しておく配列
	float*time[4] = { 0, 0, 0, 0 };
	while (*model->mpPointer != '\0'){
		model->GetToken(); // } or AnimationKey
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "AnimationKey") == 0){
			model->GetToken(); // {
			//データタイプ取得
			int type = model->GetIntToken();
			//時間数取得
			mKeyNum = model->GetIntToken();
			switch (type){
			case 0://Rotation Quaternion
				//行列の配列を時間数分確保
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				//時間を繰り返す
				for (int i = 0; i < mKeyNum; i++){
					//時間取得
					time[type][i] = model->GetFloatToken();
					model->GetToken();//4を読み飛ばし
					//w,x,y,zを取得
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1://拡大縮小の行列作成
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken();//3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].mM[0][0] = x;
					key[type][i].mM[1][1] = y;
					key[type][i].mM[2][2] = z;
				}
				break;
			case 2://移動の行列作成
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					
					time[type][i] = model->GetFloatToken();
					model->GetToken();//3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].Translate(x, y, z);
				}
				break;
			case 4://行列データを取得
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					mpKey[i].mTime = model->GetFloatToken();//Time
					model->GetToken();//16
					for (int j = 0; j < 16; j++){
						mpKey[i].mMatrix.mF[j] = model->GetFloatToken();
					}
				}
				break;
			}
			model->GetToken();//}
		}
		else{
			model->SkipNode();
		}
	}
	//行列データではないとき
	if (mpKey == 0){
		//数時間分キーを作成
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++){
			//時間設定
			mpKey[i].mTime = time[2][i];//Time
			//行列作成 Size*Rotation*Position
			mpKey[i].mMatrix = key[1][i] * key[0][i] * key[2][i];
		}
	}
	//確保したエリア開放
	for (int i = 0; i < ARRY_SIZE(key); i++){
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}
	
//#ifdef _DEBUG
	//printf("Animation:%s\n", mpFrameName);
	//mpKey[0].mMatrix.Print();
//#endif
}


void CModelXFrame::AnimateCombined(CMatrix*parent){
	//自分の変換行列に、親からの変換行列を掛ける
	mCombinedMatrix = mTransformMatrix*(*parent);
	//子フレームの合成行列を作成する
	for (int i = 0; i < mChild.size(); i++){
		mChild[i]->AnimateCombined(&mCombinedMatrix);
	}
//#ifdef _DEBUG
	//printf("Frame:%s\n", mpName);
	//mCombinedMatrix.Print();
//#endif

}


void CModelX::SetSkinWeightFrameIdex(){
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++){
		//メッシュに面があった場合
		if (mFrame[i]->mMesh.mFaceNum>0){
			//スキンウェイト分繰り返し
			for (int j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++){
				//フレーム名のフレームを取得する
				CModelXFrame*frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//フレーム番号を設定する
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}


void CModelX::AnimateVertex(){
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++){
		//メッシュに面がある場合
		if (mFrame[i]->mMesh.mFaceNum>0){
			//頂点をアニメーションで更新する
			mFrame[i]->mMesh.AnimateVertex(this);
		}
	}
}



void CMesh::AnimateVertex(CModelX*model){
	//アニメーション用頂点のエリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector)*mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector)*mNormalNum);
	//スキンウェイト分繰り返し
	for (int i = 0; i < mSkinWeights.size(); i++){
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//オフセット行列とフレーム合成行列を合成
		CMatrix mSkinnigMatrix = mSkinWeights[i]->mOffset*model->mFrame[frameIndex]->mCombinedMatrix;
		//頂点分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++){
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinnigMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinnigMatrix * weight;
		}
		//法線を正規化する
		for (int i = 0; i < mNormalNum; i++){
			mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
		}
	}
}


//マテリアル名に該当するマテリアルを返却する
CMaterial*CModelX::FindMaterial(char*name){
	std::vector<CMaterial*>::iterator itr;
	//マテリアル配列を先頭から順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++){
		//名前が一致すればマテリアルのポインタを返却
		if (strcmp(name, (*itr)->mName) == 0){
			return*itr;
		}
	}
	return NULL;
}


void CMesh::Render(){
	//頂点データ、法線データの有効
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//データの場所指定
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	//頂点のインデックスの場所を指定し、図形を描画
	for (int i = 0; i < mFaceNum; i++){
		//マテリアルの適用
		mMaterial[mpMaterialIndex[i]]->Enabled();
		//図形の描画
		glDrawElements(GL_TRIANGLES, 3,
			GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
	}
	//データ配列の無効
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
void CModelXFrame::Render(){
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}


void CModelX::Render(){
	for (int i = 0; i < mFrame.size(); i++){
		mFrame[i]->Render();
	}

}
