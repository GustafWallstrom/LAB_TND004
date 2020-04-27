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
	head->next = newNode;
	tail->prev = newNode;
}


//Constructor to create a Set from a SORTED array
Set::Set(int a[], int n) // a is sorted
:Set()
{
	counter = n;

	for(int i = 0; i < n; ++i)
    {
        Node* newNode = new Node(a[i], tail, tail->prev);
		tail->prev->next = newNode;
		tail->prev = newNode;
    }

}


//Make the set empty
void Set::make_empty()
{
	counter = 0;

    Node* temp = head;

    while(temp->next != tail)
    {
        Node* temp2 = temp->next;
        temp->next = temp2->next;
        delete temp2;
    }

	head->next = tail;
	tail->prev = head;
}


Set::~Set()
{
	if(counter != 0) make_empty();
	
	delete head;
	delete tail;
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
		tail->prev->next = newNode;
		tail->prev = newNode;
        currNode = currNode->next;
    }
}

//Move constructor
Set::Set(Set&& source)
:counter(source.counter), head(source.head), tail(source.tail)
{
	source.counter = 0;
	source.head = nullptr;
	source.tail = nullptr;
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

	if (this->head == S.head)
	{
		return *this;
	}

	Set temp(*this);


	make_empty();

	string flag;

	Node* lhs = temp.head->next;
	Node* rhs = S.head->next;

	if (rhs == S.tail)
	{
		flag = "rhs";
	}

	while(lhs != temp.tail && rhs != S.tail)
    {
		if(lhs->value > rhs->value)
		{
			Node* newNode = new Node(rhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			rhs = rhs->next;
			if(rhs == S.tail)
            {
                flag = "rhs";
                break;
            }

		}
		else if(lhs->value < rhs->value)
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			lhs = lhs->next;
		}
		else
        {
            Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			lhs = lhs->next;
			rhs = rhs->next;
			if(rhs == S.tail)
            {
                flag = "rhs";
                break;
            }
        }
    }

	if(flag == "rhs") //Rhs reached end
	{
		while(lhs != temp.tail)
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			lhs = lhs->next;
		}
	}
	else //Lhs reached end
	{
		while (rhs != S.tail)
		{
			Node* newNode = new Node(rhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			rhs = rhs->next;
		}
	}


	return *this;
}


//Modify Set *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{

	if (this->head == S.head) //If the first and
	{
		return *this;
	}

	Set temp(*this);

	make_empty();
	
	Node* lhs = temp.head->next;
	Node* rhs = S.head->next;


	while (lhs != temp.tail && rhs != S.tail)
	{
		if (lhs->value > rhs->value)
		{
			rhs = rhs->next;
		}
		else if (lhs->value < rhs->value)
		{
			lhs = lhs->next;
		}
		else
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			lhs = lhs->next;
			rhs = rhs->next;
		}
	}

	return *this;
}


//Modify Set *this such that it becomes the Set difference between *this and Set S
Set& Set::operator-=(const Set& S)
{
	if (this->head == S.head)
	{
		make_empty();
		return *this;
	}
	
	Set temp(*this);
	make_empty();
	string flag;

	Node* lhs = temp.head->next;
	Node* rhs = S.head->next;

	if (rhs == S.tail)
	{
		flag = "rhs";
	}

	while(lhs != temp.tail && rhs != S.tail)
	{
		if (lhs->value > rhs->value)
		{
			rhs = rhs->next;
			if (rhs == S.tail)
			{
				flag = "rhs";
				break;
			}
		}
		else if (lhs->value < rhs->value)
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;
			lhs = lhs->next;
		}
		else
		{
			lhs = lhs->next;
			rhs = rhs->next;
			if (rhs == S.tail)
			{
				flag = "rhs";
				break;
			}
		}
	}
	
	if (flag == "rhs") //Rhs reached end
	{
		while (lhs != temp.tail)
		{
			Node* newNode = new Node(lhs->value, tail, tail->prev);
			tail->prev->next = newNode;
			tail->prev = newNode;
			++counter;

			lhs = lhs->next;
		}
	}
	
	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	Node* lhs = head->next;
	Node* rhs = b.head->next;

	if (b.counter < counter)
	{
		return false;
	}

	while (lhs != tail && rhs != b.tail)
	{
		if (lhs->value < rhs->value)
		{
			return false;
		}
		else if (lhs->value > rhs->value)
		{
			rhs = rhs->next;
		}
		else
		{
			rhs = rhs->next;
			lhs = lhs->next;
		}
	}
	
	
	return true;
}


//Return true, if the set is equal to set b
//a == b, if a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	if (b.counter != counter)
	{
		return false;
	}
	
	Node* lhs = head->next;
	Node* rhs = b.head->next;

	while (lhs != tail && rhs != b.tail)
	{
		if ((lhs->value < rhs->value) || (lhs->value > rhs->value))
		{
			return false;
		}
		else
		{
			rhs = rhs->next;
			lhs = lhs->next;
		}
	}

	return true;
}


//Return true, if the set is different from set b
//a == b, if a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	return !(*this == b);
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, if a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	if (*this <= b && counter != b.counter) {
		return true;
	}
	
	return false;
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


