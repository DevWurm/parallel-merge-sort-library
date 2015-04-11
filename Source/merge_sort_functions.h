

#include <deque>
#include "deque_functions.h"

using std::deque;

namespace par_merge_sort {

template<typename T>
deque<T> merge_sort_merge(deque<T>& list1, deque<T>& list2) {
	if (list1.size()==1 && list2.size()==0) {
		return list1;
	}
	else {
		deque<T> listret;
		while (list1.size() > 0 && list2.size() >0) {
			if (list1.at(0)<list2.at(0)) {
				restack(list1, listret, 1);
			}
			else {
				restack(list2, listret, 1);
			}
		}
		if (list1.size()>0) {
			restack(list1, listret, list1.size());
		}
		else if (list2.size()>0) {
			restack(list2, listret, list2.size());
		}
		return listret;
	}

}

template<typename T>
void merge_sort(deque<T>& input) {
	int input_size = input.size();
	for (int list_width = 1; list_width < input_size; list_width *= 2) {
		deque<T> buffer;
		restack(input, buffer, input.size());
		while (buffer.size() > 0) {
			deque<T> list1;
			deque<T> list2;
			if (buffer.size() >= list_width) {
				restack(buffer, list1, list_width);
			}
			else {
				restack(buffer, list1, buffer.size());
			}
			if (buffer.size() >= list_width) {
				restack(buffer, list2, list_width);
			}
			else {
				restack(buffer, list2, buffer.size());
			}
			deque<T> return_buffer = merge_sort_merge(list1, list2);
			restack(return_buffer, input, return_buffer.size());
		}

	}
}

}
