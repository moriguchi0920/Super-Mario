
#include "const.h"
#include "keyManager.h"
#include"componentManager.h"
#include"objectManager.h"
#include"collisionManager.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"renderableManager.h"
#include"sampleObject.h"
#include"scrollManager.h"
#include"eventServer.h"
#include"mario.h"
#include"floor.h"
#include "rengablock.h"
#include "dokan.h"
#include"hatenablock.h"
#include"hardBlock.h"
#include"goomba.h"
#include"koopaTroopa.h"
#include"background.h"
#include"goal.h"
#include "DxLib.h"
#include "soundManager.h"
#include"superMushroom.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	SetWindowSizeExtendRate(EXTEND_RATE);

	SoundManager* pSound = SoundManager::getInstance();
	pSound->setSoundInfo(SoundManager::PB_PLAY_BGM, "Sound/stage.wav");//BGM
	pSound->setSoundInfo(SoundManager::SE_JUMP, "Sound/jump.wav");//ジャンプ
	pSound->setSoundInfo(SoundManager::SE_BREAK, "Sound/break.wav");//ブロック破壊
	pSound->setSoundInfo(SoundManager::SE_PUSH, "Sound/push.wav");//ブロック押す
	pSound->setSoundInfo(SoundManager::SE_DEATH, "Sound/death.wav");//死亡
	pSound->setSoundInfo(SoundManager::SE_COIN, "Sound/coin.wav");//コイン
	pSound->setSoundInfo(SoundManager::SE_STEPON, "Sound/stepon.wav");//踏む
	pSound->setSoundInfo(SoundManager::SE_NOKO01, "Sound/nokonoko01.wav");//ノコノコ蹴る音
	pSound->setSoundInfo(SoundManager::SE_NOKO02, "Sound/nokonoko02.wav");//ノコノコが跳ね返る音
	pSound->setSoundInfo(SoundManager::SE_GOALPOLE, "Sound/flagpole.wav");//ポール



	// 登録したものを今すぐロードする！
	pSound->loadSoundAll();

	//踏む音の音量調節
	int steponHandle = pSound->getSoundHandle(SoundManager::SE_STEPON);
	if (steponHandle != -1)
	{
		ChangeVolumeSoundMem(255, steponHandle);
	}

	//ジャンプ音の音量調節
	int jumpHandle = pSound->getSoundHandle(SoundManager::SE_JUMP);
	if (jumpHandle != -1)
	{
		// 120だと元の音量の半分くらいになります。小さすぎたら数値を上げて調整してください
		ChangeVolumeSoundMem(100, jumpHandle);
	}

	// BGMの再生
	int bgmHandle = pSound->getSoundHandle(SoundManager::PB_PLAY_BGM);
	if (bgmHandle != -1)
	{
		//PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, FALSE);
	}

	//---------------------------------------
	// 変数の作成や初期化、その他初期設定
	// ↓ システム初期化 ↓
	KeyManager::getInstance().initKeyManager();
	// ↑ システム初期化 ↑
	//---------------------------------------
	
	ObjectManager::getInstance();



	Background::setNextInfo(Background::Type::CLOUD_1, Float2(160.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_1, Float2(130.0f, 195.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_3, Float2(72.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_1, Float2(235.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_3, Float2(320.0f, 70.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_2, Float2(490.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_2, Float2(580.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_2, Float2(700.0f,185.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(830.0f, 70.0f));
	ObjectManager::createObject<Background>();

	Background::setNextInfo(Background::Type::PLANT_3, Float2(900.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_1, Float2(960.0f, 195.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(1020.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_3, Float2(1140.0f, 70.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_1, Float2(1050.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_2, Float2(1300.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_2, Float2(1370.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_2, Float2(1490.0f, 185.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(1580.0f, 70.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_3, Float2(1655.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_1, Float2(1722.0f, 195.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(1770.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_1, Float2(1820.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_3, Float2(1910.0f, 70.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_2, Float2(2000.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_2, Float2(2111.5f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_2, Float2(2225.0f, 185.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(2390.0f, 70.0f));
	ObjectManager::createObject<Background>();

	Background::setNextInfo(Background::Type::PLANT_3, Float2(2465.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_1, Float2(2532.0f, 195.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(2580.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_1, Float2(2630.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_3, Float2(2720.0f, 70.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_2, Float2(2860.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_2, Float2(3105.0f, 185.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CLOUD_1, Float2(3200.0f, 45.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::PLANT_3, Float2(3272.0f, 200.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::MOUNTAIN_1, Float2(3335.0f, 195.0f));
	ObjectManager::createObject<Background>();
	Background::setNextInfo(Background::Type::CASTLE, Float2(3250.0f, 170.0f));
	ObjectManager::createObject<Background>();

	ObjectManager::createObject<Mario>();
	ObjectManager::createObject<Floor>(0.0f, 1000.0f);
	ObjectManager::createObject<Floor>(1050.0f, 200.0f);
	ObjectManager::createObject<Floor>(1300.0f, 1000.0f);
	ObjectManager::createObject<Floor>(2350.0f, 600.0f);

	ObjectManager::createObject<Dokan>(300.0f, 30.0f);
	ObjectManager::createObject<Goomba>(Rect(Float2(100.0f, 144.0f), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<KoopaTroopa>(Rect(Float2(400.0f, 144.0f), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<Dokan>(500.0f, 30.0f);
	ObjectManager::createObject<Dokan>(630.0f, 30.0f);
	ObjectManager::createObject<Dokan>(830.0f, 30.0f);
	ObjectManager::createObject<Dokan>(2500.0f, 30.0f);
	ObjectManager::createObject<Dokan>(2890.0f, 30.0f);

	
	ObjectManager::createObject<Goal>(Rect(Float2(3155.0f, 120.0f), Float2(160.0f, 16.0f)));

	SetBackgroundColor(107, 140, 255);

	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 7, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<SuperMushroom>(Rect(Float2(SPRITE_SIZE * 11, SPRITE_SIZE * 8), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 11, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 12, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 13, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 71, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 89, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 100, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 103, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 103, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 106, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 123, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 124, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<hatenablock>(Rect(Float2(SPRITE_SIZE * 167, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));


	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 10, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 12, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 14, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 70, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 72, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 74, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 75, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 76, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 77, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 78, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 79, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 80, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 81, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 82, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 86, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 87, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 88, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 89, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 95, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 96, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 112, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 115, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 116, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 117, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 122, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 123, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 124, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 125, SPRITE_SIZE * 6), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 165, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 166, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));
	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 168, SPRITE_SIZE * 9), Float2(SPRITE_SIZE, SPRITE_SIZE)));


	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			ObjectManager::createObject<HardBlock>(
				Rect(
					Float2(
						SPRITE_SIZE * (130 -  x) , SPRITE_SIZE * (9 + y)
					),
					Float2(SPRITE_SIZE, SPRITE_SIZE)
				)
			);
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			ObjectManager::createObject<HardBlock>(
				Rect(
					Float2(
						SPRITE_SIZE * (133 + x), SPRITE_SIZE * (9 + y)
					),
					Float2(SPRITE_SIZE, SPRITE_SIZE)
				)
			);
		}
	}

	for (int y = 1; y < 5; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			ObjectManager::createObject<HardBlock>(
				Rect(
					Float2(
						SPRITE_SIZE * (145 - x), SPRITE_SIZE * (8 + y)
					),
					Float2(SPRITE_SIZE, SPRITE_SIZE)
				)
			);
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			ObjectManager::createObject<HardBlock>(
				Rect(
					Float2(
						SPRITE_SIZE * (148 + x), SPRITE_SIZE * (9 + y)
					),
					Float2(SPRITE_SIZE, SPRITE_SIZE)
				)
			);
		}
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			ObjectManager::createObject<HardBlock>(
				Rect(
					Float2(
						SPRITE_SIZE * ( 190 - x), SPRITE_SIZE * (5 + y)
					),
					Float2(SPRITE_SIZE, SPRITE_SIZE)
				)
			);
		}
	}

	//ObjectManager::createObject<rengablock>(80.0f, 130.0f);
	//ObjectManager::createObject<hatenablock>(50.0f, 130.0f);




	//// 2. マネージャーからBGMのハンドルを取得する
	//int bgmHandle = SoundManager::getInstance()->getSoundHandle(SoundManager::PB_PLAY_BGM);

	//// 3. BGMが正常に読み込めていたら、ループ再生を開始する
	//if (bgmHandle != -1)
	//{
	//	// 第2引数に DX_PLAYTYPE_LOOP を渡すことで、曲が終わっても自動で最初から流れます
	//	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, FALSE);
	//}



	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		KeyManager::getInstance().updateKeyState();
		// ↑ システム更新 ↑
		//---------------------------------------

		ObjectManager::updateAll();
		EventServer::getInstance()->dequeueEventsAll();
		CollisionManager::getInstance()->collisionUpdate();
		ScrollManager::getInstance()->scrollAll();
		//SoundManager::getInstance()->loadSoundAll();	// 1. まず全音源を読み込む（さっきのCPPで登録したファイルが読み込まれます）




		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		RenderableManager::getInstance()->renderAll();

		//if (KeyManager::pullUpKey(KEY_INPUT_SPACE))
		//{
		//	DrawString(0, 0, "スペースキーが離された瞬間", GetColor(255, 255, 255));
		//}
		

		ScreenFlip();
	}
	ObjectManager::creanUpAll();

	DxLib_End();

	return 0;
}