

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
void parallel_merge_sort(deque<T>& input) {
	int num_of_threads = thread::hardware_concurrency();
	deque<thread_block<T>> thread_list;
	int input_size = input.size();
	int basic_width = 1;

	while (num_of_threads > 0) {
		for (int i = 0; i <= num_of_threads-1; i++) {
			thread_list.emplace_back();
			if (i != num_of_threads-1) {
				restack(input,thread_list.at(i).data, ceil(input_size/num_of_threads));
				thread_list.at(i).t = thread(merge_sort<T>, ref(thread_list.at(i).data), ref(basic_width));
			}
			else {
				restack(input,thread_list.at(i).data, input.size());
				thread_list.at(i).t = thread(merge_sort<T>, ref(thread_list.at(i).data), ref(basic_width));
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
