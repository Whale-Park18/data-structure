#include "types/list.h"

#include <iostream>
#include <vector>

int main()
{
	park18::types::TList<int> list;

	for (int i = 1; i <= 10; i++)
	{
		list.PushBack(i);
	}
	list.Insert(500, 3);

	for (int i = 0; i < list.GetSize(); i++)
	{
		std::cout << list.At(i) << std::endl;
	}
}