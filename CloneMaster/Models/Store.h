#pragma once

#ifndef _STORE_
#define _STORE_

#include <vector>
#include "../Models/Item.h"
#include "../Models/Character.h"
#include "../Utilities/Utils.h"

template<typename T>
class AbsLoot
{
public: 
	T* deleteEntity(const std::string& name);

	bool isFull();

	void addEntity(T some);

	void printInfo();

	bool isEmpty();

private:
	std::vector<T> entities_;
	int maxSize_ = 6;
};

using Inventory = AbsLoot<Item*>;

using Squad = AbsLoot<Character*>;

#endif // !_STORE_

template<typename T>
inline T* AbsLoot<T>::deleteEntity(const std::string& name)
{
	int index = -1;
	for (auto& it = entities_.begin(); it != entities_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName())) {
			index = it - entities_.begin();
			break;
		}
	}
	if (index == -1)
	{
		std::cout << "Failed to remove" << std::endl;
		return;
	}

	T* entityPtr = entities_[index];
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
