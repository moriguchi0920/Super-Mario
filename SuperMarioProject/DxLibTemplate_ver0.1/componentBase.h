#pragma once
#include<memory>
class Object;

// すべてのコンポーネントの基底クラス
// 自分の保持者のidを持つ
// また、途中でコンポーネントを非処理状態にできるように
// bool型変数も保持
class Component
{
protected:
	// 親のid
	int entityId;
	// 現在有効かどうか
	bool isActive;

public:
	// コンストラクタ
	// 必ず生成時親のidをもらう
	Component(int id);

	// 親のid取得
	int getParentId();

	// 有効状態取得
	bool getIsActive();

	void setActive(bool active);

	// デストラクタ
	virtual ~Component();

};