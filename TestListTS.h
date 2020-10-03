#pragma once
#include <iostream>
#include<fstream>
#include <vector>
#include<string>
#include"QuestionTS.h"
#include"MyFunction.h"
#include"ErrorTS.h"
#include"StatisticsElem.h"
using namespace std;

class TestListTS {
	string name;
	string fileName;
	vector<QuestionTS*> questions;
public:
	TestListTS(string name) {
		this->name = name;
		fileName = this->name + ".txt";
	}

	void loadFromFile() {
		int cntQw;
		ifstream inp(fileName);
		if (!inp.is_open()) throw FileError(fileName, "������ ����� ������ ���!");
		inp >> cntQw; inp.ignore(2, '\n');
		for (int j = 0; j < cntQw; j++) {
			QuestionTS* qwst = new QuestionTS();
			qwst->loadFromFile(inp);
			questions.push_back(qwst);
		}
		inp.close();
	}

	void saveToFile() {
		ofstream out(fileName);
		out << questions.size() << endl;
		for (auto i : this->questions) {
			i->saveToFile(out);
		}
		out.close();
	}

	void print(bool withCorrect = false) {
		for (int i = 0; i < this->questions.size(); i++) {
			cout << i + 1 << " ";
			questions[i]->print(withCorrect);
		}
	}

	void addQuestion() {
		QuestionTS* newQw = new QuestionTS();
		cin >> newQw;
		questions.push_back(newQw);
	}

	void deleteQw(int id) {
		questions.erase(questions.begin() + id);
	}

	//�������� ��������� �����
	void showTest() {
		loadFromFile();
		system("cls");
		cout << "�������� ����������� �����" << endl;
		cout << "-------------------------------------\n" << endl;
		cout << "���� \"" << name << "\"" << endl;
		print(true);
		char actn = '�';
		cout << "������ ������ ��������� � ����?(�/�): ";
		cin >> actn;
		cin.ignore(2, '\n');
		if (actn == '�') {
			try {
				editTest();
				cout << "��������� ��������� ���������?(�/�): ";
				cin >> actn; cin.ignore(2, '\n');
				if (actn == '�') saveToFile();
			}
			catch (ErrorTS err) {
				cout << "������! " << err.getError() << endl;
			}
		}
		system("pause");
	}

	//�������������� ����������� �����
	void editTest() {
		char actn = '�';
		do {
			system("cls");
			cout << "�������������� ����� " << "\"" << name << "\"" << endl;
			cout << "-------------------------------------\n" << endl;
			char ch;
			cout << "��� ����� ������?\n1-�������� ������;\n2-�������� ������\n3-������� ������" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			int No;
			switch (ch)
			{
			case '1':
				addQuestion();
				break;
			case '2':
				cout << "����� ������ ����� ������? ";
				No = getValue();
				if (No - 1 < 0 || No - 1 >= questions.size()) throw OutOfRangeError("������� � ����� ������� �� ����������!");
				questions[No - 1]->edit();
				break;
			case '3':
				cout << "����� ������ ����� �������? ";
				No = getValue();
				if (No - 1 < 0 || No - 1 >= questions.size()) throw OutOfRangeError("������� � ����� ������� �� ����������!");
				deleteQw(No - 1);
				break;
			default:
				cout << "��������� ����..." << endl;
				break;
			}
			cout << "������ ���������� �������������� �����?(�/�): ";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == '�');		
	}

	//������ ������������
	StatisticsElem* beginTesting(StatisticsElem* bgnStEl, string ctgrName) {
		loadFromFile();
		int beginNo = 0; int id = -1;
		if (bgnStEl != nullptr && !bgnStEl->isFinished()) {
			cout << "�� ������������ �� ������� �" << (bgnStEl->getNoLast()) + 1 << ". ���������� ����������� �����(�) ��� ������ �������(�)?" << endl;
			char ch;
			cin >> ch;
			cin.ignore(3200, '\n');
			if (ch == '�') beginNo = bgnStEl->getNoLast();
			else {
				id = bgnStEl->getId();
				bgnStEl = nullptr;
			}
		}
		StatisticsElem* rezTest = doTesting(beginNo, ctgrName);
		if (bgnStEl == nullptr) {
			if (id != -1) rezTest->setId(id);
			return rezTest;
		}
		else {
			if (bgnStEl->isFinished()) {

				if (rezTest->getGetingMark() > bgnStEl->getGetingMark()) return rezTest;
				else {
					if (rezTest != nullptr)delete rezTest;
					return bgnStEl;
				}
			}
			else {
				StatisticsElem* rez = bgnStEl->operator+(rezTest);
				if (rezTest != nullptr)delete rezTest;
				return (rez);

			}
		}
	}


