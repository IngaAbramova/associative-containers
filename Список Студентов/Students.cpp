//���������� ���������� � ������������ ����
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
	//���������� ������� ���������
	setlocale(LC_ALL, "Russian");
	//������� ������������
	int comand=-1;
	cout << "1. ��������� ������ ��������� �� �����" << endl;
	cout << "2. ��������� ������ ��������� � ����" << endl;
	cout << "3. ������� ������ ��������� �� �����" << endl;
	cout << "4. ��������� ������ ��������� �� �����" << endl;
	cout << "5. ��������� ������ ��������� � ����" << endl;
	cout << "6. ������� ������ ��������� �� �����" << endl;
	cout << "7. �������� �������" << endl;
	cout << "8. ������� ��������" << endl;
	cout << "9. �������� ��������" << endl;
	cout << "10. �������� ������" << endl;
	cout << "0. �����" << endl;
	//������������� ������ �������
	cin >> comand;
	//map < int, int > Mark;
	//�������������� ������
	List<Information> *P = new List<Information>();
	List<Subjects> *K = new List<Subjects>();
	K->LoadSubjectsFromFile("SubjectsIn.txt");
	while (comand != 0)
{
		//�������� ������ ��������� �� �����
		if (comand == 1)
		{
            P->LoadFromFile("StudentsIn.txt", *&K);
			cout << "C����� ��������� �������� �� �����" << endl;
		}
		//�������� ������ ��������� � ����
		if (comand == 2)
		{
			P->LoadInFile("StudentsOut.txt");
			cout << "C����� ��������� �������� � ����" << endl;
		}
		//����� ������ ��������� �� �����
		if (comand == 3)
		{
			P->LoadOnScreen();
		}
		//�������� ������ ��������� �� �����
		if (comand == 4)
		{
			//K->LoadSubjectsFromFile("SubjectsIn.txt");
			cout << "C����� ��������� �������� �� �����" << endl;
		}
		//�������� ������ ��������� � ����
		if (comand == 5)
		{
			K->LoadSubjectsInFile("SubjectsOut.txt");
			cout << "C����� ��������� �������� � ����" << endl;
		}
		//����� ������ ��������� �� �����
		if (comand == 6)
		{
			K->LoadOnScreenSubjects();
		}
		//���������� ���������� �� �������� ��� ��������
		if (comand == 7)
		{
			cout << "������� ������� ��������";
			char ch[20];
			cin>>ch;
			cout << "������� ����� ��������";
			int number=0;
			cin >> number;
			cout << "������� ������";
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
		cout << "1. ��������� ������ ��������� �� �����" << endl;
		cout << "2. ��������� ������ ��������� � ����" << endl;
		cout << "3. ������� ������ ��������� �� �����" << endl;
		cout << "4. ��������� ������ ��������� �� �����" << endl;
		cout << "5. ��������� ������ ��������� � ����" << endl;
		cout << "6. ������� ������ ��������� �� �����" << endl;
		cout << "7. �������� �������" << endl;
		cout << "8. ������� ��������" << endl;
		cout << "9. �������� ��������" << endl;
		cout << "10. �������� ������" << endl;
		cout << "0. �����" << endl;
		cin >> comand;
}
	system("pause");
}








