#include"AnimationDataSet.h"
#include<stdlib.h>

// 指定された番号のアニメーション情報を取得
AnimationData* AnimationDataSet::getAnimationData(int no)
{
	AnimationData* ret = NULL;
	// 指定された番号が有効なものかどうか
	if (isValidAnimationDataNo(no))
	{
		ret = &animDataArray[no];
	}
	return ret;
}
// 指定されたアニメーション番号が、有効なものかチェック
bool AnimationDataSet::isValidAnimationDataNo(int no)
{
	bool ret = false;
	if (0 <= no && no < ANIMATION_DATA_NUM)
	{
		ret = true;
	}
	return ret;
}