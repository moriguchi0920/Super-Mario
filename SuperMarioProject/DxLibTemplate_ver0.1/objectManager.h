#pragma once

#include"entityObject.h"
#include<memory>
#include<vector>
#include<utility>
#include<algorithm>
#include<unordered_map>



class ObjectManager
{
private:
	static inline int lastId;

	static inline std::vector<std::shared_ptr<Object>> objects;


private:
	inline ObjectManager()
	{
		lastId = 0;
		objects.clear();
	}
	ObjectManager& operator = (const ObjectManager& other) = delete;
	ObjectManager(const ObjectManager& other) = delete;

public:
	static inline ObjectManager* getInstance()
	{
		static ObjectManager instance;
		return &instance;
	}

public:
	inline ~ObjectManager()
	{
		objects.clear();
	}

public:

	template <typename _T_, typename... Arg>
	static _T_* createObject(Arg&&... args)
	{
		//static_assert(std::is_base_of(Object, _T_), "Objectを継承していないクラスは生成出来ません");
		auto newObject = std::make_shared<_T_>(std::forward<Arg>(args...));
		auto castedObj = std::static_pointer_cast<Object>(newObject);

		objects.push_back(castedObj);
		return newObject.get();
	}

	template <typename _T_>
	static _T_* createObject()
	{
		//static_assert(std::is_base_of(Object, _T_), "Objectを継承していないクラスは生成出来ません");
		auto newObject = std::make_shared<_T_>();
		auto castedObj = std::static_pointer_cast<Object>(newObject);

		objects.push_back(castedObj);
		return newObject.get();
	}

	static inline int makeId()
	{
		return lastId++;

	}

	static inline std::weak_ptr<Object> getObjectById(int id)
	{
		for (auto& obj : objects)
		{
			if (obj->getId() == id)
			{
				return obj;
			}
		}
	}

	static inline void updateAll()
	{
		for (auto& object : objects)
		{
			if (object)
			{
				object->update();
			}
		}
	}


	static inline void creanUpAll()
	{
		objects.clear();
	}
};

