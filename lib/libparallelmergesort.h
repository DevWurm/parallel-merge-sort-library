/*
 * libparallelmergesort.h
 *
 *  Created on: 05.04.2015
 *      Author: leo
 */

#ifndef LIB_LIBPARALLELMERGESORT_H_
#define LIB_LIBPARALLELMERGESORT_H_

#include <deque>
#include <string>
#include <ostream>
#include <istream>
#include <stdexcept>
#include <cmath>
#include "liberror.h"
#include "libcsv.h"

using std::deque;
using std::string;
using csv::csv_parser;
using csv::csv_creator;
using csv::csv_handler;
using std::ostream;
using std::istream;
using std::out_of_range;
using err::error;


namespace par_merge_sort {

	template<typename T>
	class data_row {
	private:
		deque<T> data;
		string type;
	public:
		data_row(); //standard constructor
		data_row(deque<T>&& input); //move constructor from deque
		data_row(const deque<T>& input); //copy constructor from deque

		data_row<T>& operator=(deque<T>&& input); //move operator from deque
		data_row<T>& operator=(const deque<T>& input); //assign operator from deque

		template<typename S>
		friend data_row<S>& operator >>(csv_parser<S>& input, data_row<S>& target);
		csv_creator<T>& operator >>(csv_creator<T> target);
		template<typename S>
		friend istream& operator >>(istream& input, data_row<S> target);
		template<typename S>
		friend ostream& operator <<(ostream& output, data_row<S> source);

		void merge_sort_data();
		void parallel_merge_sort_data();

		void set_data(deque<T>&& input); //set data from deque (move)
		void set_data(const deque<T>& input); //set data from deque

		deque<T> get_data() const; //get data as deque
		string get_type() const; //get type

		void clear(); //delete data
	};

	template<typename T>
	data_row<T>::data_row() {
		type = typeid(T).name();
	}

	template<typename T>
	data_row<T>::data_row(deque<T>&& input): data(input) {
		type = typeid(T).name();
		input.clear();
	}

	template<typename T>
	data_row<T>::data_row(const deque<T>& input): data(input) {
		type = typeid(T).name();
	}

	template<typename T>
	data_row<T>& data_row<T>::operator =(const deque<T>& input) {
		data = input;
	}

	template<typename T>
	data_row<T>& data_row<T>::operator =(deque<T>&& input) {
		data = input;
		input.clear();
	}

	template<typename T>
	data_row<T>& operator >>(csv_parser<T>& input, data_row<T>& target) {
		input >> target.data;
		return target;
	}

	template<typename T>
	csv_creator<T>& data_row<T>::operator >>(csv_creator<T> target) {
		data >> target;
		return target;
	}

	template<typename T>
	istream& operator >>(istream& input, data_row<T> target) {
		csv_handler<T> temp_handler;
		input >> temp_handler >> target.data;
		return input;
	}

	template<typename T>
	ostream& operator <<(ostream& output, data_row<T> source) {
		csv_handler<T> temp_handler;
		source.data >> temp_handler >> output;
		return output;
	}

	template<typename T>
	void data_row<T>::set_data(const deque<T>& input) {
		data = input;
	}

	template<typename T>
	void data_row<T>::set_data(deque<T>&& input) {
		data = input;
		input.clear();
	}

	template<typename T>
	deque<T> data_row<T>::get_data() const {
		return data;
	}

	template<typename T>
	string data_row<T>::get_type() const {
		return type;
	}

	template<typename T>
	void data_row<T>::clear() {
		data.clear();
	}

	template<typename T>
	void restack (deque<T>& source, deque<T>& target, int n){ //move n elements from the front of source to the end of target
		for (int i = 0; i <= n-1; i++) {
			try {
				target.push_back(source.at(0));
				source.pop_front();
			}
			catch (out_of_range& e) {
				throw(error(1, "Not enough entries in source list"));
			}
		}
	}

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

	template<typename T>
	void data_row<T>::merge_sort_data() {
		data = merge_sort(data);
	}

	template<typename T>
	void data_row<T>::parallel_merge_sort_data() {
		data = merge_sort(data);
	}

}




#endif /* LIB_LIBPARALLELMERGESORT_H_ */
