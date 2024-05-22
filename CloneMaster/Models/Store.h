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
	//get index of entity
	int getEntityByName(const std::string& name);
	//get entity by index
	T getEntity(int i);
	//check if full
	bool isFull();
	//add entity
	void addEntity(T some);
	//just print list of what you have
	void printInfo();
	//check if empty
	bool isEmpty();
	//delete
	void dispose();
	//get all entities
	std::vector<T> getEntities();
	//get list of names
	std::vector<std::string> getEntitiesNames();
	//get entity clue
	void getEntityClue(int i);
private:
	std::vector<T> entities_;
	int maxSize_ = 6;
};

using Inventory = AbsLoot<Item*>;

using Squad = AbsLoot<Character*>;

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

template<typename T>
inline std::vector<std::string> AbsLoot<T>::getEntitiesNames()
{
	std::vector<std::string> names;

	std::transform(entities_.begin(), entities_.end(), std::back_inserter(names),
		[](T const& entity) { return entity->getName(); });

	return names;

}

template<typename T>
inline void AbsLoot<T>::getEntityClue(int i)
{
	std::cout << entities_[i]->getClue() << std::endl;
}

template<typename T>
inline int AbsLoot<T>::getEntityByName(const std::string& name)
{
	int index = -1;
	for (auto it = entities_.begin(); it != entities_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName())) {
			index = static_cast<int>(it - entities_.begin());
			break;
		}
	}

	return index;
}

template<typename T>
inline T AbsLoot<T>::getEntity(int i)
{
	T entityPtr = entities_[i];
	entities_.erase(i + entities_.begin());
	return entityPtr;
}

#endif // !_STORE_