#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__

class KeyManager final
{
private:
	// キーの状態を保存するバッファの長さ
	static const int KEY_STATE_BUFFER_LENGTH = 256;
	// キーの状態を保存するバッファの行数
	static const int KEY_STATE_BUFFER_ROW = 2;
	// キーの状態を保存するバッファ(1フレーム前と現在の状態を保存するため2行)
	static char keyStateBuffer[KEY_STATE_BUFFER_ROW][KEY_STATE_BUFFER_LENGTH];
	// キーの押下瞬間の状態を保存するバッファ
	static char keyStateBufferTrigger[KEY_STATE_BUFFER_LENGTH];
	// キーの離された瞬間の状態を保存するバッファ
	static char keyStateBufferPullUp[KEY_STATE_BUFFER_LENGTH];
	// 現在のバッファのインデックス
	static int currentBufferIdx;

	// キーの状態を文字列で保存するバッファの長さ
	static const int STR_KEY_STATE_BUFFER_LENGTH = KEY_STATE_BUFFER_LENGTH + 1;
	// キーの状態を文字列で保存するバッファの行数
	static const int STR_KEY_STATE_BUFFER_ROW = 2;
	// キーの状態を文字列で保存するバッファ(1フレーム前と現在の状態を保存するため2行)
	static char strKeyStateBuffer[STR_KEY_STATE_BUFFER_ROW][STR_KEY_STATE_BUFFER_LENGTH];

private:
	// コンストラクタとコピーコンストラクタ、代入演算子を削除してシングルトンパターンを実装
	KeyManager();
	KeyManager(const KeyManager&) = delete;
	KeyManager& operator=(const KeyManager&) = delete;

public :
	// シングルトンインスタンスを取得するための静的メソッド
	static inline KeyManager& getInstance()
	{
		static KeyManager instance;
		return instance;
	}

public:

	// デストラクタ
	~KeyManager();

	// キーマネージャの初期化
	void initKeyManager();

	// キーの状態を更新
	void updateKeyState();

	// キーが押されているか調べる
	// 戻り値:
	//		0: 押されていない
	//		1: 押されている
	static int checkHitKey(int key);

	// キーが押された瞬間か調べる
	// 戻り値:
	//		0: 押された瞬間ではない
	//		1: 押さた瞬間
	static int pushHitKey(int key);

	// キーが押された状態から離れた瞬間か調べる
	// 戻り値:
	//		0: 離れた瞬間ではない
	//		1: 離れた瞬間
	static int pullUpKey(int key);


	// 全てのキーの押下状態を文字列で取得
	// 戻り値:
	//		全てのキーの状態を示す文字列
	const char* getStrKeyState();

	// 全てのキーの押下瞬間状態を文字列で取得
	// 戻り値:
	//		全てのキーの押下瞬間状態を示す文字列
	const char* getStrKeyStateTrigger();

};
#endif