#include"componentRenderable.h"
#include"renderableManager.h"
#include"componentManager.h"
#include<memory>
#include<vector>
#include<algorithm>
#include"DxLib.h"

//#define IS_DEBUG

RenderableManager::RenderableManager()
{

}

RenderableManager* RenderableManager::getInstance()
{
	static RenderableManager instance;
	return &instance;
}


void RenderableManager::renderAll()
{
	ComponentManager* pComManager = ComponentManager::getInstance();
	std::vector<std::weak_ptr<ComponentRenderable>> comRenders = pComManager->getComponentsByBase<ComponentRenderable>();
	sortByPriority(comRenders);
	for (auto& com : comRenders)
	{
		if (!com.expired())
		{
			com.lock()->render();
		}
	}
#ifdef IS_DEBUG
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		printfDx("[%d]: %llu\n", i, pRenderableArray[i]);
	}
#endif
}



void RenderableManager::sortByPriority(std::vector<std::weak_ptr<ComponentRenderable>> coms)
{
	//---------------------------------------
	// 表示物の並び替え(小さい順)
	//---------------------------------------

	// まず入れ替える回数をとる
	size_t dataNum = coms.size();

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
				ComponentRenderable* pComRenderLeft = coms[i].lock().get();
				// ポインタ配列の右の要素のポインタ
				ComponentRenderable* pComRenderRight = coms[i + 1].lock().get();
				// プライオリティの値の大小を比較
				if (pComRenderLeft->getPriority() < pComRenderRight->getPriority())
				{
					std::swap(coms[i], coms[i + 1]);
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

