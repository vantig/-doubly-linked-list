#include"Header.h"

int main()
{
	DualList<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(5);
	list.pushBack(6);

	std::cout << list;

	return 0;
}