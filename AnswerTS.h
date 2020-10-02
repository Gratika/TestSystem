#pragma once
#include <iostream>
#include<fstream>
#include<string>

using namespace std;

class AnswerTS {
    bool isCorrect = false;
    string name;
public:
    AnswerTS() {}
    bool getCorrect() { return this->isCorrect; }
    void setCorrect(bool crt) { this->isCorrect = crt; }
    string getName() { return this->name; }
    void setName(string name) { this->name = name; }

    void edit() {
        char crt;
        cout << "Этот ответ правильный?(д/н): ";
        cin >> crt;
        if (crt == 'д')isCorrect = true;
        else isCorrect = false;
        cout << "Хотите изменить формулировку ответа?(д/н): ";
        cin >> crt;
        cin.ignore(3200, '\n');
        if (crt == 'д') {
            cout << "Новая формулировка: ";
            getline(cin, name); 
        }
    }

    void print(bool withCorrect = false) {
        if (withCorrect) {
            if (isCorrect)cout << "+";
            else cout << "-";
        }
        cout << this->name << endl;
    }

    void saveToFile(ofstream& out) {
        print(true);
    }

    void loadFromFile(ifstream& inp) {
        char crt;
        inp >> crt;
        if (crt == '+')this->isCorrect = true;
        else this->isCorrect = false;
        getline(inp, this->name);
        inp.ignore('\n');
    }
    friend istream& operator>>(istream& inp, AnswerTS* answ) {
        cout << "Сформулируйте ответ: ";
        getline(inp, answ->name);
        char crt;
        cout << "Этот ответ правильный?(д/н): ";
        inp >> crt;
        if (crt == 'д') answ->isCorrect = true;
        else answ->isCorrect = false;
        return inp;

    }

    ~AnswerTS(){}
};

