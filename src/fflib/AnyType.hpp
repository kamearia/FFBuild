// -*- Mode : c++ -*-
//
// SUMMARY  :      
// USAGE    :        
// ORG      : 
// AUTHOR   : Frederic Hecht
// E-MAIL   : hecht@ann.jussieu.fr
//

/*

This file is part of Freefem++

Freefem++ is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

Freefem++  is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Freefem++; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
//   definition of the a type to store any bacis type
//   void *, long, double, complex, all bigger type 
//   are pointer 
//#define WITHCHECK
#pragma once
#include <ostream>
using namespace std;
/// cf [[file:AFunction.hpp::basicForEachType]]

class basicForEachType;

/// <<aType>> uses [[file:AFunction.hpp::basicForEachType]]

typedef const  basicForEachType * aType;

ostream & operator<<(ostream & f, const basicForEachType & e);

//typedef  unsigned char  AnyData[24]; 

//typedef  unsigned char  AnyData[2*(sizeof(void*)+2*sizeof(double))];
//  change for 64 architecture must containt 2*(1 ptr + 3 long))
//  and for 32    2( ptr + 2 double) 
//  so 2( 3ptr + double ) sims Ok FH MAI 2006
//typedef  unsigned char  AnyData[2*(3*sizeof(void*)+sizeof(double))];
typedef  unsigned char  AnyData[2 * (5 * sizeof(void*))]; //  change . 

template <class T, bool ok>
class CheckSize { };
template <class T>
class CheckSize<T, false> {
	CheckSize() { } // private constructor to see the error
};

#ifdef WITHCHECK
extern map<const string, basicForEachType *> map_type;


class AnyTypeWithCheck {

private:
	union {
		AnyData data;
		void * p;
		double r;
		long l;
		bool b;
		//      complex<double> c;
	};
public:
	const basicForEachType *ktype;
	//    friend ostream & operator<<(ostream &f,const AnyTypeWithCheck &p);  
	AnyTypeWithCheck() : ktype(0) {}
	AnyTypeWithCheck(long ll) { l = ll; ktype = map_type[typeid(long).name()]; }
	AnyTypeWithCheck(double dd) { r = dd; ktype = map_type[typeid(double).name()]; }
	AnyTypeWithCheck(bool bb) { b = bb; ktype = map_type[typeid(bool).name()]; }

	void operator =(void *pp) { p = pp; }
};

template<typename T>   AnyTypeWithCheck SetAny(const T & x)
{
	AnyTypeWithCheck any;
	CheckSize<T, sizeof(T) <= sizeof(AnyData) >();
	throwassert((any.ktype = map_type[typeid(T).name()]));
	throwassert(sizeof(T) <= sizeof(AnyData));
	//a.t=x;
	memcpy(&any, &x, sizeof(x));
	return any;
}
template<typename T>   AnyTypeWithOutCheck inline SetPtrAny(T *  p)
{
	throwassert((any.ktype = map_type[typeid(T*).name()]));
	return p;
}
inline AnyTypeWithCheck PtrtoAny(void * p, aType r)
{
	AnyTypeWithCheck any;
	any = p;
	throwassert(any.ktype = r);
	return any;
}
template<class T> inline const T& GetAny(const AnyTypeWithCheck & x);

template<class T> inline  const T& GetAny(const AnyTypeWithCheck & x)
{
	CheckSize<T, sizeof(T) <= sizeof(AnyData) >();
	if (x.ktype != map_type[typeid(T).name()])
	{
		cerr << "GetAny: PB type <";
		cerr << typeid(T).name();
		cerr << "> <=" << *(x.ktype) << endl;
		throw(ErrorExec("exit", 1));
	}
	return *static_cast<const T*>(static_cast<const void*>(&x));
}
typedef   AnyTypeWithCheck AnyType;

#else

class AnyTypeWithOutCheck {

public:
	union {
		AnyData data;
		void * p;
		double r;
		long l;
		bool b;
		//      complex<double> c;
	};
public:
	AnyTypeWithOutCheck() {}
	AnyTypeWithOutCheck(long ll) { l = ll; }
	AnyTypeWithOutCheck(double dd) { r = dd; }
	AnyTypeWithOutCheck(void *pp) { p = pp; }
	AnyTypeWithOutCheck(bool bb) { b = bb; }

	void operator =(void *pp) { p = pp; }
	static void test();
};

template<typename T>   AnyTypeWithOutCheck inline SetAny(const T & x)
{
	AnyTypeWithOutCheck any;
	CheckSize<T, sizeof(T) <= sizeof(AnyData) >();
	// plus stable ???  F avril 2006 FH. 
	memcpy(&any, &x, sizeof(x));
	// plante  de temps en temps sous wind32 .  FH 
	//any = *(  (AnyTypeWithOutCheck *) (void *) &x); 
	return any;
}

template<typename T>   AnyTypeWithOutCheck inline SetPtrAny(T *  p)
{
	return p;
}
inline AnyTypeWithOutCheck PtrtoAny(void * p, aType)
{
	return p;
}
template<>  inline AnyTypeWithOutCheck SetAny<double>(const double & x)
{
	return x;
}
template<> inline  AnyTypeWithOutCheck SetAny<long>(const long & x)
{
	return x;
}
template<> inline  AnyTypeWithOutCheck SetAny<bool>(const bool & x)
{
	return x;
}

template<typename T>  inline  AnyTypeWithOutCheck SetAny(T *  x)
{
	return reinterpret_cast<void *>(x);
}
template<typename T>  inline  AnyTypeWithOutCheck SetAny(const T * x)
{
	return reinterpret_cast<void *>(x);
}
template<typename T> inline  const T& GetAny(const AnyTypeWithOutCheck & x)
{
	CheckSize<T, sizeof(T) <= sizeof(AnyData) >();
	return *static_cast<const T*>(static_cast<const void*>(&x));
}

template<> inline const double& GetAny<double>(const AnyTypeWithOutCheck & x)
{
	return x.r;
}
template<>  inline const long& GetAny<long>(const AnyTypeWithOutCheck & x)
{
	return x.l;
}
template<>  inline const bool& GetAny<bool>(const AnyTypeWithOutCheck & x)
{
	return x.b;
}

template<class T>  inline T * PGetAny(const AnyTypeWithOutCheck & x)
{
	return static_cast< T*>(x.p);
}

//template<class T>  inline   T * const & GetAny<T*>(const AnyTypeWithOutCheck & x)
//  { return  x.p;}

typedef   AnyTypeWithOutCheck AnyType;
#endif

void AnyType::test() {
	AnyType x(1.0);
	cout << "x.r= " << x.r << endl;

	AnyType y(SetAny(1.0));
	cout << "y.r= " << y.r << endl;

	cout << "GetAny<double>(y)=" << GetAny<double>(y) << endl;

	int *p =new int[5];
	p[0] = 1, p[1]=2, p[2]=3, p[3]=4;
	AnyType z(p);
	int *zz = GetAny<int *>(z);
	cout << "zz= ";
	for (int i = 0; i < 5; i++)
		cout << "  [ " << i << "]=" << zz[i];
	cout<<endl;
	delete[] zz;
}



