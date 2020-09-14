#pragma once
#include <iostream>
using namespace std;

template<class T>
class MyData
{
public:
	T val;
	MyData* next = nullptr;
	MyData* prev = nullptr;

};

template<class T, int size>
class MyArrayList
{
	MyData<T>* first = nullptr;
	MyData<T>* last = nullptr;
	MyData<T>* top = nullptr;
	int lenght = 0;
	int maxSize = size;
	int grow = 1;
	void push();
	void pop();
	MyData<T>& peek(int pos);

public:
	MyArrayList();
	int getSize();
	void setSize(int newSize, int grow = 1);
	int getUpperBound();
	bool isEmpty();
	void FreeExtra();
	void RemoveAll();
	T getAt(int pos);
	bool setAt(int pos, T val);
	T operator[](int pos);
	void add(T val);
	MyArrayList<T, size>& append(const MyArrayList<T, size>& arrList);
	MyArrayList<T, size>& operator=(const MyArrayList<T, size>& arrList);
	MyArrayList<T, size>& getData();
	bool insertAt(T val, int pos);
	bool removeAt(int pos);
	void print();
	~MyArrayList();



};

template<class T, int size>
void MyArrayList<T, size>::push()
{
	MyData<T>* newVal = new MyData<T>;
	if (!first) {
		first = newVal;
		last = first;
		top = first;
	}
	else {
		last->next = newVal;
		newVal->prev = last;
		last = newVal;
	}
}

template<class T, int size>
void MyArrayList<T, size>::pop()
{
	if (last) {
		MyData<T>* tmp = last;
		last = last->prev;
		if (last) last->next = nullptr;
		delete tmp;
	}
}

template<class T, int size>
MyData<T>& MyArrayList<T, size>::peek(int pos)
{
	MyData<T>* tmp;
	if (pos <= lenght / 2) {
		tmp = first;
		for (int i = 0; i < pos; i++)
			tmp = tmp->next;
	}
	else {
		tmp = top;
		for (int i = 0; i < lenght - pos - 1; i++)
			tmp = tmp->prev;
	}

	return *tmp;
}

template<class T, int size>
MyArrayList<T, size>::MyArrayList() {
	for (int i = 0; i < maxSize; i++)
		push();
}

template<class T, int size>
int MyArrayList<T, size>::getSize()
{
	return this->maxSize;
}

template<class T, int size>
void MyArrayList<T, size>::setSize(int newSize, int grow)
{
	if (newSize > maxSize) {
		//if (lenght == maxSize) top = last;
		int r = newSize - maxSize;
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= grow; j++) {
				push();
				maxSize++;
			}
		this->grow = grow;
	}
	else {
		if (lenght > newSize) {
			lenght = newSize;
			*top = peek(lenght - 1);
		}
		int r = maxSize - newSize;
		for (int i = 1; i <= r; i++) {
			pop();
			maxSize--;
		}
	}
}

template<class T, int size>
int MyArrayList<T, size>::getUpperBound()
{
	return lenght - 1;
}

template<class T, int size>
bool MyArrayList<T, size>::isEmpty()
{
	return this->lenght == 0;
}

template<class T, int size>
void MyArrayList<T, size>::FreeExtra()
{
	int r = maxSize - lenght;
	if (r > 0) top = top->prev;
	for (int i = 0; i < r; i++) {
		pop();
		maxSize--;
	}
}

template<class T, int size>
void MyArrayList<T, size>::RemoveAll()
{
	for (int i = 0; i < maxSize; i++)
		pop();
	maxSize = 0;
	lenght = 0;
	last = first = top = nullptr;
}

template<class T, int size>
T MyArrayList<T, size>::getAt(int pos)
{
	if (pos < 0 || pos >= lenght) cout << "Error position!" << endl;
	else  return (peek(pos)).val;
}

template<class T, int size>
bool MyArrayList<T, size>::setAt(int pos, T val)
{
	if (pos < 0 || pos >= lenght) {
		cout << "Error position!" << endl;
		return false;
	}
	else {
		(peek(pos)).val = val;
		return true;
	}

}

template<class T, int size>
T MyArrayList<T, size>::operator[](int pos)
{
	if (pos < 0 || pos >= lenght) cout << "Error position!" << endl;
	else  return (peek(pos)).val;
}

template<class T, int size>
void MyArrayList<T, size>::add(T val)
{
	if (lenght == maxSize) {
		setSize(maxSize + grow);
		top = top->next;
	}
	lenght++;
	setAt(lenght - 1, val);
	if (top->next) top = top->next;

}

template<class T, int size>
inline MyArrayList<T, size>& MyArrayList<T, size>::append(const MyArrayList<T, size>& arrList)
{
	MyArrayList<T, size>* newArr = new MyArrayList<T, size>;
	MyData<T>* tmp = this->first;
	for (int i = 0; i < this->lenght; i++) {
		newArr->add(tmp->val);
		tmp = tmp->next;
	}
	tmp = arrList.first;
	for (int i = 0; i < arrList.lenght; i++) {
		newArr->add(tmp->val);
		tmp = tmp->next;
	}
	return *newArr;
}

template<class T, int size>
MyArrayList<T, size>& MyArrayList<T, size>::operator=(const MyArrayList<T, size>& arrList)
{
	RemoveAll();
	for (int i = 0; i < arrList.lenght; i++)
		this->add(array[i]);
	return *this;
}

template<class T, int size>
MyArrayList<T, size>& MyArrayList<T, size>::getData()
{
	return *this;
}

template<class T, int size>
bool MyArrayList<T, size>::insertAt(T val, int pos)
{
	if (pos<0 || pos>lenght) {
		cout << "Error position" << endl;
		return false;
	}
	else {
		MyData<T>* newData = new MyData<T>;
		newData->val = val;
		MyData<T>* tmp;
		if (pos < lenght / 2) {
			tmp = first;
			for (int i = 0; i < pos - 1; i++)
				tmp = tmp->next;
		}
		else {
			tmp = top;
			for (int i = 0; i < lenght - pos; i++)
				tmp = tmp->prev;
		}
		newData->next = tmp->next;
		tmp->next->prev = newData;
		newData->prev = tmp;
		tmp->next = newData;
		if (pos == 0) first = newData;
		if (pos == lenght) top = newData;
		if (pos == maxSize) last = newData;
		lenght++;
		return true;
	}
}

template<class T, int size>
inline bool MyArrayList<T, size>::removeAt(int pos)
{
	if (pos<0 || pos>lenght) {
		cout << "Error position" << endl;
		return false;
	}
	else {
		MyData<T>* tmp;
		if (pos < lenght / 2) {
			tmp = first;
			for (int i = 0; i < pos; i++)
				tmp = tmp->next;
		}
		else {
			tmp = top;
			for (int i = 0; i < lenght - pos - 1; i++)
				tmp = tmp->prev;
		}
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		lenght--;
		return true;
	}
}

template<class T, int size>
void MyArrayList<T, size>::print()
{
	MyData<T>* tmp = first;
	for (int i = 0; i < lenght; i++) {
		cout<<i+1<<" " << tmp->val << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

template<class T, int size>
inline MyArrayList<T, size>::~MyArrayList()
{
	RemoveAll();
}
