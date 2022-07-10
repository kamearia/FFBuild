#include "stdafx.h"
#include "AFunction.hpp"
#include "Operator.hpp"
#include "InitFunct.hpp"
//extern void * stack;
void a_tutorial() {
	double a=1;
	set_eq<double> p;
	double x=*(p.f)(&a, 9.);
	Stack s = newStack(1000);
	callInitsFunct();
	//	stack = newStack(1024);
	Type_Expr t0 = CConstant<double>(0);
	Type_Expr tow = CConstant<double>(2);
	C_F0 pai = Find("pi");
	C_F0 pi2=C_F0(TheOperators, "*", tow, pai);



	double r=GetAny<double> (pi2.eval(s));
}