#include <iostream>
#include <ctime>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>

#include "windows.h"

using namespace std;

// Функция вычисления индекса в строке карты Карно,
// соответствующего индексу двоичного числа таблицы истинности 

int spiral_index(int i, int n)
{
	return (
		(i % 2) * ((i % 4) % 3) * (n - 1) +
		((int)((int)(fabsf((float)(i % 4 - 2.5)) + 0.5) % 3) % 2) * ((n - 1) / 2 + 1 + (int)pow(-1, i % 2 + 1) * ((int)(i / 4) + 0.5)) +
		((int)((int)(fabsf((float)(i % 4 - 0.5)) + 0.5) % 3) % 2) * (int)pow(-1, i % 2) * (int)(i / 4)
		);
}

// Класс бинарных чисел
class BIN
{
private:
	int
		bin_val, // Бинарная форма
		dec_val; // Десятичная форма
public:
	BIN(int _dec_val)
	{
		int count;

		dec_val = _dec_val;
		bin_val = 0;

		if (dec_val <= 1)
		{
			bin_val = dec_val;
			return;
		}

		for (count = 1; dec_val >= 1; count *= 10)
		{
			bin_val += count * (dec_val % 2);
			dec_val = (int)(dec_val / 2);
		}

		dec_val = _dec_val;
	}

	//Методы
	//Метод инкрементации
	void increase()
	{
		int count;

		for (count = 10; ; count *= 10)
		{
			if (count > (bin_val % count) * 10)
			{
				bin_val += count / 10;
				bin_val -= bin_val % (count / 10);
				break;
			}
		}
	}

	//Метод, возвращающий значение в двоичной СС
	int get_bin_val()
	{
		return bin_val;
	}
};

//Класс масссивов чисел кода Грея
class GRAY
{
private:
	int
		**array,//массив для хранения последовательности чисел
		length,//количество чисел Грея
		rank,//количество символов в числе
		count1,//переменные для организации цикла
		count2;

public:

	//Конструктор последовательности кода Грея для _rank символов в числе 
	GRAY(int _rank)
	{
		rank = _rank;
		length = (int)pow(2, rank);

		array = new int*[length];
		for (count1 = 0; count1 < length; count1++)
			array[count1] = new int[rank];

		//Цикл перебора чисел Грея в последовательности
		for (count1 = 0; count1 < length; count1++)
		{
			//Цикл перебора символов в числе
			for (count2 = 0; count2 < rank; count2++)
			{
				//       | 1, если |n % 2^(2 + i) - 2^(2 + i) / 2| < 2^(2 + i) / 4
				// [i] = |
				//       | 0, если |n % 2^(2 + i) - 2^(2 + i) / 2| > 2^(2 + i) / 4
				//         где i - разряд (позиция) символа в числе Грея, начиная от нуля
				//             n - количество символов в числе Грея
				if (abs(((count1 % (int)pow(2, 2 + count2)) - (pow(2, 2 + count2) - 1) / 2)) > (pow(2, 2 + count2) - 1) / 4)
					array[count1][count2] = 0;
				else
					array[count1][count2] = 1;
			}
		}
	}

	//Метод, возвращающий строку с числом Грея, записанным через пробелы между символами
	string get_string(int string_num)
	{
		string ans_string;

		for (count1 = rank - 1; count1 > 0; count1--)
		{
			ans_string.append(to_string(array[string_num][count1]));
			ans_string.append(" ");
		}
		ans_string.append(to_string(array[string_num][0]));
			

		return ans_string;
	}

	//Метод, возвращающий количество символов в числе
	int get_rank()
	{
		return rank;
	}
};

//Класс таблиц истинности
class tTable
{
public:
	//Конструктор класса, n - количество аргументов х логической функции
	tTable(int num, string how_to_fill)
	{
		int count;

		num1 = num;
		num2 = (int)pow(2, num1);
		xArr = new int*[num1];
		for (count = 0; count < num1; count++)
			xArr[count] = new int[num2];

		yArr = new int[num2];

		fill(how_to_fill);
	}

