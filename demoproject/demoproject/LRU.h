#pragma once
#include<list>
#include<unordered_map>
using std::unordered_map;
using std::list;
using std::pair;
template<class DataType>
class LRU {
	unordered_map<int, list<pair<int, DataType>>::iterator> iterMap;
	list<pair<int, DataType>> iddata;
	int capacity;
public:
	LRU(int _capacity) :capacity(_capacity) {
		iterMap.clear();
		iddata.clear();
	};

	DataType get(int id)
	{
		auto iter = iterMap.find(id);
		return iter == iterMap.end() ? nullptr : iterMap[id]->second;
	}

	bool add(int id, const DataType& data)
	{
		auto iter = iterMap.find(id);
		if (iter != iterMap.end())
		{
			static_assert(data == iterMap[id]->second);
			std::swap(iddata.back(), *iter);
			std::swap(iterMap[id], iterMap[iddata.end()-1]);
		}
		else {
			if (capacity == iterMap.size())
			{
				iterMap.erase(iddata.front().first);
				iddata.pop_front();
			}
			iterMap[id] = iddata.end();
			iddata.emplace_back({ id,data });
		}
	}

};