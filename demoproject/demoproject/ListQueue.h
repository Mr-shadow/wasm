#pragma once
#include<memory>
#include<stdexcept>
template<class T>
class ListQueue {
	struct ListNode
	{
		T val;
		ListNode* next;
		ListNode() :val(T()), next(nullptr) {};
		ListNode(int n) :val(n), next(nullptr) {};
	};
	int _size;
	ListNode* head;
	ListNode* cur;

public:
	ListQueue() :head(nullptr), cur(nullptr),_size(0) {};

	T top() { 
		return head->val;
	}

	void pop() {
		if (head == nullptr) return;
		ListNode* tmp = head;
		head = head->next;
		delete tmp;
		_size--;
	}

	void push(const T& val)
	{
		ListNode* node = new ListNode(val);
		if (cur == nullptr)
		{
			cur = head = node;
		}
		else {
			cur->next = node;
			cur = node;
		}
		_size++;

	}
	int size() { return _size; }
};
