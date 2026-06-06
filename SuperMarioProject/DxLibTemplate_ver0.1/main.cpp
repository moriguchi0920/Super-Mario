
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
#include "DxLib.h"

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

	//---------------------------------------
	// 変数の作成や初期化、その他初期設定
	// ↓ システム初期化 ↓
	KeyManager::getInstance().initKeyManager();
	// ↑ システム初期化 ↑
	//---------------------------------------
	
	ObjectManager::getInstance();

	ObjectManager::createObject<Floor>(0.0f, 1000.0f);
	ObjectManager::createObject<Floor>(1050.0f, 200.0f);
	ObjectManager::createObject<Floor>(1300.0f, 1000.0f);
	ObjectManager::createObject<Floor>(2350.0f, 600.0f);

	ObjectManager::createObject<Dokan>(100.0f, 160.0f);

	ObjectManager::createObject<Mario>();
<<<<<<< HEAD

	ObjectManager::createObject<rengablock>(Rect(Float2(SPRITE_SIZE * 3, SPRITE_SIZE * 8), Float2(SPRITE_SIZE, SPRITE_SIZE)));
=======
	ObjectManager::createObject<rengablock>(80.0f, 130.0f);
	ObjectManager::createObject<hatenablock>(50.0f, 130.0f);
>>>>>>> 51d47f93176d3c800e9de460daea874e0e1c9c2b

	



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