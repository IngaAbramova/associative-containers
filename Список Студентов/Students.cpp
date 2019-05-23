//Подключаем библиотеку и заголовочный файл
#include <iostream>
#include "Students.h"
using namespace std;

/*float AVG(std::set<GradesForTheExam> pass)
{
	float Sum = 0;
	int n = 0;
	List<GradesForTheExam> *q;
	for (std::set<GradesForTheExam>::iterator it = pass.begin(); it != pass.end(); ++it)
	{
		GradesForTheExam a = *it;
		a.WriteExamOnScreen();
		Sum = Sum + a.get_mark();
		n++;
	}
	Sum = Sum / n;
	return Sum;
}*/
int main()
{
	//Используем русскую раскладку
	setlocale(LC_ALL, "Russian");
	//Команда пользователя
	int comand=-1;
	cout << "1. Загрузить список студентов из файла" << endl;
	cout << "2. Загрузить список студентов в файл" << endl;
	cout << "3. Вывести список студентов на экран" << endl;
	cout << "4. Загрузить список предметов из файла" << endl;
	cout << "5. Загрузить список предметов в файл" << endl;
	cout << "6. Вывести список предметов на экран" << endl;
	cout << "7. Добавить экзамен" << endl;
	cout << "8. Удалить студента" << endl;
	cout << "9. Добавить студента" << endl;
	cout << "10. Изменить оценку" << endl;
	cout << "0. Выйти" << endl;
	//Пользоватедль вводит команду
	cin >> comand;
	//map < int, int > Mark;
	//Инициализируем списки
	List<Information> *P = new List<Information>();
	List<Subjects> *K = new List<Subjects>();
	K->LoadSubjectsFromFile("SubjectsIn.txt");
	while (comand != 0)
{
		//Загрузка списка студентов из файла
		if (comand == 1)
		{
            P->LoadFromFile("StudentsIn.txt", *&K);
			cout << "Cписок студентов загружен из файла" << endl;
		}
		//Загрузка списка студентов в файл
		if (comand == 2)
		{
			P->LoadInFile("StudentsOut.txt");
			cout << "Cписок студентов загружен в файл" << endl;
		}
		//Вывод списка студентов на экран
		if (comand == 3)
		{
			P->LoadOnScreen();
		}
		//Загрузка списка предметов из файла
		if (comand == 4)
		{
			//K->LoadSubjectsFromFile("SubjectsIn.txt");
			cout << "Cписок предметов загружен из файла" << endl;
		}
		//Загрузка списка предметов в файл
		if (comand == 5)
		{
			K->LoadSubjectsInFile("SubjectsOut.txt");
			cout << "Cписок предметов загружен в файл" << endl;
		}
		//Вывод списка предметов на экран
		if (comand == 6)
		{
			K->LoadOnScreenSubjects();
		}
		//Добавление информации об экзамене для студента
		if (comand == 7)
		{
			cout << "Введите фамилию студента";
			char ch[20];
			cin>>ch;
			cout << "Введите номер предмета";
			int number=0;
			cin >> number;
			cout << "Введите оценку";
			int mark = 0;
			cin >> mark;
			P->AddEXAM(ch,number,mark, *&K);
		}
		if (comand == 8)
		{
			P->Delete();
		}
		if (comand == 9)
		{
		    P->AddStudent(*&K);
		}
		if (comand == 10)
		{
			P->Change(*&K);
		}
		cout << "1. Загрузить список студентов из файла" << endl;
		cout << "2. Загрузить список студентов в файл" << endl;
		cout << "3. Вывести список студентов на экран" << endl;
		cout << "4. Загрузить список предметов из файла" << endl;
		cout << "5. Загрузить список предметов в файл" << endl;
		cout << "6. Вывести список предметов на экран" << endl;
		cout << "7. Добавить экзамен" << endl;
		cout << "8. Удалить студента" << endl;
		cout << "9. Добавить студента" << endl;
		cout << "10. Изменить оценку" << endl;
		cout << "0. Выйти" << endl;
		cin >> comand;
}
	system("pause");
}








