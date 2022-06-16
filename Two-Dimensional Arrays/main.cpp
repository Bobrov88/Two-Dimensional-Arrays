#include <iostream>
#include <conio.h>
#define _MSG cout<<" Now your _array is -> ";
#define _EMPTY cout<<" empty ";
#define OPERATION_LIST cout<<"\n Choose an operation:\n 1. Push_back\n 2. Push_front\n 3. Insert\n 4. Pop_back\n 5. Pop_front\n 6. Erase\n\n 0. to quit\t";
#define _DATATYPE cout << "\n Choose datatype: 1 - int  2 - double  3 - char  "

using namespace std;

template<typename T> int _call_menu(T**&, const int&, const int&);
template<typename T> void _print_array(T**&, const int&, const int&);
template<typename T> void _operation(T**&, int&, int&, int&);
template<typename T> void insert(T**&, int&, int&, bool, int);
template<typename T> void push_back(T**&, int&, int&, bool);
template<typename T> void push_front(T**&, int&, int&, bool);
template<typename T> void erase(T**&, int&, int&, bool, int);
template<typename T> void pop_back(T**&, int&, int&, bool);
template<typename T> void pop_front(T**&, int&, int&, bool);
template<typename T> void _delete(T**&, int &rows);

int main()
{
	setlocale(0, "");
	int** int_array = nullptr;
	double** double_array = nullptr;
	char** char_array = nullptr;
	int rows{ 0 }, cols{ 0 }, key{ 0 };
	_DATATYPE; cin >> key;
	switch (key)
	{
	case 1: while (key = _call_menu(int_array, rows, cols)!='0')		_operation(int_array, rows, cols, key);			_delete(int_array, rows);		break;
	case 2: while (key = _call_menu(double_array, rows, cols)!='0')		_operation(double_array, rows, cols, key);		_delete(double_array, rows);	break;
	case 3: while (key = _call_menu(char_array, rows, cols)!='0')		_operation(char_array, rows, cols, key);		_delete(char_array, rows);		break;
	default: break;
	}
	return 0;
}

template<typename T>
int _call_menu(T**& _array, const int& rows, const int& cols)
{
	system("cls");
	_print_array(_array, rows, cols);
	OPERATION_LIST;
	char key;
	cin >> key;
	return key;
}

template<typename T>
void _print_array(T**& _array, const int& rows, const int& cols)
{
	_MSG;
	if (rows == 0) _EMPTY;
	cout << "\n\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << "\t" << _array[i][j];
		}
		cout << endl;
	}
}

template<typename T>
void _operation(T**& _array, int& rows, int& cols, int& key)
{
	int position = 0;
	bool _work_with_rows = true;
	switch (key)
	{
	case '1':
	{
		cout << "\n Push back: Rows - 1  Cols - 0 "; cin >> _work_with_rows;
		push_back(_array, rows, cols, _work_with_rows);
		break;
	}
	case '2':
	{
		cout << "\n Push front: Rows - 1  Cols - 0 "; cin >> _work_with_rows;
		push_front(_array, rows, cols, _work_with_rows);
		break;
	}
	case '3':
	{
		cout << "\n Insert: Rows - 1  Cols - 0 "; cin >> _work_with_rows;
		cout << "\n Enter a position -> "; cin >> position;
		insert(_array, rows, cols, _work_with_rows, position);
		break;
	}
	case '4':
	{
		cout << "\n Pop back: Rows - 1  Cols - 0 "; cin >> _work_with_rows;
		pop_back(_array, rows, cols, _work_with_rows);
		break;
	}
	case '5':
	{
		cout << "\n Pop front: Rows - 1  Cols - 0 "; cin >> _work_with_rows;
		pop_front(_array, rows, cols, _work_with_rows);
		break;
	}
	case '6':
	{
		cout << "\n Erase: Rows - 1  Cols - 0 "; cin >> _work_with_rows;
		cout << "\n Choose " << (_work_with_rows == true ? "rows" : "columns") << " -> "; cin >> position;
		erase(_array, rows, cols, _work_with_rows, position);
		break;
	}
	case '0':
		break;
	default:
	{
		cout << "\n Unknows operation. Re-choose..." << endl;
		break;
	}
	}
}

template<typename T>
void insert(T**& _array, int& rows, int& cols, bool _add_rows, int _where_to_add)
{
	srand(time(NULL));
	if (_add_rows) {
		if (_where_to_add >= rows) _where_to_add = rows;
		T** _temp = new T * [++rows];
		if (cols == 0) ++cols;
		int i = 0, j = 0;
		while (i < rows) {
			if (i == _where_to_add)	++i;
			else {
				_temp[i] = _array[j];
				++i;
				++j;
			}
		}
		_temp[_where_to_add] = new T[cols];
		for (int i = 0; i < cols; ++i) _temp[_where_to_add][i] = rand()%100;
		delete _array;
		_array = _temp;
	}
	else {
		if (rows == 0) ++rows;
		++cols;
		if (_where_to_add >= cols) _where_to_add = cols;
		int k, j;
		T** _temp = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			_temp[i] = new T[cols];
			k = 0, j = 0;
			while (k < cols) {
				if (k == _where_to_add) ++k;
				else {
					_temp[i][k] = _array[i][j];
					++j;
					++k;
				}
			}
			_temp[i][_where_to_add] = rand()%100;
		}
		delete[]_array;
		_array = _temp;
	}
}

template<typename T>
void push_back(T**& _array, int& rows, int& cols, bool _add_rows)
{
	insert(_array, rows, cols, _add_rows, _add_rows ? rows : cols);
}

template<typename T>
void push_front(T**& _array, int& rows, int& cols, bool _add_rows)
{
	insert(_array, rows, cols, _add_rows, 0);
}

template<typename T>
void erase(T**& _array, int& rows, int& cols, bool _delete_rows, int _from_where_to_delete)
{
	if ((rows == 1 && _delete_rows) || (cols == 1 && !_delete_rows)) {
		_delete(_array, rows);
		rows = cols = 0;
		return;
	}
	if (rows == 0 && cols == 0) return;

	if (_delete_rows) {
		T** _temp = new T * [rows - 1];
		int i = 0, j = 0;
		while (i < rows)
		{
			if (i == _from_where_to_delete) {
				delete[]_array[i];
				++i;
			}
			else {
				_temp[j] = _array[i];
				++i;
				++j;
			}
		}
		--rows;
		delete[]_array;
		_array = _temp;
	}
	else
	{
		int j, k;
		T* _temp;
		for (int i = 0; i < rows; i++) {
			_temp = new T[cols - 1];
			k = 0; j = 0;
			while (k < cols) {
				if (k == _from_where_to_delete) ++k;
				else {
					_temp[j] = _array[i][k];
					++j;
					++k;
				}
			}
			delete[]_array[i];
			_array[i] = _temp;
		}
		--cols;
	}
}

template<typename T>
void pop_back(T**& _array, int& rows, int& cols, bool _delete_rows)
{
	erase(_array, rows, cols, _delete_rows, _delete_rows ? rows : cols);
}

template<typename T>
void pop_front(T**& _array, int& rows, int& cols, bool _delete_rows)
{
	erase(_array, rows, cols, _delete_rows, 0);
}

template<typename T>
void _delete(T**& _array, int &rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[]_array[i];
	}
}