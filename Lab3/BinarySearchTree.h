#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

class Frequency
{
private:

	string key;

	friend ostream& operator<<(ostream& os, const Frequency &freq)
	{
		os << left << setw(15) << freq.key << setw(10) << right << freq.counter;
		return os;
	}

public:

	int counter = 1;

	Frequency(string inKey)
		:key{ inKey }
	{
	}

	void update_counter()
	{
		counter++;
	}

	bool operator<(const Frequency &rhs) const
	{
		return (key < rhs.key);
	}
};

template <typename Comparable>
class BinarySearchTree
{
	private:
		
		struct BinaryNode
		{
			Comparable element;
			BinaryNode *parent = nullptr;
			BinaryNode *left;
			BinaryNode *right;

			BinaryNode(const Comparable& theElement, BinaryNode *lt, BinaryNode *rt)
				:element{ theElement }, left{ lt }, right{ rt }  {}

			BinaryNode(Comparable&& theElement, BinaryNode *lt, BinaryNode *rt)
				:element{ std::move(theElement) }, left{ lt }, right{ rt }{}
		};

		BinaryNode *root;

	public:

		class BiIterator
		{
			private:
				BinaryNode* current;
			
			public:
				BiIterator()
				:current{nullptr}
				{

				}
			
				BiIterator(BinaryNode* node)
				{
					current = node;
				}
			
				BiIterator& operator++()
				{
					current = find_successor(current);

					return *this;
				}

				BiIterator& operator++(int)
				{
					const BiIterator old(*this);
					++(*this);
					return old;
				}

				BiIterator& operator--()
				{
					current = find_predecessor(current);

					return *this;
				}

				BiIterator& operator--(int)
				{
					const BiIterator old(*this);
					--(*this);
					return old;
				}

				bool operator==(const BiIterator &rhs)
				{
					return (current == rhs.current);
				}

				bool operator!=(const BiIterator &rhs)
				{
					return !(*this == rhs);
				}

				Comparable& operator*()
				{
					return current->element;
				}

				Comparable* operator->()
				{
					return current;
				}

		};

	BiIterator begin()
	{
		if (isEmpty()) return end();

		return BiIterator(findMin(root));
	}

	BiIterator end()
	{
		return BiIterator();
	}

