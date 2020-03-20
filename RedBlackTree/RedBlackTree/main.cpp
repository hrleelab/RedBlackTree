#include <iostream>
#include "redblack.h"

using namespace std;

int main() {
	int inserts[] = { 10,15,30,52,40,35,38,39,7,9,6 };

	IntRBTree rbtree;

	for (int i = 0;i < 11;i++) {
		rbtree.insert(inserts[i], i);
		rbtree.print();
	}

	return 0;
}