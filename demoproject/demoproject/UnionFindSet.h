#pragma once
#include<vector>
#include<map>
class UnionFindSet {
	std::vector<int> Parents;
	std::vector<int> Ranks;
	int find(const int& n)
	{
		if (Parents[n] != n) Parents[n] = find(Parents[n]);
		return Parents[n];
	}
public:

	UnionFindSet(int _capacity) {
		Parents.reserve(_capacity);
		for (int i = 0; i < _capacity; i++) Parents.push_back(i);
		Ranks.assign(_capacity, 1);
	}

	bool merge(int a, int b)
	{
		int pa = Parents[a], pb = Parents[b];
		if (pa == pb) return false;
		if (Ranks[pa] < Ranks[pb]) Parents[pa] = pb;
		else {
			Parents[pb] = pa;
			if (Ranks[pa] == Ranks[pb]) Ranks[pa]++;
		}
		return true;
	}

	bool inSameSet(int a, int b) { return find(a) == find(b); }

	std::map<int, std::vector<int>> getUnionSets()
	{
		std::map<int, std::vector<int>> group;
		for (int i = 0; i < Parents.size(); i++) group[Parents[i]].push_back(i);
		return group;
	}
};