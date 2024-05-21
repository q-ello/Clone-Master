#pragma once

#ifndef _STORE_
#define _STORE_

#include "../stdafx.h"
#include "../Models/Item.h"
#include "../Models/Character.h"
#include "../Utilities/Utils.h"

template<typename T>
class AbsLoot
{
public: 
	T deleteEntity(const std::string& name);

	bool isFull();

	void addEntity(T some);

	void printInfo();

	bool isEmpty();

	void dispose();

	std::vector<T> getEntities();

private:
	std::vector<T> entities_;
	int maxSize_ = 6;
};

using Inventory = AbsLoot<Item*>;

using Squad = AbsLoot<Character*>;

template<typename T>
inline T AbsLoot<T>::deleteEntity(const std::string& name)
{
	int index = -1;
	for (auto it = entities_.begin(); it != entities_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName())) {
			index = static_cast<int>(it - entities_.begin());
			break;
		}
	}
	if (index == -1)
	{
		return nullptr;
	}

	T entityPtr = entities_[index];
	entities_.erase(index + entities_.begin());
	return entityPtr;
}

template<typename T>
inline bool AbsLoot<T>::isFull()
{
	return entities_.size() >= maxSize_;
}

template<typename T>
inline void AbsLoot<T>::addEntity(T some)
{
	entities_.push_back(std::move(some));
}

template<typename T>
inline void AbsLoot<T>::printInfo()
{
	for (auto& entity : entities_)
	{
		std::cout << entity->getName() << std::endl;
	}
}

template<typename T>
inline bool AbsLoot<T>::isEmpty()
{
	return entities_.size() == 0;
}

template<typename T>
inline void AbsLoot<T>::dispose()
{
	entities_.clear();
}

template<typename T>
inline std::vector<T> AbsLoot<T>::getEntities()
{
	return entities_;
}

#endif // !_STORE_