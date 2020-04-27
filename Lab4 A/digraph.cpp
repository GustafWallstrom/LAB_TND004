/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <queue>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INF = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
	Queue<int> Q;

	for(int i = 1; i <= size; ++i)
	{
		dist[i] = INF;
		path[i] = 0;
	}

	dist[s] = 0;

	Q.enqueue(s);

	while(!Q.isEmpty())
	{
		int v = Q.getFront();
		Q.dequeue();

		Node *temp = array[v].getFirst();

		while(temp != nullptr)
		{
			if(dist[temp->vertex] == INF)
			{
				dist[temp->vertex] = dist[v] + 1;
				path[temp->vertex] = v;
				Q.enqueue(temp->vertex);
			}

			temp = temp->next;
		}
	}

}

// positive weighted single source shortest paths
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
	for (int i = 1; i <= size; ++i)
	{
		dist[i] = INF;
		path[i] = 0;
		done[i] = false;
	}

	dist[s] = 0;
	done[s] = true;

	int v = s;

	while(true)
	{
		Node *temp = array[v].getFirst();

		while (temp != nullptr)
		{
			if (!done[temp->vertex] && dist[temp->vertex] > (dist[v] + temp->weight))
			{
				dist[temp->vertex] = dist[v] + temp->weight;
				path[temp->vertex] = v;
			}

			temp = temp->next;
		}

		priority_queue<int, vector<int>, greater<>> pq;
		for(int n = 1; n <= size; ++n)
		{
			if(!done[n]) pq.push(dist[n]);
		}
		
		if(pq.empty()) break;
		else
		{
			for(int k = 1; k <= size; ++k)
			{
				if (dist[k] == pq.top()) v = k;
			}
		}

		done[v] = true;
	}
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
	if (path[t] == 0)
	{
		cout << " " << t << " ";
		return;
	} 

	printPath(path[t]);
	cout << "-> " << t << " ";

}
