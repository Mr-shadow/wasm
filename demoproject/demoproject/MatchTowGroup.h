#pragma once
#include<vector>
#include<cmath>
using std::vector;
class MatchTwoGroup {
	vector<int> group1, group2;
	vector<int> matching, matched;

	bool matchable(int a, int b) // ºÍÊÇËØÊý
	{
		int sum = a + b;
		if (sum < 3) return true;
		if (sum % 6 != 5 && sum % 6 != 1) return false;
		for (int i = 3; i * i < sum; i++)
			if (sum % i == 0) return false;
		return true;
	}

	bool match(int item)
	{
		for (int i = 0; i < group2.size(); i++)
		{
			if (!matchable(item, group2[i]) || matching[i] != -1) continue;
			matching[i] = item;
			if (matched[i] == -1 || match(matched[i]))
			{
				matched[i] = item;
				return true;
			}

		}
		return false;
	}
public:
	MatchTwoGroup(const vector<int>& groupFirst, const vector<int>& groupSecond)
	{
		if (groupFirst.size() > groupSecond.size()) {
			group1.assign(groupSecond.begin(), groupSecond.end());
			group2.assign(groupFirst.begin(), groupFirst.end());
			matching = vector<int>(groupFirst.size(), -1);
			matched = vector<int>(groupFirst.size(), -1);
		}
		else {
			group1.assign(groupFirst.begin(), groupFirst.end());
			group2.assign(groupSecond.begin(), groupSecond.end());
			matching = vector<int>(groupSecond.size(), -1);
			matched= vector<int>(groupSecond.size(), -1);
		}
	}

	int getMaxPairNum() {
		int pairNum = 0;
		for (const int& item : group1)
		{
			matching.assign(group2.size(),-1);
			if (match(item)) pairNum++;
		}
		return pairNum;
	}
};
