#include "types/list.h"

#include <iostream>
#include <vector>

int main()
{
	park18::types::List<int> list;

	std::cout << "/********** PushBack **********/" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		list.PushBack(i);
	}
	list.Print();

	std::cout << "/********** Insert **********/" << std::endl;
	list.Insert(100, 1);
	list.Insert(300, 3);
	list.Insert(500, 5);
	list.Insert(600, 6);
	list.Insert(800, 8);
	list.Insert(900, 9);
	list.Print();

	std::cout << "/********** Erase **********/" << std::endl;
	list.Erase(list.GetSize() - 1);
	list.Erase(9);
	list.Erase(6);
	list.Erase(5);
	list.Erase(1);
	list.Erase(0);
	list.Print();

	std::cout << "/********** PopFront **********/" << std::endl;
	list.PopFront();
	list.Print();
	
	std::cout << "/********** PopBack **********/" << std::endl;
	list.PopBack();
	list.Print();

	std::cout << "/********** Clear **********/" << std::endl;
	list.Clear();
	list.Print();
}