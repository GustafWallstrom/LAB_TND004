#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include "../../BinarySearchTree.h"

using namespace std;

//Test program 4: Frequency table
int main()
{
	BinarySearchTree<Frequency> T;
	ifstream file("words.txt");

	if (!file)
	{
		cout << "couldn't open file words.txt" << endl;
		return 1;
	}

	vector<Frequency> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
	file.close();

	for (auto j : V1)
		T.insert(j);

	/**************************************/
	cout << "\nPHASE 0: Display frequency table\n\n";
	/**************************************/

	for (BinarySearchTree<Frequency>::BiIterator it = T.begin(); it != T.end(); ++it)
	{
		cout << *it << endl;
	}
	
	cout << "\nFinished testing" << endl;

	return 0;

}