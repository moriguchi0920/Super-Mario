#pragma once

#include"entityObject.h"
#include<memory>
#include<vector>
#include<utility>
#include<algorithm>
#include<unordered_map>


// 全オブジェクトを保持、管理するマネージャークラス
// shared_ptrのvectorを保持し、生成、更新、破棄を管理
// Object型を継承していれば生成が可能
class ObjectManager
{
private:
	// 静的メンバ
	// id管理用の変数
	// 定義をヘッダー内ですると多重定義になるが
	// テンプレートを使ったクラスのためcppでも定義出来ないので
	// inlineで無理やり解決
	static inline int lastId;

	// 静的メンバ
	// オブジェクトのshared_ptrのvector
	static inline std::vector<std::shared_ptr<Object>> objects;


private:
	// コンストラクタ
	inline ObjectManager()
	{
		lastId = 0;
		objects.clear();
	}
	// シングルトンにするためにコピーコンストラクタと=演算子削除
	ObjectManager& operator = (const ObjectManager& other) = delete;
	ObjectManager(const ObjectManager& other) = delete;

public:
	// インスタンス取得
	static inline ObjectManager* getInstance()
	{
		static ObjectManager instance;
		return &instance;
	}

public:
	// デストラクタ
	inline ~ObjectManager()
	{
		objects.clear();
	}

public:

	// テンプレート関数(コンポーネントのコンストラクタを動かすために引数用の可変長テンプレート使用)
	template <typename _T_, typename... Arg>
	// オブジェクト生成
	static _T_* createObject(Arg&&... args)
	{
		static_assert(std::is_base_of<Object, _T_>::value, "Objectを継承していないクラスは生成出来ません");
		// 新しいオブジェクトを引数に指定された可変長テンプレート変数から値を出しコンストラクタに代入
		// ただしコンストラクタの引数は正しい順番、型を入れること！
		auto newObject = std::make_shared<_T_>(std::forward<Arg>(args)...);
		// Objectクラスにキャスト
		auto castedObj = std::static_pointer_cast<Object>(newObject);

		// vectorに追加
		objects.push_back(castedObj);
		// 生ポインタを返す
		return newObject.get();
	}

	template <typename _T_>
	// オブジェクト生成の引数なしバージョン
	static _T_* createObject()
	{
		//static_assert(std::is_base_of(Object, _T_), "Objectを継承していないクラスは生成出来ません");
		auto newObject = std::make_shared<_T_>();
		auto castedObj = std::static_pointer_cast<Object>(newObject);

		objects.push_back(castedObj);
		return newObject.get();
	}
	// id生成
	static inline int makeId()
	{
		return lastId++;

	}

	// idからオブジェクトを取得
	static inline std::weak_ptr<Object> getObjectById(int id)
	{
		// 範囲forで走査
		for (auto& obj : objects)
		{
			// idが一致するオブジェクトが居たら
			if (obj->getId() == id)
			{
				// 返す
				return obj;
			}
		}
		// 無ければ空のweak_ptrを返す
		return std::weak_ptr<Object>();
	}

	// 存在する全オブジェクトの更新を一括で行う
	static inline void updateAll()
	{
		// 範囲forで走査
		for (auto& object : objects)
		{
			// オブジェクトが存在したら
			if (object)
			{
				if (object->getState() == Object::ObjectState::READY)
				{
					object->activate();
				}

				if (object->getState() != Object::ObjectState::ACTIVE)
				{
					continue;
				}
				

				// 更新
				object->update();
			}
		}
		objects.erase(std::remove_if(objects.begin(), objects.end(), [](std::shared_ptr<Object> obj) {return obj->getState() == Object::ObjectState::DEAD; }), objects.end());

	}

	// 全削除
	static inline void creanUpAll()
	{
		objects.clear();
	}
};

