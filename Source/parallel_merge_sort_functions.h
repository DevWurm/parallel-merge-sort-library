

#include <deque>
#include <thread>
#include <cstdlib>
#include "deque_functions.h"
#include <cmath>
#include "./merge_sort_functions.h"

using std::deque;
using std::thread;
using std::ref;
using std::ceil;
using std::floor;

namespace par_merge_sort {

template<typename T>
struct thread_block {
	thread t;
	deque<T> data;
};

template<typename T>
void parallel_merge_sort(deque<T>& input, int& basic_width) {
	int input_size = input.size();
	for (int list_width = basic_width; list_width <= ceil(input_size/2); list_width *= 2) {
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

template<typename T>
void parallel_merge_sort_manager(deque<T>& input) {
	int num_of_threads = thread::hardware_concurrency();
	deque<thread_block<T>> thread_list;
	int input_size = input.size();
	int basic_width = 1;

	while (num_of_threads > 0) {
		for (int i = 0; i <= num_of_threads-1; i++) {
			if (i != num_of_threads-1) {
				thread_list.push_back(new thread_block<T>);
				restack(input,thread_list.at(i).data, ceil(input_size/num_of_threads));
				thread_list.at(i).t = thread(parallel_merge_sort<T>, ref(thread_list.at(i).data), ref(basic_width));
			}
			else {
				thread_list.push_back(new thread_block<T>);
				restack(input,thread_list.at(i).data, ceil(input.size()));
				thread_list.at(i).t = thread(parallel_merge_sort, ref(thread_list.at(i).data), ref(basic_width));
			}
		}
		for (int i = 0; i <= thread_list.size()-1; i++ ) {
			thread_list.at(i).t.join();
			restack(thread_list.at(i).data, input, thread_list.at(i).data.size());
		}
		thread_list.erase(thread_list.begin(), thread_list.end());
		basic_width = ceil(input_size/num_of_threads);
		num_of_threads = floor(num_of_threads/2);
	}

}

}