	//Метод заполнения значений х таблицы истинности
	void fill(string how_to_fill)
	{
		int
			count1,
			count2,
			bin_value = 0,
			ans;

		bool
			repeat_0 = false;

		//Заполнение значений Х согласно возрастанию двоичного числа table_count
		BIN table_count(0);
		for (count1 = 0; count1 < num2; count1++)
		{
			for (count2 = 0; count2 < num1; count2++)
			{
				xArr[count2][count1] = (int)((table_count.get_bin_val() % (int)pow(10, count2 + 1)) / pow(10, count2));
			}
			table_count.increase();
		}

		//Заполнение Y
		//Заполнение Y нулями
		if (how_to_fill == "zeros") 
		{
			for (count1 = 0; count1 < num2; count1++)
				yArr[count1] = 0;
		}
		//Заполнение Y единицами
		else if (how_to_fill == "ones")
		{
			for (count1 = 0; count1 < num2; count1++)
				yArr[count1] = 1;
		}
		//Заполнение Y случайными числами
		else if (how_to_fill == "rand")
		{
			srand((int)time(0));
			for (count1 = 0; count1 < num2; count1++)
				yArr[count1] = rand() % 2;
		}
		//Заполнение вручную
		else if (how_to_fill == "manually")
		{
			cout << "Последовательно введите значения логической функции в порядке возрастания индексов:\n\n";
			for (count1 = 0; count1 < num2; count1++)
			{
				cout << "y(";

				for (count2 = 0; count2 < num1 - 1; count2++)
					cout << xArr[count2][count1] << ", ";
				cout << xArr[num1 - 1][count1] << ") = ";

				cin >> yArr[count1];
			}
			cout << "\n\n";
		}
		//Ввод Y из файла
		else
		{
			ifstream file;
			do {
				file.open(how_to_fill);

				//Считывание значений
				for (count1 = 0; count1 < num2; count1++)
				{
					//При достижении конца файла
					if (file.peek() == EOF)
						break;
					file >> yArr[count1];
				}

				//При считывании значений в количестве меньшем, чем указано
				if (count1 < num2)
				{
					cout << "Считано " << count1 << " значений из " << num2 <<
						". Выберите дальнейшее действие: \n1 — заполнить оставшиеся элементы нулями;\n2 — заполнить оставшиеся элементы единицами;" <<
						"\n3 — изменить путь к файлу;\n4 — заполнить все элементы случайными значениями;\n5 — изменить количество аргументов функции, " <<
						"исходя из считанных значений.\n\nВвведите число: ";

					cin >> ans;
					cout << "\n";

					//Выбор вариантов 
					switch (ans)
					{
					//Заполнение оставшихся элементов нулями
					case 1:
					{
						for ( ; count1 < num2; count1++)
							yArr[count1] = 0;
						repeat_0 = false;
					} break;
					//Заполнение оставшихся элементов единицами
					case 2:
					{
						for ( ; count1 < num2; count1++)
							yArr[count1] = 1;
						repeat_0 = false;
					} break;
					//Изменение имени файла
					case 3:
					{
						file.close();
						cout << "Введите имя файла для считывания: ";
						cin >> how_to_fill;
						cout << "\n";
						repeat_0 = true;
					} break;
					//Заполнение случайными числами
					case 4:
					{
						srand((int)time(0));
						for (count1 = 0; count1 < num2; count1++)
							yArr[count1] = rand() % 2;
						repeat_0 = false;
					} break;
					//Переопределение размера таблицы
					case 5:
					{
						num1 = (int)(log(count1) / log(2));
						num2 = (int)pow(2, num1);
						fill(how_to_fill);
						repeat_0 = false;
					} break;
					default:
					{
						
					}
					}
				}
			} while (repeat_0);
			
		}
	}

	//Вывод таблицы истинности
	void print()
	{
		int
			count1,
			count2;

		for (count1 = 0; count1 < num1; count1++)
		{
			cout << "x" << count1 + 1 << ":  ";
			for (count2 = 0; count2 < num2; count2++)
			{
				cout << xArr[count1][count2] << "  ";
			}
			cout << "\n\n";
		}

		cout << "y:   ";
		for (count1 = 0; count1 < num2; count1++)
			cout << yArr[count1] << "  ";
		cout << "\n\n";
	}
	
