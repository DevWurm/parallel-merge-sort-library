

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
deque<T> merge_sort(deque<T>& input) {
	if (input.size() <= 1) {
		return input;
	}
	else {
		deque<T> list1;
		deque<T> list2;
		restack(input, list1, ceil(input.size()/2));
		restack(input, list2, input.size());
		list1=merge_sort(list1);
		list2=merge_sort(list2);
		return merge_sort_merge(list1, list2);
	}
}

}
