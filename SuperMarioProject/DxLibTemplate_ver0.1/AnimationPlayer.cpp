#include"AnimationPlayer.h"
#include"AnimationDataSet.h"
#include"DxLib.h"


AnimationPlayer::AnimationPlayer(AnimationDataSet* pAdc)
{
	pAnimDataSet = pAdc;
	imgId = 0;
	wait = 0;
	animIdx = 0;
	animNo = 0;
	x = 0;
	y = 0;

	cropX = 0;
	cropY = 0;
	cropW = 0;
	cropH = 0;
	state = AnimationPlayerState::AP_PLAY;

	angle = 0.0f;
	angle_plus = 0.0f;
	angle_to = 0.0f;

	reverseX = false;
	reverseY = false;
	isStop = false;
}

// 現在再生中のアニメーションの番号を取得
int AnimationPlayer::getCurrentAnimationNo()
{
	return animNo;
}

// 再生するアニメーションを変更
void AnimationPlayer::changeAnimation(int no)
{
	// 指定された番号は正常なものかチェック
	if (pAnimDataSet->isValidAnimationDataNo(no) == false)
	{
		return;
	}
	if (animNo == no)
	{
		return;
	}

	wait = 0;
	animIdx = 0;
	animNo = no;
	state = AP_PLAY;
}

// アニメーションの更新
void AnimationPlayer::update()
{
	// アニメーションが再生中か
	if (state != AP_PLAY)
	{
		// 再生中ではないので更新を抜ける
		return;
	}
	wait--;
	while (wait <= 0)
	{
		AnimationData* pAd = pAnimDataSet->getAnimationData(animNo);
		if (pAd == NULL)
		{
			return;
		}
		// 現在処理すべきアニメーションデータを取得
		const AnimationDataElem* pAde = pAd->getData(animIdx);
		if (pAde == NULL)
		{
			return;
		}
		// アニメーションデータを取得したら、次のデータを見るように
		// インデックスを一つ進める。
		animIdx++;
		isStop = false;

		// 現在のコマンドに対する処理
		switch (pAde->command)
		{
		case AC_SET_IMAGE:
			imgId = pAde->data.imageHandle;
			break;
		case AC_SET_WAIT:
			wait = pAde->data.wait;
			break;
		case AC_JUMP:
			animIdx = pAde->data.jumpDataIdx;
			break;
		case AC_END:
			isStop = true;
			state = AP_STOP;
			break;
		case AC_PLAYSOUND:
			break;
		case AC_SET_CROP_BEGIN:
			cropX = pAde->data.crop_begin.x;
			cropY = pAde->data.crop_begin.y;
			break;

		case AC_SET_CROP_SIZE:
			cropW = pAde->data.crop_size.x;
			cropH = pAde->data.crop_size.y;
		case AC_SET_ANGLE:
			angle = pAde->data.angle;
			break;
		case AC_SET_ANGLE_TO:
			angle_to = pAde->data.angle_to[0];
			angle_plus = pAde->data.angle_to[1];
			break;
		case AC_SET_REVERSE_X:
			reverseX = pAde->data.reverseX;
			break;
		case AC_SET_REVERSE_Y:
			reverseY = pAde->data.reverseY;
			break;

		}
	}

}



// アニメーションの描画
// 絶対座標で表示
// (基準となるxとyの座標をもらわないので、画面左上、つまり絶対座標での表示を行う。)
void AnimationPlayer::render()
{
	//DrawGraph( x, y, imageArray[imgId], 1);
	render(0, 0);
}
// 相対座標で表示
// (こちらは基準となる座標をもらうので、その座標を基準として、つまり相対座標での表示を行う。)
void AnimationPlayer::render(int baseX, int baseY)
{
	// 自分の座標をローカル座標として扱い、引数にもらった基準となる座標を加えて絶対座標に変換する。
	//DrawGraph(baseX + x, baseY + y, imageArray[imgId], 1);
	DrawRotaGraph(baseX + x, baseY + y, 1.0, angle, imgId, TRUE, reverseX, reverseY);

	//// デバッグ表示
	//printfDx("pAnimDataSet: %llu\n", pAnimDataSet);
	//printfDx("imgId: %d\n", imgId);
	//printfDx("wait: %d\n", wait);
	//printfDx("animIdx: %d\n", animIdx);
	//printfDx("animNo: %d\n", animNo);
	//printfDx("state : %d\n", state);
}
