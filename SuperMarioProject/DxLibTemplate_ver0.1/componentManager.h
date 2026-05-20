#pragma once
#include"componentStorage.h"
#include<typeindex>
#include<typeinfo>
#include<unordered_map>


class ComponentManager
{
private :
	std::unordered_map<std::type_index, std::unique_ptr<ComponentStorage>> comStorages;

private :
	inline ComponentManager()
	{
		comStorages.clear();
	}

	inline ~ComponentManager()
	{
		comStorages.clear();
	}
	ComponentManager& operator = (const ComponentManager& other) = delete;
	ComponentManager(const ComponentManager& other) = delete;



public:

	static inline ComponentManager* getInstance()
	{
		static ComponentManager instance;
		return &instance;
	}

	// コンポーネントのストレージ確保関数
	inline ComponentStorage* ensureStorage(const std::type_index& type)
	{
		// 引数に指定された型名からそのコンポーネントのストレージがあるか探す
		// unordered_mapの.find()で指定されたキー(値とセットになっている鍵)の値があるか検索
		// ある場合はそのイテレータが、ない場合は末尾要素の一個先(存在しない)イテレータ返る
		// 学習要素：イテレータとは、簡単にはコンテナや配列の要素を指すポインタのようなもの
		auto it = comStorages.find(type);
		// イテレータが末尾一個先(.end()でも取れる)と同じだったら
		// 指定されたコンポーネントのストレージが存在しないので
		if (it == comStorages.end())
		{
			// unique_ptrで作成
			auto storagePtr = std::make_unique<ComponentStorage>();
			// 生ポインタも取っておく
			auto storageRawPtr = storagePtr.get();
			// ストレージ群に追加
			// 学習要素：unordered_mapの.emplace()は、コンテナ内に直接要素を作成する
			// 要素のコピーが発生しないので高速だが、失敗すると無駄なメモリが消費されるリスクがある
			comStorages.emplace(type, std::move(storagePtr));
			// ストレージの生ポインタを返す
			return storageRawPtr;
		}
		else
		{
			// ストレージがあればその生ポインタを返す
			return it->second.get();
		}

	}


	template<typename _T_>
	// コンポーネントの追加
	std::weak_ptr<_T_> addComponent(int objectId, std::shared_ptr<_T_> component)
	{
		// テンプレート引数がComponentを継承していなければ弾く
		static_assert(std::is_base_of<Component, _T_>::value, "Componentクラスを継承していないクラスがaddComponentに指定されています");
		// テンプレート引数の型をtypeid演算子で型情報型に変換し、その後、さらにtype_index型に
		// 学習要素：typeidとtype_index
		// typeidとは、型名情報(type_info)を生成する演算子で、型名情報は、条件式などで特定の型を使いたい時に用いる
		// type_indexは、その型名情報を、unordered_mapなどのコンテナのキーやインデックスに使いたい場合に用いる
		auto key = std::type_index(typeid(_T_));
		// type_indexをキーとしてストレージを呼び出す
		auto storage = ensureStorage(key);
		// ストレージにコンポーネントを追加
		// 学習要素：static_pointer_castはshared_ptr版のstatic_cast
		std::shared_ptr<Component> com = std::static_pointer_cast<Component>(component);
		storage->addComponent(objectId, com);
		// weak_ptrに変換して返す
		return std::weak_ptr<_T_>(component);

	}
	
	template<typename _T_>
	// コンポーネントの登録解除
	bool removeComponent(int objectId)
	{
		// テンプレート引数の型をtypeid演算子で型情報型に変換し、その後、さらにtype_index型に
		auto key = std::type_index(typeid(_T_));
		// 型情報をキーとしてストレージを探す
		auto it = comStorages.find(key);
		// ストレージがあったら
		if (it != comStorages.end())
		{
			// ストレージのコンポーネントを取り除く
			it->second->removeComponent(objectId);
			// 一応成否を判定するためtrueを返す
			return true;
		}
		// 無ければfalse
		return false;
	}

	template<typename _T_>
	// コンポーネント取得(一応オブジェクトのidから行えるようにすることで、複数個所からアクセスをしやすくする)
	// (保守性は下がる)
	std::weak_ptr<_T_> getComponent(int objectId)
	{
		// テンプレート引数の型をtypeid演算子で型情報型に変換し、その後、さらにtype_index型に
		auto key = std::type_index(typeid(_T_));
		// 型情報をキーとしてストレージを探す
		auto it = comStorages.find(key);
		// ストレージが無かったら
		if (it == comStorages.end())
		{
			// 空のweak_ptrを返す
			return std::weak_ptr<_T_>();
		}
		else
		{
			// ストレージからコンポーネントを取得
			it->second->getComponent(objectId);
		}

	}

	// オブジェクトが破壊された時の登録解除処理
	inline bool objectDestroyed(int objectId)
	{
		// 範囲forでストレージ群を走査
		for (auto& comSt : comStorages)
		{
			// idからコンポーネントを登録解除
			comSt.second->removeComponent(objectId);

		}
		return true;
	}

	// 期限切れになっているコンポーネントを登録解除
	void removeExpiredAll()
	{
		// 範囲forでストレージ群を走査
		for (auto& comSt : comStorages)
		{
			// idからコンポーネントを登録解除
			comSt.second->removeExpiredComponents();
		}

	}


	template<typename _T_>
	std::vector<std::weak_ptr<_T_>> getComponentsByBase()
	{
		std::vector<std::weak_ptr<_T_>> components;
		for (auto& comSt : comStorages)
		{
			auto com = comSt.second->getAnyComponent();
			if (!com.expired())
			{
				auto spCom = com.lock();
				auto castedCom = std::dynamic_pointer_cast<_T_>(spCom);
				if (castedCom)
				{
					std::vector<std::weak_ptr<Component>> vector = comSt.second->getAllComponent();
					for (size_t i = 0; i < vector.size(); i++)
					{
						std::shared_ptr<_T_> castedElem = std::dynamic_pointer_cast<_T_>(vector[i].lock());
						std::weak_ptr<_T_> wpCastedElem = std::weak_ptr<_T_>(castedElem);
						components.push_back(wpCastedElem);
					}

				}
				else
				{
					continue;
				}
			}
		}
		return components;
	}


};