	//Получение строки записи СДНФ: choice = 0
	//Получение строки записи СКНФ: choice = 1
	string nf_string(int choice)
	{
		int
			count1,
			count2;
		bool
			check = false;
		string 
			nf_string;

		for (count1 = 0; count1 < num2; count1++)
		{
			if ((yArr[count1] + choice) % 2)
			{
				if (check)
				{
					if (choice)
                        nf_string += "  &  ";
					else
						nf_string += "  V  ";
				}
				check = true;

				nf_string += "(";

				for (count2 = 0; count2 < num1 - 1; count2++)
				{
					if (!((xArr[count2][count1] + choice) % 2))
					{
						nf_string += "-";
					}

					nf_string += "x";
					nf_string += to_string(count2 + 1);
					
					if (choice)
						nf_string += " V ";
					else
						nf_string += " & ";
				}

				if (!((xArr[num1 - 1][count1] + choice) % 2))
				{
					nf_string += "-";
				}

				nf_string += "x";
				nf_string += to_string(num1);
				nf_string += ")";
			}
		}
			
		return nf_string;
	}

	//Получение значения функции по индексу
	int get_val(int index)
	{
		return yArr[index];
	}

	//Получение значения переменной по индексу
	int get_arg(int index_y, int index_x)
	{
		return xArr[index_y][index_x];
	}

private:
	int
		**xArr,
		*yArr,
		num1,
		num2;
};

//Класс карт Карно
class KMap
{
public:
	//Конструктор класса
	KMap(int n, tTable table)
	{
		int
			//Вспомогательные массивы для формирования карты Карно
			*sub_array_1,
			*sub_array_2,
			*sub_array_3;
		int
			//Переменные для организации циклов
			count_1,
			count_2,
			q;

		//Задание начального массива последовательности перечисления элементов карты Карно
		sub_array_1 = new int[2];
		sub_array_1[0] = 0;
		sub_array_1[1] = 1;

		n_ = n;
		N = (int)pow(2, n);
		n_x = (int)(n / 2);
		n_y = n - n_x;
		N_x = (int)pow(2, n_x);
		N_y = (int)pow(2, n_y);

		//Выделение памяти для основных массивов
		truth_to_Karn = new int*[N_y];
		for (count_1 = 0; count_1 < N_y; count_1++)
			truth_to_Karn[count_1] = new int[N_x];

		Karn_to_truth = new int*[N_y];
		for (count_1 = 0; count_1 < N_y; count_1++)
			Karn_to_truth[count_1] = new int[N_x];

		Karn_to_truth_index = new int*[N_y];
		for (count_1 = 0; count_1 < N_y; count_1++)
			Karn_to_truth_index[count_1] = new int[N_x];

		//Процедура формирования "опорных" (первых в каждой строке) значений таблицы таблицы Карно 
		for (count_1 = 2; count_1 <= n; count_1++)
		{
			if (count_1 % 2 == 0)
			{
				//Последовательность "опорных" значений для четного количества 
				//переменных равна поэлементно удвоенной последовательности для 
				//предыдущего нечетного количества.
				for (count_2 = 0; count_2 < pow(2, count_1 / 2); count_2++)
					sub_array_1[count_2] *= 2;
			}
			else
			{
				//Последовательность "опорных" значений для нечетного количества 
				//переменных в два раза больше последовательности для предыдущего
				//четного количества элементов, образуется слиянием двух массивов.

				//Формирование второго массива
				q = (int)pow(2, (int)(count_1 / 2));
				sub_array_2 = new int[q];

				//Каждый элемент второго массива берется из второй половины 
				//увеличенной последовательности и соответствует элементу первого
				//массива по определенному правилу.
				for (count_2 = 0; count_2 < pow(2, (int)(count_1 / 2)); count_2++)
					sub_array_2[count_2] = (int)(pow(2, count_1) - pow(2, (int)(count_1 / 2)) - sub_array_1[count_2]);

				//Формирование удвоенного массива
				q = (int)pow(2, count_1 - (int)(count_1 / 2));
				sub_array_3 = new int[q];

				//Слияние массива последовательности предыдущей итерации
				//с дополнительным, сформированным на текущей
				for (count_2 = 0; count_2 < q; count_2++)
				{
					//Четный элемент берется из первого массива
					if (count_2 % 2 == 0)
						sub_array_3[count_2] = sub_array_1[(int)(count_2 / 2)];

					//Нечетный элемент берется из второго массива
					else
						sub_array_3[count_2] = sub_array_2[(int)(count_2 / 2)];
				}

				//Освобождение памяти, занятой массивом нечетных элементов
				delete[] sub_array_2;

				//Переопределение размера первого массива и перемещение 
				//в него элементов третьего массива для использования 
				//на следующих итерациях
				sub_array_1 = new int[q];
				for (count_2 = 0; count_2 < q; count_2++)
					sub_array_1[count_2] = sub_array_3[count_2];

				//Освобождение памяти, занятой третьим массивом
				delete[] sub_array_3;
			}
		}

		//Процедура заполнения таблицы Карно по "опорным" значениям
		for (count_1 = 0; count_1 < N_y; count_1++)
		{
			for (count_2 = 0; count_2 < N_x; count_2++)
			{
				truth_to_Karn[count_1][count_2] = (int)(spiral_index(count_2, (int)pow(2, (int)(n / 2))) + sub_array_1[count_1]);
			}
		}

		//Процедура фомирования массива соответствия индексу элемента в карте Карно индексу двоичного кода
		for (count_1 = 0; count_1 < N_y; count_1++)
		{
			for (count_2 = 0; count_2 < N_x; count_2++)
			{
				Karn_to_truth_index[(int)(truth_to_Karn[count_1][count_2] / N_x)][truth_to_Karn[count_1][count_2] % N_x] = count_1 * N_x + count_2;
				Karn_to_truth[(int)(truth_to_Karn[count_1][count_2] / N_x)][truth_to_Karn[count_1][count_2] % N_x] = table.get_val(count_1 * N_x + count_2);
			}
		}
	}

