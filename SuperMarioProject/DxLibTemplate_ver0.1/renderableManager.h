#ifndef __RENDERABLEMANAGER_H__
#define __RENDERABLEMANAGER_H__

#include "renderable.h"

// 表示物管理クラス
// このクラスは表示物のポインタを内部で持ち、
// 表示優先順に並び変えて表示する機能を持つ。
//
// ただTaskManagerのようにポインタの管理だけでなく、
// メモリの開放まで行うわけではないので注意！
class RenderableManager
{
public :
	static RenderableManager* getInstance();

private :
	// コンストラクタ
	RenderableManager();
	// 代入演算子
	RenderableManager& operator = (RenderableManager& other) = delete;
	// コピーコンストラクタ
	RenderableManager(const RenderableManager& other) = delete;


private:
	// 登録可能数
	static const int RENDERABLE_ARRAY_LENGTH = 3200;

	// Renderableクラスオブジェクトのポインタ配列
	Renderable* pRenderableArray[RENDERABLE_ARRAY_LENGTH];


public :
	// 表示物の登録
	bool addObject(Renderable* pObj);

	// 登録された全描画物を表示
	void renderAll();

	// 表示物の登録解除
	bool removeObject(Renderable* pObj);

private:
	// 登録時同じオブジェクトを間違えて登録しないための安全措置
	bool isAlreadyExist(Renderable* pObj);

	// 描画優先順位順に並び替え
	void sortByPriority();

	// 空きを詰める
	void fillGap();
};

#endif