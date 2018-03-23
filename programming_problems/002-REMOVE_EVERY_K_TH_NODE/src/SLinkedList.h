/*
 * SSLinkedList.h
 *
 *  Created on: Mar 7, 2018
 *      Author: dan
 */

#ifndef SLINKEDLIST_H_
#define SLINKEDLIST_H_

#include <iostream>
#include  <stdexcept>

using namespace std;

//#define DEBUG_ON


// Forward declarations
template <typename T> class SLinkedList;
template <typename T> void print(const SLinkedList<T> &);

template <typename U>
struct Node {
	U val;
	Node *next;
	Node(const U &a) : val{a}, next{nullptr} {
#ifdef DEBUG_ON
		cout << "Entering constructor Node::Node(const U &a)" << endl;
#endif

	}
	Node(U &&a) : val{move(a)}, next{nullptr} {
#ifdef DEBUG_ON
		cout << "Entering constructor Node::Node(U &&a)" << endl;
#endif

	}
};


template <typename T>
class SLinkedList {

	Node<T> *_head, *_tail;
	size_t _size;

	friend void print<T>(const SLinkedList<T>&);

public:
	SLinkedList();
	SLinkedList(const SLinkedList<T> &);
	SLinkedList(SLinkedList<T> &&);
	~SLinkedList();

	SLinkedList<T>& operator=(const SLinkedList<T> &);
	SLinkedList<T>& operator=(SLinkedList<T> &&);


	SLinkedList<T>& push_front(const T &);
	SLinkedList<T>& push_back(const T &);
	SLinkedList<T>& push_front(T &&);
	SLinkedList<T>& push_back(T &&);

	void pop_front();
	T& top();
	SLinkedList<T>& delete_k_th(int k = 1);

	size_t size() { return _size; }


};


///////////////////////////////////////////////
///////////////////////////////////////////////
///
/// CONSTRUCTORS & ASSIGNMENTS
///
///////////////////////////////////////////////
///////////////////////////////////////////////

template <typename T>
SLinkedList<T>::SLinkedList() :
		_head{nullptr}, _tail{nullptr},
		_size{0} {

#ifdef DEBUG_ON
	cout << "Entering Default Constructor SLinkedList<T>::SLinkedList()" << endl;

#endif

}

template <typename T>
SLinkedList<T>::SLinkedList(const SLinkedList<T> &l) :
		_head{nullptr}, _tail{nullptr},
		_size{0} {


#ifdef DEBUG_ON
	cout << "Entering Copy Constructor SLinkedList<T>::SLinkedList(const SLinkedList<T> &)" << endl;
#endif

	Node<T> *cursor{l._head};

	while (cursor) {

		Node<T> *n = new Node<T>{cursor->val};

		if (!_head) _head = _tail = n;
		else {
			_tail->next = n;
			_tail = n;
		}

		cursor = cursor->next;
	}

	_size = l._size;

}

template <typename T>
SLinkedList<T>::SLinkedList(SLinkedList<T> &&l) :
		_head{l._head}, _tail{l._tail},
		_size{l._size} {

#ifdef DEBUG_ON
	cout << "Entering Move Constructor SLinkedList<T>::SLinkedList(SLinkedList<T> &&)" << endl;
#endif

	l._head = l._tail = nullptr;
	l._size = 0;
}

template <typename T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList<T> &l) {
#ifdef DEBUG_ON
	cout << "Entering Copy Assignment SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList<T> &)" << endl;
#endif

	if (this != &l) {

		Node<T> *cursor{l._head};

		while (cursor) {

			Node<T>* n = new Node<T>{cursor->val};

			if (!_head) _head = _tail = n;
			else {
				_tail->next = n;
				_tail = n;
			}

			cursor = cursor->next;
		}

		_size = l._size;

	}

	return *this;

}


template <typename T>
SLinkedList<T>& SLinkedList<T>::operator=(SLinkedList<T> &&l) {

#ifdef DEBUG_ON
	cout << "Entering Move Assignment SLinkedList<T>& SLinkedList<T>::operator=(SLinkedList<T> &&)" << endl;
#endif

	swap(_head, l._head);
	swap(_tail, l._tail);
	swap(_size, l._size);

	return *this;
}


