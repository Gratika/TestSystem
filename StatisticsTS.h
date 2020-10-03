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
		data.erase(data.begin()+el->getId());
		data.insert(data.begin() + el->getId(), el);		
	}

	void findUserStatistic(string login) {
		bool flag = false;
		for (auto el : data) {
			if (el->getLogin() == login){
				el->print();
				flag = true;
			}
			cout << endl;
		}
		if (!flag) cout << "\nК сожалению, мы ничего не нашли..." << endl;
	}

	void findTestStatistic(string testName) {
		bool flag = false;
		for (auto el : data) {
			if (el->getTestName() == testName){
				el->print();
				flag = true;
			}
			cout << endl;
		}
		if (!flag) cout << "\nК сожалению, мы ничего не нашли..." << endl;
	}

	StatisticsElem* findTestStatisticForUser(string login,string testName, string testCategory) {
		StatisticsElem* findStat = nullptr;
		for (auto el : data) {
			if (el->getLogin() == login && el->getTestName() == testName && el->getTestCategory() ==testCategory)
				findStat = el;			
		}
		return findStat;
	}


	void findTestCategoryStatistic(string testCategory) {
		bool flag = false;
		for (auto el : data) {
			if (el->getTestCategory() == testCategory) {
				el->print();
				flag = true;
			}
			cout << endl;
		}
		if (!flag) cout << "\nК сожалению, мы ничего не нашли..." << endl;
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
