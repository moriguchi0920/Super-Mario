#include"renderableManager.h"
#include"DxLib.h"

//#define IS_DEBUG

RenderableManager::RenderableManager()
{
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		pRenderableArray[i] = NULL;
	}
}

RenderableManager* RenderableManager::getInstance()
{
	static RenderableManager instance;
	return &instance;
}

bool RenderableManager::isAlreadyExist(Renderable* pObj)
{
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		if (pRenderableArray[i] == pObj)
		{
			return true;
		}
	}
	return false;
}

bool RenderableManager::addObject(Renderable* pObj)
{
	if (isAlreadyExist(pObj))
	{
		return false;
	}
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		if (pRenderableArray[i] == NULL)
		{
			pRenderableArray[i] = pObj;
			return true;
		}
	}
	return false;
}

bool RenderableManager::removeObject(Renderable* pObj)
{
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		if (pRenderableArray[i] == pObj)
		{
			pRenderableArray[i] = NULL;
			return true;
		}
	}
	return false;
}

void RenderableManager::renderAll()
{
	fillGap();
	sortByPriority();
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		if (pRenderableArray[i] != NULL)
		{
			pRenderableArray[i]->render();
		}
	}
#ifdef IS_DEBUG
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		printfDx("[%d]: %llu\n", i, pRenderableArray[i]);
	}
#endif
}

void RenderableManager::fillGap()
{
	//---------------------------------------
	// 表示物の空きを詰める(この後並び替えをスムーズに行うため)
	//---------------------------------------
	int head = 0;
	int tail = RENDERABLE_ARRAY_LENGTH - 1;
	bool loopEnd = false;
	while (loopEnd == false)
	{
		// 現在headが参照している場所はNULLか？
		if (tail <= head)
		{
			loopEnd = true;
		}
		Renderable** ppHead = &pRenderableArray[head];
		if (*ppHead == NULL)
		{
			// 現在の場所がNULLなので、後ろからデータを詰める処理を行う。
			while (true)
			{
				if (tail == head)
				{
					loopEnd = true;
					break;
				}
				// 現在tailが見ている場所にデータがあるか
				Renderable** ppTail = &pRenderableArray[tail];
				if (*ppTail == NULL)
				{
					// 今tailが見ている場所にデータはないので、
					// tailの位置を進めて比較を続ける
					tail--;
					continue;
				}

				// 現在のtailの場所にデータが見つかったので、
				// 入れ替えを行う
				*ppHead = *ppTail;
				*ppTail = NULL;
				break;

			}
		}

		head++;
	}


}

void RenderableManager::sortByPriority()
{
	//---------------------------------------
	// 表示物の並び替え(小さい順)
	//---------------------------------------

	// まず入れ替える回数をとる
	int dataNum = 0;
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		if (pRenderableArray[i] != NULL)
		{
			dataNum++;
		}
	}
	// 入れ替える必要がある(要素数が2以上)
	if (2 <= dataNum)
	{
		// ソート処理のwhileループ(入れ替えが発生しなかったらループを抜ける)
		while (true)
		{
			// 入れ替え回数
			int flipCount = 0;
			// 入れ替え
			for (int i = 0; i < dataNum - 1; i++)
			{
				// ポインタ配列の左の要素のポインタ
				Renderable** ppLeft = &pRenderableArray[i];
				// ポインタ配列の右の要素のポインタ
				Renderable** ppRight = &pRenderableArray[i + 1];
				// プライオリティの値の大小を比較
				if ((*ppRight)->getPriority() < (*ppLeft)->getPriority())
				{
					// 左右の入れ替え
					Renderable* tmp = *ppLeft;
					// ダブルポインタ経由での入れ替えのため
					// ループカウンタが不要
					*ppLeft = *ppRight;
					*ppRight = tmp;

					// 入れ替えが発生したので回数をカウントアップ
					flipCount++;
				}
			}
			// 入れ替えが発生しなかったら
			if (flipCount == 0)
			{
				// ループを抜ける
				break;
			}
		}

	}
}