///////////////////////////////////////////////
///////////////////////////////////////////////
///
/// METHODS
///
///////////////////////////////////////////////
///////////////////////////////////////////////


template <typename T>
SLinkedList<T>& SLinkedList<T>::push_front(const T &val) {

#ifdef DEBUG_ON
	cout << "Entering SLinkedList<T>& SLinkedList<T>::push_front(const T &val)" << endl;
#endif
	Node<T> *n = new Node<T>{val};

	if(!_head) _head = _tail = n;
	else {
		n->next = _head;
		_head = n;
	}

	++_size;

	return *this;
}

template <typename T>
SLinkedList<T>& SLinkedList<T>::push_front(T &&val) {

#ifdef DEBUG_ON
	cout << "Entering SLinkedList<T>& SLinkedList<T>::push_front(T &&val)" << endl;
#endif

	Node<T> *n = new Node<T>{move(val)};

	if(!_head) _head = _tail = n;
	else {
		n->next = _head;
		_head = n;
	}

	++_size;

	return *this;
}


template <typename T>
SLinkedList<T>& SLinkedList<T>::push_back(const T &val) {

#ifdef DEBUG_ON
	cout << "Entering SLinkedList<T>& SLinkedList<T>::push_back(const T &val)" << endl;
#endif

	Node<T> *n = new Node<T>{val};

	if(!_head) _head = _tail = n;
	else {
		_tail->next = n;
		_tail = n;
	}

	++_size;

	return *this;
}

template <typename T>
SLinkedList<T>& SLinkedList<T>::push_back(T &&val) {

#ifdef DEBUG_ON
	cout << "Entering SLinkedList<T>& SLinkedList<T>::push_back(T &&val)" << endl;
#endif

	Node<T> *n = new Node<T>{move(val)};

	if(!_head) _head = _tail = n;
	else {
		_tail->next = n;
		_tail = n;
	}

	++_size;

	return *this;
}

template <typename T>
void SLinkedList<T>::pop_front() {

	if (_size <= 0) throw range_error{"The list is empty"};

	if (_size == 1) {

		delete _head;
		_head = _tail = nullptr;

	} else {

		Node<T> *tmp{_head};
		_head = _head->next;

		delete tmp;
	}

	--_size;

	return;
}

template <typename T>
T& SLinkedList<T>::top() {

	if (_size <= 0) throw range_error{"The list is empty"};

	return _head->val;
}

template <typename T>
SLinkedList<T>& SLinkedList<T>::delete_k_th(int k) {

	if ((k <= 0) || !_size || (static_cast<size_t>(k) > _size)) return *this;

	if (k == 1) {

		SLinkedList<T> *tmp = new SLinkedList<T>{move(*this)};
		delete tmp;

	} else {

		Node<T> *cursor1{_head}, *cursor2{_head->next};

		int counter = 1;
		bool flag{_size % k};

		while (cursor2) {

			if (counter == k - 1) {

				cursor1->next = cursor2->next;
				delete cursor2;

				--_size;

				if (!cursor1->next) break;
				else {

					counter = 1;
					cursor1 = cursor1->next;
					cursor2 = cursor1->next;
				}
			} else {

				++counter;

				cursor1 = cursor1->next;
				cursor2 = cursor1->next;
			}

			if (!flag) _tail = cursor1;

		} // End while
	}

	return *this;
}

///////////////////////////////////////////////
///////////////////////////////////////////////
///
/// DESTRUCTOR
///
///////////////////////////////////////////////
///////////////////////////////////////////////

template <typename T>
SLinkedList<T>::~SLinkedList() {

#ifdef DEBUG_ON
	cout << "Entering DE-structor SLinkedList<T>::~SLinkedList() - delete list with size: " \
		 << _size << endl;
#endif

	while (_head) {

		Node<T> *tmp{_head};
		_head = _head->next;

		delete tmp;
	}

	_head = _tail = nullptr;
	_size = 0;
}

template <typename T>
void print(const SLinkedList<T> &l) {

	Node<T> *cursor{l._head};

	while (cursor) {

		cout << cursor->val << " ";
		cursor = cursor->next;

	}

	cout << endl;
}

#endif /* SLINKEDLIST_H_ */
