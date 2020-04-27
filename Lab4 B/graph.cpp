/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <queue>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INF = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
	int *dist = new int[size + 1];
	int *path = new int[size + 1];
	bool *done = new bool[size + 1];

	for(int n = 1; n <= size; ++n)
	{
		dist[n] = INF;
		path[n] = 0;
		done[n] = false;
	}

	int v = 1;
	dist[v] = 0;
	done[v] = true;

	int totW = 0;
	int d;

	while (true)
	{
		Node *temp = array[v].getFirst();

		while (temp != nullptr)
		{
			if (!done[temp->vertex] && dist[temp->vertex] > temp->weight)
			{
				dist[temp->vertex] = temp->weight;
				path[temp->vertex] = v;
			}

			temp = temp->next;
		}

		d = INF;

		for(int i = 1; i <= size; ++i)
		{
			if(!done[i] && dist[i] < d)
			{
				d = dist[i];
				v = i;
			}
		}

		if (d == INF) break;

		Edge myEdge(path[v], v, dist[v]);
		cout << myEdge << endl;

		totW += dist[v];

		done[v] = true;
	}

	cout << "Total weight is: " << totW << endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
	int totW = 0;

	Heap<Edge> myHeap(size - 1);

	//Add all edges to heap
	for(int i = 1; i <= size; ++i)
	{
		Node* temp = array[i].getFirst();
		while(temp != nullptr)
		{
			if(i < temp->vertex)
			{
				Edge myEdge(i, temp->vertex, temp->weight);
				myHeap.insert(myEdge);
			}

			temp = temp->next;
		}
	}

	DSets mySets(size);
	

	int counter = 0;

	while(counter < size - 1)
	{
		Edge myEdge = myHeap.deleteMin();

		if(mySets.find(myEdge.head) != mySets.find(myEdge.tail))
		{
			cout << myEdge << endl;
			mySets.join(mySets.find(myEdge.head), mySets.find(myEdge.tail));
			totW += myEdge.weight;
			counter++;
		}

	}

	cout << "Total weight is: " << totW << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
