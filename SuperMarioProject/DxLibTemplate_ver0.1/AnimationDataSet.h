#ifndef __ANIMATION_DATA_SET_H__
#define __ANIMATION_DATA_SET_H__

#include"AnimationData.h"

// 複数のAnimationDataを持ち、複数のアニメーションを切り替えられるようにするためのクラス
class AnimationDataSet
{
private:
	static const int ANIMATION_DATA_NUM = 16;

public:
	// 指定された番号のアニメーション情報を取得
	AnimationData* getAnimationData(int no);
	// 指定されたアニメーション番号が、有効なものかチェック
	bool isValidAnimationDataNo(int no);

private:


	AnimationData animDataArray[ANIMATION_DATA_NUM];


};

#endif