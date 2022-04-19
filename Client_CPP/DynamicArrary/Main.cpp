#include <iostream>
//#include "DynamicArrary.h"
#include "DynaminArraryTemplate.h"

int main() {

	/*DynamicArrary da;
	da.Add(1);
	da.Add(2);

	std::cout << "1 을 찾을 수 있나여 ?" << da.IsExist(1) << std::endl;

	da.Remove(1);

	da.Delete();*/

	DynamicArrary<int> int_DA;
	DynamicArrary<double> double_DA;
	DynamicArrary<float> float_DA;

	int_DA.Add(0);
	int_DA.Remove(0);

	return 0;
}