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
			
		public:
			List()
			{
				size = 0;
				start = (Node*)0;
				end = (Node*)0;
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
				
				Node* cur_node = start;
				Node* prev_node = start; // safeguard against crash
				
				for (int i = 0; i < idx; i++)
				{
					prev_node = cur_node;
					cur_node = cur_node->next;
				}
				
				prev_node->next = cur_node->next;
				if (idx == 0) start = cur_node->next;
				if (idx == (size - 1)) end = prev_node;
				if (size == 1)
				{
					// clear 
					start = (Node*)0;
					end = (Node*)0;
				}
				// if else if else if else
				
				delete cur_node;
				size--;
			}
			
			T operator[](unsigned long index)
			{	
				Node* cur_node = start;
				for (int i = 0; i < index; i++)
				{
					cur_node = cur_node->next;
				}
				return cur_node->data;
			}
			
			int getSize()
			{
				return size;
			}
		};
	}
}