	//Метод вывода карты Карно
	void print()
	{
		//Переменные для организации циклов
		int
			count_1,
			count_2,
			count_3;

		//Строки, формирующие карту Карно
		string
			table_gap_1,
			table_gap_2,
			table_gap_3,
			table_gap_4,
			val_table_gap,
			x_y_gap,
			x_x_gap;

		//Создание двух массивов чисел Грея для таблицы Карно
		GRAY Gx(n_x);
		GRAY Gy(n_y);

		//Формирование строк, формирующих таблицу
		//Формировние заполняющих и разделяющих строк
		for (count_1 = 0; count_1 < 2 * n_y - 1; count_1++)
		{
			table_gap_1.append("_");
			table_gap_4.append(" ");
		}
		table_gap_1.append("_|");
		table_gap_4.append(" |");

		for (count_1 = 0; count_1 < 2 * n_x - 1; count_1++)
		{
			table_gap_2.append("_");
			table_gap_3.append(" ");
		}
		table_gap_2.append("__|");
		table_gap_3.append("  |");

		//Формирование строки для обозначения переменных по первому столбцу
		for (count_1 = n_x + 1; count_1 <= n_x + n_y; count_1++)
			x_y_gap.append(to_string(count_1));

		for (count_1 = n_x + 1; count_1 <= n_x + n_y; count_1++)
			x_y_gap.append("_");

		x_y_gap.append("|");

		//Формирование строки для обозначения переменных по первой строке
		for (count_1 = 0; count_1 < (int)x_y_gap.length() - n_x - 1; count_1++)
			x_x_gap.append(" ");

		for (count_1 = 1; count_1 <= n_x; count_1++)
			x_x_gap.append(to_string(count_1));

		x_x_gap.append("|");

		//Вывод
		//Вывод первой разделительной черты
		for (count_1 = 0; count_1 < N_x * (2 * n_x + 2) + 2 * n_y; count_1++)
			cout << "_";
		cout << "\n";

		//Вывод обозначения по горизонтали
		cout << x_x_gap;

		//Заполнение пробелов
		for (count_2 = 0; count_2 < N_x; count_2++)
		{
			cout << table_gap_3;
		}
		cout << "\n";

		cout << table_gap_4 << " ";

		//Вывод кода Грея по горизонтали
		for (count_1 = 0; count_1 < N_x; count_1++)
		{
			cout << Gx.get_string(count_1) << " | ";
		}
		cout << "\n";

		//Вывод обозначения по вертикали
		cout << x_y_gap;

		//Заполнение пробелов
		for (count_1 = 0; count_1 < N_x; count_1++)
		{
			cout << table_gap_2;
		}
		cout << "\n";

		//Цикл для заполнения тела таблицы
		for (count_1 = 0; count_1 < N_y; count_1++)
		{
			//Заполнение пробелов
			cout << table_gap_4;
			for (count_2 = 0; count_2 < N_x; count_2++)
			{
				cout << table_gap_3;
			}
			cout << "\n";

			//Вывод кода Грея по вертикали
			cout << Gy.get_string(count_1) << " |";

			//Заполнение строки таблицы
			for (count_2 = 0; count_2 < N_x; count_2++)
			{
				//Формирование строки со значением логической функции
				for (count_3 = 0; count_3 < n_x; count_3++)
					val_table_gap.append(" ");

				val_table_gap.append(to_string(Karn_to_truth[count_1][count_2]));

				for (count_3 = 0; count_3 < n_x; count_3++)
					val_table_gap.append(" ");

				val_table_gap.append("|");

				cout << val_table_gap;

				//Очистка строки со значением логической функции
				val_table_gap.clear();
			}
			cout << "\n";

			//Заполнение пробелами
			cout << table_gap_1;
			for (count_2 = 0; count_2 < N_x; count_2++)
			{
				cout << table_gap_2;
			}
			cout << "\n";
		}
	}

