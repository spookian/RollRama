#include "common/List.h"
#define nullptr (Node*)0

namespace hel
{
	namespace common
	{
		List::Node()
		{
			size = 0;
			start = nullptr;
			end = nullptr;
		}
		
		List::~Node()
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
		
		void List::add(T object)
		{
			if (end == nullptr)
			{
				if (start == nullptr) start = new Node();
				end = new Node();
				start->next = end;
			}
			else
			{
				end->next = new Node();
				end = end->next;
			}
			end->data = object;
			size++;
			
			return;
		}
		
		void List::remove(int idx)
		{
			if ((idx > size) || (idx < 0) || (size == 0)) return;
			
			Node* cur_node = start;
			Node* prev_node;
			
			for (int i = 0; i < idx; i++)
			{
				if (i == (idx - 1)) prev_node = cur_node;
				cur_node = cur_node->next;
			}
			
			prev_node->next = cur_node->next;
			delete cur_node;
			size--;
		}
		
	}
}