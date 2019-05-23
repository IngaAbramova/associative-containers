#pragma once
#ifndef Students
#define Students
//Подключаем необходимые библиотеки
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iterator>
using namespace std;
//Классы
class Information;
class GradesForTheExam;
class Subjects;
template <class T>
//Шаблон списка
class List
{
	friend class List<GradesForTheExam>;
	friend class GradesForTheExam;
	//Указатель на следующий элемент списка
	List<T> *next;
	//Информационное поле
	T data;
	//Конструктор
	List(T &v) { data = v; next = NULL; }
public:
	List<T> *get_next() { return next; }
	void set_next(List<T> *next) { this->next = next; }
	T get_data() { return data; }
	void set_data(T data) { this->data = data; }
	//Методы класса
	void LoadInFile(const char *StudentsOut);
	void LoadOnScreen();
	int LoadFromFile(const char *StudentsIn, List<Subjects> *&R);
	void LoadOnScreenSubjects();
	int LoadSubjectsFromFile(const char *SubjectsIn);
	void LoadSubjectsInFile(const char *SubjectsOut);
	void AddEXAM(char *ch, int number,int mark, List<Subjects> *&);
	void Delete();
	void Change(List<Subjects> *&R);
	void AddStudent(List<Subjects> *&);
	//Конструктор
	List()
	{
		next = NULL;
	};
	//Деструктор
	~List()
	{
		if (next != NULL) delete next;
	};
	//Функция добавления элемнта в список
	void AddElements(T &c)
	{
		List *p, *q;
		T S = c;
		p = new List(c);
		q = this;
		p->next = q->next;
		q->next = p;
	};
};

//Оценки за экзамены для студента
class GradesForTheExam
{
	friend class List<GradesForTheExam>;
	//Номер предмета
	int subject;
	//Указатель на соответствующий элемент списка предметов
	List<Subjects> *Sub;
	//Оценка
	int mark;
public:
	
	void set_subject(int s) { this->subject = s; };
	void set_mark(int m) { this->mark = m; };
	void set_Sub(List<Subjects> *S) { this->Sub = S; };
	int get_subject() const { return subject; }
	int get_mark() const { return mark; }
	bool operator<(const GradesForTheExam& A) const { return(subject < A.get_subject()); }
	//Методы класса
	int  ReadExam(std::ifstream &f, List<Subjects> *&R);
	void WriteExam(std::ofstream &f);
	void WriteExamOnScreen();
	bool operator==(int n_code) const
	{
		return subject == n_code;
	}
	//Конструктор
    GradesForTheExam()
	{
		Sub = NULL;
		subject = 0;
		mark = 0;
	};
	//Деструктор
	~GradesForTheExam()
	{
	};
};

