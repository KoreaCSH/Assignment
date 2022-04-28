#include "doublylinkedlist.h"
#include <iostream>
#include <math.h>

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 2022. 4. 4  Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  */

/*
 * Iterator
 */
template<class T>
typename DoublyLinkedList<T>::Iterator& 
DoublyLinkedList<T>::Iterator::operator++() 
{ 
	this->current = this->current->rlink; 
	return *this; 
}

template<class T>
typename DoublyLinkedList<T>::Iterator  
DoublyLinkedList<T>::Iterator::operator++(int) 
{ 
	Iterator temp = *this;
	++(*this);
	return temp;
}

template<class T>
typename DoublyLinkedList<T>::Iterator& 
DoublyLinkedList<T>::Iterator::operator--() 
{ 
	this->current = this->current->llink; 
	return *this; 
}

template<class T>
typename DoublyLinkedList<T>::Iterator  
DoublyLinkedList<T>::Iterator::operator--(int) 
{ 
	Iterator temp = *this;
	--(*this);
	return temp;
}


/*
 * Reverse Iterator
 */
template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator&
DoublyLinkedList<T>::Reverse_Iterator::operator++() 
{ 
	this->current = this->current->llink; 
	return *this;
}

template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator
DoublyLinkedList<T>::Reverse_Iterator::operator++(int)
{ 
	Reverse_Iterator temp = *this;
	++(*this);
	return temp;
}

template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator&
DoublyLinkedList<T>::Reverse_Iterator::operator--() 
{ 
	this->current = this->current->rlink; 
	return *this;
}

template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator
DoublyLinkedList<T>::Reverse_Iterator::operator--(int)
{ 
	Reverse_Iterator temp = *this;
	--(*this);
	return temp;
}

/*
 * Doubly linked list
 */
// Default constructor
template<class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	first = new NodeType();
	first->rlink = first;
	first->llink = first;
}

// Copy constructor
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& source)
{
	this->first = new NodeType();
	this->first->rlink = this->first;
	this->first->llink = this->first;
	for ( Iterator it = source.Begin(); it != source.End(); ++it )
	{
		this->InsertLast(*it);
	}
}


// Destructor
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	NodeType* delNode = this->first->rlink;
	while(delNode != this->first)
	{
		NodeType* temp = delNode->rlink;
		delete delNode;
		delNode = temp;
	}
	delete this->first;
}


// Assignment operator
template<class T>
DoublyLinkedList<T>& 
DoublyLinkedList<T>::operator = (const DoublyLinkedList<T>& source)
{
	if ( this == &source )
	{
		return *this;
	}
	else
	{
		NodeType* delNode = this->first->rlink;
		while(delNode != this->first)
		{
			NodeType* temp = delNode->rlink;
			delete delNode;
			delNode = temp;
		}
		delete this->first;
		this->first = new NodeType();
		this->first->rlink = first;
		this->first->llink = first;
			
		for ( Iterator it = source.Begin(); it != source.End(); ++it )
		{
			this->InsertLast(*it);
		}
		return *this;
	}
}



// Total number of nodes in the list
template<class T>
int 
DoublyLinkedList<T>::Size() const
{
	int count = 0;
	for ( Iterator it = this->Begin(); it != this->End(); ++it )
	{
		count++;
	}
	return count;
}


// Insert a new node to the list as the first node
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator 
//typename Iterator
DoublyLinkedList<T>::InsertFirst(const T& data)
{
	NodeType* newNode = new NodeType();
	newNode->data = data;
	if ( this->first->rlink == this->first )
	{
		newNode->rlink = this->first;
		newNode->llink = this->first;
		this->first->rlink = newNode;
		this->first->llink = newNode;
	}
	else
	{
		newNode->rlink = this->first->rlink;
		newNode->rlink->llink = newNode;
		newNode->llink = this->first;
		this->first->rlink = newNode;
	}
	return newNode;
}


