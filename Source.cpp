#include <iostream>
#include<string>
#include<Windows.h>
#include "SystemLogin.h"
#include "StructureTS.h"
#include "InvokerTS.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//SystemLoginTS sl;
	//sl.showMainMenu();
	//StructureTS st;
	//st.print();
	/*ofstream out("Математика.txt");
	out << "TestCategoryTS" << endl;
	out << "Арифметика" << endl;
	out << "TestCategoryTS" << endl;
	out << "Алгебра" << endl;
	out << "TestCategoryTS" << endl;
	out << "Математический анализ" << endl;
	out << "TestTS" << endl;
	out << "Сложение и вычитание чисел" << endl;	
	out.close();*/
	shared_ptr<InvokerTS<StructureTS, SystemLoginTS>>invoker_ = make_shared <InvokerTS<StructureTS, SystemLoginTS>>(new StructureTS(), new SystemLoginTS());
	//InvokerTS<StructureTS, SystemLoginTS> *invoker_ = new InvokerTS<StructureTS, SystemLoginTS>(new StructureTS(), new SystemLoginTS())
	invoker_->mainScript();
}