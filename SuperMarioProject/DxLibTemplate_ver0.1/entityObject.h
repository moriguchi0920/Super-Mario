#pragma once

#include<vector>
#include"componentManager.h"
#include"componentTransform.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentGravity.h"
#include<memory>
#include<algorithm>
#include<type_traits>
#include<utility>


// コンポーネントを追加し、ゲーム用オブジェクトを完成させていくための基底となるクラス
class Object
{
protected:
	// 生成ID
	int id;
	// コンポーネントの可変長配列
	std::vector<std::shared_ptr<Component>> components;

	int state;
public:
	enum ObjectState
	{
		READY,
		ACTIVE,
		INACTIVE,
		DEAD
	};

public:
	// 仮想関数update(更新処理)
	virtual void update()
	{

	}
	// オブジェクトを更新状態に
	void activate()
	{
		state = ObjectState::ACTIVE;
		activateProc();
	}
	// 更新開始時に行う処理
	virtual void activateProc()
	{

	}
	// オブジェクトを非更新状態に
	void deactivate()
	{
		state = ObjectState::INACTIVE;
		deactivateProc();
	}
	// 非更新開始時行う処理
	virtual void deactivateProc()
	{
		
	}
	// オブジェクトを死亡状態に
	void die()
	{
		state = ObjectState::DEAD;
		deathProc();
	}
	// 死亡時行う処理
	virtual void deathProc()
	{

	}




	// コンストラクタ
	inline Object(int _id)
	{
		id = _id;
		components.clear();
		state = ObjectState::READY;
	}
	// デストラクタ
	inline virtual ~Object()
	{
		ComponentManager::getInstance()->objectDestroyed(this->id);
		components.clear();
	}

	inline int getId()
	{
		return id;
	}

	// 一部座標が必要なコンポーネントを座標コンポーネントと連携
	inline void bindComponentToTransformComponent(std::shared_ptr<Component> com)
	{
		auto wpTransform = getComponent<ComponentTransform>();
		if (wpTransform.expired())
		{
			return;
		}
		auto wpGravity = getComponent<ComponentGravity>();
		if (wpGravity.expired())
		{
			return;
		}
		else
		{
			wpTransform = static_cast<std::weak_ptr<ComponentTransform>>(wpGravity);
		}
		

		if (auto renderable = std::dynamic_pointer_cast<ComponentCollisionShape>(com))
		{
			renderable->bindToTransform(wpTransform);
		}
		if (auto renderable = std::dynamic_pointer_cast<ComponentRenderable>(com))
		{
			renderable->bindToTransform(wpTransform);
		}


	}

	// テンプレート関数(コンポーネントのコンストラクタを動かすために引数用の可変長テンプレート使用)
	template <typename _T_, typename... Arg>
	// コンポーネント追加
	// 学習要素：Arg&&... argは、引数の型が可変長であることを表す。std::forward<Arg>(arg)...は、引数を完全転送するためのもの
	// これにより、引数が右辺値参照であれば右辺値参照として、左辺値参照であれば左辺値参照として渡される
	std::weak_ptr<_T_> addComponent(Arg&&... arg)
	{
		// 基底クラスComponentを継承していないクラスを指定した場合は弾く
		// 学習要素：static_assert(条件式, エラーメッセージ)で、条件式がfalseのときにコンパイルエラーを発生させることができる
		static_assert(std::is_base_of<Component, _T_>::value, "Componentクラスを継承していないクラスがaddComponentに指定されています");

		auto spCom = std::make_shared<_T_>(std::forward<Arg>(arg)...);

		components.push_back(std::static_pointer_cast<Component>(spCom));


		ComponentManager::getInstance()->addComponent(this->id, spCom);

		bindComponentToTransformComponent(spCom);

		return std::weak_ptr<_T_>(spCom);
	}
	// テンプレート関数
	template <typename _T_>
	// コンポーネント取得
	std::weak_ptr<_T_> getComponent()
	{
		// 範囲for文でコンポーネントの配列を回し、指定された型のコンポーネントがあれば返す
		for (auto& ptr : components)
		{
			// dynamic_pointer_cast(shared_ptr版アップキャスト)でnullptrでなければ指定された型のコンポーネントがあると判断して返す
			auto casted = std::dynamic_pointer_cast<_T_>(ptr);
			if (casted)
			{
				return std::weak_ptr<_T_>(casted);
			}
		}
		// なければ空のweak_ptrを返す
		return std::weak_ptr<_T_>();
	}
	// テンプレート関数
	template <typename _T_>
	// 同じコンポーネントが複数ある場合のコンポーネント取得
	std::vector<std::weak_ptr<_T_>> getComponentArray()
	{
		std::vector<std::weak_ptr<_T_>> coms;
		// 範囲for文でコンポーネントの配列を回し、指定された型のコンポーネントがあれば返す
		for (auto& ptr : components)
		{
			// dynamic_pointer_cast(shared_ptr版アップキャスト)でnullptrでなければ指定された型のコンポーネントがあると判断して返す
			auto casted = std::dynamic_pointer_cast<_T_>(ptr);
			if (casted)
			{
				coms.push_back(std::weak_ptr<_T_>(casted));
			}
		}
		// なければ空のweak_ptrを返す
		return coms;
	}



	// テンプレート関数
	template <typename _T_>
	// コンポーネント削除
	void removeComponent()
	{
		// remove_ifにラムダ式を渡し、dynamic_pointer_castの結果がnullptrでないものを削除するようにする
		// 学習要素：ラムダ式は、[キャプチャ](引数) -> 戻り値 {関数の内容}で書くことができる。今回は、引数はshared_ptr<Component>&で、戻り値はboolで、関数の内容は、dynamic_pointer_castの結果がnullptrでないものを削除するようにする
		// キャプチャは、[]の中に、外部の変数を指定することができる。今回は、_T_を指定することで、テンプレート引数をラムダ式の中で使えるようにする
		components.erase(std::remove_if(components.begin(), components.end(), [](std::shared_ptr<Component>& ptr) { return std::dynamic_pointer_cast<_T_>(ptr) != nullptr; }), components.end());

		ComponentManager::getInstance().removeComponent(this->id);
	}

	inline int getState()
	{
		return state;
	}


};