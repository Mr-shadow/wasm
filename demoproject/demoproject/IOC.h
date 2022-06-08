#pragma once
#include<functional>
#include<string>
#include<map>
#include<memory>
#include<iostream>

using namespace std;
template<class T>
class Ioc {
	using ObjectType = function<T* ()>;
	map<std::string, ObjectType> objMap;

public:

	template<class T_Child>
	bool registerType(const string& key)
	{
		if (objMap.find(key) != objMap.end()) throw(runtime_error("this type has exist!"));
		ObjectType obj = []() {return new T_Child(); };
		objMap[key] = obj;
		return true;
	}

	shared_ptr<T> getInstance(const string& key)
	{
		auto iter = objMap.find(key);
		if (iter == objMap.end()) throw(runtime_error("this type has not regist!"));
		return  shared_ptr<T>(iter->second());
	}
};


class A {
public:
	A() { cout << "A build\n"; }
	virtual ~A() { cout << "A delete\n"; }
	virtual void run() { cout << " A run!\n"; }
};

class C : public A {
public:
	C() { cout << "C build\n"; }
	~C() { cout << "C delete\n"; }
	void run() { cout << "C run\n"; }
};

class B : public A {
public:
	B() { cout << "B build\n"; }
	~B() { cout << "B delete\n"; }
	void run() { cout << "B run\n"; }
};

