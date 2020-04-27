#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set()
:counter{0}
{
	head = new Node();
    tail = new Node();

    head->next = tail;
    tail->prev = head;
}


//Conversion constructor
Set::Set(int n)
:Set()
{
    counter = 1;

	Node* newNode = new Node(n, tail, head);
	head->next = tail->prev = newNode;
}


//Constructor to create a Set from a SORTED array
Set::Set (int a[], int n) // a is sorted
:Set()
{
	counter = n;

	for(int i = 0; i < n; ++i)
    {
        Node* newNode = new Node(a[i], tail, tail->prev);
        tail->prev->next = tail->prev = newNode;
    }

}


//Make the set empty
void Set::make_empty()
{
	counter = 0;

	while(head != tail)
    {
        head->prev = nullptr;
        head->next->value = 0;
        head = head->next;
    }

    head->next = tail;
    tail->prev = head;
}


Set::~Set()
{
	make_empty();
	head = nullptr;
	tail = nullptr;
}


//Copy constructor
Set::Set (const Set& source)
:Set()
{
    counter = source.counter;

    Node* currNode = source.head->next;

    while(currNode != source.tail)
    {
        Node* newNode = new Node(currNode->value, tail, tail->prev);
        tail->prev->next = tail->prev = newNode;
        currNode = currNode->next;
    }
}


//Copy-and-swap assignment operator
//Note that call-by-value is used for source parameter
Set& Set::operator=(Set source)
{
    counter = source.counter;

    std::swap(head, source.head);
    std::swap(tail, source.tail);

	return *this;
}


//Test whether a set is empty
bool Set::_empty () const
{
	return (!counter);
}


//Test set membership
bool Set::is_member (int val) const
{
	Node* currNode = this->head->next;

    while(currNode != this->tail)
    {
        if(currNode->value == val) return true;
        currNode = currNode->next;
    }

	return false;
}



//Return number of elements in the set
unsigned Set::cardinality() const
{
	return counter;
}



//Modify Set *this such that it becomes the union of *this with Set S
//Add to Set *this all elements in Set S (repeated elements are not allowed)
//Algorithm used in exercise 5, of lesson 1 in TNG033 is useful to implement this function
Set& Set::operator+=(const Set& S)
{
	//IMPLEMENT before HA session on week 15
	Set temp(*this);

	make_empty();

	string flag;

	Node* lhs = temp.head->next;
	Node* rhs = S.head->next;


	while(lhs != temp.tail || rhs != S.tail)
    {
		if(lhs->value > rhs->value)
		{
			Node* newNode = new Node(rhs->value, tail, tail->prev);
			tail->prev->next = tail->prev = newNode;

			rhs = rhs->next;
			if(rhs == S.tail) flag = "rhs";

		}
		else if (lhs->value < rhs->value)
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = tail->prev = newNode;

			lhs = lhs->next;
		}
    }

	if(flag == "rhs") //Rhs reached end
	{
		while(lhs != temp.tail)
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = tail->prev = newNode;

			lhs = lhs->next;
		}
	}
	else //Lhs reached end
	{
		while (rhs != S.tail)
		{
			Node* newNode = new Node(rhs->value, tail, tail->prev);
			tail->prev->next = tail->prev = newNode;

			rhs = rhs->next;
		}
	}

	
	return *this;
}


//Modify Set *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT

	return *this;
}


//Modify Set *this such that it becomes the Set difference between *this and Set S
Set& Set::operator-=(const Set& S)
{
	//IMPLEMENT

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is equal to set b
//a == b, if a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


// Overloaded operator<<
ostream& operator<<(ostream& os, const Set& b)
{
	if (b._empty())
	{
		os << "Set is empty!" << endl;
	}
	else
	{
		auto temp = b.head->next;

		os << "{ ";
		while (temp != b.tail)
		{
			os << temp->value << " ";
			temp = temp->next;
		}

		os << "}" << endl;
	}

	return os;
}


