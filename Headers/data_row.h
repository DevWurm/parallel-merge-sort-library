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

#ifndef DATA_ROW_H_
#define DATA_ROW_H_

#include <deque>
#include <string>
#include <ostream>
#include <istream>
#include "../libcsv/libcsv.h"

using std::deque;
using std::string;
using csv::csv_parser;
using csv::csv_creator;
using std::ostream;
using std::istream;


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
	data_row(data_row<T>&& input); //move constructor from data_row
	data_row(const data_row<T>& input); //copy constructor from data_row

	data_row<T>& operator=(deque<T>&& input); //move operator from deque
	data_row<T>& operator=(const deque<T>& input); //assign operator from deque

	friend data_row<T>& operator >>(csv_parser<T>& input, data_row<T>& target);
	csv_creator<T>& operator >>(csv_creator<T> target);
	friend istream& operator >>(istream& input, data_row<T> target);
	friend ostream& operator <<(ostream& output, data_row<T> source);

	void merge_sort();
	void parallel_merge_sort();

	void set_data(deque<T>&& input); //set data from deque (move)
	void set_data(const deque<T>& input); //set data from deque

	deque<T> get_data() const; //get data as deque
	string get_type() const; //get type

	void clear(); //delete data
};


}



#endif /* DATA_ROW_H_ */
