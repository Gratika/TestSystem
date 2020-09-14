#pragma once
#include "SystemUser.h"
#include <map>
#include <string>
#include"ErrorTS.h"


template<class Base>
class AbstractObjectCreator {
public:
	AbstractObjectCreator(){}
	virtual ~AbstractObjectCreator(){}
	virtual Base* create() = 0;

};


template<class T, class Base>
class ObjectCreator:public AbstractObjectCreator<Base> {
public:
	ObjectCreator(){}
	virtual ~ObjectCreator(){}
	Base* create() override {
		return new T;
	}

};

template<class Base>
class ObjectFactory {
	std::map<string, AbstractObjectCreator<Base>*> ufactory;
public:
	ObjectFactory(){}
	~ObjectFactory(){}
	
	void add(const string creatorId, AbstractObjectCreator<Base>* ucreator) {
		auto rec = ufactory.find(creatorId);
		if (rec == ufactory.end())
			ufactory[creatorId] = ucreator;
	}

	Base* create(string creatorId) {
		auto rec = ufactory.find(creatorId);
		if (rec == ufactory.end()) throw ObjectCreatorError("Не могу создать объект " + creatorId);
		return rec->second->create();
	}

};