	string get_min_func(tTable table)
	{
		int
			count_1,
			count_2,
			count_3,
			count_x,
			count_y,
			count_xy,
			sub_N_x,
			sub_N_y,
			area,
			size,
			area_length_1,
			area_height_1,
			area_length_2,
			area_height_2,
			x,
			y;

		bool
			area_1,
			check = false,
			is_sub_area = false;

		string
			min_string;

		vector < vector <int> > areas;
		vector < vector <int> > new_areas;
		vector <int> const_x;

		//Цикл перебора элементов по строкам
		for (count_1 = 0; count_1 < N_y; count_1++)
		{
			//Цикл перебора элементов в пределах одной строки
			for (count_2 = 0; count_2 < N_x; count_2++)
			{
				//Ограничитель перебора по вертикали
				sub_N_y = N_y;
				//Ограничитель перебора по горизонтали
				sub_N_x = N_x;

				area_1 = false;

				//Цикл перемещения вниз-вправо.
				//Количество итераций ограничено наименьшим из ограничителей
				//по вертикали и горизонтали
				for (count_xy = 0; count_xy < sub_N_x && count_xy < sub_N_y; count_xy++)
				{
					//Цикл перемещения вправо.
					//Количество итераций ограничено ограничителем по горизонтали
					for (count_x = 0; count_x < sub_N_x; count_x++)
					{
						//Если элемент, отстоящий от "опорного" (цикл вниз-вправо) вправо на count_x равен нулю
						if (!Karn_to_truth[(count_1 + count_xy) % N_y][(count_2 + count_xy + count_x) % N_x])
						{
							//Если пройдено 0 шагов
							if (!count_x)
								//Ограничение по горизонтали до нуля
								sub_N_x = 0;

							//Если пройдено больше 0 шагов
							else
							{
								//Ограничение по горизонтали до ближайшей минимальной степени 2
								//с учетом элементов, пройденных по диагонали
								sub_N_x = (int)pow(2, (int)(log(count_xy + count_x) / log(2)));

								//Значение площади контура - произведение текущего ограничителя 
								//по горизонтали на количество элементов, пройденных по диагонали (вниз),
								//ограниченное ближайшей минимальной степенью двойки
								area = sub_N_x * (int)pow(2, (int)(log(count_xy + 1) / log(2)));

								areas.push_back(vector <int>());
								areas[areas.size() - 1].push_back(area);
								areas[areas.size() - 1].push_back(count_1);
								areas[areas.size() - 1].push_back(count_2);
								areas[areas.size() - 1].push_back((count_1 + (int)pow(2, (int)(log(count_xy + 1) / log(2))) - 1) % N_y);
								areas[areas.size() - 1].push_back((count_2 + sub_N_x - 1) % N_x);
							}
						}
					}

					//Если пройдено максимально допустимое количество элементов
					if (count_x == sub_N_x)
					{
						area = sub_N_x * (int)pow(2, (int)(log(count_xy + 1) / log(2)));

						areas.push_back(vector <int>());
						areas[areas.size() - 1].push_back(area);
						areas[areas.size() - 1].push_back(count_1);
						areas[areas.size() - 1].push_back(count_2);
						areas[areas.size() - 1].push_back((count_1 + (int)pow(2, (int)(log(count_xy + 1) / log(2))) - 1) % N_y);
						areas[areas.size() - 1].push_back((count_2 + sub_N_x - 1) % N_x);
					}

					//Цикл перемещения вниз.
					//Количество итераций ограничено ограничителем по вертикали.
					//Дополнительное условие выполнения - ненулевой ограничитель по горизонтали 
					//(т. к. иначе area == 0)
					for (count_y = 0; count_y < sub_N_y && sub_N_x; count_y++)
					{
						//Если элемент, отстоящий от "опорного" (цикл вниз-вправо) вниз на count_y равен нулю
						if (!Karn_to_truth[(count_1 + count_xy + count_y) % N_y][(count_2 + count_xy) % N_x])
						{
							//Если пройдено 0 шагов
							if (!count_y)
								//Ограничение по горизонтали до нуля
								sub_N_y = 0;

							//Если пройдено больше 0 шагов
							else
							{
								//Ограничение по вертикали до ближайшей минимальной степени 2
								//с учетом элементов, пройденных по диагонали
								sub_N_y = (int)pow(2, (int)(log(count_xy + count_y) / log(2)));

								//Значение площади контура - произведение текущего ограничителя 
								//по вертикали на количество элементов, пройденных по диагонали (вправо),
								//ограниченное ближайшей минимальной степенью двойки
								area = sub_N_y * (int)pow(2, (int)(log(count_xy + 1) / log(2)));

								areas.push_back(vector <int>());
								areas[areas.size() - 1].push_back(area);
								areas[areas.size() - 1].push_back(count_1);
								areas[areas.size() - 1].push_back(count_2);
								areas[areas.size() - 1].push_back((count_1 + sub_N_y - 1) % N_y);
								areas[areas.size() - 1].push_back((count_2 + (int)pow(2, (int)(log(count_xy + 1) / log(2))) - 1) % N_x);
							}
						}
					}

					//Если пройдено максимально допустимое количество элементов
					if (count_y == sub_N_y)
					{
						area = sub_N_y * (int)pow(2, (int)(log(count_xy + 1) / log(2)));

						areas.push_back(vector <int>());
						areas[areas.size() - 1].push_back(area);
						areas[areas.size() - 1].push_back(count_1);
						areas[areas.size() - 1].push_back(count_2);
						areas[areas.size() - 1].push_back((count_1 + sub_N_y - 1) % N_y);
						areas[areas.size() - 1].push_back((count_2 + (int)pow(2, (int)(log(count_xy + 1) / log(2))) - 1) % N_x);
					}
				}
			}
		}

		//Удаление контуров, покрываемых другими контурами
		//Перебор всех элементов в каждом контуре и проверка
		//на наличие этого элемента в других контурах
		size = areas.size();
		area = 0;

		//Цикл поиска контура максимальной площади
		for (count_1 = 0; count_1 < size; count_1++)
		{
			if (areas[count_1][0] > area)
				area = areas[count_1][0];
		}
		
		//Цикл перебора контуров по площадям, начиная с меньшей (равной 1)
		for (count_1 = 1; count_1 <= area; count_1 *= 2)
		{
			//Цикл перебора по контурам до конца вектора контуров
			for (count_2 = 0; count_2 < size; count_2++)
			{
				//Если размер вектора ненулевой (проверка на удаление на предыдущих итерациях)
				//и площадь контура равна заданной во внешнем цикле
				if (areas[count_2].size())
				{
					if (areas[count_2][0] == count_1)
					{
						//Вычисление длины контура
						area_length_1 = (areas[count_2][4] - areas[count_2][2] + N_x) % N_x + 1;
						//Вычисление высоты контура
						area_height_1 = (areas[count_2][3] - areas[count_2][1] + N_y) % N_y + 1;

						//Цикл перебора элементов контура по вертикали
						for (count_y = 0; count_y < area_height_1; count_y++)
						{
							//Вычисление значения Y рассматриваемого элемента
							y = (areas[count_2][1] + count_y) % N_y;

							//Цикл перебора элементов контура по горизонтали
							for (count_x = 0; count_x < area_length_1; count_x++)
							{
								//Логическая переменная, показывающая,
								//входит ли данный элемент в состав других контуров
								is_sub_area = false;
								//Вычисление значения Х рассматриваемого элемента
								x = (areas[count_2][2] + count_x) % N_x;

								//Цикл перебора по контурам, возможно пересекающимся с рассматриваемым
								for (count_3 = 0; count_3 < size; count_3++)
								{
									//Если рассматриваемый контур не является рассматриваемым во внешнем цикле
									//и размер вектора ненулевой (проверка на удаление на предыдущих итерациях)
									if (count_3 != count_2 && areas[count_3].size())
									{
										//Вычисление длины контура
										area_length_2 = (areas[count_3][4] - areas[count_3][2] + N_x) % N_x + 1;
										//Вычисление высоты контура
										area_height_2 = (areas[count_3][3] - areas[count_3][1] + N_y) % N_y + 1;

										//Проверка на принадлежность точки (X, Y) контура, рассматриваемого во внешнем цикле,
										//рассматриваемому контуру
										//Если точка не принадлежит контуру, контур нужно оставить, то есть соответствующий
										//вектор не нужно очищать
										if (
											areas[count_3][4] - area_length_2 + 1 <= x &&
											areas[count_3][2] + area_length_2 - 1 >= x &&
											areas[count_3][3] - area_height_2 + 1 <= y &&
											areas[count_3][1] + area_height_2 - 1 >= y
											)
										{
											if ((areas[count_3][1] - areas[count_3][3] > 0 && y < areas[count_3][1] && y > areas[count_3][3]) ||
												(areas[count_3][2] - areas[count_3][4] > 0 && y < areas[count_3][2] && y > areas[count_3][4]))
												continue;
											else
											{
												is_sub_area = true;
												break;
											}	
										}
									}
								}
								if (!is_sub_area)
									break;
							}
							if (count_x != area_length_1)
								break;
						}
						if (count_y == area_height_1) 
							areas[count_2].clear();
					}
				}
			}
		}
		
		//Перемещение непустых векторов из вектора new_areas в areas
		for (count_1 = 0; count_1 < size; count_1++)
		{
			if (areas[count_1].size())
				new_areas.push_back(areas[count_1]);
		}
		
		//Вывод координат контуров (для отладки)
		size = new_areas.size();
		cout << "\n" << size << " contours:\n\n";

		for (count_1 = 0; count_1 < size; count_1++)
		{
			cout << "S = " << new_areas[count_1][0] << "; " <<
				"(" << new_areas[count_1][1] << " : " <<
				new_areas[count_1][2] << ") -> " <<
				"(" << new_areas[count_1][3] << " : " <<
				new_areas[count_1][4] << ")\n\n";
		}

		//Выделение константных переменных в пределах контуров 
		if (size == 1 && new_areas[0][0] == N)
		{
			min_string = "1";
		} 
		else if (!size)
		{
			min_string = "0";
		}
		else 
		{
			//Перебор контуров
			for (count_1 = 0; count_1 < size; count_1++)
			{
				//Вычисление длины контура
				area_length_1 = (new_areas[count_1][4] - new_areas[count_1][2] + N_x) % N_x + 1;
				//Вычисление высоты контура
				area_height_1 = (new_areas[count_1][3] - new_areas[count_1][1] + N_y) % N_y + 1;

				//Очистка вектора константных значений переменных с предыдущей итерации
				const_x.clear();

				//Заполнение вектора значений переменных в левом верхнем элементе контура
				for (count_2 = 0; count_2 < n_; count_2++)
				{
					const_x.push_back(table.get_arg(count_2, Karn_to_truth_index[new_areas[count_1][1]][new_areas[count_1][2]]));
				}

				//Перебор элементов по горизонтали контура
				for (count_x = 1; count_x < area_length_1; count_x++)
				{
					//Вычисление координаты данной точки
					x = (new_areas[count_1][2] + count_x) % N_x;

					//Перебор по значениям переменных горизонтального кода Грея
					for (count_2 = 0; count_2 < n_x; count_2++)
					{
						//Если значение переменной не совпадает с текущим в данной позиции, 
						//присваиваем ему "бессмысленное" значение -1 для дальнейшей фильтрации
						if (table.get_arg(count_2, Karn_to_truth_index[new_areas[count_1][1]][x]) != const_x[count_2])
							const_x[count_2] = -1;
					}
				}

				//Перебор элементов по вертикали контура
				for (count_y = 1; count_y < area_height_1; count_y++)
				{
					//Вычисление координаты данной точки
					y = (new_areas[count_1][1] + count_y) % N_y;

					//Перебор по значениям переменных вертикального кода Грея
					for (count_2 = 0; count_2 < n_y; count_2++)
					{
						//Если значение переменной не совпадает с текущим в данной позиции, 
						//присваиваем ему "бессмысленное" значение -1 для дальнейшей фильтрации
						if (table.get_arg(count_2 + n_x, Karn_to_truth_index[y][new_areas[count_1][2]]) != const_x[count_2 + n_x])
							const_x[count_2 + n_x] = -1;
					}
				}

				//Логическая переменная для организации вывода
				if (check)
					min_string.append(" V ");
				check = true;

				//Цикл записи элементарных конъюнкций
				for (count_2 = 0; count_2 < n_; count_2++)
				{
					//Если значение переменной равно 1,
					//записываем в прямом виде
					if (const_x[count_2] == 1)
					{
						min_string.append("x");
						min_string.append(to_string(count_2 + 1));
					}
					//Если значение переменной равно 0,
					//записываем в инверсном виде
					if (const_x[count_2] == 0)
					{
						min_string.append("-");
						min_string.append("x");
						min_string.append(to_string(count_2 + 1));
					}
				}
			}
		}
		
		return min_string;
	}

private:
	int
		**Karn_to_truth, //массив соответствия индексов в карте Карно значения функции в таблице истинности
		**truth_to_Karn, //массив соответствия индексов в таблице истинности индексу значения функции в карте Карно
		**Karn_to_truth_index, //массив соответствия индексов в карте Карно индексу значения функции в таблице истинности
		n_, //количество переменных логической функции
		n_x, //количество цифр в коде Грея по горизонтали
		n_y, //количество цифр в коде Грея по вертикали
		N_x, //горизонтальный размер карты Карно
		N_y, //вертикальный размер карты Карно
		N; //количество элементов карты Карно
};


