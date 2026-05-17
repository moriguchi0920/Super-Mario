#ifndef __ANIMATION_DATA_ELEM_H__
#define __ANIMATION_DATA_ELEM_H__


enum AnimationCommand
{
	// アニメーションの終了
	AC_END,
	// 表示画像の切り替え
	AC_SET_IMAGE,
	// 待ち時間の設定
	AC_SET_WAIT,
	// 指定したアニメーションデータへ移動
	AC_JUMP,
	// 音声を再生する
	AC_PLAYSOUND,
	// 切り出し開始位置を設定
	AC_SET_CROP_BEGIN,
	// 切り出しサイズを設定
	AC_SET_CROP_SIZE,
	// 角度を設定
	AC_SET_ANGLE,
	// 最終角度を設定(現在の角度からこの角度まで徐々に変更を加える)
	AC_SET_ANGLE_TO,
	// 画像のxを反転させるか設定
	AC_SET_REVERSE_X,
	// 画像のyを反転させるか設定
	AC_SET_REVERSE_Y,

};

struct Crop
{
	int x;
	int y;
};


struct AnimationDataElem
{
	
	// あるフレームで、実行・設定したい内容の種類
	int command;

	// 上記のコマンドを実行するのに必要なデータの配列
	union ElemData
	{
		// サイズ調整用のパディング
		char padding[32];

		int imageHandle;
		int wait;
		int jumpDataIdx;
		int soundHandle;
		Crop crop_begin;
		Crop crop_size;
		bool reverseX;
		bool reverseY;
		bool transitionFlag;
		
		// AC_SET_ANGLEで使用
		float angle;
		// AC_SET_ANGLE_TOで使用
		// [0]: これが最終到達角度
		// [1]: 角度の変化量
		float angle_to[2];

	}data;
};


#endif