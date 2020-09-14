#include <iostream>
#include<string>
#include<Windows.h>
#include "SystemLogin.h"
#include "StructureTS.h"
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SystemLogin sl;
	//sl.showMainMenu();
	StructureTS st;
	st.print();
	

}