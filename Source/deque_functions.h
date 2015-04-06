/*
 * deque_functions.h
 *
 *  Created on: 05.04.2015
 *      Author: leo
 */

#ifndef DEQUE_FUNCTIONS_H_
#define DEQUE_FUNCTIONS_H_

#include <deque>
#include <stdexcept>
#include <cmath>
#include "../liberror/liberror.h"

using std::deque;
using std::out_of_range;
using err::error;

namespace par_merge_sort {

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

}

#endif /* DEQUE_FUNCTIONS_H_ */
