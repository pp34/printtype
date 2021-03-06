// printType.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define printType(t) std::cout<<#t<<"'s type is : "<<type_name<decltype(t)>()<<std::endl

template <typename T> std::string type_name();


int main()
{
	const int &p=12;
	printType(p);
    return 0;
}

template <class T>
std::string
type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own
	(
#ifndef _MSC_VER
		abi::__cxa_demangle(typeid(TR).name(), nullptr,
			nullptr, nullptr),
#else
		nullptr,
#endif
		std::free
	);
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)
		r += " const";
	if (std::is_volatile<TR>::value)
		r += " volatile";
	if (std::is_lvalue_reference<T>::value)
		r += "&";
	else if (std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}