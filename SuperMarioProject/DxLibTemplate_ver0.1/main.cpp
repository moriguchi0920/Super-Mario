
#include "const.h"
#include "keyManager.h"
#include"componentManager.h"
#include"objectManager.h"
#include"collisionManager.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"renderableManager.h"
#include"sampleObject.h"
#include "dxlib.h"

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

	//---------------------------------------
	// 変数の作成や初期化、その他初期設定
	// ↓ システム初期化 ↓
	KeyManager::getInstance().initKeyManager();
	// ↑ システム初期化 ↑
	//---------------------------------------
	
	ObjectManager::createObject<SampleObject>();



	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		KeyManager::getInstance().updateKeyState();
		// ↑ システム更新 ↑
		//---------------------------------------

		ObjectManager::updateAll();

		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		RenderableManager::getInstance()->renderAll();

		if (KeyManager::pullUpKey(KEY_INPUT_SPACE))
		{
			DrawString(0, 0, "スペースキーが離された瞬間", GetColor(255, 255, 255));
		}

		ScreenFlip();
	}
	ObjectManager::creanUpAll();

	DxLib_End();

	return 0;
}