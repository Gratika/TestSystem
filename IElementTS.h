#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<Windows.h>
#include <vector>
#include "ObjectFactory.h"
#include"ErrorTS.h"
#include<iomanip>
using namespace std;

class IElementTS {
protected:
	string name;
	string elType;
	IElementTS* parent = nullptr;
	int level = 0;
public:
	IElementTS() {}
	void setParent(IElementTS* p) { this->parent = p; }
	IElementTS* getParent() { return this->parent; }
	virtual string getName() { return this->name; }
	string getType() { return this->elType; }
	virtual int getSize() { return 0; };	
	virtual void setLevel(int lvl) { this->level = lvl; }
	virtual int getLevel() { return this->level; }
	virtual bool isComposite() { return false; }
	virtual void setParam(string name) {
		this->name = name;
	}
	virtual void loadFromFile(ObjectFactory<IElementTS>*& f) {}
	virtual void saveToFile() {}
	virtual void add(IElementTS* elem) {}
	virtual void remove(int id) {}
	virtual void print() {cout << name << endl;}
	virtual void show() {}
	virtual IElementTS* getElement(int id) {return nullptr;	}

	virtual ~IElementTS() = 0 {}
protected:
	string getFilename() {
		return this->name + ".txt";
	}
};

class Leaf : public IElementTS {
public:
	void print()override {
		cout << name<<" (тест)" << endl;
	}	
	Leaf(){}
	~Leaf(){}
};

class ConteinerTS :public IElementTS {
protected:
	vector<IElementTS*> elements;
public:
	ConteinerTS() {}

	void add(IElementTS* elem) override {
		this->elements.push_back(elem);
		elem->setParent(this);
		elem->setLevel(this->getLevel() + 1);
	}	

	void print()override {
		if (this->parent != nullptr) cout << name << endl;		
		for (int i = 0; i < this->elements.size(); i++) {
			int l = this->elements[i]->getLevel();
			cout << setw(4 * (l-1)) /*<< i + 1 */<< " ";
			elements[i]->print();
		}		
	}
	
	virtual void show() override {	
		string tname = " (тест)";		
		for (int i = 0; i < this->elements.size(); i++) {			
			cout << i + 1 << " "<<this->elements[i]->getName();
			if (!this->elements[i]->isComposite()) cout << tname;
			cout << endl;
		}

	}

	void remove(int id) override {
		if (id<0 || id>this->elements.size()) throw OutOfRangeError("¬ыход за пределы допустимого диапазона");
		this->elements.erase(elements.begin() + id);
	}

	int getSize()override {
		return this->elements.size();
	}
	IElementTS* getElement(int id)override {
		if (id<0 || id>=this->elements.size()) throw OutOfRangeError("¬ыход за пределы допустимого диапазона");
		return elements[id];
	}

	bool isComposite()override { return true; }

	void loadFromFile(ObjectFactory<IElementTS>*& f)override {
		string fileName = this->getFilename(), elName, elType;
		ifstream inp(fileName);
		if (inp.is_open()) {
			int cnt;
			inp >> cnt; inp.ignore(2, '\n');
			for (int i = 0; i < cnt; i++) {
				getline(inp, elType);
				getline(inp, elName);
				try {
					IElementTS* elem = f->create(elType);
					elem->setParam(elName);
					this->add(elem);
				}
				catch (ObjectCreatorError err) {
					cout << err.getError();
				}
			}
			inp.close();
		}
		for (IElementTS* el : this->elements) {
			if (el->getType() == "TestCategoryTS")el->loadFromFile(f);
		}
	}

	void saveToFile()override {
		string fileName = this->getFilename();
		ofstream out(fileName);
		out << this->getSize() << endl;
		for (auto i : this->elements) {
			out << i->getType() << endl;
			out << i->getName() << endl;
		}
		out.close();
		
	}
	virtual ~ConteinerTS() {
		this->elements.~vector();
	}

};

class TestCategoryTS : public ConteinerTS {
public:
	TestCategoryTS() {
		this->elType = "TestCategoryTS";
	}
	~TestCategoryTS(){}

};

class TestTS :public Leaf {
public:
	TestTS() {
		this->elType = "TestTS";
	}
};






