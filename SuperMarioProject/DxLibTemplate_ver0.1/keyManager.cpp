#include "dxlib.h"
#include <string.h>
#include "keyManager.h"

// 静的メンバ変数の定義

char KeyManager::keyStateBuffer[KEY_STATE_BUFFER_ROW][KEY_STATE_BUFFER_LENGTH];

char KeyManager::keyStateBufferTrigger[KEY_STATE_BUFFER_LENGTH];

char KeyManager::keyStateBufferPullUp[KEY_STATE_BUFFER_LENGTH];

int KeyManager::currentBufferIdx = 0;
		
char KeyManager::strKeyStateBuffer[STR_KEY_STATE_BUFFER_ROW][STR_KEY_STATE_BUFFER_LENGTH];





KeyManager::KeyManager()
{

}


KeyManager::~KeyManager()
{
}

// キーマネージャの初期化
void KeyManager::initKeyManager()
{
	for ( int row = 0; row < KEY_STATE_BUFFER_ROW; row++)
	{
		char* curBuffer = keyStateBuffer[row];
		for ( int col = 0; col < KEY_STATE_BUFFER_LENGTH; col++ )
		{
			curBuffer[col] = 0;
		}
	}
	currentBufferIdx = 0;

	for (int row = 0; row < STR_KEY_STATE_BUFFER_ROW; row++)
	{
		char* curBuffer = strKeyStateBuffer[row];
		for (int col = 0; col < STR_KEY_STATE_BUFFER_LENGTH; col++)
		{
			curBuffer[col] = '0';
		}
		curBuffer[STR_KEY_STATE_BUFFER_LENGTH - 1] = '\0';
	}

}

// キーの状態を更新
void KeyManager::updateKeyState()
{
	int nextCurBufferIdx = (currentBufferIdx + 1) % KEY_STATE_BUFFER_ROW;
	char* curBuffer = keyStateBuffer[nextCurBufferIdx];
	char* prevBuffer = keyStateBuffer[currentBufferIdx];

	GetHitKeyStateAll(curBuffer);

	for ( int col = 0; col < KEY_STATE_BUFFER_LENGTH; col++ )
	{
		keyStateBufferTrigger[col] = (prevBuffer[col] == 0) && (curBuffer[col] == 1) ? 1 : 0;
	}

	for (int col = 0; col < KEY_STATE_BUFFER_LENGTH; col++)
	{
		keyStateBufferPullUp[col] = (prevBuffer[col] == 1) && (curBuffer[col] == 0) ? 1 : 0;
	}


	currentBufferIdx = nextCurBufferIdx;
}

// キーが押されているか調べる
// 戻り値:
//		0: 押されていない
//		1: 押されている
int KeyManager::checkHitKey(int key)
{
	return (int)keyStateBuffer[currentBufferIdx][key];
}

// キーが押された瞬間か調べる
// 戻り値:
//		0: 押された瞬間ではない
//		1: 押さた瞬間
int KeyManager::pushHitKey(int key)
{
	return (int)keyStateBufferTrigger[key];
}

int KeyManager::pullUpKey(int key)
{
	return (int)keyStateBufferPullUp[key];
}

// 全てのキーの押下状態を文字列で取得
// 戻り値:
//		全てのキーの状態を示す文字列
const char* KeyManager::getStrKeyState()
{
	char* orgBuffer = keyStateBuffer[currentBufferIdx];
	char* strBuffer = strKeyStateBuffer[0];
	for (int col = 0; col < KEY_STATE_BUFFER_LENGTH; col++)
	{
		strBuffer[col] = '0' + orgBuffer[col];
	}

	return strBuffer;
}

// 全てのキーの押下瞬間状態を文字列で取得
// 戻り値:
//		全てのキーの押下瞬間状態を示す文字列
const char* KeyManager::getStrKeyStateTrigger()
{
	char* orgBuffer = keyStateBufferTrigger;
	char* strBuffer = strKeyStateBuffer[1];
	for (int col = 0; col < KEY_STATE_BUFFER_LENGTH; col++)
	{
		strBuffer[col] = '0' + orgBuffer[col];
	}

	return strBuffer;
}