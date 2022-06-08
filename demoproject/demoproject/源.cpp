#include<iostream>
#include<vector>
#include<map>
#include<functional>
#include"ListQueue.h"
#include"listStack.h"
#include"LRU.h"
#include"IOC.h"
using namespace std;

int maxSumSubMatrix(const vector<vector<int>>& matrix)
{
	int row = matrix.size();
	int col = matrix[0].size();
	int leftTopRow, leftTopCol, rightBottonRow, rightBottonCol;
	int sum = 0, maxsum = INT_MIN;
	auto colsums = vector<int>(col, 0);
	int tmprow, tmpcol;
	for (int strow = 0; strow < row; strow++)
	{
		colsums.assign(col, 0);
		for (int edrow = strow; edrow < row; edrow++)
		{
			sum = 0;
			for (int i = 0; i < col; i++)
			{
				colsums[i] += matrix[edrow][i];
				if (sum > 0) sum += colsums[i];
				else {
					tmprow = strow;
					tmpcol = i;
					sum = colsums[i];
				}
				if (sum > maxsum)
				{
					maxsum = sum;
					leftTopRow = tmprow;
					leftTopCol = tmpcol;
					rightBottonRow = edrow;
					rightBottonCol = i;
				}
			}
		}
	}
	int ans = 0;
	for (int i = leftTopRow; i <= rightBottonRow; i++)
		for (int j = leftTopCol; j <= rightBottonCol; j++) ans += matrix[i][j];
	return ans;

}

int maxSumSubVec(const vector<int>& vec)
{
	int n = vec.size();
	auto sums = vector<int>(n, 0);
	int sum = 0;
	int max = INT_MIN;
	int st, ed;
	for (int i = 0; i < n; i++)
	{
		if (sum > 0) sum += vec[i];
		else {
			st = i;
			sum = vec[i];
		}
		if (sum > max)
		{
			max = sum;
			ed = i;
		}
	}
	int ans = 0;
	while (st <= ed) ans += vec[st++];
	return ans;
}

class UnionSet {
	vector<int> m_parents;
	vector<int> m_ranks;
	map<int, vector<int>> setMap;
public:
	explicit UnionSet(const int& n) {
		m_parents.reserve(n);
		m_ranks.reserve(n);
		for (int i = 0; i < n; i++) {
			m_parents.push_back(i);
			m_ranks.push_back(1);
		}
	}

	int find(int item) {
		if (m_parents[item] != item)
			m_parents[item] = find(m_parents[item]);
		return m_parents[item];
	}

	bool merge(int a, int b)
	{
		int pa = find(a), pb = find(b);
		if (pa == pb) return false;
		if (m_ranks[pa] < m_ranks[pb]) 		m_parents[pa] = pb;
		else {
			m_parents[pb] = pa;
			if (m_ranks[pa] == m_ranks[pb]) m_ranks[pa] += 1;
		}
		return true;
	}

	map<int, vector<int>> getSets()
	{
		if (setMap.empty()) {
			for (int i = 0; i < m_parents.size(); i++)
				setMap[find(m_parents[i])].push_back(i);
		}
		return setMap;
	}
};

string eraseSame(const string& str) {
	vector<char> stack;
	for (const char& c : str)
	{
		if (!stack.empty() && stack.back() == c) stack.pop_back();
		else stack.push_back(c);
	}
	return string(stack.begin(), stack.end());
}

int main() {

	vector<vector<int>> matrix{
		{-3, 5,-1,5},{2,4,-2,4},{-1,3,-1,3}
	};
	std::cout << maxSumSubMatrix(matrix)<<endl;


	//string color = "brbryy";
	//string number = "324332";
	//UnionSet myset(color.size());
	//for (int i = 0; i < color.size(); i++)
	//{
	//	for (int j = i + 1; j < color.size(); j++)
	//		if (color[i] == color[j] || number[i] == number[j]) myset.merge(i, j);
	//}
	//auto ans = myset.getSets();
	//for (auto& x : ans) {
	//	for (auto& item : x.second) 	cout << item << " ";
	//	cout << "\n";
	//}
	//cout << eraseSame("abcddcba");

	Ioc<A> ioc;

	ioc.registerType<B>("B");
	ioc.registerType<C>("C");

	auto b = ioc.getInstance("B");
	auto c = ioc.getInstance("C");

	b->run();
	c->run();

	ListQueue<int> queue;
	ListStack<int> skt;


	for (int i = 0; i < 5; i++) {

		queue.push(i);
		skt.push(i);
	}

	while (queue.size()!=0) { 
		cout << queue.top() << " ";
		queue.pop(); 
	}
	cout << "\n";
	while (skt.size() != 0) {
		cout << skt.top() << " ";
		skt.pop();
	}
	return 0;
}

int maxsubmatrix(const vector<vector<int>>& nums)
{
	if (nums.empty()) return 0;
	int row = nums.size(), col = nums[0].size();
	int ltrow, ltcol, rbrow, rbcol, tmprow,tmpcol;
	int sum=0, max=-999999;
	vector<int> sums;
	for (int strow = 0; strow < row; strow++)
	{
		sums.assign(col, 0);
		for (int edrow = strow; edrow < row; edrow++)
		{

			for (int stcol = 0; stcol < col; stcol++)
			{
				sums[stcol] += nums[edrow][stcol];
				if (sum > 0) {
					sum += sums[stcol];
				}
				else {
					sum = sums[stcol];
					tmprow = edrow;
					tmpcol = stcol;
				}
				if (sum > max) {
					max = sum;
					rbrow = edrow;
					rbcol = stcol;
					ltrow = tmprow;
					ltcol = tmpcol;
				}
			}
		}
	}
}