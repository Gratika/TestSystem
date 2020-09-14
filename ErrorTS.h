#pragma once
#include<iostream>
#include<string>
using namespace std;

class ErrorTS {
protected:
	string msg;
public:
	ErrorTS() {};
	ErrorTS(string msg) :msg(msg) {}
	virtual string getError() {
		return "Ошибка!"+ msg;
	}
	virtual ~ErrorTS() {};
};

class ObjectCreatorError:public ErrorTS {	
public:
	ObjectCreatorError(string msg):ErrorTS(msg){}	
	~ObjectCreatorError(){}
};

class FileError :public ErrorTS {
public:
	FileError(string filename, string msg) {
		ErrorTS::msg = "Ошибка доступа к файлу \"" + filename + "\". " + msg;
	}
	~FileError(){}
};

class ObjectInfoNotFound :public ErrorTS {
public:
	ObjectInfoNotFound(string msg):ErrorTS(msg){}
	~ObjectInfoNotFound(){}
};

