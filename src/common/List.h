#pragma once

namespace hel
{
	namespace common
	{
		template <typename T>
		class List
		{
			struct Node
			{
				T data;
				Node* next;
			};
			
			unsigned long size;
			Node* start;
			Node* end;
			
		public:
			Node();
			~Node();
			void add(T object);
			T& operator[](unsigned long index);
		};
	}
}