	StatisticsElem* doTesting(int beginNo, string ctgrName) {

		double getMark = 0, maxMark = getMaxCost();//���������� ��� ����������
		int cntCrtQw = 0, cntIncrtQw = 0, cntMsnQw = 0, NoLast;
		int NoAnsw;
		for (int NoQw = beginNo; NoQw < questions.size(); NoQw++) { //���������� ������� �����
			system("cls");
			cout << "���� \"" << name << "\" (���-�� ��������: " << questions.size() << ")" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			NoLast = NoQw;
			QuestionTS* qw = questions[NoQw]; //������� ������ �� ������
			int costQw = qw->getCost();//��������� �������
			double tmpCostQw = 0;//��������� ������, ������� ������� ������������
			cout << "������ � " << NoQw + 1 << " (��� ������� - " << costQw << " �.)" << endl;
			qw->print();
			int cntCrctAnsw = qw->getCountCorrectAnswer();//���������� ���������� �������
			int allAnsw = 0, getCntCrctAnsw = 0;
			char ch = '�';
			do {
				cout << "������� ����������, �� ��� ������, ������� ������(0 - ���������� ������, -1 - �������� ������������):";
				do {
					NoAnsw = getValue();
					if (NoAnsw < 0 || NoAnsw > qw->getSize())
						cout << "��������� ����. ��� �������: ";
				} while ((NoAnsw < 0 || NoAnsw > qw->getSize()) && (NoAnsw != -1));
				if (NoAnsw != -1) {//���� ������������ �� �������� ������������
					if (NoAnsw != 0) {//���� ������������ �� ���������� ������
						allAnsw++;
						if (qw->isCorrect(NoAnsw-1))
							getCntCrctAnsw++;//������� ��������� ���������
						cout << "����� ���� ��� ���������� ������?(�/�): ";
						cin >> ch;
					}
					else cntMsnQw++;//����� - ����������� ����� ����������� ��������
				}

			} while (ch == '�');
			if (NoAnsw != -1) {
				if (NoAnsw != 0)
				{
					getMark += (getCntCrctAnsw * costQw) / cntCrctAnsw / allAnsw;//������� ���������� ���
				  //����������, ���� ������� ������: ���������� ��� ���
					if (cntCrctAnsw == getCntCrctAnsw && cntCrctAnsw == allAnsw)cntCrtQw++;
					else cntIncrtQw++;
				}
			}
			else {
				cout << " \n������������ �������� �� ������� ������������" << endl;
				break;
			}
		}
		StatisticsElem* newStEl = new StatisticsElem(ctgrName, name, questions.size(), maxMark, getMark, cntCrtQw, cntIncrtQw, cntMsnQw, NoLast);
		return newStEl;
	}

	int getMaxCost() {
		int mCost = 0;
		for (auto el : questions)
			mCost += el->getCost();
		return mCost;
	}

	//�������� ����� (� ������� ��������� ����������)
	void createTest() {
		char ch = '�';
		do {
			system("cls");
			cout << "�������� ������ �����" << endl;
			cout << "-------------------------------------\n" << endl;
			addQuestion();
			cout << "-------------------------------------" << endl;
			cout << "�������� ��� ���� ������ � �����?(�/�) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == '�');
		cout << "��������� ��������� ���������?(�/�): ";
		cin >> ch;cin.ignore(2, '\n');
		if(ch == '�') saveToFile();
		cout << "�������� �������" << endl;
		system("pause");
	}
};
