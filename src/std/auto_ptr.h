#pragma once
#include "allocate.h"

namespace std
{
	template <class T>
	struct auto_ptr
	{
		T* ptr;
		
		auto_ptr(T* _ptr)
		{
			ptr = _ptr;
		}
		
		~auto_ptr()
		{
			delete ptr;
		}
		
		inline T* operator->() const
		{
			return ptr;
		}
	};
}