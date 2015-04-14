/*
	 * License

	 * Copyright 2015 DevWurm

	 * This file is part of parallel_merge_sort_library.

	 *  parallel_merge_sort_library is free software: you can redistribute it and/or modify
	    it under the terms of the GNU General Public License as published by
	    the Free Software Foundation, either version 3 of the License, or
	    (at your option) any later version.

	    parallel_merge_sort_library is distributed in the hope that it will be useful,
	    but WITHOUT ANY WARRANTY; without even the implied warranty of
	    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	    GNU General Public License for more details.

	    You should have received a copy of the GNU General Public License
	    along with parallel_merge_sort_library.  If not, see <http://www.gnu.org/licenses/>.

	    Diese Datei ist Teil von parallel_merge_sort_library.

	    parallel_merge_sort_library ist Freie Software: Sie können es unter den Bedingungen
	    der GNU General Public License, wie von der Free Software Foundation,
	    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
	    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

	    parallel_merge_sort_library wird in der Hoffnung, dass es nützlich sein wird, aber
	    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	    Siehe die GNU General Public License für weitere Details.

	    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/


#include "../Headers/data_row.h"
#include <deque>
#include <chrono>
#include <sstream>

using std::deque;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::hours;
using std::chrono::minutes;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::nanoseconds;
using std::stringstream;


namespace par_merge_sort {

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
steady_clock::duration data_row<T>::get_operation_time(string unit) const { //return duration casted in given unit (default: milliseconds)
	if (unit == "h") {
		return duration_cast<hours>(operation_time);
	}
	else if (unit == "m") {
		return duration_cast<minutes>(operation_time);
	}
	else if (unit == "s") {
		return duration_cast<seconds>(operation_time);
	}
	else if (unit == "mic") {
		return duration_cast<microseconds>(operation_time);
	}
	else if (unit == "nan") {
		return duration_cast<nanoseconds>(operation_time);
	}
	else {
		return duration_cast<milliseconds>(operation_time);
	}
}

template<typename T>
steady_clock::duration data_row<T>::get_operation_time() const { //return duration casted in milliseconds
	return duration_cast<milliseconds>(operation_time);
}

template<typename T>
string data_row<T>::get_operation_time_string(string unit) const { //return duration casted in given unit (default: milliseconds)
	stringstream converter;
	if (unit == "h") {
		converter << duration_cast<hours>(operation_time).count();
		return converter.str();
	}
	else if (unit == "m") {
		converter << duration_cast<minutes>(operation_time).count();
		return converter.str();
	}
	else if (unit == "s") {
		converter << duration_cast<seconds>(operation_time).count();
		return converter.str();
	}
	else if (unit == "mic") {
		converter << duration_cast<microseconds>(operation_time).count();
		return converter.str();
	}
	else if (unit == "nan") {
		converter << duration_cast<nanoseconds>(operation_time).count();
		return converter.str();
	}
	else {
		converter << duration_cast<milliseconds>(operation_time).count();
		return converter.str();
	}
}

template<typename T>
string data_row<T>::get_operation_time_string() const { //return duration casted in milliseconds
	stringstream converter;
	converter << duration_cast<milliseconds>(operation_time).count();
	return converter.str();
}

template<typename T>
int data_row<T>::get_data_length() const {
	return data.length();
}

}
