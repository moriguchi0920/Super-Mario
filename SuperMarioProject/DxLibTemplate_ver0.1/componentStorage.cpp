#include "componentStorage.h"

// コンストラクタ
ComponentStorage::ComponentStorage()
{
	componentMap.clear();
}

// デストラクタ
ComponentStorage::~ComponentStorage()
{
	componentMap.clear();
}

// コンポーネント追加関数
// 学習要素：unordered_mapの要素へのアクセスは、map[key]で行うことができる。もしkeyが存在しない場合は、新しい要素が追加される。
void ComponentStorage::addComponent(int id, std::shared_ptr<Component> component)
{
	std::weak_ptr<Component> com(component);
	componentMap[id] = com;
}

std::weak_ptr<Component> ComponentStorage::getComponent(int id)
{
	// .find関数を使って要素を検索
	// 学習要素：unordered_mapの要素を検索するには、find関数を使用する。見つからなかった場合はend()を返す。
	auto it = componentMap.find(id);
	// 要素があったら
	// 学習要素：if文でイテレータがend()でないことを確認することで、指定されたIDのコンポーネントが存在するかどうかを判断できる。
	if (it != componentMap.end())
	{
		// その要素内の数値を返す
		// 学習要素：イテレータのsecondメンバにアクセスすることで、対応する値（この場合はコンポーネント）を取得できる。
		return std::weak_ptr<Component>(it->second);
	}
	// なければ空のweak_ptrを返す
	return std::weak_ptr<Component>();
}

// コンポーネント削除関数
void ComponentStorage::removeComponent(int id)
{
	// idから要素を削除
	componentMap.erase(id);
}

// 生きていないコンポーネントを破棄する関数
void ComponentStorage::removeExpiredComponents()
{
	// イテレータを利用し、コンポーネントマップを走査
	// 学習要素：unordered_mapのイテレータを使用して、コンポーネントマップをループすることができる。イテレータは、begin()からend()までの範囲で使用できる。
	// for文内で.erase()を行うとイテレータがずれて未定義動作を起こすので
	// イテレータのカウントアップは削除が行われなかったときのみにする
	for (auto it = componentMap.begin(); it != componentMap.end();)
	{
		// 生きていないweak_ptrだったら
		if (it->second.expired())
		{
			// 削除
			// 学習要素：unordered_mapのerase関数は、イテレータを渡すことで、そのイテレータが指す要素を削除することができる。削除後、イテレータは次の要素を指すようになる。
			it = componentMap.erase(it);
		}
		else
		{
			// イテレータをカウントアップしてループを進める
			++it;
		}
	}
}
// コンポーネントが一つでも存在したら返す関数(特定のコンポーネント探索用)
std::weak_ptr<Component> ComponentStorage::getAnyComponent()
{
	// 範囲forで走査
	for (auto& com : componentMap)
	{
		// 生きているコンポーネントが居たら
		if (!com.second.expired())
		{
			// 返す
			return com.second;
		}
	}

	// 居なかったら空のweak_ptr
	return std::weak_ptr<Component>();
}

// 内部の存在するコンポーネントを全部vectorに入れて返す関数
std::vector<std::weak_ptr<Component>> ComponentStorage::getAllComponent()
{
	// 空のvector作成
	auto components = std::vector<std::weak_ptr<Component>>();
	// 範囲forで走査
	for (auto& com : componentMap)
	{
		// 生きているコンポーネントが居たら
		if (!com.second.expired())
		{
			// vectorに追加
			components.push_back(com.second);
		}
	}

	// 返す
	return components;
}



