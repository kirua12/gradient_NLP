#include "Program.h"

void Program::FormulaInput(std::string *fomula, float *x1, float *x2, int *method)
{
	
	std::cout << "���� �Է��� �ֽʽÿ�!"<<std::endl << std::endl << std::endl;

	std::cout << "�� =    ";

	std::cin >> *fomula;
	std::cout << std::endl << std::endl;
	std::cout << "�ʱ� ���� �Է��� �ֽʽÿ�!" << std::endl << std::endl << std::endl;

	std::cout << "x1 =    ";
	std::cin >> *x1;
	std::cout << std::endl << std::endl;
	std::cout << "x2 =    ";
	std::cin >> *x2;

	std::cout << std::endl << std::endl;

	std::cout << "Exaustive search �̸� 1�� local search �� 2���Դϴ�";
	std::cin >> *method;



}
Program::Program()
{

}


void Program::Operate()
{

	std::string fomula;
	float x1, x2;
	int method;

	/////////debuging 
	fomula = "sin(x1)+0.1*x2^2+0.05*x1^2";
	x1 = -2;
	x2 = -3;
	
	///////
	//F_Input(&fomula, &x1, &x2,&method);
	c_f = Funtion(fomula);
	c_f.CalculateLocal(x1, x2);
	c_f.CalculateExhaustive(-5, -3, 1, 3);

}


