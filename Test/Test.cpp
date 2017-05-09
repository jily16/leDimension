// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "leDimension.h"
#include <cassert>
#include <iostream>
#include <type_traits>

using namespace le;
using std::cout;
using std::endl;

namespace
{
	int tot_case = 0;
}
#define LE_ASSERT(expression)	\
		do{	\
		assert(expression);	\
		cout<<"Case #"<<++tot_case<<" passed!"<<endl;}while(0)
		
int main()
{
	{
		length l1(1);
		length l2(2);
		length l = l1 + l2;
		LE_ASSERT(l.value == 3);
	}
	{
		length l1(1);
		length l2(2);
		l1 += l2;
		LE_ASSERT(l1.value == 3);
	}
	{
		length l(1);
		length l1 = l + 1;
		length l2 = 1 + l;
		(l += 1) += 1;
		LE_ASSERT(l.value == 3 && l1.value == 2 && l2.value == 2);
	}
	{
		length l1(1);
		length l2(2);
		length l = l2 - l1;
		LE_ASSERT(l.value == 1);
	}
	{
		length l1(1);
		length l2(2);
		l2 -= l1;
		LE_ASSERT(l2.value == 1);
	}
	{
		length l(9);
		l -= 1;
		l = 10 - l;
		LE_ASSERT(l.value == 2);
	}
	{
		length l(1);
		scalar s(1);
		l *= s;
		quality<dimension<0, 2, 0, 0, 0, 0, 0>> l_square = l*l;
		LE_ASSERT(l_square.value == 1);
	}
	{
		length l(4);
		(l /= 2) /= 2;
		auto rat = l / (length(0.5));
		quality<dimension<0, 1, -1, 0, 0, 0, 0>> mps = l / (time(1));
		LE_ASSERT(rat.value == 2 && mps.value == 1);
	}
	{
		//compare operators
		length l1(9);
		length l2(10);
		LE_ASSERT(l1 < l2 && l1 < 10);
	}
	system("pause");
    return 0;
}

