#include <iostream>
#include "List.h"
#include "tree.h"
#include "Map.h"
#include <string>


int main()
{
	Map <string, int> marker;

	

	marker.insert("QWERT",10);
	marker.insert("ASDFG",100);
	marker.insert("SERGEY", 1000);

	cout << endl;
	marker.printTree();
}

