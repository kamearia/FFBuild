#include "stdafx.h"
//#include "AFunction.hpp"
#include "AnyType.hpp"
#include "CodeAlloc.hpp"
#include "AFunction.hpp"

using namespace std;
/*
int main() {
//	ForTypeVoid *x=new ForTypeVoid();
//	cout << x << endl;

//	AnyType::test();
//	CodeAllocT<int>::test();

	Init_map_type();
}
*/
int getprog(char *fn, int argc, char **argv);
int mainff(int  argc, char **argv);
int main(int  argc, char **argv)
{
#ifndef kame
	ffapi::init(); // [[file:~/ff/src/fflib/ffapi.cpp::init]]

				   // Calls either [[file:~/ff/src/mpi/parallelempi.cpp::init_ptr_parallelepmi]] or
				   // [[file:~/ff/src/mpi/parallelempi-empty.cpp::init_ptr_parallelepmi]]
	init_ptr_parallelepmi();
#endif
//	return mainff(argc, argv); // [[file:lg.ypp::mainff]]
//	char      fn[1024];
//	if (getprog(fn, argc, argv))
		return mainff(argc, argv);
}