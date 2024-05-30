#pragma once

#ifndef _STORE_
#define _STORE_

#include "../stdafx.h"
#include "../Models/Item.h"
#include "../Models/NPC.h"
#include "../Utilities/Utils.h"

template<typename T>
class AbsLoot
{
public: 
	AbsLoot()
		:entities_{}
		, maxSize_{5}
	{};
	~AbsLoot()
	{
		entities_.clear();
	}
	T getEntity(const std::string& name, bool toDelete = false);

	T getEntity(int i, bool toDelete = false);

	//check if full
	bool isFull();

	//add entity
	void addEntity(T some);

	//just print list of what you have
	void printInfo();

	//check if empty
	bool isEmpty();

	//get all entities
	std::vector<T> getEntities();

	//get list of names
	std::vector<std::string> getEntitiesNames();

	void deleteEntity(int i);
	void deleteEntity(const std::string& name);
	
protected:
	std::vector<T> entities_;
	int maxSize_;
};

using Inventory = AbsLoot<Item*>;

using SquadBase = AbsLoot<NPC*>;

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
inline std::vector<T> AbsLoot<T>::getEntities()
{
	return entities_;
}


template<typename T>
inline void AbsLoot<T>::deleteEntity(int i)
{
	entities_.erase(i + entities_.begin());
}

template<typename T>
inline void AbsLoot<T>::deleteEntity(const std::string& name)
{
	int i = -1;
	for (auto it = entities_.begin(); it != entities_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName())) {
			i = static_cast<int>(it - entities_.begin());
			break;
		}
	}
	if (i != -1)
	{
		entities_.erase(i + entities_.begin());
	}

}

template<typename T>
inline std::vector<std::string> AbsLoot<T>::getEntitiesNames()
{
	std::vector<std::string> names;

	std::transform(entities_.begin(), entities_.end(), std::back_inserter(names),
		[](T const& entity) { return entity->getName(); });

	return names;

}

template<typename T>
inline T AbsLoot<T>::getEntity(const std::string& name, bool toDelete)
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
		return nullptr;

	if (toDelete)
	{
		deleteEntity(index);
	}

	return entities_[index];
}


template<typename T>
inline T AbsLoot<T>::getEntity(int i, bool toDelete)
{
	if (toDelete)
	{
		deleteEntity(i);
	}
	return entities_[i];
}

class Squad : public SquadBase
{
	using SquadBase::SquadBase;

public:
	int getOverallDamage();
};

#endif // !_STORE_