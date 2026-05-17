#include "dxlib.h"
#include "const.h"
#include "keyManager.h"

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



	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		KeyManager::getInstance().updateKeyState();
		// ↑ システム更新 ↑
		//---------------------------------------



		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------

		if (KeyManager::pullUpKey(KEY_INPUT_SPACE))
		{
			DrawString(0, 0, "スペースキーが離された瞬間", GetColor(255, 255, 255));
		}

		ScreenFlip();
	}


	DxLib_End();

	return 0;
}