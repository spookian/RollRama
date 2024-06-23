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
			
			int size;
			Node* start;
			Node* end;
			
			//performanace increase
			Node* cache_node;
			int cache_idx;
		public:
			List()
			{
				size = 0;
				cache_idx = 0;
				
				start = (Node*)0;
				end = start;
				cache_node = start;
			}
			
			~List()
			{
				Node* cur_node = start;
				for (int i = 0; i < size; i++)
				{
					Node* temp = cur_node->next;
					delete cur_node;
					
					cur_node = temp;
				}
				return;
			}
			
			void append(T object)
			{
				Node* new_end = new Node();
				if (end != (Node*)0) end->next = new_end;
				if (start == (Node*)0) start = new_end;
				end = new_end;
				
				end->data = object;
				size++;
				
				return;
			}
			
			void remove(unsigned long idx)
			{
				if (idx > (size - 1)) return;
				if (idx == cache_idx) cache_node = (Node*)0; // this is the simplest solution
				Node* cur_node = start;
				Node* prev_node = start; // safeguard against crash
				if (idx == 0)
				{
					start = cur_node->next;
					if (size == 1)
					{
						// clear 
						start = (Node*)0;
						end = (Node*)0;
					}
				}
				else
				{
					for (int i = 0; i < idx; i++)
					{
						prev_node = cur_node;
						cur_node = cur_node->next;
					}
					
					prev_node->next = cur_node->next;
					if (idx == (size - 1)) end = prev_node;
				}
				
				delete cur_node;
				size--;
			}
			
			T operator[](unsigned long index)
			{	
				int iterate = index;
				Node* cur_node = start;
				
				if ((cache_node) && (index >= cache_idx))
				{
					cur_node = cache_node;
					iterate = index - cache_idx;
				}

				for (int i = 0; i < iterate; i++)
				{
					cur_node = cur_node->next;
				}
				
				cache_idx = index; 
				cache_node = cur_node;
				return cur_node->data;
			}
			
			int getSize()
			{
				return size;
			}
		};
	}
}