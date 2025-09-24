#include <cmath>			// математические функции
#include <locale.h>	// функции, устанавливающие национальные кодировки символов
#include <iostream>	// Эта - часть библиотеки STL (Standard Template Library)
#include <limits>			// Полезные константы
// ADDED
#include <climits>
#include <cfloat>

using namespace std;		// Обеспечивает видимость имен STL
//#define stop //__asm nop// Эта макроподстановка упрощает установку точек останова

int n;	 // Глобальная переменная. По умолчанию она обнуляется.

namespace space	 // В пространстве имен - space
{
	int n = 1;	 // Объявлена переменная n
}				 // space определяет область видимости этой переменной

int  main()
{
	// Выполняя программу по шагам, следите за значениями переменных  и интерпретируйте результат, объясняя себе
	// наблюдаемые значения. Обратите внимание на разную интерпретацию отладчиком  signed и unsigned типов данных.
	char c = 'A'; // 65 'A' 0x41 
	// В комментарии справа полезно проставить десятичное символьное и шестнадцатиричное 
	// значения переменной после выполнения указанной строки. Вы должны видеть их в окне Autos.
	c = 0x42;		// 66 'B' 0x42
	c = -1;		// -1 'я' 0xff
	c = CHAR_BIT;	 // Размер переменной типа char
	//stop;

	// В комментариях напишите результат, возвращаемый оператором sizeof для
	// переменной типа wchar_t (ее размер)
	wchar_t cw = L'Ф'; // 1060 L'Ф'
	size_t ns = sizeof(cw); // 4

	unsigned char uc = 0x41; // 65 'A'
	uc = 'B'; // 66 'B' 0x42
	uc = -128; // 128 '\377' 0xff
	//stop;

	int i = 1; // 0x1
	i = -1; // 0xffffffff
	//stop;

	unsigned int ui = 1; // 0x1
	ui = -1; // 0xffffffff

	short s = static_cast<short>(0xffff);	 // Здесь compiler генерирует warning. Измените код, чтобы убрать warning
	//s = short(0xffff);
	s = 1;

	//==== Измените код, чтобы убрать warning
	unsigned short us = 0xffff;
	us = 5;

	long l = 0xffffffffL; //-1
	l = -128;

	// Все эти константы вы должны найти в файле limits (float.h) и объяснить их смысл по комментариям
	
	// https://learn.microsoft.com/ru-ru/cpp/c-language/limits-on-floating-point-constants?view=msvc-170
	// FLT_RADIX - основание экспоненциальной формы представления; 2
	l = FLT_MAX_EXP; // макс. целое число, при кот. знач. FLT_RADIX, возведенное
	// в степень этого числа, является представимым числом с плав. запятой; 128
	l = DBL_MAX_EXP; // описание то же; 1024

	l = FLT_MANT_DIG; // кол-во цифр для основания, заданного конст. 
	// FLT_RADIX, в знач. части числа с плав. запятой; основание содержит два 
	// знака, следовательно, эти значения определяют разряды; 24
	l = DBL_DIG; // Количество цифр q, при котором число с плавающей запятой 
	// с q десятичными цифрами можно округлить в представление с плавающей 
	// запятой и обратно без потери точности.

	l = FLT_MANT_DIG; // описано выше
	l = DBL_MANT_DIG; // описание, как у FLT_MANT_DIG; 53

	float f = -12.56;	 // Здесь warning. Уберите его.
	f = -1.e-27f;

	f = FLT_MAX;
	f = FLT_MIN;

	double d = 0.1234567890123456789123456789;
	d = -0.123456789012345e+306;
	d = DBL_MAX;
	d = DBL_MIN;
	d = DBL_EPSILON; // Самая маленькая разность между двумя пер-ми типа double
//x1-x2<DBL_EPSILON
	uc = ~2;		 // Побитовое отрицание // 253 '\377' 0xff
	// 1111 1101          
	i = ~0; // 256 0x100
	//stop;
	// Раннее (при компиляции) или неявное приведение типов данных
	// Объясните те значения, которые вы наблюдаете в окне Autos. Определите порядок выполения присваиваний.
	// присваиваются справа налево.
	d = f = i = s = c = 1 / 3; // all 0 since 1/3=0 in var c and 0 is always 0
	c = s = i = f = d = 100 / 3; // 33'!' 33 33 33 33
	c = s = i = f = d = 10 / 3; // 3'\003' 3 3 3 3
	c = s = i = f = d = 1 / 3.; // 0'\000' 0 0 0.33..43 0.33..1

	// Пример "небрежного" использования неявного приведения типов.	 Объясните результаты.
	i = 256; // 256
	c = i; // 0; целочисленное переполнение, макс. в с может быть 127

	uc = 255; // 255 '\377'
	unsigned char u = 2, sum = uc + u; // sum = 255+2=257-256=1 (макс. 255)
	//stop;

	// Явное приведение типов	Объясните разницу результатов в строках (3) и (4)
	i = 100;
	f = d = i / 3;	// (3) по 33; dividing ints
	f = d = (double)i / 3; // (4) 33.3..21, 33.3..6 ; dividing double and int
	f = d = double(i) / 3; // (4) same
	f = d = static_cast<double>(i) / 3;	// (4) same
	//stop;

	// Область действия, область видимости и время существования. В этом фрагменте фигурируют четыре
	//  переменных с одним и тем же именем n.  Одна - глобальная, вторая определена в своем пространстве имен,
	// третья - локальная внутри функции main(), четвертая - локальная внутри блока. 
	//  Обратите внимание, что глобальная переменная и та, что в пространстве имен space - объявлены вне функции main()
	// Определите, к какой из четырех переменных идет обращение, cформулируйте область действия и область видимости
	// каждой переменной. Для выполнения задания рекомендуется пользоваться  закладкой "Watches" или "Locals" окна
	// "Autos". Подсказка: В окно "Watches" можно поместить сразу все переменные (n, ::n, и space::n)
	n = 100; // global
	space::n = 200; // space
	n++; // global
	int n;	//Где живет эта переменная ? // main
	n = 10; // main
	::n++; // global

	{				//  Начало блока
		int n;		// Эта переменная живет внутри блока
		n = -1; // block
		n++; // block
		::n++; // global
		space::n++; // space
	}		// Конец блока
	n--; // main
	::n--; // global
	space::n--; // space

	// Спецификатор класса памяти - static Выполняя задание по шагам, обратите внимание на  разное поведение
	// переменных nLoc и nStat
	{
	Again:
		int outer;
		for (int i = 0; i < 5; i++)
		{
			static int nStat; // value of static var is saved between
			{ // the iterations; deleted upon exitting the programm
				int nLoc = 0; // the value of auto var is not saved between
				nLoc++;		nStat++; // the iterations since it is deleted
			} // upon each block exit and redefined during every iteration.
			outer = nStat;
		}
		if (outer < 10)
			goto Again;
	}
	// Перечисления - enum. Обратите внимание на явную и неявную инициализацию констант
	enum RANK
	{
		One, // 0
		Two, // 1
		Three, // 2
		Four, // 3
		Jack = 6, // 6
		Queen, // 7
		Ace = Queen + 3, // 10
		Joker = 20 // 20
	};
	typedef RANK RANG; // created nickname for this enum

	RANG r = Jack; // 6
	if (r == Jack) // true
		r = Queen; // 7

	if (r == Queen) // true
	{
		// Любой целочисленной переменной можно присвоить enum-переменную 
		int i = r; // 7
		r = RANK(i++); // 7 Queen // Обратное преобразование надо указывать явно
		i = r; // 7, 7 Queen
		r = RANK(++i); // i = 8; r = 8, no equivalent; enum sets possible
		i = r; // values (One, Queen), but doesn't prevent us from putting
	} // to vars of its type other integers. In i=r line both are 8.
	RANK rr = Ace; // 10
	//stop;
	//	Логический тип bool.	Выполняя задание по шагам, следите за значениями переменной b
	{
		int n = 127;
		bool b = n != 0; // 1 true
		b = n == 0; // 0 false
		b = n > 0; // 1 true
		b = n <= 0; // 0 false
		b = n > 1; // 1 true

		b = -5;
		int num = static_cast<int>(b); // 1
		if (b) // true
			cout << "\n\t My flag is: true" << "   or: " << b
			<< "\n\t Conversion to int: " << num << endl;
		b = n == num; // 0 false
		cout << "\n\t Now the flag is: false" << "   or: " << b;
	}

	//	Модификатор const
	const double pi = acos(-1.); // 3.14159265...; below is 1.245...e-06
	double space_permiability = 4.e-7 * pi;		//	Магнитная проницаемость пустоты
	const int dozen = 12; // 12
	int var = dozen; // 12

	//	Раскомментируйте следующую строчку и объясните ошибку компиляции (l-value означает left value)
	//	dozen = 1;
	//	Директивы условной трансляции. Объясните значение, которое принимает переменная version.
	//	Что нужно сделать для того, чтобы результат был другим?
#define _MSVER400
	const char* version;
#if defined _MSVER400 // true
	version = "version 4.00";
#elif defined _MSVER311 // false
	version = "version 3.11";
#else // false
	version = "version Unknown";
#endif

	cout << endl << version << endl;
	//stop;

	//В окне ClassView или Solution Explorer поставьте фокус на имя проекта дайте команду Project/Properties.
	//	В диалоге Property Pages щелкните на папке Configuration Properties, убедитесь, что в разделе Code Generation
	//	установлена константа компиляции _DEBUG. Создайте директивы препроцессора и код С++, которые
	//	в зависимости от действующей конфигурации проекта (_DEBUG или NDEBUG) выводят соответствующее
	//	сообщение. Измените конфигурацию проекта (в диалоге Property Pages) и проверьте ваш код.
	//	Чтобы изменить конфигурацию пользуйтесь кнопкой Configuration Manager

#ifdef _DEBUG
    cout << "DEBUG version" << endl;
#elif defined NDEBUG
    cout << "RELEASE version" << endl;
#else
    cout << "No configuration set" << endl;
#endif

	//	Простейшие циклы. Объясните суть происходящего. 
	{
		// Цикл while надо использовать, когда неизвестно количество итераций (повторений) цикла.
		cout << "\n\nGradually eat out all the units:\n\n";
		unsigned short us = 0xff; // 255
		while (us)
		{
			cout << hex << us << endl;
			us &= us - 1; // mask; one by one all 1 will be 'eaten'
		}
		cout << hex << us << "\nDone\n";
		// Цикл for надо использовать, когда известно количество итераций и/или есть код подготовки.
		// Подсказка: odd - нечетое, even - четное.
		cout << "\n\nShow even-odd:\n\n";
		for (int i = 0; i < 10; i++)
		{
			if (4 & 1) // we check the last bit which tells if it's even or odd
				cout << i << " - odd\n";
			else
				cout << i << " - even\n";
		}
		// Когда нужно использовать цикл do-while?
		// answer: when the amount of iterations is unknown but we MUST do
		// it at least once
		char c = ' ';
		do // in the first iteration we go to 'else' block which is not
		{ // associated with any letter expected from the user. We also go there
			if (c == 'a') // any time the user enters a wrong character.
				cout << "\nAction is a delegate type in C#"; // then we do
			else if (c == 'b') // this loop until the user enters 'q'
				cout << "\nbreak is one of the 'leave' statements in all C-like languages";
			else if (c == 'c')
				cout << "\ncontinue is a 'go on' statement in all C-like languages";
			else if (c == 'd')
				cout << "\ndo-while is a rarely used loop statement in all C-like languages";
			else
				cout << "\nPlease read the rules of this loop";
			cout << "\n\nEnter chars: a, b, c, d (q - to quit):\n\n";
			cin >> c;
			if (c == 'q')
				cout << "\nI am going to leave the loop\n";
		} while (c != 'q');
		//stop;
	}
	//	Логические условные операторы и циклы. Функция y = f(x) задана графиком
	//	Напишите фрагмент кода, который с шагом 0.1 вычисляет y = f(x)  и выводит в консольное окно значения x и y. 
	/*	  y
	//	  | 
	//	 2|__________
	//	  |         /\
	//	  |        /  \
	//	  |       /    \
	//	  |______/      \__________  x
	//	  0      1   2   3
	//	 Реалируйте 2 варианта этого алгоритма:   1. Используйте операторы if	 2. Используйте тернарные операции    ? :
*/

	{
		for (double x = 0; x <= 4.0; x += 0.1) {
			double y;
			if (x <= 1.0) {
				y = 0;
			} else if (x <= 2.0) {
				y = 2 * x - 2;
			} else if (x <= 3.0) {
				y = -2 * x + 6;
			} else {
				y = 0;
			}
			cout << "x = " << x << ", y = " << y << endl;
		}

		for (double x = 0; x <= 4.0; x += 0.1) {
			double y = (x <= 1.0) ? 0 : 
					   (x <= 2.0) ? 2 * x - 2 :
					   (x <= 3.0) ? -2 * x + 6 :
					   0;
			cout << "x = " << x << ", y = " << y << endl;
		}
	}

	//	Напишите фрагмент, который с помощью for и switch реализует следующую логику. Если пользователь ввел:
	//	символ 'a',   ваш алгоритм выводит  "Ok" (в кавычках)
	//	символ 'b',   ваш алгоритм выводит  Bell (alert - звуковой сигнал)
	//	символ 'с',   ваш алгоритм выводит  число, которое равно количеству введенных символов
	//	символ 'Esc', ваш алгоритм выводит  "to quit use 'q'"
	//	символ 'q',   ваш алгоритм выводит  "Bye" и выходит из цикла ввода

	{
		char ch;
		int count = 0;
		bool stop = false;

		cout << "\n--- Enter characters (q to quit) ---\n";
		cout.setf(ios::dec);

		while (true) {
			//cout << "> ";
			ch = cin.get();  // read one char //_getch()
			count++;

			// ignoring newline characters
			if (ch == '\n') {
				count--;
				continue;
			}

			switch (ch) {
				case 'a':
					cout << "\"Ok\"\n";
					break;
				case 'b':
					cout << "Bell\n";
					cout << '\a';
					break;
				case 'c':
					cout << "Count: " << count << endl;
					break;
				case 27:  // ASCII code for Esc
					cout << "to quit use 'q'\n";
					break;
				case 'q':
					cout << "Bye" << endl;
					stop = true;
					break; 
				default:
					cout << "Unknown command\n";
			}
			if (stop) break;
		}
    }

	//	Побитовые операции:  |, &, ~, ^ и сдвиги >>, <<
	//	Поменяйте местами байты переменной flags и выведите результат в консолное окно unsigned short flags = 0xaabb;
	//	Ваш код
	unsigned short flags = 0xaabb;
    cout << "\nOriginal flags: " << hex << flags << " " << dec << flags << endl;

    flags = (flags << 8) | (flags >> 8);
    cout << "Swapped bytes: " << hex << flags << " " << dec << flags << endl;

	//	Для вывода в шестнадцатеричном виде используйте  cout <<"\n bits = " << hex << flags;
	//	В переменной unsigned char byte = 0x26; 
        //      - установите в единицу 3-й бит (счет от нуля). Выведите результат.
	//	- инвертируйте два младших бита. Выведите результат. 
        //      - обнулите 4 младших бита. Выведите результат.
	//	cout <<endl << hex << flags << endl<<dec<<flags;    

	unsigned char byte = 0x26; // 0010 0110
	cout << "\nOriginal byte: " << hex << (int)byte << " " << dec << (int)byte << endl;
	byte |= (1 << 3); // set 3rd bit to 1 : 0010 1110
	cout << "\nAfter setting the 3rd bit: " << hex << (int)byte << " " << dec << (int)byte << endl;
	byte ^= 0x03; // XOR with 0000 0011 : 0010 1101
	cout << "After inverting 2 LSB: " << hex << (int)byte << " (" << dec << (int)byte << ")" << endl;
	byte &= 0xf0; // 4 MSB left as they are, 4 LSB set to 0 : 0010 0000
	cout << "After clearing 4 LSB: " << hex << (int)byte << " (" << dec << (int)byte << ")" << endl;

	//cout << "\n\n"; 
	cout << ns << ui << us << l << sum << rr << space_permiability << var << endl;
}	// Конец функции main()
