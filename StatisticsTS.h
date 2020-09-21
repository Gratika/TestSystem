#pragma once
#include<iostream>
#include <string>
#include<iomanip>
#include<fstream>
#include<vector>
#include "ErrorTS.h"
#include"StatisticsElem.h"
using namespace std;
class StatisticsTS {
	vector<StatisticsElem*> data;
public:
	
	StatisticsTS() {
		loadFromFile();
	}
	
	void loadFromFile() {
		ifstream inp("StatisticsTS.txt");
		if (inp.is_open()) {
			int cntRec;
			inp >> cntRec;
			inp.ignore(2, '\n');
			for (int i = 0; i < cntRec; i++) {
				StatisticsElem* el = new StatisticsElem();
				el->loadFromFile(inp);
				el->setId(i);
				data.push_back(el);
			}
			inp.close();
		}
	}

	bool isEmpty(){	return data.empty();}

	void add(StatisticsElem* el) {
		if(el->getId()==-1){
			el->setId(data.size());
			data.push_back(el);
		}
		else replace(el);
		
	}
	void replace(StatisticsElem* el) {
		StatisticsElem* tmp = data[el->getId()];
		if (tmp != el) {
			data[el->getId()] = el;
			delete tmp;
		}		
	}

	StatisticsElem* findUserStatistic(string login) {
		for (auto el : data) {
			if (el->getLogin() == login)
				el->print();
			cout << endl;
		}
	}

	StatisticsElem* findTestStatistic(string testName) {
		for (auto el : data) {
			if (el->getTestName() == testName)
				el->print();
			cout << endl;
		}
	}

	StatisticsElem* findTestStatisticForUser(string login,string testName, string testCategory) {
		StatisticsElem* findStat = nullptr;
		for (auto el : data) {
			if (el->getLogin() == login && el->getTestName() == testName && el->getTestCategory() ==testCategory)
				findStat = el;			
		}
		return findStat;
	}


	StatisticsElem* findTestCategoryStatistic(string testCategory) {
		for (auto el : data) {
			if (el->getTestCategory() == testCategory)
				el->print();
			cout << endl;
		}
	}

	void saveToFile() {
		ofstream out("StatisticsTS.txt");
		out << data.size() << endl;
		for (auto el : data)
			el->saveToFile(out);
		out.close();
	}

	~StatisticsTS(){
	}
};
