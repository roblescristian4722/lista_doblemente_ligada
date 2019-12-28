#include <iostream>
#include "ldl.h"
using namespace std;

int main()
{
	LDL<int> lista;
	lista.push_back(55);
	lista.push_back(44);
	lista.push_back(33);
	lista.push_back(22);
	lista.push_back(11);
	lista.insert(55, 0);
	lista.insert(55, 3);
	lista.remove(55);

	LDL<int> lista2(lista);

	cout << " Vacia : " << lista.empty() << endl
		 << " Tamaño: " << lista.size() << endl
		 << " Frente: " << lista.front() << endl
		 << " Detras: " << lista.back() << endl
		 << endl;

	for (int i = 0; i < lista.size(); ++i)
		cout << i << ": " << lista[i] << endl;

	lista.clear();

	cout << " Vacia : " << lista2.empty() << endl
	   	 << " Tamaño: " << lista2.size() << endl
		 << " Frente: " << lista2.front() << endl
		 << " Detras: " << lista2.back() << endl << endl;

	for (int i = 0; i < lista2.size(); ++i)
		cout << i << ": " << lista2[i] << endl;
} 
