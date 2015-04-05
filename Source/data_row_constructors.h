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
#include <string>

using std::deque;
using std::string;

namespace par_merge_sort {

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

/*
template<typename T>
data_row<T>::data_row(data_row<T>&& input) {
	type = typeid(T).name();
	data.assign(input.get_data().begin(), input.get_data().end());
	input.get_data().clear();
}

template<typename T>
data_row<T>::data_row(const data_row<T>& input) {
	type = typeid(T).name();
	data.assign(input.get_data().begin(), input.get_data().end());
}
*/
}
