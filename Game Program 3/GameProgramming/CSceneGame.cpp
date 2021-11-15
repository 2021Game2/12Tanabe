#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CItem.h"
#include"CInvisibleBlock.h"
#include"CKeyItem.h"
#include"CKeyBlock.h"
#include"CBulletEnemy.h"

CItem Item();
int Score = 0;
extern int KeyItem;//鍵
extern int mLife;//	現在のライフ
int CountEnemy = 0;//敵の数をカウント
int CountItem = 0;//アイテムの数をカウント
int CountKeyItem = 0;//所持している鍵の数をカウント
int CountKeyBlock = 0;//開いていない鍵付きの通路をカウント

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;

	Texture.Load("Image.tga");
	//Texture.Load("player.tga");
	//Texture.Load("Enemy.tga");
	//Texture.Load("CureItem.tga");
	//Texture.Load("Item.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");


	int map[6][62] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 1, 5, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 4, 0, 3, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 3, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 4, 3, 3, 1, 1, 3, 3, 3, 0, 4, 0, 0, 0, 2, 1, 1, 1, 0, 3, 0, 3, 0, 3, 0, 0, 4, 5, 0, 0, 2, 6, 0, 1, 0, 1, 4, 0, 2, 1, 0, 0, 0, 3, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
	};


	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 62; i++) {
			//mapの要素が1の時、四角形配置
			if (map[j][i] == 1) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
			else if (map[j][i] == 0) {
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
			}
			else if (map[j][i] == 3) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
				CItem* Item = new CItem();
				Item->x = i * 100 - 350;
				Item->y = j * -100 + 250;
				CountItem++;

			}
			else if (map[j][i] == 5) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
				CKeyItem* KeyItem = new CKeyItem();
				KeyItem->x = i * 100 - 350;
				KeyItem->y = j * -100 + 250;
				CountKeyItem++;
			}
			else if (map[j][i] == 6) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
				CKeyBlock* KeyBlock = new CKeyBlock();
				KeyBlock->x = i * 100 - 350;
				KeyBlock->y = j * -100 + 250;
				CountKeyBlock++;
			}
			else if (map[j][i] == 4) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
				CInvisibleBlock* InvisibleBlock = new CInvisibleBlock();
				InvisibleBlock->x = i * 100 - 350;
				InvisibleBlock->y = j * -100 + 250;
			}

			else if (map[j][i] == 2) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
				CEnemy* Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//右へ移動
				Enemy->mFx = 1;
				Enemy->mFy = 0;
				CountEnemy++;

			}
			else if (map[j][i] == 7) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CMap0* Map0 = new CMap0();
				//四角形に値を設定
				//背景
				Map0->mEnabled = true;
				Map0->x = i * 100 - 350;
				Map0->y = j * -100 + 250;
				Map0->w = 50;
				Map0->h = 50;
				Map0->mTag = CRectangle::E0;
				CBulletEnemy* BulletEnemy = new CBulletEnemy();
				BulletEnemy->x = i * 100 - 350;
				BulletEnemy->y = j * -100 + 250;
				//右へ移動
				BulletEnemy->mFx = 1;
				BulletEnemy->mFy = 0;
				CountEnemy++;

			}
		}
	}
	//クラスのメンバ変数への代入
	CPlayer* Player = new CPlayer();
	Player->x = 50;
	Player->y = 50;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;


}

void CSceneGame::Update() {

	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//衝突処理
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;
	//イテレータを先頭
	itr = VectorRect.begin();
	//最後まで繰り返し
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//次へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete* itr;
			//リストからも削除
			itr = VectorRect.erase(itr);
		}
	}

	//描画範囲変数の作成（範囲下-３００、範囲上３００固定）
	double mLeft, mRight, mBottom = -300.0, mTop = 300.0;
	//画面範囲左の設定
	mLeft = CPlayer::spInstance->x - 300.0;
	//画面範囲右の設定
	mRight = mLeft + 800.0f;
	//画面投影範囲の変更
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//2D画面を設定
	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	for (int i = 0; i < VectorRect.size(); i++) {
		VectorRect[i]->Render();
	}
	glLoadIdentity();
	gluOrtho2D(-400, 400, -300, 300);
	//描画処理
	CText::DrawString("Score", -370, 270, 20, 20);

	char buf[10];
	sprintf(buf, "%d", Score);
	CText::DrawString(buf, -290, 230, 20, 20);
	if (KeyItem > 0) {
		CText::DrawString("KeyItem", 140, 270, 20, 20);

		sprintf(buf, "%d", KeyItem);
		CText::DrawString(buf, 290, 230, 20, 20);
	}
	CText::DrawString("Life", -50, 270, 20, 20);
	if (mLife > 0) {
		sprintf(buf, "%d", mLife);
		CText::DrawString(buf, 0, 230, 20, 20);
	}

	if (CPlayer::spInstance->mGameover) {
		CountEnemy = 0;
		CountItem = 0;
		CountKeyItem = 0;
		KeyItem = 0;

		CText::DrawString("GameOver", -270, 50, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = ETITLE;
			Score = 0;
			mLife = 3;
		}
	}
	if (CPlayer::spInstance->mGameclear) {
		CountEnemy = 0;
		CountItem = 0;
		CountKeyItem = 0;
		KeyItem = 0;
		CText::DrawString("GameClear", -300, 40, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);

		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = ETITLE;
			Score = 0;
			mLife = 3;
		}
	}

}


//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