//Основная функция
int main()
{
	//Языковые настройки
	setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	//Блок переменных
	int
		n,
		ans;

	string
		info;

	
	do {
		//Приветствие
		cout << "Application to obtaining conjunctive and disjunctive normal forms of logical function.\n\n";
		cout << "Enter the number of arguments x to the boolean function: ";
		cin >> n;
		cout << "\nHow to fill in the y(x) values of a boolean function?\n1) from the file;\n2) enter manually;" <<
			"\n3) fill with random values;\n4) fill with zeros;\n5) fill with units.\n\nEnter the number: ";
		cin >> ans;
		cout << "\n";

		//Выбор вариантов ввода
		switch (ans)
		{
		case 1:
		{
			cout << "Enter the name of the file to read: ";
			cin >> info;
			cout << "\n";
		} break;
		case 2:
		{
			info = "manually";
		} break;
		case 3:
		{
			info = "rand";
		} break;
		case 4:
		{
			info = "zeros";
		} break;
		case 5:
		{
			info = "ones";
		} break;
		default:
		{

		}
		}

		//Начало работы
		//Создание объекта для таблицы истинности с заданием количества переменных и способа ввода
		tTable Table_1(n, info);

		//Вывод таблицы истинности
		cout << "Truth table:\n\n";
		Table_1.print();

		//Вывод СДНФ и СКНФ
		cout << "DNF:  " << Table_1.nf_string(0) << "\n\n";
		cout << "CNF:  " << Table_1.nf_string(1) << "\n\n";

		//Создание объекта для карты Карно с заданием количества переменных 
		//и соответствующей таблицей истинности
		KMap Map_1(n, Table_1);

		//Вывод карты Карно
		cout << "Carnot Map:\n";
		Map_1.print();

		//Получение и вывод минимизированной функции
		cout << "Minimal DNF:\n" << Map_1.get_min_func(Table_1) << "\n";

		cout << "\nAgain?\n";
		cin >> ans;
		cout << "\n";
	} while (ans);
	
	cout << "\ndone\n";

	return 0;
}