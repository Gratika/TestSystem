#pragma once
#include <iostream>
#include<fstream>
#include <vector>
#include<string>
#include"AnswerTS.h"
#include"MyFunction.h"
#include"ErrorTS.h"
using namespace std;
class QuestionTS {
    string name;
    int costQw = 0;
    vector<AnswerTS*> answers;
public:
    QuestionTS() {}
    int getCost() { return this->costQw; }
    void setCorrect(int cst) { this->costQw = cst; }
    string getName() { return this->name; }
    void setName(string name) { this->name = name; }
    
    void print(bool withCorrect = false) {
        cout << name << endl;
        for (int i = 0; i < answers.size(); i++) {
            cout << "   " << i + 1<<") ";
            answers[i]->print(withCorrect);
        }
    }

    void deleteAnsw(int id) {
        answers.erase(answers.begin()+id);
    }
    void addAnswer() {
        AnswerTS* newAnsw = new AnswerTS();
        cin >> newAnsw;
        answers.push_back(newAnsw);
    }
    void edit() {        
        char ch='�';
        do {
            system("cls");
            cout << "�������������� �������:" << endl;
            print(true);
            cout << "--------------------------------------------------------------\n" << endl;
            cout << "��� ������?\n1-������������ �������;\n2-��������� �������\n3-������\n0-�����" << endl;
            cin >> ch;
            switch (ch) {
            case '1':
                cout << "\n����� ������������: ";
                getline(cin, name);
                break;
            case '2':
                cout << "\n����� ���������: ";
                costQw = getValue();
                break;
            case '3': 
                try {
                    editAnswer();
                }
                catch (OutOfRangeError err) {
                    cout << err.getError() << endl; 
                }                
                break;
            case '0': return;
            default:
                cout << "��������� ����..." << endl;
                break;
            }
            cout << "������ ���������� �������������� ����� �������?(�/�): ";
            cin >> ch;
            cin.ignore(3200,'\n');
            system("pause");
        } while (ch == '�');       

    }
    //�������������� ������� (�������� ������ �������� � �� ����������)
    void editAnswer() {
      
        char actn = '�', ch;  
        int answ;
        do {
            system("cls");
            cout << "�������������� ������� �� ������:" << endl;
            print();
            cout << "---------------------------------------\n" << endl;
            cout << "��� ����� ������?\n1-�������� ������; \n2-��������� ������;\n3-������� ������;" << endl;
            cin >> ch; cin.ignore(32000, '\n');
            switch (ch)
            {
            case '1':                
                cout << "����� ����� ����� ������?" << endl;
                answ = getValue();
                if (answ - 1 < 0 || answ - 1 >= answers.size())throw OutOfRangeError("������ � ����� ������� �� ����������!");
                answers[answ-1]->edit();
                break;
            case '2':
                addAnswer();
                break;
            case '3':
                cout << "����� ����� ����� �������?" << endl;
                answ = getValue();
                if (answ - 1 < 0 || answ - 1 >= answers.size())throw OutOfRangeError("������ � ����� ������� �� ����������!");
                deleteAnsw(answ-1);
                break;
            default:
                cout << "��������� ����..." << endl;
                break;
            }
            cout << "������ ���������� ������ �������?(�/�): ";
            cin >> actn; cin.ignore(32000, '\n');
        } while (actn == '�');
    }

    void saveToFile(ofstream& out) {
        out << costQw << endl;
        out << name << endl;
        out << answers.size() << endl;
        for (auto el : answers)
            el->saveToFile(out);
    }

    void loadFromFile(ifstream& inp) {
        inp >> costQw; inp.ignore(2, '\n');
        getline(inp, this->name);
        int cntAnsw;
        inp >> cntAnsw; inp.ignore(2, '\n');
        for (int j = 0; j < cntAnsw; j++) {
            AnswerTS* answ = new AnswerTS();
            answ->loadFromFile(inp);
            answers.push_back(answ);
        }

    }

    int getCountCorrectAnswer() {
        int cntCrtQw = 0;
        for (auto el: answers)
            if (el->getCorrect())cntCrtQw++;
        return cntCrtQw;
    }

    bool isCorrect(int id) {
        return answers[id]->getCorrect();
    }

    int getSize() {
        return answers.size();
    }

    friend istream& operator>>(istream& inp, QuestionTS* qwsn) {
        cout << "������� ��������� �������: ";
        qwsn->costQw = getValue();
        cout << "������������� ������: ";
        getline(inp, qwsn->name);
        char ch = '�';
        do {
            qwsn->addAnswer();
            cout << "�������� ��� ���� �����?(�/�): ";
            cin >> ch;
            cin.ignore(3200, '\n');
        } while (ch == '�');
        return inp;
    }
    ~QuestionTS() {
        answers.~vector();
    }

};