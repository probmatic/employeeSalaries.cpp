/*probmatic*/
/*Program: Employee Salaries*/

#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "Employee.h"

using namespace std;

vector<employee> emps; //global vector 

void loadData(string filename); // load data into a global vector of employees.
void print(vector<employee> empIn); //print all the information from vector empIn 
void GeneralReport(string filename, vector<employee> empOut); //create a report file from vector empOut
void AboveAverage(vector<employee> empIn, vector<employee> &empOut);//find out the employee whose salary is higher than average
void RemoveHighestSalary(vector<employee> &empIn);//remove the employee with higest salary from vector empIn

int main()
{
	string filename; //string for filename

	cout << "Please input the name of datafile:";
	cin >> filename;
	loadData(filename); //load data into global vector
	cout << "The number of emplyee record is: " << emps.size() << endl << endl;
	print(emps); // call print function to print out every record from record emps
	cout << endl;

	vector<employee> empOut; //vector for output file
	AboveAverage(emps, empOut); // find out the employee above average salary and copy these records in vector empOut
	cout << "Input the report name for above average:";
	cin >> filename;
	GeneralReport(filename, empOut); // create a report for above average employees
	cout << "Input the report name after removing highest:";
	cin >> filename;
	RemoveHighestSalary(emps); // remove the employee record with higest salary
	GeneralReport(filename, emps); //create a report 

	system("pause");
	return 0;
}



void loadData(string filename)
{
	ifstream input;
	input.open(filename);

	employee e; //I still don't understand why we need to do this- creates a subclass? idk..


				//cout << setw(20) << right << "Name" << setw(20) << right << "ID" << setw(20) << right << "Salary" << endl; //for debugging to see how things print out

	while (!input.eof())
	{
		getline(input, e.name); //gets string name
		input >> e.id; //id is an int
		input >> e.salary; //salary is a double
		input.ignore(); //Use this when using getline and cin together
						//cout << setw(20) << e.name << setw(20) << e.id << setw(20) << fixed << setprecision(1) << e.salary << setw(20) << endl; //for debugging to make sure file is being read correctly and printed out
		emps.push_back(e); //THIS IS HOW YOU COUNT HOW MANY THERE ARE!! AHH I FINALLY UNDERSTAND YAY
	}
}

void print(vector<employee> empIn)
{
	employee e;
	int s = (empIn.size());
	cout << setw(20) << right << "Name" << setw(20) << right << "ID" << setw(20) << right << "Salary" << endl;
	for (int i = 0; i < s; i++)
	{
		e = empIn.at(i);
		cout << setw(20) << e.name << setw(20) << e.id << setw(20) << fixed << setprecision(1) << e.salary << setw(20) << endl;
	}
}

void GeneralReport(string filename, vector<employee> empOut)
{
	ofstream output;
	output.open(filename);
	employee e;
	int s = empOut.size();

	output << setw(20) << right << "Name" << setw(20) << right << "ID" << setw(20) << right << "Salary" << endl;
	for (int i = 0; i < s; i++)
	{
		e = empOut.at(i);
		output << setw(20) << e.name << setw(20) << e.id << setw(20) << fixed << setprecision(1) << e.salary << setw(20) << endl;
	}

}

void AboveAverage(vector<employee> empIn, vector<employee> &empOut)
{
	employee e;
	int s = emps.size();
	double sum = 0.0;
	double average = 0.0;

	for (int i = 0; i < s; i++)
	{
		e = emps.at(i);
		sum = sum + e.salary;
	}

	average = sum / s;

	for (int j = 0; j < s; j++)
	{
		e = emps.at(j);
		if (e.salary >= average)
		{
			empOut.push_back(e);
		}
	}
	int ns = empOut.size();
	cout << "There are " << ns << " people get salary higher than average <" << average << ">" << endl; //not sure why this aligns center...
}

void RemoveHighestSalary(vector<employee> &empIn)
{
	employee e;
	int s = empIn.size();
	int ihighest = 0;
	double dhighest = 0.0;

	for (int i = 0; i < s; i++)
	{
		e = emps.at(i);
		if (e.salary > dhighest)
		{
			dhighest = e.salary;
			ihighest = i;
		}
	}
	emps.erase(emps.begin() + ihighest);  //vector::erase - Deletes elements from a vector (single & range), shifts later elements down
										  //vector::begin - Returns an iterator to start traversal of the vector.
}
