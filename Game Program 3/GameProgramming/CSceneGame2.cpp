#include "CSceneGame2.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CItem.h"
#include "CInvisibleBlock.h"
#include "CKeyItem.h"
#include "CKeyBlock.h"
#include "CKeyEnemy.h"
#include "CBulletEnemy.h"
#include "CDamageBlock.h"


CItem Item();
extern int Score;
extern int mLife;
extern int CountEnemy;
extern int CountItem;
extern int CountKeyItem;
extern int KeyItem;
extern int CountKeyBlock;

void CSceneGame2::Init() {
	//�V�[���̐ݒ�
	mScene = EGAME;

	Texture.Load("Image.tga");
	
	//Texture.Load("Enemy.tga");
	//Texture.Load("BulletEnemy.tga");
	//Texture.Load("KeyEnemy.tga");
	//Texture.Load("CureItem.tga");
	//Texture.Load("Item.tga");
	//Texture.Load("KeyItem.tga");
	//�����摜�̓ǂݍ���
	CText::mFont.Load("font.tga");


	int map[6][62] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 4, 2, 4, 7, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 9, 4, 0, 1, 1, 1, 1, 0, 0, 0, 4, 2, 4, 1, 1, 1, 0, 0, 0, 3, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 1, 3, 1, 3, 1, 3, 1, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 6, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 3, 3, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 0, 0, 3, 9, 4, 0, 1, 1, 0, 3, 0, 7, 4, 0, 0, 0, 1, 5, 3, 3, 3, 0, 0, 6, 6, 6, 0, 1, 0, 0, 1, 0, 0, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 62; i++) {
			//map�̗v�f��1�̎��A�l�p�`�z�u
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
			else if (map[j][i] == 0) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				//�w�i
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
			}
			else if (map[j][i] == 3) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CItem*Item = new CItem();
				Item->x = i * 100 - 350;
				Item->y = j * -100 + 250;
				CountItem++;
			}
			else if (map[j][i] == 5) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CKeyItem*KeyItem = new CKeyItem();
				KeyItem->x = i * 100 - 350;
				KeyItem->y = j * -100 + 250;
				CountKeyItem++;
			}
			else if (map[j][i] == 6) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CKeyBlock*KeyBlock = new CKeyBlock();
				KeyBlock->x = i * 100 - 350;
				KeyBlock->y = j * -100 + 250;
				CountKeyBlock++;
			}
			else if (map[j][i] == 4) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CInvisibleBlock*InvisibleBlock = new CInvisibleBlock();
				InvisibleBlock->x = i * 100 - 350;
				InvisibleBlock->y = j * -100 + 250;
			}

			else if (map[j][i] == 8) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CDamageBlock*DamageBlock = new CDamageBlock();
				DamageBlock->x = i * 100 - 350;
				DamageBlock->y = j * -100 + 250;
			}

			else if (map[j][i] == 9) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CKeyEnemy *BulletEnemy = new CKeyEnemy();
				BulletEnemy->x = i * 100 - 350;
				BulletEnemy->y = j * -100 + 250;
				//�E�ֈړ�
				BulletEnemy->mFx = 1;
				BulletEnemy->mFy = 0;
				CountEnemy++;

			}

			else if (map[j][i] == 2) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//�E�ֈړ�
				Enemy->mFx = 1;
				Enemy->mFy = 0;
				CountEnemy++;

			}
			else if (map[j][i] == 7) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
				Map->mTag = CRectangle::E0;
				CBulletEnemy *BulletEnemy = new CBulletEnemy();
				BulletEnemy->x = i * 100 - 350;
				BulletEnemy->y = j * -100 + 250;
				//�E�ֈړ�
				BulletEnemy->mFx = 1;
				BulletEnemy->mFy = 0;
				CountEnemy++;

			}
		}
	}
	//�N���X�̃����o�ϐ��ւ̑��
	CPlayer *Player = new CPlayer();
	Player->x = 50;
	Player->y = 50;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;


}

void CSceneGame2::Update() {

	/*
	�z��̗v�f���J��Ԃ�
	�z��.size()
	�z��̗v�f�����擾����
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		�z��̎Q��
		�z��[�Y����]
		�ʏ�̔z�񓯗l�ɓY�����ŗv�f�ɃA�N�Z�X�ł���
		*/
		//�X�V����
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//�Փˏ���
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//���X�g����폜����
	//�C�e���[�^�̐���
	std::vector<CRectangle*>::iterator itr;
	//�C�e���[�^��擪
	itr = VectorRect.begin();
	//�Ō�܂ŌJ��Ԃ�
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//����
			itr++;
		}
		else {
			//false�̃C���X�^���X���폜
			delete *itr;
			//���X�g������폜
			itr = VectorRect.erase(itr);
		}
	}

	//�`��͈͕ϐ��̍쐬�i�͈͉�-�R�O�O�A�͈͏�R�O�O�Œ�j
	double mLeft, mRight, mBottom = -300.0, mTop = 300.0;
	//��ʔ͈͍��̐ݒ�
	mLeft = CPlayer::spInstance->x - 300.0;
	//��ʔ͈͉E�̐ݒ�
	mRight = mLeft + 800.0f;
	//��ʓ��e�͈͂̕ύX
	//�s����v���W�F�N�V�������[�h�֕ύX
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//2D��ʂ�ݒ�
	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	for (int i = 0; i < VectorRect.size(); i++){
		VectorRect[i]->Render();
	}
	glLoadIdentity();
	gluOrtho2D(-400, 400, -300, 300);
	//�`�揈��
	CText::DrawString("Score", -370, 270, 20, 20);

	char buf[10];
	sprintf(buf, "%d", Score);
	CText::DrawString(buf, -290, 230, 20, 20);

	if (KeyItem > 0){
		CText::DrawString("KeyItem", 140, 270, 20, 20);

		sprintf(buf, "%d", KeyItem);
		CText::DrawString(buf, 290, 230, 20, 20);
	}
	CText::DrawString("Life", -50, 270, 20, 20);
	if (mLife > 0){
		sprintf(buf, "%d", mLife);
		CText::DrawString(buf, 0, 230, 20, 20);
	}


	if (CPlayer::spInstance->mGameover){
		CountEnemy = 0;
		CountItem = 0;
		CountKeyItem = 0;
		KeyItem = 0;
		mLife = 0;
		CText::DrawString("GameOver", -270, 50, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = EGAME;
			Score = 0;
			mLife = 2;
		}
	}
	if (CPlayer::spInstance->mGameclear){
		CountEnemy = 0;
		CountItem = 0;
		CountKeyItem = 0;
		KeyItem = 0;
		mLife = 2;
		CText::DrawString("GameClear", -300, 40, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);

		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = ETITLE;

		}
	}

}


//���̃V�[���̎擾
CScene::EScene CSceneGame2::GetNextScene() {
	return mScene;
}
//�f�X�g���N�^
CSceneGame2::~CSceneGame2() {
	//�S�ẴC���X�^���X���폜���܂�
	for (int i = 0; i < VectorRect.size(); i++) {
		//�C���X�^���X�̍폜
		delete VectorRect[i];
	}
	//�ϒ��z��̃N���A
	VectorRect.clear();
}