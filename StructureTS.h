#pragma once
//#include <iostream>
//#include <fstream>
#include<string>
#include<Windows.h>
#include <vector>
#include "ObjectFactory.h"
#include"IElementTS.h"
//#include<iomanip>
using namespace std;
class StructureTS {
	ObjectFactory<IElementTS>* efactory = nullptr;
	IElementTS *rootCategory=nullptr;
public:
	StructureTS() {
		efactory = new ObjectFactory<IElementTS>();
		efactory->add("TestCategoryTS", new ObjectCreator< TestCategoryTS, IElementTS>);
		efactory->add("TestTS", new ObjectCreator< TestTS, IElementTS>);
		efactory->add("QuestionTS", new ObjectCreator< QuestionTS, IElementTS>);
		efactory->add("AnswerTS", new ObjectCreator< AnswerTS, IElementTS>);
		rootCategory = new TestCategoryTS();
		rootCategory->setParam("rootCategory");
		rootCategory->loadFromFile(efactory);
	}
	void print() {
		rootCategory->print();
	}

	void saveToFile() {
		rootCategory->saveToFile();
	}
};