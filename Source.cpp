#include <iostream>
#include<string>
#include<Windows.h>
#include "SystemLogin.h"
#include "StructureTS.h"
#include "StatisticsTS.h"
#include "InvokerTS.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
	shared_ptr<InvokerTS>invoker_ = make_shared <InvokerTS>(new StructureTS(), new SystemLoginTS(), new StatisticsTS());
	invoker_->mainScript();	
}