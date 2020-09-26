#pragma once
#include<iostream>
#include <string>
#include<iomanip>
#include<fstream>
#include "ErrorTS.h"
using namespace std;

class StatisticsElem {
	string login;
	string testCategory;
	string testName;
	int testSize = 0;
	double maxMark = 0;
	double getingMark = 0;
	double mark = 0;
	int cntCorrectQw = 0;
	int cntIncorrectQw = 0;
	int cntMissedQw = 0; // оличество пропущенных вопросов
	int NoLast = 0; //если номер последнего вопроса != testSize тест незакончен
	long id = -1;
public:
	StatisticsElem(){}
	StatisticsElem(string testCategory, string testName, int testSize, double maxMark, double getMark, int cntCorrectQw, int cntIncorrectQw, int cntMissedQw, int NoLast):
	testCategory(testCategory), testName(testName), testSize(testSize), maxMark(maxMark), getingMark(getMark), cntCorrectQw(cntCorrectQw), cntIncorrectQw(cntIncorrectQw), cntMissedQw(cntMissedQw), NoLast(NoLast){
		this->mark = round(12 * getMark / maxMark);
	}
	
	void setLogin(string login) { this->login = login; }
	void setTestCategory(string testCategory) { this->testCategory = testCategory; }
	void setTestName(string testName) { this->testName = testName; }
	void setTestSize(int testSize) { this->testSize = testSize; }
	void setMaxMark(double maxMark) { this->maxMark = maxMark; }
	void setGetingMark(double getMark) { this->getingMark = getMark; }
	void setCntCorrectQw(int cntCorrectQw) { this->cntCorrectQw = cntCorrectQw; }
	void setCntIncorrectQw(int cntIncorrectQw) { this->cntIncorrectQw = cntIncorrectQw; }
	void setCntMissedQw(int cntMissedQw) { this->cntMissedQw = cntMissedQw; }
	void setNoLast(int NoLast) { this->NoLast = NoLast; }
	void setMark(double mark) { this->mark = mark; }
	void setId(long id) { this->id = id; }

	string getLogin() { return this->login; }
	string getTestCategory() { return this->testCategory; }
	string getTestName() { return this->testName; }
	int getTestSize() { return this->testSize; }
	double getMaxMark() { return this->maxMark; }
	double getGetingMark() { return this->getingMark; }
	int getCntCorrectQw() { return this->cntCorrectQw; }
	int getCntIncorrectQw() { return this->cntIncorrectQw ; }
	int getCntMissedQw() { return this->cntMissedQw; }
	int getNoLast() { return this->NoLast; }
	double getMark() { return this->mark; }
	long getId() { return this->id; }
	
	bool isFinished() { return (this->testSize-1) == this->NoLast; }	
	
	StatisticsElem* operator+(StatisticsElem *stElem) {
		if (this->testCategory != stElem->testCategory || this->testName != stElem->testName
			|| this->testSize != stElem->testSize || this->maxMark != stElem->maxMark)
			throw StatisticsError("Ќельз€ изменить результаты статистики");
		this->getingMark += stElem->getingMark;
		this->cntCorrectQw += stElem->cntCorrectQw;
		this->cntIncorrectQw += stElem->cntIncorrectQw;
		this->cntMissedQw += stElem->cntMissedQw;
		this->NoLast = stElem->NoLast;
		this->mark =round( (12 * this->getingMark) / this->maxMark);
		if(stElem->id> this->id) this->id = stElem->id;
		return this;

	}
	void print() {
		cout << "ѕользователь: " << login << ", тест: \"" << testName << "\" (" << testCategory << "), кол-во вопросов: " << testSize << ", макс. баллов:" << maxMark<< "."<< endl;
		cout << setw(13) << "ѕолучено баллов:" << getingMark <<", оценка:"<<mark<< ", кол-во правил.ответов:" << cntCorrectQw << ", кол-во пропущенных вопросов:" << cntMissedQw << "." << endl;
	}

	void saveToFile(ofstream &out) {
		out << login << endl;
		out << testCategory << endl;
		out << testName << endl;
		out << testSize << " " << maxMark << " " << getingMark << " " << mark << " " << cntCorrectQw << " " << cntIncorrectQw << " " << cntMissedQw << " " << NoLast << endl;

	}
	void loadFromFile(ifstream& inp) {
		getline(inp,login);
		getline(inp, testCategory);
		getline(inp, testName);
		inp >> testSize >> maxMark >> getingMark >> mark >> cntCorrectQw >> cntIncorrectQw >> cntMissedQw >> NoLast;
		inp.ignore(2, '\n');		
	}
	~StatisticsElem(){}
};
