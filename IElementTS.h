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
	IElementTS* parent=nullptr;
public:
	IElementTS() {}
	void setParent(IElementTS* p) { this->parent = p; }
	IElementTS* getParent() { return this->parent; }
	virtual string getName() { return this->name; }
	string getType() { return this->elType; }
	virtual int getSize() = 0;
	virtual bool isComposite() { return false; }
	virtual void setParam(string name, int No = 0) {
		this->name = name;		
	}
	virtual void loadFromFile(ObjectFactory<IElementTS> *&f) {}
	virtual void saveToFile(){}	
	virtual void add(IElementTS* elem){}
	virtual void remove(int id){}	
	virtual void print() {
		cout << name << endl;
	}
	virtual IElementTS* getElement(int id) = 0;
	virtual void show() {
		this->print();
	}
	virtual ~IElementTS()=0 {}
protected:
	string getFilename() {
		return this->name + ".txt";
	}
};
class Leaf : public IElementTS {
public:
	int getSize()override {
		return 0;
	}
	IElementTS* getElement(int id)override {
		return nullptr;
	}

};

class ConteinerTS :public IElementTS {
protected:
	vector<IElementTS*> elements;
public:
	ConteinerTS() {}	
	
	void add(IElementTS* elem) override {
		this->elements.push_back(elem);
		elem->setParent(this);
	}
	
	/*virtual void print() override {
		int id = 1;
		cout << this->name << endl;
		for (auto i : elements) {
			cout << id << " ";
			i->print();
			id++;
		}
			
	}*/
	virtual void show() override {		
		for (int i = 0; i < this->elements.size(); i++) {
			cout << i+1 << " ";
			this->elements[i]->print();			
		}

	}
	
	void remove(int id) override {
		this->elements.erase(elements.begin()+id);
	}

	int getSize()override {
		return this->elements.size();
	}
	IElementTS* getElement(int id)override {
		if (id<0 || id>this->elements.size()) throw OutOfRangeError("����� �� ������� ����������� ���������");
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
			el->loadFromFile(f);
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
		for (IElementTS* el : this->elements) {
			el->saveToFile();
		}
	}
	virtual ~ConteinerTS() {
		this->elements.~vector();
	}

};

class TestCategoryTS: public ConteinerTS {
public:
	TestCategoryTS(){
		this->elType = "TestCategoryTS";
	}
	
	/*void loadFromFile(ObjectFactory<IElementTS> *&f)override {
		string fileName = this->getFilename() ,elName, elType;
		ifstream inp(fileName);
		if (inp.is_open()) {
			int cnt;
			inp >> cnt; inp.ignore(2,'\n');
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
	}*/
	/*void saveToFile()override {
		string fileName = this->getFilename();
		ofstream out(fileName);
		out << this -> getSize()<<endl;
		for (auto i : this->elements) {
			out << i->getType() << endl;
			out << i->getName() << endl;			
		}
		out.close();
	}*/
};

class TestTS : public ConteinerTS {
public:
	TestTS() {
		this->elType = "TestTS";
	}

	void loadFromFile(ObjectFactory<IElementTS> *&f)override {
		string fileName = this->getFilename(), elName, elType;
		int cntAnsw;
		ifstream inp(fileName);
		if (inp.is_open()) {
			while (!inp.eof()) {
				getline(inp, elType);
				getline(inp, elName);				
				IElementTS* qw = f->create(elType);
				qw->setParam(elName);
				inp >> cntAnsw; inp.ignore('\n');
				for (int i = 0; i < cntAnsw; i++) {
					getline(inp, elType);
					getline(inp, elName);
					IElementTS* answ = f->create(elType);
					answ->setParam(elName);
					qw->add(answ);
				}
				this->add(qw);
			}
			inp.close();
		}
	}
	void saveToFile()override {
		string fileName = this->getFilename();
		ofstream out(fileName);
		for (auto i : this->elements) {
			out << i->getType() << endl;
			out << i->getName() << endl;
			out << i->getSize() << endl;			
			for (int j = 0; j < i->getSize(); j++) {
				IElementTS* answ = i->getElement(j);
				out << answ->getType() << endl;
				out << answ->getName() << endl;
			}			
		}
		out.close();
	}
	void print()override {
		cout << name <<" (����)"<< endl;
	}

	/*void show()override {
		this->loadFromFile();
	}*/
};

class QuestionTS : public ConteinerTS {
private: int number;
public:
	QuestionTS() {
		this->elType = "QuestionTS";
	}
	void setParam(string name, int No=0)override {
		IElementTS::setParam(name);
		this->number = No;
	}
	void print()override{
		cout << number << " " << this->name;
	}
	/*void show()override {
		
		for (IElementTS* el : this->elements) {
			el->show();
		}
	}*/
};

class AnswerTS : public Leaf {
	bool isCorect = false;
    int number;
public:
	AnswerTS(){
		this->elType = "AnswerTS";
	}
	void setParam(string name, int No = 0)override {
		char c = name[0];
		if (c == '+') this->isCorect = true;
		name.erase(0);
		IElementTS::setParam(name);
		this->number = No;

	}
	string getName()override {
		if (this->isCorect)	return "+" + this->name;
		else return "-" + this->name;
	}
	void print()override {
		cout << number << " " << this->name;
	}

	
};