//Информация о студенте: оценки и средний балл
class Information
{
	friend class List<Information>;
	//Имя студента
	string StudentName;
	//Количество сданных экзаменов
	int  CountOfExam;
	//Средний балл
	float Avg;
	//Указатель на список экзаменов для данного студента
	set<GradesForTheExam> pass;
public:
	void EXAdd(Information *a, int number, int mark, List<Subjects> *&R);
	int get_count_of_exam() { return CountOfExam; }
	void set_count_of_exam(int c) { CountOfExam = c; }
	string get_name() { return StudentName; }
	void set_name(string c) { StudentName = c; }
	void set_Avg(float c) { Avg = c; }
	//Методы класса
	void Write(std::ofstream &f);
	void WriteOnScreen();
	int  Read(Information *a, std::ifstream &f, List<Subjects> *&R);
	//Конструктор
	Information()
	{
		CountOfExam = 0;
		Avg = 0;
		StudentName = "NONAME";
	};
	//Деструктор
	~Information()
	{

	};
};
//Информация о предмете: номер и название
class Subjects 
{
public:
	//Номер предмета
	int NumberOfSubject;
	//Название предмета
	char NameOfSubject[20];
	//Конструктор
	Subjects()
	{
		NumberOfSubject = 0;
	};
	//Деструктор
	~Subjects()
	{
	};
	//Методы класса
	int ReadSubject(std::ifstream &f);
	void  WriteSubjects(std::ofstream &f);
	void WriteSubjectsOnScreen();
};
float AVG(std::set<GradesForTheExam> pass)
{
	float Sum = 0;
	int n = 0;
	for (std::set<GradesForTheExam>::iterator it = pass.begin(); it != pass.end(); ++it)
	{
		GradesForTheExam a = *it;
		Sum = Sum + a.get_mark();
		n++;
	}
	Sum = Sum / n;
	return Sum;
}
//Функция загрузки списка студентов из файла
template<>
int List<Information>::LoadFromFile(const char *StudentsIn, List<Subjects> *&R)
{
	std::ifstream f_in(StudentsIn);
	//Обнуляем счетчик студентов
	int n = 0;
	//Пока файл существует
	while (f_in)
	{
		//Создаем информационную переменную
		Information a;
		//Вызываем функцию для чтения информации об очередном студенте из файла
		int flag = this->data.Read(&a, f_in, *&R);
		//Проверяем флаг на успешный ввод, при flag == 0
		if (!flag) 
		{
			//Добавляем элемент в список
			this->AddElements(a); n++;
		}
		else break;
	}
	//Закрываем файл
	f_in.close();
	return n;
}

