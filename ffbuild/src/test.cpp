#include "stdafx.h"
extern int main_kame(int  argc, char **argv);
extern void a_tutorial();


#include "AFunction.hpp"
template<>
void EConstant<int>::test(){
	typedef int R;
	EConstant<int> e1(1), e2(2);
	Stack s=NULL;
	AnyType a=e1(s);
	assert(GetAny<int>(a)== 1);
	Init_map_type();
	aType type= e1.operator aType();
	cout << "type:neme= " << typeid(type).name() << endl;

	e1.dump(cout);
	int c = e1.compare(&e2);
	assert(c == -1);
	EConstant<double> e3(-1.);
	c = e1.compare(&e3);
	assert(c == -1);

	assert(!e1.Empty());
	assert(e1.nbitem() == 1);
	EConstant<int> e0(0);
	assert(e0.Zero());
}

int main(int  argc, char **argv)
{
	//	EConstant<int>::test();
	//	a_tutorial();
	return main_kame(argc, argv);

	return 1;
}