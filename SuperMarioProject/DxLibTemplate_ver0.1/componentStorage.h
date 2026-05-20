#pragma once
#include<unordered_map>
#include<memory>
#include<vector>

class Component;

// コンポーネントをIDとセットで保存するクラス
class ComponentStorage
{
protected:
	// IDとコンポーネントのペアを保存するunordered_map
	// 学習要素：unordered_mapは、キーと値のペアを保存するコンテナで、キーの順序は保証されない。キーの検索や挿入が高速に行える。
	std::unordered_map<int, std::weak_ptr<Component>> componentMap;

public:
	// コンストラクタ
	ComponentStorage();
	// デストラクタ
	~ComponentStorage();
	// コンポーネント追加関数
	// 学習要素：unordered_mapの要素へのアクセスは、map[key]で行うことができる。もしkeyが存在しない場合は、新しい要素が追加される。
	void addComponent(int id, std::shared_ptr<Component> component);
	std::weak_ptr<Component> getComponent(int id);
	// コンポーネント削除関数
	void removeComponent(int id);
	// 生きていないコンポーネントを破棄する関数
	void removeExpiredComponents();
	// コンポーネントが一つでも存在したら返す関数(特定のコンポーネント探索用)
	std::weak_ptr<Component> getAnyComponent();

	std::vector<std::weak_ptr<Component>> getAllComponent();

};