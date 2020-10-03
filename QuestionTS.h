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
        char ch='н';
        do {
            system("cls");
            cout << "Редактирование вопроса:" << endl;
            print(true);
            cout << "--------------------------------------------------------------\n" << endl;
            cout << "Что меняем?\n1-Формулировку вопроса;\n2-Стоимость вопроса\n3-Ответы\n0-Выход" << endl;
            cin >> ch;
            switch (ch) {
            case '1':
                cout << "\nНовая формулировка: ";
                getline(cin, name);
                break;
            case '2':
                cout << "\nНовая стоимость: ";
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
                cout << "Ошибочный ввод..." << endl;
                break;
            }
            cout << "Хотите продолжить редактирование этого вопроса?(д/н): ";
            cin >> ch;
            cin.ignore(3200,'\n');
            system("pause");
        } while (ch == 'д');       

    }
    //редактирование ответов (варианты выбора действий и их реализация)
    void editAnswer() {
      
        char actn = 'н', ch;  
        int answ;
        do {
            system("cls");
            cout << "Редактирование ответов на вопрос:" << endl;
            print();
            cout << "---------------------------------------\n" << endl;
            cout << "Что будем делать?\n1-изменять ответы; \n2-добавлять ответы;\n3-удалять ответы;" << endl;
            cin >> ch; cin.ignore(32000, '\n');
            switch (ch)
            {
            case '1':                
                cout << "Какой ответ будем менять?" << endl;
                answ = getValue();
                if (answ - 1 < 0 || answ - 1 >= answers.size())throw OutOfRangeError("Ответа с таким номером не существует!");
                answers[answ-1]->edit();
                break;
            case '2':
                addAnswer();
                break;
            case '3':
                cout << "Какой ответ будем удалять?" << endl;
                answ = getValue();
                if (answ - 1 < 0 || answ - 1 >= answers.size())throw OutOfRangeError("Ответа с таким номером не существует!");
                deleteAnsw(answ-1);
                break;
            default:
                cout << "Ошибочный ввод..." << endl;
                break;
            }
            cout << "Хотите продолжить правку ответов?(д/н): ";
            cin >> actn; cin.ignore(32000, '\n');
        } while (actn == 'д');
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
        cout << "Укажите стоимость вопроса: ";
        qwsn->costQw = getValue();
        cout << "Сформулируйте вопрос: ";
        getline(inp, qwsn->name);
        char ch = 'н';
        do {
            qwsn->addAnswer();
            cout << "Добавить еще один ответ?(д/н): ";
            cin >> ch;
            cin.ignore(3200, '\n');
        } while (ch == 'д');
        return inp;
    }
    ~QuestionTS() {
        answers.~vector();
    }

};