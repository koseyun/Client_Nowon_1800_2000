#include <iostream>
#include <vector>
#include "DynaminArraryTemplate.h"

using namespace std;
int main() {
	
	vector<int> tmpVec;
	tmpVec.push_back(10);
	tmpVec.push_back(20);
	vector<int>::iterator iter = tmpVec.begin();
	int tmpValue = *iter;
	
	cout << tmpValue << endl;
	tmpVec.erase(iter);

	DynamicArray<int> tmpDA;
	tmpDA.Add(10);
	tmpDA.Add(20);
	tmpDA.Add(30);
	tmpDA.Add(40);

	/*DynamicArray<int>::Iterator myIter;
	myIter.p_Data = tmpDA.GetData();
	myIter._idx = 2;
	tmpValue = *myIter;
	cout << tmpValue << endl;*/

	DynamicArray<int>::Iterator iter_Begin = tmpDA.Begin();
	cout << *iter_Begin << endl;


	return 0;
}