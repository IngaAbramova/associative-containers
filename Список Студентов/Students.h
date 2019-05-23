#pragma once
#ifndef Students
#define Students
//���������� ����������� ����������
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iterator>
using namespace std;
//������
class Information;
class GradesForTheExam;
class Subjects;
template <class T>
//������ ������
class List
{
	friend class List<GradesForTheExam>;
	friend class GradesForTheExam;
	//��������� �� ��������� ������� ������
	List<T> *next;
	//�������������� ����
	T data;
	//�����������
	List(T &v) { data = v; next = NULL; }
public:
	List<T> *get_next() { return next; }
	void set_next(List<T> *next) { this->next = next; }
	T get_data() { return data; }
	void set_data(T data) { this->data = data; }
	//������ ������
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
	//�����������
	List()
	{
		next = NULL;
	};
	//����������
	~List()
	{
		if (next != NULL) delete next;
	};
	//������� ���������� ������� � ������
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

//������ �� �������� ��� ��������
class GradesForTheExam
{
	friend class List<GradesForTheExam>;
	//����� ��������
	int subject;
	//��������� �� ��������������� ������� ������ ���������
	List<Subjects> *Sub;
	//������
	int mark;
public:
	
	void set_subject(int s) { this->subject = s; };
	void set_mark(int m) { this->mark = m; };
	void set_Sub(List<Subjects> *S) { this->Sub = S; };
	int get_subject() const { return subject; }
	int get_mark() const { return mark; }
	bool operator<(const GradesForTheExam& A) const { return(subject < A.get_subject()); }
	//������ ������
	int  ReadExam(std::ifstream &f, List<Subjects> *&R);
	void WriteExam(std::ofstream &f);
	void WriteExamOnScreen();
	bool operator==(int n_code) const
	{
		return subject == n_code;
	}
	//�����������
    GradesForTheExam()
	{
		Sub = NULL;
		subject = 0;
		mark = 0;
	};
	//����������
	~GradesForTheExam()
	{
	};
};

//���������� � ��������: ������ � ������� ����
class Information
{
	friend class List<Information>;
	//��� ��������
	string StudentName;
	//���������� ������� ���������
	int  CountOfExam;
	//������� ����
	float Avg;
	//��������� �� ������ ��������� ��� ������� ��������
	set<GradesForTheExam> pass;
public:
	void EXAdd(Information *a, int number, int mark, List<Subjects> *&R);
	int get_count_of_exam() { return CountOfExam; }
	void set_count_of_exam(int c) { CountOfExam = c; }
	string get_name() { return StudentName; }
	void set_name(string c) { StudentName = c; }
	void set_Avg(float c) { Avg = c; }
	//������ ������
	void Write(std::ofstream &f);
	void WriteOnScreen();
	int  Read(Information *a, std::ifstream &f, List<Subjects> *&R);
	//�����������
	Information()
	{
		CountOfExam = 0;
		Avg = 0;
		StudentName = "NONAME";
	};
	//����������
	~Information()
	{

	};
};
//���������� � ��������: ����� � ��������
class Subjects 
{
public:
	//����� ��������
	int NumberOfSubject;
	//�������� ��������
	char NameOfSubject[20];
	//�����������
	Subjects()
	{
		NumberOfSubject = 0;
	};
	//����������
	~Subjects()
	{
	};
	//������ ������
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
//������� �������� ������ ��������� �� �����
template<>
int List<Information>::LoadFromFile(const char *StudentsIn, List<Subjects> *&R)
{
	std::ifstream f_in(StudentsIn);
	//�������� ������� ���������
	int n = 0;
	//���� ���� ����������
	while (f_in)
	{
		//������� �������������� ����������
		Information a;
		//�������� ������� ��� ������ ���������� �� ��������� �������� �� �����
		int flag = this->data.Read(&a, f_in, *&R);
		//��������� ���� �� �������� ����, ��� flag == 0
		if (!flag) 
		{
			//��������� ������� � ������
			this->AddElements(a); n++;
		}
		else break;
	}
	//��������� ����
	f_in.close();
	return n;
}

//������� ��� ����� ���������� �������� �� �����
int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&R)
{
	//���� ��� ���������� �� �����
	int flag = 1; 

	try
	{
		//������ ���
		f >> a->StudentName;
		//��������� �� ������ ������
		if ((a->StudentName.length() == 0)||(a->StudentName == "NONAME")) return 1;
		//������ ���������� ���������
		f >> (a->CountOfExam);
		//������� ���������� ��� ������ ���������� ��������� � ��������
		int n = a->CountOfExam;
		//��������� ���������� - ������ ��������� ��� ��������
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
//������� ���������� ������ ��������
int  GradesForTheExam::ReadExam(std::ifstream &f, List<Subjects> *&R)
{
	//��������� �� ����� f ����� ��������
	f >> (this->subject);
	//��������� �� ����� f ������
	f >> (this->mark);
	//������ ���������� � ���������� n
	int n = this->mark;
	List<Subjects> *q = R;
	for (q = R->next; q != NULL; q = q->next)
	{
		Subjects W = q->data;
		//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
		if (this->subject == W.NumberOfSubject)
		{
			this->Sub = q;
		}
	}
	//���������� ������
	return n;
}
//������� �������� ������ � ����
template<>
void List<Information>::LoadInFile(const char *StudentsOut)
{
	std::ofstream f_out;
	//�������� ����
	f_out.open(StudentsOut, std::ios::app);
	f_out << "	������ ���������\n\n������:\n\n";
	//������� ����������-������ ���������
	List<Information> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//�������� ������� ������ � ���� ���������� �� ����� ��������
		q->data.Write(f_out);
	}
	f_out << "\n�����\n\n";
}
//������� ������ � ���� ���������� � ��������
void   Information::Write(std::ofstream &f)
{
	f << "��� - " << this->StudentName << "\n";
	f << "������� ���� - " << this->Avg << "\n";
	//�������� ������� ������ ������ ��������� ��� ��������
	//this->pass->WriteExamens(f);
	for (std::set<GradesForTheExam>::iterator it = pass.begin(); it != pass.end(); ++it)
	{
		GradesForTheExam a = *it;
		a.WriteExam(f);
	}
	f << "\n";
}
//������� ������ ���������� �� ��������
void GradesForTheExam::WriteExam(std::ofstream &f)
{
	Subjects S;
	S= (this->Sub)->data;
	f << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//������� �������� ������ ��������� �� �����
template<>
int List<Subjects>::LoadSubjectsFromFile(const char *SubjectsIn)
{
	std::ifstream fin(SubjectsIn);
	//���������� ��������� � ������
	int number = 0;
	while (fin)
	{
		//������� ���������� - ������� ������ ���������
		Subjects subject;
		//����� ������� ������ ������ �������� �� �����
		int flag = subject.ReadSubject(fin);
		if (!flag)
		{
			//��������� ������� � ������
			AddElements(subject);
			//���������� 1 � �������� ���������
			number++;
		}
		else break;
	}
	return number; 
}
//������� �������� ���������� �� ����� �������� 
int  Subjects::ReadSubject(std::ifstream &f)
{
	try
	{
		//������ ��������
		f >> (NumberOfSubject);
		//������ �����
		f >> (NameOfSubject);
		//��������� �� ������ ������
		if (strlen(NameOfSubject) == 0) return 1;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//������� �������� ������ ��������� � ����
template<>
void List<Subjects>::LoadSubjectsInFile(const char *SubjectsOut)
{
	std::ofstream f_out;
	//��������� ����
	f_out.open(SubjectsOut, std::ios::app);
	f_out << "	������ ���������\n\n������:\n\n";
	//������� ���������� - ������ ���������
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//�������� ������� ������ ���������� �� ����� �������� � ����
		q->data.WriteSubjects(f_out);
	}
	f_out << "\n�����\n\n";
}
//������� �������� ���������� �� ����� �������� 
void   Subjects::WriteSubjects(std::ofstream &f)
{
	f << "����� - " << this->NumberOfSubject << "\n";
	f << "�������� - " << this->NameOfSubject << "\n";
	f << "\n";
}
//������� ������ ������ ��������� �� ����� �� �����
template<>
void List<Information>::LoadOnScreen()
{
	cout << "	������ ���������\n\n������:\n\n";
	//������� ���������� - ������ ���������
	List<Information> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//�������� ������� ������ ���������� �� ����� ��������
		q->data.WriteOnScreen();
	}
	cout << "\n�����\n\n";
}
//������� ������ ���������� �� ����� ��������
void   Information::WriteOnScreen()
{
	cout << "��� - " << this->StudentName << "\n";
	cout << "������� ���� - " << this->Avg << "\n";
	for (std::set<GradesForTheExam>::iterator it = pass.begin(); it != pass.end(); ++it)
	{
		GradesForTheExam a = *it;
		a.WriteExamOnScreen();
	}
	cout << "\n";
}
//������� ������ ���������� �� ����� ��������
void GradesForTheExam::WriteExamOnScreen()
{
	Subjects S;

	S = (this->Sub)->data;
	cout << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//������� ������ ������ ��������� �� �����
template<>
void List<Subjects>::LoadOnScreenSubjects()
{
	cout << "	������ ���������\n\n������:\n\n";
	//������ ���������
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//����� ������� ������ ���������� �� ����� �������� �� �����
		q->data.WriteSubjectsOnScreen();
	}
	cout << "\n�����\n\n";
}
//������� ������ ���������� �� ����� �������� �� �����
void   Subjects::WriteSubjectsOnScreen()
{
	cout << "�������� - " << this->NameOfSubject << " ";
	cout << "����� - " << this->NumberOfSubject << "\n";
	cout << "\n";
}
//������� ���������� �������� ��� ��������
template<>
void List<Information>::AddEXAM(char *ch, int number, int mark, List<Subjects> *&R)
{
	//������ ���������
	List<Information> *q;
	//� ����� �� ������ ���� �������� � ������ ��������
	for (q = this->next; q != NULL; q = q->next)
	{
		//���������� � ��������
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
	//���������� ����� ��������
	b.set_subject(number);
	//���������� ������
	b.set_mark(mark);
	List<Subjects> *f = R;
	for (f = R->get_next(); f != NULL; f = f->get_next())
	{
		Subjects W = f->get_data();
		//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
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
	cout << "������� ��� ��������: ";
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
		cout << "������� �� ������.\n";
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
//������� ���������� n ��������� � ���������� �� ������ ������
set<GradesForTheExam> AddExamens(set<GradesForTheExam> w, char *ch, List<Subjects> *&R)
{
	cout << "������� ����� ��������";
	int number = 0;
	cin >> number;
	cout << "������� ������";
	int mark = 0;
	cin >> mark;
	GradesForTheExam b;
	b.set_mark(mark);
	b.set_subject(number);
	List<Subjects> *q = R;
	for (q = R->get_next(); q != NULL; q = q->get_next())
	{
		Subjects W = q->get_data();
		//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
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
	cout << "������� ������� ��������";
	char ch[20];
	cin >> ch;
	cout << "������� ���������� ���������";
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
	cout << "������� ������� ��������";
	string ch;
	cin >> ch;
	//������ ���������
	List<Information> *q;
	//� ����� �� ������ ���� �������� � ������ ��������
	for (q = this->next; q != NULL; q = q->next)
	{
		//���������� � ��������
		Information a;
		a = q->data;
		//���� ����� ������� ��������
		if (ch == a.StudentName)
		{
			//����� ��������� ��� ��������
			set<GradesForTheExam> w;
			w = a.pass;		
			//�������� ������� ���������� ���������� � ����� �������� ��� ��������
			{
				//w = ChangeExam(w);
				cout << "������� ����� ��������";
				int ch;
				cin >> ch;
				cout << "������� ����� ������";
				int mark = 0;
				cin >> mark;
				std::set<GradesForTheExam>::iterator i=find(w.begin(),w.end(),ch);
				if (i == w.end()) { cout << "�������� � ����� ������� � �������� ���." << endl; }
				else {
					w.erase(i);
					GradesForTheExam b;
					b.set_mark(mark);
					b.set_subject(ch);
					List<Subjects> *q = R;
					for (q = R->get_next(); q != NULL; q = q->get_next())
					{
						Subjects W = q->get_data();
						//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
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