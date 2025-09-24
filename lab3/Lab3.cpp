//=======================================================================
//	Лабораторная №3. Шаблоны функций. Шаблоны классов. Стандартные шаблоны С++.
//				Обработка исключений.
//=======================================================================
//Используйте недостающие файлы из лабораторной 2
#include "MyVector.h"
#include "MyString.h"
#include "Functions.h"
#include "MyStack.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#define stop
//using namespace std;

//============= Шаблон функции для вывода с помощью итератора
template <class T> void pr(T& v, std::string s)
{
	std::cout<<"\n\n\t"<<s<<"  # Sequence:\n";
	
	// Итератор любого контейнера
	typename T::iterator p;

	int i;

	for (p = v.begin(), i=0;  p != v.end();  p++, i++)
		std::cout << '\n' << i + 1 << ". " << *p;
	std::cout << '\n';
} 

int main()
{

	//===========================================================
	// Шаблоны функций
	//===========================================================
	// Создайте шаблон функции перестановки двух параметров - Swap().
	// Проверьте работоспособность созданного шаблона с помощью
	// приведенного ниже фрагмента.
	{
		int i = 1, j = -1;
		Swap(i, j);

		double a = 0.5, b = -5.5;
		Swap(a, b);

		Vector u(1, 2), w(-3, -4);
		Swap(u, w);

		// Если вы достаточно развили класс MyString в предыдущей работе,
		// то следующий фрагмент тоже должен работать корректно.

		MyString s1("Your fault"), s2("My forgiveness");
		Swap(s1, s2);
	}
	//===========================================================
	// Шаблоны классов
	//===========================================================
	// Создайте шаблон класса MyStack для хранения элементов любого типа T.
	// В качестве основы для стека может быть выбран массив.
	// Для задания максимального размера стека может быть использован
	// параметр-константа шаблона
	// Обязательными операциями со стеком являются "Push" и "Pop","GetSize" и "Capacity"
	// Необязательной - может быть выбор по индексу (operator[]).
	// Для того, чтобы гарантировать корректное выполнение этих операций 
	// следует генерировать исключительные ситуации.

	// С помощью шаблона MyStack создайте стек переменных типа int, затем
	// стек переменных типа double и, наконец, стек из переменных типа Vector 
	// Если вы подготовите три класса для обработки исключений,
	// то следующий фрагмент должен работать
	try
	{
		std::cout << "\tTest MyStack\n";
		MyStack <int, 3> stack;

		std::cout << "\nInteger Stack capacity: " << stack.Capacity();

		stack.Push(1);
		stack.Push(2);
		stack.Push(3);

		std::cout << "\nInteger Stack has: " << stack.GetSize() << " elements";

		stack.Push(4);	// Здесь должно быть "выброшено" исключение

		std::cout << "\nInteger Stack pops: " << stack.Pop();
		std::cout << "\nInteger Stack pops: " << stack.Pop();

		std::cout << "\nInteger Stack has: " << stack.GetSize() << " elements";
		stack.Pop();
		stack.Pop();		// Здесь должно быть "выброшено" исключение
		stack.Push(2);

		int i = stack[3];	// Здесь должно быть "выброшено" исключение

		MyStack<Vector, 5> ptStack;

		std::cout << "\nVector Stack capacity: " << ptStack.Capacity();

		ptStack.Push(Vector(1, 1));
		ptStack.Push(Vector(2, 2));

		std::cout << "\nVector Stack pops: ";
		// Используйте метод класса Vector для вывода элемента
		ptStack.Pop().Out();

		std::cout << "\nVector Stack has: " << ptStack.GetSize() << " elements";
	}
	catch (StackOverflow)
	{
		std::cout << "\nStack overflow";
	}
	catch (StackUnderflow)
	{
		std::cout << "\nStack underflow";
	}
	catch (StackOutOfRange o)
	{
		o.Out();
	}

	stop;

	//=======================================================================
	// Контейнеры стандартной библиотеки. Последовательности типа std::vector
	//=======================================================================

	// Создайте пустой вектор целых чисел. Узнайте его размер с помощью метода size(),
	// С помощью метода push_back() заполните вектор какими-либо значениями.
	// Получите новый размер вектора и выведите значения его элементов.
	// В процессе работы с вектором вы можете кроме количества реально заполненных
	// элементов (size()) узнать максимально возможное количество элементов (max_size()),
	// а также зарезервированную память (capacity()).

	std::vector<int> v;
	unsigned int n = v.size();
	v.push_back(-1);
	v.push_back(-2);
	pr(v, "Elements of vector v");
	n = v.size();
	std::cout << n << std::endl;
	n = v.capacity();
	std::cout << n << std::endl;
	n = v.max_size();
	std::cout << n << std::endl;

	// Так как мы часто будем выводить последовательности, то целесообразно
	// создать шаблон функции для вывода любого контейнера.
	// Проанализируйте коды такого шабдлона (pr), который приведен выше
	// Используйте его для вывода вашего вектора

	pr(v, "Vector of ints");

	// Используем другой конструктор для создания вектора вещественных
	// с начальным размером в 2 элемента и заполнением (222.).
	// Проверим параметры вектора. Затем изменим размер вектора и его заполнение
	// (метод - resize()) и вновь проверим параметры.

	std::vector<double> vd;
	pr(vd, "Vector of doubles");
	n = vd.size();
	n = vd.capacity();
	n = vd.max_size();

	vd.resize(2, 222.);

	pr(vd, "After resize");
	n = vd.size();
	n = vd.capacity();
	n = vd.max_size();

	// Используя метод at(), а также операцию выбора [], измените значения
	// некоторых элементов вектора и проверьте результат.
	vd.at(0) = 3.14;
	pr(vd, "After at");

	// Создайте вектор вещественных, который является копией существующего.
	std::vector<double> wd = vd;
	pr(wd, "Copy");

	// Создайте вектор, который копирует часть существующей последовательности
	std::vector<double> ud(vd.begin(), vd.end() - 1);
	pr(ud, "Copy part");

	// Создайте вектор вещественных, который является копией части обычного массива.
	double ar[] = { 0., 1., 2., 3., 4., 5. };
	std::vector<double> va(ar + 1, ar + sizeof(ar) / sizeof(ar[0]) - 2);
	pr(va, "Copy part of array");

	// Создайте вектор символов, который является копией части обычной строки
	char s[] = "Array is a succession of chars";
	std::vector<char> vc(s + 2, s + 5);
	pr(vc, "Copy part of c-style string");

	// Создайте вектор элементов типа Vector и инициализируйте
	// его вектором с координатами (1,1).
	std::vector<Vector> vv(3, Vector(1, 1));

	std::cout << "\n\nvector of Vectors\n";
	for (int i = 0; i < vv.size(); i++)
		vv[i].Out();

	// Создайте вектор указателей на Vector и инициализируйте его адресами
	// объектов класса Vector

	std::vector<Vector*> vp = { new Vector(1,2), new Vector(3,4), new Vector(5,6) };
	std::cout << "\n\nvector of pointers to Vector\n";

	for (int i = 0; i < vp.size(); i++)
		vp[i]->Out();

	// Научитесь пользоваться методом assign и операцией
	// присваивания = для контейнеров типа std::vector.
	vp.assign(4, new Vector(7, 8));

	std::cout << "\n\nAfter assign\n";
	for (int i = 0; i < vp.size(); i++)
		vp[i]->Out();

	// Декларируйте новый вектор указателей на Vector и инициализируйте его 
	// с помощью второй версии assign
	//vpNew.assign 

	std::cout << "\n\nNew std::vector after assign\n";
	std::vector<Vector*> vpNew;
	vpNew.assign(vp.begin(), vp.end());
	for (int i = 0; i < vpNew.size(); i++)
		vpNew[i]->Out();


	// На базе шаблона std::vector создание двухмерный массив и
	// заполните его значениями разными способами.
	// Первый вариант - прямоугольная матрица
	// Второй вариант - ступенчатая матрица

	//========= Ступенчатая матрица
	std::vector <std::vector<double>> vdd(5); // will be default values (0)
	for (int i = 0; i < vdd.size(); i++)
		vdd[i] = std::vector<double>(i + 1, double(i));

	std::cout << "\n\n\tTest std::vector of std::vector<double>\n";
	for (int i = 0; i < vdd.size(); i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < vdd[i].size(); j++)
			std::cout << vdd[i][j] << "  ";
	}

	stop;

	//========== Прямоугольная матрица
	vdd.clear();
	vdd = std::vector<std::vector<double>>(5, std::vector<double>(3, 3.0));
	std::cout << "\n\n\tTest std::vector of std::vector<double>\n";
	for (int i = 0; i < vdd.size(); i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < vdd[i].size(); j++)
			std::cout << vdd[i][j] << "  ";
	}
	std::cout << "\n\n";

	//===================================
	// Простейшие действия с контейнерами
	//===================================
	//3б. Получение значения первого и последнего элементов последовательности.
	//Получение размера последовательности. Присваивание значений
	//элементов одной последовательности элементам другой - assign().

	//Создайте и проинициализируйте вектор из элементов char. Размер -
	//по желанию.
	std::vector<char> vChar1(10, 'a');


	//Создайте и проинициализируйте массив из элементов char. Размер -
	//по желанию.
	char cMas[10];
	for (int i = 0; i < 10; i++) {
		cMas[i] = 'b';
	}

	//Получите значение первого элемента вектора ( front() )
	char vfirst = vChar1.front();

	//Получите значение последнего элемента вектора ( back() )
	char vlast = vChar1.back();

	//Получите размер вектора
	int vsize = vChar1.size();
	std::cout << vfirst << " " << vlast << " " << vsize << std::endl;

	//Присвойте вектору любой диапазон из значений массива cMas.
	vChar1 = std::vector<char>(cMas + 1, cMas + 5);

	//Проверьте размер вектора, первый и последний элементы.
	vfirst = vChar1.front();
	vlast = vChar1.back();
	vsize = vChar1.size();
	std::cout << vfirst << " " << vlast << " " << vsize << std::endl;


	stop;


	//3в. Доступ к произвольным элементам вектора с проверкой - at()
	//и без проверки - []
	//Создайте неинициализированный вектор из 8 элементов char - vChar2.
	//С помощью at() присвойте четным элементам вектора значения
	//элементов vChar1 из предыдущего задания,
	//а с помощью [] присвойте нечетным элементам вектора vChar2 значения
	//массива {'K','U','K','U'}.

	std::vector<char> vChar2(8);
	for (int i = 0; i < 8; i += 2) // numering from 0
		vChar2.at(i) = vChar1.at(i / 2);
	char arrKuku[] = { 'K', 'U', 'K', 'U' };
	for (int i = 1; i < 8; i += 2)
		vChar2.at(i) = arrKuku[i / 2];
	pr(vChar2, "Checking replaced with at() elements");
	std::cout << std::endl;

	stop;
	//Попробуйте "выйти" за границы вектора с помощью at() и
	//с помощью []. Обратите внимание: что происходит при
	//попытке обращения к несуществующему элементу в обоих случаях

	//std::cout << vChar2.at(100) << std::endl; // out_of_range exception
	//std::cout << vChar2[100] << std::endl; // generally UB; in VS: assertion: vector subscript out of range


	stop;

	//3г.Добавьте в конец вектора vChar2  - букву Z (push_back()). Для
	//расширения кругозора можете ее сразу же и выкинуть (pop_back())
	vChar2.push_back('Z');
	std::cout << vChar2.size() << ' ' << vChar2.back() << std::endl;
	vChar2.pop_back();
	std::cout << vChar2.size() << ' ' << vChar2.back() << std::endl;


	stop;

	//3д. Вставка-удаление элемента последовательности insert() - erase()
	//Очистка последовательности - clear()



	//Вставьте перед каждым элементом вектора vChar2 букву 'W'
	for (int i = vChar2.size() - 1; i >= 0; --i)
		vChar2.insert(vChar2.begin() + i, 'W');

	//Вставьте перед 5-ым элементом вектора vChar2 3 буквы 'X'
	vChar2.insert(vChar2.begin() + 4, 3, 'X');
	pr(vChar2, "Inserted X");

	//Вставьте перед 2-ым элементом вектора vChar2 с третьего по
	//шестой элементы массива "aaabbbccc"
	char arrAbc[] = "aaabbbccc";
	vChar2.insert(vChar2.begin() + 2, arrAbc + 2, arrAbc + 5);
	pr(vChar2, "Inserted 3-6th elements of \"aaabbbccc\"");

	//Сотрите c первого по десятый элементы vChar2
	vChar2.erase(vChar2.begin(), vChar2.begin() + 10);
	pr(vChar2, "Erased 0-9 elements");

	stop;

	//Уничтожьте все элементы последовательности - clear()

	vChar2.clear();
	pr(vChar2, "Cleared");

	stop;

	//Создание двухмерного массива
	// ??? I don't quite get it, but... well...
	std::vector<std::vector<int>> twoDVector; // 2d vector of ints
	int twoDArray[10][10]; // 2d array of ints

	stop;

	///////////////////////////////////////////////////////////////////

		//Задание 4. Списки. Операции, характерные для списков.
		//Создайте два пустых списка из элементов Vector - ptList1 и
		//ptList2
	std::list<Vector> ptList1, ptList2;

	//Наполните оба списка значениями с помощью методов push_back(),
	//push_front, insrert()
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			ptList1.push_back(Vector(x, y));
			ptList2.push_front(Vector(x, y));
		}
	}
	auto it1 = ptList1.begin();
	std::advance(it1, 1);
	auto it2 = ptList2.begin();
	std::advance(it2, 1);
	ptList1.insert(it1, Vector(5, 5));
	ptList2.insert(it2, Vector(5, 5));

	pr(ptList1, "First list");
	pr(ptList2, "Second list");

	//Отсортируйте списки - sort().
	//Подсказка: для того, чтобы работала сортировка, в классе Vector
	//должен быть переопределен оператор "<"
	ptList1.sort();
	ptList2.sort();
	pr(ptList1, "Sorted first list");
	pr(ptList2, "Sorted second list");

	stop;

	//Объедините отсортированные списки - merge(). Посмотрите: что
	//при этом происходит со вторым списком.
	ptList1.merge(ptList2); //if not sorted - abort
	std::cout << "\nMerged" << std::endl;
	pr(ptList1, "First list");
	pr(ptList2, "Second list"); // It is empty now
	std::cout << ptList2.size() << ' ' << ptList2.max_size() << std::endl;

	stop;

	//Исключение элемента из списка - remove()
	//Исключите из списка элемент с определенным значением.
	//Подсказка: для этого необходимо также переопределить
	//в классе Vector оператор "=="

	ptList1.remove(Vector(5, 5));
	pr(ptList1, "Removed Vector(5, 5) (from first list)");
	ptList2.remove(Vector(100, 100)); // Nothing happens
	pr(ptList2, "Removed Vector(100, 100) (from second list)");

	stop;

	///////////////////////////////////////////////////////////////////

		//Задание 5. Стандартные алгоритмы.Подключите заголовочный файл
		//5а. Выведите на экран элементы ptList1 из предыдущего
		//задания с помощью алгоритма for_each()
		/* print elements of ptList1 using for_each()*/
	std::for_each(ptList1.begin(), ptList1.end(), [](auto element) {
		std::cout << element << ' ';
		});
	std::cout << '\n';


	stop;

	//5б.С помощью алгоритма find() найдите итератор на элемент Vector с
	//определенным значением. С помощью алгоритма find_if() найдите
	//итератор на элемент, удовлетворяющий определенному условию, 
	//например, обе координаты точки должны быть больше 2.
	//Подсказка: напишите функцию-предикат, которая проверяет условие
	//и возвращает boolean-значение (предикат может быть как глобальной
	//функцией, так и методом класса)

	/*auto predicate = [](const Vector& v) {
		return v.GetX() > 1 && v.GetY() > 1;
	};*/

	// Ищем конкретный элемент Vector(1, 1) — предположим, он есть в списке
	Vector target(1, 1);
	auto it_find = std::find(ptList1.begin(), ptList1.end(), target);

	if (it_find != ptList1.end()) {
		std::cout << "\nFound Vector(1, 1) using find(): ";
		it_find->Out();
		std::cout << '\n';
	}
	else {
		std::cout << "\nVector(1, 1) not found in ptList1.\n";
	}

	// Ищем первый элемент, где x > 1 и y > 1
	auto predicate = [](const Vector& v) {
		return v.GetX() > 1 && v.GetY() > 1;
		};

	/*auto it_find_if = std::find_if(ptList1.begin(), ptList1.end(), [](Vector* v) {
			return v->isBig();
		});*/
	auto it_find_if = std::find_if(ptList1.begin(), ptList1.end(), predicate);

	if (it_find_if != ptList1.end()) {
		std::cout << "Found first Vector with x>1 and y>1 using find_if(): ";
		it_find_if->Out();
	}
	else {
		std::cout << "No Vector found with x>1 and y>1.\n";
	}

	stop;

	//Создайте список из указателей на элеметы Vector. С помощью 
	//алгоритма find_if() и предиката (можно использовать предикат - 
	//метод класса Vector, определенный в предыдущем задании) найдите в
	//последовательности элемент, удовлетворяющий условию

	std::list<Vector*> ptPtrList;

	ptPtrList.push_back(new Vector(5, 1));
	ptPtrList.push_back(new Vector(3, 2));
	ptPtrList.push_back(new Vector(2, 5));
	ptPtrList.push_back(new Vector(5, 8));
	ptPtrList.push_back(new Vector(-1, -1));
	
	auto it = std::find_if(ptPtrList.begin(), ptPtrList.end(), [predicate](Vector* v) {
		return predicate(*v);
		});

	if (it != ptPtrList.end()) {
		std::cout << "\nFound Vector with x>2 and y>2 via pointer list: ";
		(*it)->Out();
	}
	else {
		std::cout << "\nNo Vector found with x>2 and y>2.\n";
	}

  
	
	stop;

	//5в. Создайте список элементов Vector. Наполните список
	//значениями. С помощью алгоритма replace() замените элемент
	//с определенным значением новым значением. С помощью алгоритма
	//replace_if() замените элемент, удовлетворяющий какому-либо
	//условию на определенное значение. Подсказка: условие
	//задается предикатом.

	std::list<Vector> replaceList;

	replaceList.push_back(Vector(1, 1));
	replaceList.push_back(Vector(3, 2));
	replaceList.push_back(Vector(1, 2));    
	replaceList.push_back(Vector(3, 6));
	replaceList.push_back(Vector(1, 2));    
	replaceList.push_back(Vector(8, 0));

	std::cout << "\n\n\tBefore replacement:\n";
	pr(replaceList, "Original list");

	Vector oldVal(1, 1);
	Vector newVal(99, 99);

	std::replace(replaceList.begin(), replaceList.end(), oldVal, newVal);

	std::cout << "\n\tAfter replace(Vector(1,1) -> Vector(99,99)):\n";
	pr(replaceList, "After replace");

	Vector replaceWith(-1, -1);

	std::replace_if(replaceList.begin(), replaceList.end(), predicate, replaceWith);

	std::cout << "\n\tAfter replace_if(x>2 OR y>2 -> Vector(-1,-1)):\n";
	pr(replaceList, "After replace_if");

  
	stop;


	//5г. Создайте вектор строк (string). С помощью алгоритма count()
	//сосчитайте количество одинаковых строк. С помощью алгоритма
	//count_if() сосчитайте количество строк, начинающихся с заданной
	//буквы

	std::vector<std::string> strVec = {
		"Aboba",
		"among",
		"us",
		"Blue",
		"purple", 
		"ORANGE",
		"black",
		"wooooooooow",
		"ABOBA",
		"Aboba",
		"C++ labs are so interesting",
		"I want to finish it ASAP",
		"Amogus",
		"Abobus",
		"Abooooobus"
	};

	std::cout << "\n\n\tVector of strings:\n";
	for (size_t i = 0; i < strVec.size(); ++i) {
		std::cout << i + 1 << ". \"" << strVec[i] << "\"\n";
	}

	std::string targetStr = "Aboba";
	size_t countApple = std::count(strVec.begin(), strVec.end(), targetStr);

	std::cout << "\nCount of \"" << targetStr << "\": " << countApple << " times\n";

	auto startsWithA = [](const std::string& s) {
		return !s.empty() && (s[0] == 'A' || s[0] == 'a');
		};

	size_t countStartsWithA = std::count_if(strVec.begin(), strVec.end(), startsWithA);

	std::cout << "Count of strings starting with 'A' or 'a': " << countStartsWithA << " times\n";

	auto startsWithCapitalA = [](const std::string& s) {
		return !s.empty() && s[0] == 'A';
		};

	size_t countStartsWithCapitalA = std::count_if(strVec.begin(), strVec.end(), startsWithCapitalA);
	std::cout << "Count of strings starting with 'A' (capital only): " << countStartsWithCapitalA << " times\n";


	//5д. С помощью алгоритма count_if() сосчитайте количество строк,
	//которые совпадают с заданной строкой. Подсказка: смотри тему
	//объекты-функции

	std::cout << "Target string to match: \"" << targetStr << "\"\n";

	class StringMatcher {
	public:
		StringMatcher(const std::string& target) : target_(target) {}

		bool operator()(const std::string& s) const {
			return s == target_;
		}

	private:
		std::string target_;
	};

	size_t countMatched = std::count_if(strVec.begin(), strVec.end(), StringMatcher(targetStr));

	std::cout << "\nNumber of strings matching \"" << targetStr << "\": " << countMatched << " times\n";


	stop;


	std::cout << "\n\n";
}