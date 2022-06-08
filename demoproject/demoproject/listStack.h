#pragma once
#include<memory>
#include<stdexcept>

template<class T>
class ListStack {
	struct ListNode
	{
		T val;
		ListNode* next;
		ListNode(int n) :val(n), next(nullptr) {};
	};
	int _size;
	ListNode* head;
public:
	ListStack() {
		_size = 0;
	}
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
		node->next = head;
		head = node;
		_size++;
	}
	int size() { return _size; }
};
