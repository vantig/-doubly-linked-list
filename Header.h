#pragma once
#include<iostream>

template<class T>
class DualList
{
public:
	class Node
	{
	public:
		T data;
		Node* prev;
		Node* next;

		Node() = default;//конструктор по умолчанию
		Node(const T& _data, Node* _prev = nullptr, Node* _next = nullptr)
			: data(_data), prev(_prev), next(_next) {};
		~Node() = default;
	};

	DualList() : size(0), head(nullptr), tail(nullptr) {};
	DualList(const DualList<T>&);
	~DualList();

	void pushBack(const T&);
	void pushFront(const T&);
	void insert(const T&, size_t);
	void insert(const T&, size_t, size_t numOfElements);

	T popBack();
	T popFront();
	T erase(size_t);

	void replace(const T&, const T&);

	T& operator[](size_t);
	const T& operator[](size_t) const;

	template<class T>
	friend std::ostream& operator<<(std::ostream&, DualList<T>&);

private:
	size_t size;
	Node* head;
	Node* tail;

public:
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(Node* _ptr) : ptr(_ptr) {};
		~Iterator() = default;

		//префиксная форма
		Iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		//постфиксная форма
		Iterator& operator++(int)
		{
			Iterator temp(*this);//связали временный указатель с текущим объектом
			operator++();//инкремент для текущего объекта
			return temp;//возврат неизмененного объекта
		}
		//самостоятельно
		/*Iterator& operator--()
		Iterator& operator--(int)*/

		//оператор разыменования
		T& operator*() const { return ptr->data; }

		bool operator==(const Iterator& i) const
		{
			return ptr == i.ptr;
		}
		bool operator!=(const Iterator& i) const
		{
			return ptr != i.ptr;
		}

	private:
		Node* ptr;
	};
	//самостоятельно
	/*class Reverse_iterator
	{

	};*/
	//Reverse_iterator Rbegin() { return Reverse_iterator(tail); }
	//Reverse_iterator Rend() { return Reverse_iterator(head->prev); }

	T erase(Iterator start, Iterator end);
	Iterator find(const T&);

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(tail->next); }

};

template <class T>
void DualList<T>::pushBack(const T& val)
{
	Node* temp = new Node(val, tail);
	if (size == 0)
	{
		head = temp;
	}
	else
	{
		tail->next = temp;
	}
	tail = temp;
	size++;
}

template<class T>
T DualList<T>::popBack()
{
	Node* temp = tail;
	T returnValue;
	if (size == 0)
	{
		std::cout << "List is empty.\n";
		return T();
	}
	if (size == 1)
		tail = head = nullptr;

	else
	{
		tail = temp->prev;
		tail->next = nullptr;
	}

	returnValue = temp->data;
	size--;
	delete temp;

	return returnValue;
}

template<class T>
T DualList<T>::popFront()
{
	Node* temp = head;
	T returnValue;
	if (size == 0)
	{
		std::cout << "List is empty.\n";
		return T();
	}
	if (size == 1)
		tail = head = nullptr;

	else
	{
		head = temp->next;
		head->prev = nullptr;
	}

	returnValue = temp->data;
	size--;
	delete temp;

	return returnValue;
}

template<class T>
std::ostream& operator<<(std::ostream& out, DualList<T>& list)
{
	if (list.size == 0)
	{
		out << "List is empty.\n";
		return out;
	}

	for (auto i = list.begin(); i != list.end(); i++)
		out << *i << " ";

	return out;
}

template<class T>
DualList<T>::~DualList()
{
	while (size != 0)
	{
		popBack();
	}
}

template<class T>
T DualList<T>::erase(size_t pos)
{
	T returnValue;
	Iterator it = head;
	if (pos > size)
	{
		std::cout << "Position is out of range.\n";
		return T();
	}

	for (size_t i = 0; i < pos; i++, it++);

	returnValue = *it;

	//перегрузить стрелку
	(it->prev)->next = it->next;
	(it->next)->prev = it->prev;
	delete it;
	size--;

	return returnValue;

	if (pos == 0) return popFront();
	if (pos == size) return popBack();
}


//template<class T>
//T erase(Iterator start, Iterator end);