// Insert a new node to the list as the last node
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator
DoublyLinkedList<T>::InsertLast(const T & data)
{
	NodeType* newNode = new NodeType();
	newNode->data = data;
	if ( this->first->llink == this->first )
	{
		newNode->rlink = this->first;
		newNode->llink = this->first;
		this->first->llink = newNode;
		this->first->rlink = newNode;
	}
	else
	{
		newNode->rlink = this->first;
		newNode->llink = this->first->llink;
		newNode->llink->rlink = newNode;
		this->first->llink = newNode;
	}
	return newNode;
}


// Insert a new node to the list after pos
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator 
DoublyLinkedList<T>::InsertNext(DoublyLinkedList<T>::Iterator pos, const T & data)
{
	int count = 0;
	NodeType* posNode = this->first->rlink;
	NodeType* newNode = new NodeType();
	newNode->data = data;
		
	for ( Iterator it = this->Begin(); it != pos; ++it )
	{
		count++;
	}
		
	while ( count > 0 )
	{
		posNode = posNode->rlink;
		count--;
	}
		
	newNode->rlink = posNode->rlink;
	newNode->llink = posNode;
	posNode->rlink->llink = newNode;
	posNode->rlink = newNode;
		
	return newNode;
}


// Insert a new node to the list before pos
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator 
DoublyLinkedList<T>::InsertPrev(DoublyLinkedList<T>::Iterator pos, const T & data)
{
	int count = 0;
	NodeType* posNode = this->first->rlink;
	NodeType* newNode = new NodeType();
	newNode->data = data;
		
	for ( Iterator it = this->Begin(); it != pos; ++it )
	{
		count++;
	}
		
	while ( count > 0 )
	{
		posNode = posNode->rlink;
		count--;
	}
		
	newNode->rlink = posNode;
	newNode->llink = posNode->llink;
	posNode->llink->rlink = newNode;
	posNode->llink = newNode;
		
	return newNode;
}


// Delete node at pos in the list
template<class T>
bool 
DoublyLinkedList<T>::DeleteNode(Iterator pos)
{
	if ( this->Size() == 0 )
	{
		return false;
	}
	else if ( this->Size() == 1 )
	{
		NodeType* delNode = this->first->rlink;
		this->first->rlink = this->first;
		this->first->llink = this->first;
		delete delNode;
		return true;
	}
	else
	{
		int count = 0;
		NodeType* posNode = this->first->rlink;
	
		for ( Iterator it = this->Begin(); it != pos; ++it )
		{
			count++;
		}
		
		while ( count > 0 )
		{
			posNode = posNode->rlink;
			count--;
		}
		
		posNode->llink->rlink = posNode->rlink;
		posNode->rlink->llink = posNode->llink;
		delete posNode;
		return true;
	}
}


// Delete first node
template<class T>
bool 
DoublyLinkedList<T>::DeleteFirst()
{
	if ( this->first->rlink == this->first && this->first->llink == this->first )
	{
		return false;
	}
	else if (this->Size() == 1)
	{
		NodeType* delNode = this->first->rlink;
		this->first->rlink = this->first;
		this->first->llink = this->first;
		delete delNode;
		return true;
	}
	else
	{
		NodeType* delNode = this->first->rlink;
		this->first->rlink = delNode->rlink;
		delNode->rlink->llink = this->first;
		delete delNode;
		return true;
	}
}


// Delete last node
template<class T>
bool 
DoublyLinkedList<T>::DeleteLast()
{
	if ( this->first->rlink == this->first && this->first->llink == this->first )
	{
		return false;
	}
	else if(this->Size() == 1) 
	{
		NodeType* delNode = this->first->rlink;
		this->first->rlink = this->first;
		this->first->llink = this->first;
		delete delNode;
		return true;
	}
	else
	{
		NodeType* delNode = this->first->llink;
		this->first->llink = delNode->llink;
		delNode->llink->rlink = this->first;
		delete delNode;
		return true;
	}
}


template<class T>
void 
DoublyLinkedList<T>::Print(bool reverse)
{
	if(reverse)
	{
		for(Reverse_Iterator rit = rBegin(); rit!=rEnd(); rit++)
		{	
			std::cout << *rit << ", ";
		}
	}
	else 
	{		
		for(Iterator it = Begin(); it!=End(); it++)
		{	
			std::cout << *it << ", ";
		}		
	}
	
	std::cout << std::endl;
}

