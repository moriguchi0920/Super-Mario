#ifndef __RENDERABLEMANAGER_H__
#define __RENDERABLEMANAGER_H__

#include<memory>
#include<vector>

class ComponentRenderable;

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





public :

	// 登録された全描画物を表示
	void renderAll();


private:

	// 描画優先順位順に並び替え
	void sortByPriority(std::vector<std::weak_ptr<ComponentRenderable>> coms);

};

#endif