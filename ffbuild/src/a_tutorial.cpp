#include "stdafx.h"
#include "AFunction.hpp"
#include "Operator.hpp"
#include "InitFunct.hpp"
//extern void * stack;
void a_tutorial() {
	double a=1;
	set_eq<double> p;
	double aa=*(p.f)(&a, 9.);
	Stack s = newStack(1000);
	callInitsFunct();

	Block *block = 0;
	Block::open(block);

	//	stack = newStack(1024);
	Type_Expr t0 = CConstant<double>(0);
	Type_Expr tow = CConstant<double>(2);
	C_F0 pai = Find("pi");
	C_F0 pi2=C_F0(TheOperators, "*", tow, pai);

	Block::open(block);
	AC_F0 args;
	args= block->NewVar<LocalVariable>("t", atype<double*>());
	args += t0;
	args += pi2;
	args += block->NewVar<LocalVariable>("IndexBorder", atype<long*>());
	Block::open(block);

	C_F0 x = Find("x");
	C_F0 cos = Find("cos");
	C_F0 t = Find("t");

	AC_F0 argsx;
	argsx= t;
//	C_F0 xf = C_F0(x, cos, t);

	double r=GetAny<double> (pi2.eval(s));
}