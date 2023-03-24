#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
class Funtion
{
	std::vector<std::string> c_formulas;
	std ::vector<std::vector<std::string>> c_differ_formula;
	std::vector<std::vector<std::string>> c_two_differ_formula;
	float local_optima_x1;
	float local_optima_x2;


public:
	Funtion(std::string fomula);
	Funtion();
	float CalculateObj(float x1, float x2);
	void CalculateLocal(float x1, float x2);
	void CalculateExhaustive(float x1, float x2, float max_x1, float max_x2);
	float FormulaCaculate(std::vector<std::string> input, float x1, float x2);
	std::vector<std::string> Differential(std::vector<std::string> formula , int value);
	int CheckNext(std::vector<std::string>, int i,std::string);
	void Gradient(float *x1, float *x2);
};

