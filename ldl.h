#ifndef LDL_H
#define LDL_H
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class LDL
{
public:
	LDL(const LDL<T> &other)
	{
		listSize = 0;
		listFront = nullptr;
		listBack = nullptr;
		NodoLDL *temp = other.listFront;
		for (int i = 0; i < other.listSize; i++)
		{
			push_back(temp->dato);
			temp = temp->siguiente;
		}
	}
	LDL()
	{
		listSize = 0;
		listFront = nullptr;
		listBack = nullptr;
	}
	virtual ~LDL(){}

	// STATUS
	bool empty() const;
	size_t size() const;

	// ADD
	void push_front(const T& element);
	void push_back(const T& element);
	void insert(const T& element, size_t position);

	// REMOVE
	void pop_front();
	void pop_back();
	void erase(size_t position);
	void clear();
	void remove(const T& value);

	// GET
	const T& front() const;
	const T& back() const;

	// OPERATOR OVERLOAD
	void operator =(const LDL<T> other);
	const T& operator [](size_t index);

private:
	struct NodoLDL
	{
		NodoLDL(const T& element, NodoLDL* sig = nullptr, NodoLDL* ant = nullptr)
		{
			dato = element;
			siguiente = sig;
			anterior = ant;
		}
		T dato;
		NodoLDL* siguiente;
		NodoLDL* anterior;
	};
	size_t listSize;
	NodoLDL* listFront;
	NodoLDL* listBack;
};

template<typename T>
bool LDL<T>::empty() const
{
	return listSize == 0;
}

template<typename T>
size_t LDL<T>::size() const
{
	return listSize;
}

template<typename T>
void LDL<T>::push_front(const T& element)
{
	if (empty())
	{
		listFront = new NodoLDL(element);
		listBack = listFront;
	}
	else
	{
		NodoLDL* nuevo = new NodoLDL(element, listFront);
		listFront->anterior = nuevo;
		listFront = nuevo;
	}

	++listSize;
}

template<typename T>
void LDL<T>::push_back(const T& element)
{
	if (empty())
	{
		listFront = new NodoLDL(element);
		listBack = listFront;
	}
	else
	{
		NodoLDL* nuevo = new NodoLDL(element, nullptr, listBack);
		listBack->siguiente = nuevo;
		listBack = nuevo;
	}
	++listSize;
}

template<typename T>
const T& LDL<T>::front() const
{
	if (empty())
		throw range_error("front() on empty list");
	return listFront->dato;
}

template<typename T>
const T& LDL<T>::back() const
{
	if (empty())
		throw range_error("back() on empty list");
	return listBack->dato;
}

template<typename T>
void LDL<T>::pop_front()
{
	if (empty())
		throw range_error("pop_front() on empty list");

	NodoLDL* eliminar = listFront;
	listFront = listFront->siguiente;
	if (listFront != nullptr)
		listFront->anterior = nullptr;
	eliminar->siguiente = nullptr;
	delete eliminar;
	eliminar = nullptr;

	--listSize;
}

template<typename T>
void LDL<T>::pop_back()
{
	if (empty())
		throw range_error("pop_back() on empty list");

	NodoLDL* eliminar = listBack;
	listBack = listBack->anterior;
	if (listBack != nullptr)
		listBack->siguiente = nullptr;
	eliminar->anterior = nullptr;
	delete eliminar;
	eliminar = nullptr;

	--listSize;
}

template <typename T>
void LDL<T>::insert(const T& element, size_t position)
{
	if (position > listSize)
		throw range_error("insert() on a non valid position");
	if (!position)
		push_front(element);
	else if(position == listSize)
		push_back(element);
	else
	{
		NodoLDL* temp = listFront;
		for (int i = 0; i < position - 1; ++i)
			temp = temp->siguiente;
		NodoLDL* nuevo = new NodoLDL(element, temp->siguiente, temp);
		temp->siguiente->anterior = nuevo;
		temp->siguiente = nuevo;
		++listSize;
	}
}

template <typename T>
void LDL<T>::erase(size_t position)
{
	if (empty())
		throw range_error("erase(int position) on an empty list");
	if (position >= listSize)
		throw range_error("erase(int position) on a non valid position");
	if (!position)
		pop_front();
	else if (position == listSize - 1)
		pop_back();
	else
	{
		NodoLDL* temp = listFront;
		for (int i = 0; i < position - 1; ++i)
			temp = temp->siguiente;
		NodoLDL* borrar = temp->siguiente;
		borrar->siguiente->anterior = temp;
		temp->siguiente = borrar->siguiente;
		borrar->siguiente = nullptr;
		borrar->anterior = nullptr;
		delete borrar;
		borrar = nullptr;
		--listSize;
	}
}

template <typename T>
void LDL<T>::operator =(const LDL<T> other)
{
	listSize = 0;
	listFront = nullptr;
	listBack = nullptr;
	NodoLDL* temp = other.listFront;
	for (int i = 0; i < other.listSize; i++)
	{
		push_back(temp->dato);
		temp = temp->siguiente;
	}
}

template <typename T>
const T& LDL<T>::operator [](size_t index)
{
	if (empty())
		throw range_error("[] on empty list");
	if (index >= listSize)
		throw range_error("[] on non valir position");
	NodoLDL* temp = listFront;
	for (int i = 0; i < index; ++i)
		temp = temp->siguiente;
	return temp->dato;
}

template <typename T>
void LDL<T>::clear()
{
	NodoLDL* temp = listFront;
	while(listSize != 0)
		pop_front();
	listFront = nullptr;
	listBack = nullptr;
}

template <typename T>
void LDL<T>::remove(const T& value)
{
	if (empty())
		throw range_error("remove(const T& value) in an empty list");

	NodoLDL* temp = listFront;
	T dato;
	for (int i = 0; temp != nullptr; ++i)
	{
		dato = temp->dato;
		temp = temp->siguiente;
		if (dato == value)
		{
			erase(i);
			--i;
		}
	}
}

#endif // LDL_H