    BinarySearchTree( )
	:root{nullptr}
    {
	};

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree& rhs) : root{nullptr}
    {
        root = clone( rhs.root );
	};

    /**
     * Move constructor
     */
    BinarySearchTree(BinarySearchTree&& rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
	};

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
	};

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree& operator=(BinarySearchTree _copy)
    {
        std::swap( root, _copy.root );
        return *this;
	};


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable& findMin() const
    {
        if(isEmpty())
        {
            throw UnderflowException{};
        }

        return findMin(root)->element;
	};

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable& findMax() const
    {
        if(isEmpty())
        {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    //Uncomment for Exercise 1 & 2
	//bool contains(const Comparable& x) const
	//Uncomment for Execise 3 & 4
    BiIterator contains(const Comparable &x) const
    {
		//Uncomment for Exercise 1 & 2
        //return (contains(x, root) != nullptr);
		
    	//Uncomment for Execise 3 & 4
		return BiIterator(contains(x, root));
    }


    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(ostream & out = cout) const
    {
        if(isEmpty())
        {
            out << "Empty tree" << endl;
        }
        else
        {
            printTreePreOrder( root, out );
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable & x)
    {
		root = insert(x, root);
	};

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable && x)
    {
        root = insert(std::move(x), root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable& x)
    {
        root = remove(x, root);
    }

	Comparable get_parent(const Comparable& x)
    {
		BinaryNode* temp = root;
		Comparable temp_comp(0);

		while (temp != nullptr)
		{
			if (temp->element < x) temp = temp->right;
			else if (temp->element > x) temp = temp->left;
			else
			{
				return (temp->parent != nullptr) ? temp->parent->element : temp_comp;
			}
		}

		return temp_comp;
    }

	void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& suc)
	{
    	if(contains(x, root) != nullptr)
    	{
			if (findMin(root)->element >= x) pred = x;
    		else pred = find_predecessor(contains(x, root))->element;
			
			if (findMax(root)->element <= x) suc = x;
			else suc = find_successor(contains(x, root))->element;
    	}
		else //x is not found in tree
		{
			BinaryNode* tempRoot = root;
			while(tempRoot != nullptr)
			{
				if(tempRoot->element < x)
				{
					pred = tempRoot->element;
					tempRoot = tempRoot->right;
				}
				else
				{
					suc = tempRoot->element;
					tempRoot = tempRoot->left;
				}
			}
		}
	}

  private:

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
    */
	BinaryNode* insert(const Comparable& x, BinaryNode* t)
    {

        if(t == nullptr)
        {
            t = new BinaryNode{x, nullptr, nullptr};
        }
        else if(x < t->element)
        {
            t->left = insert(x, t->left);
			t->left->parent = t;
        }
        else if(t->element < x)
        {
            t->right = insert(x, t->right);
			t->right->parent = t;
        }
        else
        {
			//Uncomment for Exercise 4
			/*if(is_same<Frequency, Comparable>::value)
			{
				t->element.update_counter();
			}*/
        }
        return t;
	}

	/**
	 * Private member function to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x.
	 */
	BinaryNode* insert(Comparable &&x, BinaryNode* t)
	{
		if (t == nullptr)
		{
			t = new BinaryNode{ std::move(x), nullptr, nullptr };
		}
		else if (x < t->element)
		{
			t->left = insert(std::move(x), t->left);
			t->left->parent = t;
		}
		else if (t->element < x)
		{
			t->right = insert(std::move(x), t->right);
			t->right->parent = t;
		}
		else
		{
			;
		}
		return t;
	};

    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    BinaryNode* remove(const Comparable& x, BinaryNode *t)
    {
        if(t == nullptr)
        {
            return t;   // Item not found
        }
        if(x < t->element)
        {
            t->left = remove(x, t->left);
        }
        else if(t->element < x)
        {
             t->right = remove(x, t->right);
        }

        else if(t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
        }
        else
        {
        	BinaryNode *oldNode = t;

			if(t->left != nullptr || t->right != nullptr) // Check if leaf
			{
				(t->left != nullptr) ? t->left->parent = t->parent : t->right->parent = t->parent;
			}

			t = (t->left != nullptr) ? t->left : t->right;

            delete oldNode;
        }

         return t;
    }

	static BinaryNode* find_successor(BinaryNode* t)
    {
		
		if (t->right != nullptr) return findMin(t->right);

		BinaryNode* p = t->parent;
		while(p != nullptr && t == p->right)
		{
			t = p;
			p = p->parent;
		}

		return p;
    }

	static BinaryNode* find_predecessor(BinaryNode* t)
	{

		if (t->left != nullptr) return findMax(t->left);

		BinaryNode* p = t->parent;
		while (p != nullptr && t == p->left)
		{
			t = p;
			p = p->parent;
		}

		return p;
	};

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static BinaryNode* findMin(BinaryNode *t)
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        if(t->left == nullptr)
        {
           return t;
        }

        //Tail recursion can be easily replaced by a loop
        return findMin(t->left); //recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static BinaryNode* findMax(BinaryNode *t)
    {
        if( t != nullptr )
        {
            while( t->right != nullptr )
            {
                t = t->right;
            }
        }

        return t;
    }


    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    BinaryNode* contains(const Comparable &x, BinaryNode *t) const
    {
        if(t == nullptr)
        {
            return t;
        }
        else if(x < t->element)
        {
            return contains(x, t->left);
        }
        else if(t->element < x)
        {
            return contains(x, t->right);
        }
        else
        {
            return t;    // Match
        }
    }
/****** NONRECURSIVE VERSION*************************
    Node* contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
        {
            if( x < t->element )
            {
                t = t->left;
            }
            else if( t->element < x )
            {
                t = t->right;
            }
            else
            {
                return t;    // Match
            }
        }

        return t;   // No match
    }
*****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    BinaryNode* makeEmpty( BinaryNode *t)
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }

        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( BinaryNode *t, ostream & out) const
    {
        if(t != nullptr)
        {
            printTree(t->left, out);
			out << t->element << endl;
            printTree(t->right, out);
        }
    }

	void printTreePreOrder(BinaryNode *t, ostream& out, string d = "") const
    {
	    if( t != nullptr)
	    {
			out << d << t->element << endl;
	    	printTreePreOrder(t->left, out, d + "   ");
			printTreePreOrder(t->right, out, d + "   ");
	    }
    }

    /**
     * Private member function to clone subtree.
     */
    BinaryNode* clone(BinaryNode *t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        else
        {
            
			BinaryNode* temp = new BinaryNode(t->element, clone(t->left), clone(t->right));

			if(temp->left != nullptr)
			{
				temp->left->parent = temp;
			}

			if(temp->right != nullptr)
			{
				temp->right->parent = temp;
			}

			return temp;

        }
    }
};

#endif
