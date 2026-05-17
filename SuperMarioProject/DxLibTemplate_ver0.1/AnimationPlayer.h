#ifndef __ANIMATION_PLAYER_H__
#define __ANIMATION_PLAYER_H__

#include"const.h"

// 下のAnimationPlayerクラスではAnimationDataSetの"ポインタ"しか使用していないので、
// AnimationDataSetクラスの詳細な内容を知らなくてもよい。
// なぜなら"ポインタ"を使うには"8(or 4)Byte"用意すればよいと判断できるからである。
// こういう時には"こういう型のクラスがあるよ"ということを示す
// "前方宣言"だけを行っても問題ない。
class AnimationDataSet;





enum AnimationPlayerState
{
	// 再生中
	AP_PLAY = 0,
	// 再生終了
	AP_STOP
};



class AnimationPlayer
{
public:
	AnimationPlayer(AnimationDataSet* pAdc);

	// 現在再生中のアニメーションの番号を取得
	int getCurrentAnimationNo();

	inline bool getIsStop()
	{
		return isStop;
	}

	// 再生するアニメーションを変更
	void changeAnimation(int no);

	// アニメーションの更新
	void update();

	inline void setAds(AnimationDataSet* pAdc)
	{
		pAnimDataSet = pAdc;
		imgId = 0;
		wait = 0;
		animIdx = 0;
		animNo = 0;
	}

	// アニメーションの描画
	// 絶対座標で表示
	// (基準となるxとyの座標をもらわないので、画面左上、つまり絶対座標での表示を行う。)
	void render();
	// 相対座標で表示
	// (こちらは基準となる座標をもらうので、その座標を基準として、つまり相対座標での表示を行う。)
	void render(int baseX, int baseY);

public:
	int x;
	int y;

private :
	int cropX;
	int cropY;
	int cropW;
	int cropH;
	float angle;
	float angle_to;
	float angle_plus;
	bool reverseX;
	bool reverseY;
	bool isStop;

private:
	AnimationDataSet* pAnimDataSet;
	int imgId;
	int wait;
	int animIdx;
	int animNo;
	int state;
};

#endif