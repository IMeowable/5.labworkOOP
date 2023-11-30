// labworkOOP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
using namespace std;

#include <iostream>
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <fstream>

class Function
{
private:

	double first_x;
	double last_x;
	double current_x;
	double current_y;
	list <double> x_to_write;
	list <double> y_to_write;


public:

	//интерфейс для обработки информации записи в файл.
	list <double> GetX_To_Write() { return x_to_write; }
	list <double> GetY_To_Write() { return y_to_write; }
	//Коснтруктор для итеративного поиска точек
	Function(double first_x, double last_x)
	{
		this->first_x = first_x;
		this->last_x = last_x;
		find_y(first_x, last_x);

	};
	//Конструктор для поиска одного значения f(x)
	Function(double x)
	{
		this->current_x = x;
		find_y(x);
	};

private:
	void find_y(double user_input)//Найти f(x)


	{
		current_x = user_input;
		//определение принадлежности графику введенного значения условными операторами
		if (user_input <= -6)
		{
			//уравнение полукруга y = -1 * sqrt(R^2 - x^2)
			//r = 2, центр окружности (-8; 2)
			//(x+8)^2+(y-2)^2 = 4 
			//  (y-2)^2 = 4 - (x+8)^2
			//y = sqrt(4-(x+8))^2) + 2
			current_y = -sqrt((4 - pow((user_input + 8), 2))) + 2;

		}
		if (user_input > -6 && user_input <= -4)
		{
			//на графике фнукция параллельна оси Ox
			current_y = 2;

		}
		if (user_input == 0) {
			current_y = 0;

		}
		if (user_input > -4 && user_input < 2 && user_input != 0)
		{
			//k = -1/2 , функция y = kx + m	
			current_y = -user_input / 2.;

		}
		if (user_input >= 2)
		{
			//функция y = kx + m    k = 1 m = -3
			current_y = user_input - 3.;

		}
		x_to_write.push_back(user_input);
		y_to_write.push_back(current_y);
		cout << "X: " << user_input << "\t" << "Y:" << current_y << endl;

	}
private: void find_y(double first_x, double last_x)
{
	double i = first_x;
	for (i; i <= last_x; i++)
	{
		find_y(i);
	}

}
};

bool IsDouble(string check_string)
{

	istringstream iss{ (check_string) };
	double f;
	iss >> noskipws >> f;
	if (iss.eof() && !iss.fail() and f > -10)
	{

		return true;
	}
	else
	{

		return false;
	}
}
void TxtWriter(list <double> x_wr, list <double> y_wr)
{
	std::ofstream out("numbers.txt", std::ios::app);//открываем в режиме записи в конец файла
	if (out.is_open())
	{
		out << "x\t";
		for (auto i : x_wr)//перебираем наши иксы и отправляем в файл
		{
			out << i << "\t";

		}
		out << endl;
		out << "Y\t";
		for (auto i : y_wr)//также перебираем Y
		{
			out << i << "\t";
		}
		out << endl;
		out << endl;
	}
	out.close();
}

void txt_read()

{

	cout << "Предыдущие вычисления из numbers.txt" << endl << endl;
	cout << endl;
	string line;
	ifstream in("numbers.txt");
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл
	cout << "Для продолжение нажмите enter" << endl << endl;
	getchar();
	
}


int main()
{
	setlocale(LC_ALL, "ru");
	txt_read();
	while (1)
	{
		cout << "Выберите режим рассчёта: Введите 1, чтобы найти одну точку. Введите 2 - чтобы найти точки на промежутке\n 3 - вернуться к результатам" << endl << endl;
		int choise;
		cin >> choise;

		switch (choise)
		{
		case 1:
		{
			cout << "Введите x" << endl << endl;
			string first_x;
			cin >> first_x;
			if (IsDouble(first_x))
			{
				Function MyFoo(stod(first_x));
				TxtWriter(MyFoo.GetX_To_Write(), MyFoo.GetY_To_Write());
			}
			else cout << "Неверный ввод" << endl << endl;;
			break;
		}
		case 2:
		{
			cout << "Введите x1 и x2" << endl << endl;
			string first_x;
			string last_x;
			cin >> first_x;
			cin >> last_x;

			if (IsDouble(first_x) && IsDouble(last_x))
			{
				Function MyFoo(stod(first_x), stod(last_x));
				TxtWriter(MyFoo.GetX_To_Write(), MyFoo.GetY_To_Write());
				break;

			}
		

			else cout << "Неверный ввод" << endl << endl;
			break;

		}
		case 3:
			
			txt_read();
			break;

		default:

			break;
		}

	}

}