//Функция для ввода очередного студента из файла
int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&R)
{
	//Если нет считывания из файла
	int flag = 1; 

	try
	{
		//Читаем имя
		f >> a->StudentName;
		//Проверяем на пустую строку
		if ((a->StudentName.length() == 0)||(a->StudentName == "NONAME")) return 1;
		//Читаем количество экзаменов
		f >> (a->CountOfExam);
		//Создаем переменную для записи количества экзаменов у студента
		int n = a->CountOfExam;
		//Обьявляем переменную - список предметов для студента
		for (int i = 0; i < n; i++)
		{
			GradesForTheExam b;
			int flag = b.ReadExam(f, *&R);
			if (flag!=0)
			{
				a->pass.insert(b);
			}
		}
		a->Avg=AVG(a->pass);
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//Функция считывания одного экзамена
int  GradesForTheExam::ReadExam(std::ifstream &f, List<Subjects> *&R)
{
	//Прочитаем из файла f номер предмета
	f >> (this->subject);
	//Прочитаем из файла f оценку
	f >> (this->mark);
	//Оценку записываем в переменную n
	int n = this->mark;
	List<Subjects> *q = R;
	for (q = R->next; q != NULL; q = q->next)
	{
		Subjects W = q->data;
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (this->subject == W.NumberOfSubject)
		{
			this->Sub = q;
		}
	}
	//Возвращаем оценку
	return n;
}
//Функция загрузки списка в файл
template<>
void List<Information>::LoadInFile(const char *StudentsOut)
{
	std::ofstream f_out;
	//Открывам файл
	f_out.open(StudentsOut, std::ios::app);
	f_out << "	Список студентов\n\nНачало:\n\n";
	//Создаем переменную-список студентов
	List<Information> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызываем функцию записи в файл информации об одном студенте
		q->data.Write(f_out);
	}
	f_out << "\nКонец\n\n";
}
//Функция записи в файл информации о студенте
void   Information::Write(std::ofstream &f)
{
	f << "Имя - " << this->StudentName << "\n";
	f << "Средний балл - " << this->Avg << "\n";
	//Вызываем функцию записи списка экзаменов для студента
	//this->pass->WriteExamens(f);
	for (std::set<GradesForTheExam>::iterator it = pass.begin(); it != pass.end(); ++it)
	{
		GradesForTheExam a = *it;
		a.WriteExam(f);
	}
	f << "\n";
}
//Функция записи информации об экзамене
void GradesForTheExam::WriteExam(std::ofstream &f)
{
	Subjects S;
	S= (this->Sub)->data;
	f << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//Функция загрузки списка предметов из файла
template<>
int List<Subjects>::LoadSubjectsFromFile(const char *SubjectsIn)
{
	std::ifstream fin(SubjectsIn);
	//Количество предметов в списке
	int number = 0;
	while (fin)
	{
		//Срздаем переменную - элемент списка предметов
		Subjects subject;
		//Вызов функции чтения одного предмета из файла
		int flag = subject.ReadSubject(fin);
		if (!flag)
		{
			//Добавляем элемент в список
			AddElements(subject);
			//Прибавляем 1 к счетчику предметов
			number++;
		}
		else break;
	}
	return number; 
}
//Функция загрузки информации об одном предмете 
int  Subjects::ReadSubject(std::ifstream &f)
{
	try
	{
		//Читаем название
		f >> (NumberOfSubject);
		//Читаем номер
		f >> (NameOfSubject);
		//Проверяем на пустую строку
		if (strlen(NameOfSubject) == 0) return 1;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//Функция загрузки списка предметов в файл
template<>
void List<Subjects>::LoadSubjectsInFile(const char *SubjectsOut)
{
	std::ofstream f_out;
	//Открываем файл
	f_out.open(SubjectsOut, std::ios::app);
	f_out << "	Список предметов\n\nНачало:\n\n";
	//Создаем переменную - список предметов
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызываем функцию записи информации об одном предмете в файл
		q->data.WriteSubjects(f_out);
	}
	f_out << "\nКонец\n\n";
}
//Функция загрузки информации об одном предмете 
void   Subjects::WriteSubjects(std::ofstream &f)
{
	f << "Номер - " << this->NumberOfSubject << "\n";
	f << "Название - " << this->NameOfSubject << "\n";
	f << "\n";
}
//Функция вывода списка студентов на экран на экран
template<>
void List<Information>::LoadOnScreen()
{
	cout << "	Список студентов\n\nНачало:\n\n";
	//Создаем переменную - список студентов
	List<Information> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызываем функцию вывода информации об одном студенте
		q->data.WriteOnScreen();
	}
	cout << "\nКонец\n\n";
}
//Функция вывода информации об одном студенте
void   Information::WriteOnScreen()
{
	cout << "Имя - " << this->StudentName << "\n";
	cout << "Средний балл - " << this->Avg << "\n";
	for (std::set<GradesForTheExam>::iterator it = pass.begin(); it != pass.end(); ++it)
	{
		GradesForTheExam a = *it;
		a.WriteExamOnScreen();
	}
	cout << "\n";
}
//Функция вывода информации об одном экзамене
void GradesForTheExam::WriteExamOnScreen()
{
	Subjects S;

	S = (this->Sub)->data;
	cout << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//Функция вывода списка предметов на экран
template<>
void List<Subjects>::LoadOnScreenSubjects()
{
	cout << "	Список предметов\n\nНачало:\n\n";
	//Список предметов
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызов функции вывода информации об одном предмете на экран
		q->data.WriteSubjectsOnScreen();
	}
	cout << "\nКонец\n\n";
}
//Функция вывода информации об одном предмете на экран
void   Subjects::WriteSubjectsOnScreen()
{
	cout << "Название - " << this->NameOfSubject << " ";
	cout << "Номер - " << this->NumberOfSubject << "\n";
	cout << "\n";
}
//Функция добавления экзамена для студента
template<>
void List<Information>::AddEXAM(char *ch, int number, int mark, List<Subjects> *&R)
{
	//Список студентов
	List<Information> *q;
	//В цикле по списку ищем студента с нужной фамилией
	for (q = this->next; q != NULL; q = q->next)
	{
		//Информация о студенте
		Information a;
		a = q->data;
		if (ch==a.StudentName)
		{
			a.EXAdd(&a, number, mark, *&R);
			a.CountOfExam = a.CountOfExam + 1;
		}
		q->data = a;
	}
}
void Information::EXAdd(Information *a,int number, int mark, List<Subjects> *&R)
{
	GradesForTheExam b;
	//Записываем номер предмета
	b.set_subject(number);
	//Записываем оценку
	b.set_mark(mark);
	List<Subjects> *f = R;
	for (f = R->get_next(); f != NULL; f = f->get_next())
	{
		Subjects W = f->get_data();
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (number == W.NumberOfSubject)
		{
			b.set_Sub(f);
		}
	}
	a->pass.insert(b);
	a->set_Avg(AVG(a->pass));
}
template <class T>
void List<T>::Delete()
{
	string s_name;
	cout << "Введите имя студента: ";
	cin >> s_name;
	List<Information> *flag;
		List<Information> *p = this->next;
		while (p != NULL)
		{
			if (p->data.StudentName == s_name)
				break;
			p = p->next;
		}
		flag = p;
	if (flag == NULL)
	{
		cout << "Студент не найден.\n";
		return;
	}
	List<Information> *w, *u;
	for (w = this; (w->next != NULL) && (w->next != flag); w = w->next);
	if (w->next == NULL) return;
	u = w->next; w->next = u->next;
	u->next = NULL;
	u->data.pass.clear();
	delete u;
}
//Функция считывания n экзаменов и добавление их список оценок
set<GradesForTheExam> AddExamens(set<GradesForTheExam> w, char *ch, List<Subjects> *&R)
{
	cout << "Введите номер предмета";
	int number = 0;
	cin >> number;
	cout << "Введите оценку";
	int mark = 0;
	cin >> mark;
	GradesForTheExam b;
	b.set_mark(mark);
	b.set_subject(number);
	List<Subjects> *q = R;
	for (q = R->get_next(); q != NULL; q = q->get_next())
	{
		Subjects W = q->get_data();
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (number == W.NumberOfSubject)
		{
			b.set_Sub(q);
		}
	}
	w.insert(b);
	return w;
}
template<>
void List<Information>::AddStudent(List<Subjects> *&R)
{
	cout << "Введите фамилию студента";
	char ch[20];
	cin >> ch;
	cout << "Введите количество экзаменов";
	int count = 0;
	cin >> count;
		List<Information> *q;
		q = this->next;
		Information a;
		a = q->data;
		a.StudentName=ch;
		a.CountOfExam=count;
		set<GradesForTheExam> w;
		for (int u = 0;u < count;u++)
		{
			w=AddExamens(w, ch, R);
		}
		a.pass = w;
		a.Avg=(AVG(w));
			AddElements(*&a);
}
template<>
void List<Information>::Change(List<Subjects> *&R)
{
	cout << "Введите фамилию студента";
	string ch;
	cin >> ch;
	//Список студентов
	List<Information> *q;
	//В цикле по списку ищем студента с нужной фамилией
	for (q = this->next; q != NULL; q = q->next)
	{
		//Информация о студенте
		Information a;
		a = q->data;
		//Если нашли нужного студента
		if (ch == a.StudentName)
		{
			//Списк экзаменов для студента
			set<GradesForTheExam> w;
			w = a.pass;		
			//Вызываем функцию добавления информации о новом экзамене для студента
			{
				//w = ChangeExam(w);
				cout << "Введите номер предмета";
				int ch;
				cin >> ch;
				cout << "Введите новую оценку";
				int mark = 0;
				cin >> mark;
				std::set<GradesForTheExam>::iterator i=find(w.begin(),w.end(),ch);
				if (i == w.end()) { cout << "Предмета с таким номером у студента нет." << endl; }
				else {
					w.erase(i);
					GradesForTheExam b;
					b.set_mark(mark);
					b.set_subject(ch);
					List<Subjects> *q = R;
					for (q = R->get_next(); q != NULL; q = q->get_next())
					{
						Subjects W = q->get_data();
						//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
						if (ch == W.NumberOfSubject)
						{
							b.set_Sub(q);
						}
					}
					w.insert(b);
				}
			}
			a.pass = w;
			a.set_Avg(AVG(w));
			q->data = a;
		}

	}
}
#endif