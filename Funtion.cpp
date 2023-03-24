#include "Funtion.h"

Funtion::Funtion(std::string fomula)
{
    std::string seperate = "+,-,*,/";


    int cur_position = 0;
    int position;

    while ((position = fomula.find_first_of(seperate, cur_position)) != std::string::npos) {
        c_formulas.push_back(fomula.substr(cur_position, position - cur_position));
        c_formulas.push_back(fomula.substr(position, 1));
        cur_position = position + 1;
    }
    c_formulas.push_back(fomula.substr(cur_position));
   
    c_differ_formula.push_back(Differential(c_formulas,1));
    c_differ_formula.push_back(Differential(c_formulas, 2));
    c_two_differ_formula.push_back(Differential(c_differ_formula.at(0), 1));
    c_two_differ_formula.push_back(Differential(c_differ_formula.at(0), 2));
    c_two_differ_formula.push_back(Differential(c_differ_formula.at(1), 1));
    c_two_differ_formula.push_back(Differential(c_differ_formula.at(1), 2));
}

Funtion::Funtion()
{
}

// 식을 계산함 -> 맨처음 식을 여기서 설정
float Funtion::CalculateObj(float x1, float x2)
{
    float result;
    std::vector<std::string> objformula = c_formulas;
    result = FormulaCaculate(objformula,x1,x2);
	return result;
}



void Funtion::CalculateLocal(float x1, float x2)
{

    float min = CalculateObj(x1, x2);
    float min_x1 = x1;
    float min_x2 = x2;
    int one_more = 0;

    while (1) {
        Gradient(&x1, &x2);
        float p_min = CalculateObj(x1, x2); //최솟값이 될 확률
        if (p_min < min) {
            min = p_min;
            min_x1 = x1;
            min_x2 = x2;

            one_more = 0;
        }
        else {
            if(one_more ==0)
                one_more = 1;
            else {
                break;
            }
        }

    }

    local_optima_x1 = min_x1;
    local_optima_x2 = min_x2;






}

void Funtion::CalculateExhaustive(float x1, float x2, float max_x1, float max_x2)
{   
    float min = CalculateObj(x1, x2);
    float min_x1 = x1;
    float min_x2 = x2;




    for (float i = x1+0.004;i < max_x1; i += 0.004) {
        for (float j = x2 + 0.004;j < max_x2; j += 0.004) {
            float p_min = CalculateObj(i, j); //최솟값이 될 확률
            if (p_min < min) {
                min = p_min;
                min_x1 = i;
                min_x2 = j;
            }

        }
    }

    local_optima_x1 = min_x1;
    local_optima_x2 = min_x2;

}

float Funtion::FormulaCaculate(std::vector<std::string> input, float x1, float x2)
{

    std::string seperator = "sin, cos, ^, tan,x";
    if (input.size() == 0) {
        input.push_back("0");
    }

    for (int i = 0;i < input.size(); i++) {
        int position;
        position = input.at(i).find_first_of(seperator, 0);
        int pow_check = -1;
        if (position >= 0) {
            pow_check = input.at(i).find("^", 1);
        }
        // 내가 찾는 변수가 없을때
        if (position < 0) {
            continue;
        }

        //삼각 함수일 때 계산 하는 방법 
        else if (input.at(i).substr(position, 1) == "s") {

            // 변수가 무엇인지
            int x1_check = input.at(i).find("x1", 0);
            int x2_check = input.at(i).find("x2", 0);

            if (x1_check > 0) {

                if (position - 1 >= 0 && input.at(i).substr(position - 1, 1) == "-")
                    input.at(i) = std::to_string(-std::sinf(x1));
                else
                    input.at(i) = std::to_string(std::sinf(x1));

            }
            else if (x2_check > 0) {
                if (position - 1 >= 0 && input.at(i).substr(position - 1, 1) == "-")
                    input.at(i) = std::to_string(-std::sinf(x2));
                else
                    input.at(i) = std::to_string(std::sinf(x2));
            }
        }
        else if (input.at(i).substr(position, 1) == "c") {

            // 변수가 무엇인지
            int x1_check = input.at(i).find("x1", 0);
            int x2_check = input.at(i).find("x2", 0);

            if (x1_check > 0) {

                if (position - 1 >= 0 && input.at(i).substr(position - 1, 1) == "-")
                    input.at(i) = std::to_string(-std::cosf(x1));
                else
                    input.at(i) = std::to_string(std::cosf(x1));

            }
            else if (x2_check > 0) {
                if (position - 1 >= 0 && input.at(i).substr(position - 1, 1) == "-")
                    input.at(i) = std::to_string(-std::cosf(x2));
                else
                    input.at(i) = std::to_string(std::cosf(x2));
            }
        }
        else if (input.at(i).substr(position, 1) == "t") {

            // 변수가 무엇인지
            int x1_check = input.at(i).find("x1", 0);
            int x2_check = input.at(i).find("x2", 0);

            if (x1_check > 0) {

                if (position - 1 >= 0 && input.at(i).substr(position - 1, 1) == "-")
                    input.at(i) = std::to_string(-std::tanf(x1));
                else
                    input.at(i) = std::to_string(std::tanf(x1));

            }
            else if (x2_check > 0) {
                if (position - 1 >= 0 && input.at(i).substr(position - 1, 1) == "-")
                    input.at(i) = std::to_string(-std::tanf(x2));
                else
                    input.at(i) = std::to_string(std::tanf(x2));
            }
        }

        //제곱 연산자일때ㅐ 계산하는 방법
        
        else if (pow_check >= 0) {

            // 변수가 무엇인지
            int x1_check = input.at(i).find("x1", 0);
            int x2_check = input.at(i).find("x2", 0);

            if (x1_check >= 0) {

                input.at(i) = std::to_string(std::powf(x1, std::stoi(input.at(i).substr(pow_check + 1, 1))));
            }
            else if (x2_check >= 0)
                input.at(i) = std::to_string(std::powf(x2, std::stoi(input.at(i).substr(pow_check + 1, 1))));
        }

        int x1_check = input.at(i).find("x1", 0);
        int x2_check = input.at(i).find("x2", 0);
        if (x1_check >= 0 && pow_check <0) {

            input.at(i) = std::to_string(x1);
        }
        else if (x2_check >= 0 && pow_check < 0)
            input.at(i) = std::to_string(x2);



    }



    //// 곱하기 연산



    for (int i = 0;i < input.size(); i++) {

        if (input.at(i) == "*") {
            float temp = std::stof(input.at(i - 1)) * std::stof(input.at(i + 1));
            input.at(i + 1) = std::to_string(temp);
            input.erase(input.begin() + i - 1);
            input.erase(input.begin() + i - 1);
            i = i - 2;
        }
        else if (input.at(i) == "/") {
            float temp = std::stof(input.at(i - 1)) / std::stof(input.at(i + 1));
            input.at(i + 1) = std::to_string(temp);
            input.erase(input.begin() + i - 1);
            input.erase(input.begin() + i - 1);
            i = i - 2;
        }
    }


    // 더하기 혹은 빼기


    for (int i = 0;i < input.size(); i++) {

        if (input.at(i) == "+") {
            float temp = std::stof(input.at(i - 1)) + std::stof(input.at(i + 1));
            input.at(i + 1) = std::to_string(temp);
            input.erase(input.begin() + i - 1);
            input.erase(input.begin() + i - 1);
            i = i - 2;
        }
        else if (input.at(i) == "-") {
            float temp = std::stof(input.at(i - 1)) - std::stof(input.at(i + 1));
            input.at(i + 1) = std::to_string(temp);
            input.erase(input.begin() + i - 1);
            input.erase(input.begin() + i - 1);
            i = i - 2;
        }
    }

    return std::stof(input.at(0));
}

std::vector<std::string> Funtion::Differential(std::vector<std::string> formula, int value)
{
    std::string seper_plus_minus = "+.-";
    std::string seper_triple = "s, c, t";
    std::string differ_value = "x" + std::to_string(value);

    for (int i = 0; i < formula.size();i++) {
        int position;
        position = formula.at(i).find(differ_value, 0);
        int order_check = formula.at(i).find("^", 0);
        int triple_check = formula.at(i).find_first_of(seper_triple, 0);
        // 내가 찾는 변수가 없을때
        if (position < 0) {
            if(formula.at(i)=="+" || formula.at(i) == "-")
                continue;
            else {
                int check_next = CheckNext(formula, i, differ_value);
                if (check_next == -1) {
                    continue;

                }
                else {

                    if (check_next == formula.size() - 1&& i-1>=0) {

                        if ((formula.at(i - 1) == "+" || formula.at(i - 1) == "-")) {
                            formula.erase(formula.begin() + i - 1);
                            i = i - 1;
                            check_next -= 1;
                        }
                    }

                    for (int j = i;j < check_next+1;) {

                        formula.erase(formula.begin()+j);
                        check_next -= 1;
                        
                    }
                    i = i - 1;

                }
            }
        }
        // 찻수 미분
        else if (order_check >= 0 && position >= 0 && formula.at(i).substr(position+1,1) == std::to_string(value)) {
            int order = std::stoi(formula.at(i).substr(order_check+1, formula.at(i).size()- order_check - 1));
            if (order - 1 == 1) {
                formula.at(i) = differ_value;
            }
            else {
                formula.at(i) = differ_value + "^" + std::to_string(order);
            }
            formula.insert(formula.begin() + i, std::to_string(order));
            formula.insert(formula.begin() + i+1, "*");
            
            i = i + 2;
            
        }
        // 삼각함수 미분
        else if (position >= 0 && triple_check >= 0) {
            std::string differ_triple;
            if (formula.at(i).substr(triple_check, 3) == "sin") {
                differ_triple = "cos(" + differ_value + ")";
                if (triple_check - 1 >= 0) {
                    if (formula.at(i).substr(triple_check - 1, 1) == "-") {
                        differ_triple = "-" + differ_triple;
                    }
                }
                formula.at(i) = differ_triple;
            }

            else if(formula.at(i).substr(triple_check, 3) == "cos") {
                if (triple_check - 1 >= 0) {
                    if (formula.at(i).substr(triple_check - 1, 1) == "-") {
                        differ_triple = "sin(" + differ_value + ")";
                    }
                }
                else
                    differ_triple = "-sin(" + differ_value + ")";
                

                formula.at(i) = differ_triple;
            }

        }
        else if (position >= 0 && formula.at(i).substr(position, 2) == differ_value) {
            formula.erase(formula.begin() + i - 1);
            formula.erase(formula.begin() + i - 1);
            i = i - 2;

        }
     

    }


    return formula;
}

int Funtion::CheckNext(std::vector<std::string> formula, int i, std::string differ_value)
{
    int check_value = formula.at(i).find_first_of(differ_value);
    if (formula.at(i) == "*" || formula.at(i) == "/") {
        if (i + 1 > formula.size())
            return i;
        else
            return CheckNext(formula, i + 1, differ_value);
        
    }
    
    else if (formula.at(i) == "+"|| formula.at(i) == "-")
        return i;
    else if (check_value >=0) {
        if(formula.at(i).substr(check_value, 2) == differ_value)
            return -1;
        else {
            if (i + 1 > formula.size()-1)
                return i;
            else
                return CheckNext(formula, i + 1, differ_value);
        }
    }
    else {
        if (i + 1 > formula.size())
            return i;
        else
            return CheckNext(formula, i + 1, differ_value);
    }

}

void Funtion::Gradient(float* x1, float* x2)
{
    float d_x1 = FormulaCaculate(c_differ_formula.at(0), *x1, *x2);
    float d_x2 = FormulaCaculate(c_differ_formula.at(1), *x1, *x2);
    float d_x1_x1 = FormulaCaculate(c_two_differ_formula.at(0), *x1, *x2);
    float d_x1_x2 = FormulaCaculate(c_two_differ_formula.at(1), *x1, *x2);
    float d_x2_x1 = FormulaCaculate(c_two_differ_formula.at(2), *x1, *x2);
    float d_x2_x2 = FormulaCaculate(c_two_differ_formula.at(3), *x1, *x2);

    float inv_denominator = 1 / (d_x1_x1 * d_x2_x2 - d_x1_x2 * d_x2_x1);

    float inv_d_x1_x1 = inv_denominator * d_x2_x2;
    float inv_d_x1_x2 = inv_denominator * -d_x1_x2;
    float inv_d_x2_x1 = inv_denominator * -d_x2_x1;
    if (d_x1_x2 == 0) {
        inv_d_x1_x2 = 0;
    }

    if (d_x2_x1 == 0) {
        inv_d_x2_x1 = 0;
    }

    float inv_d_x2_x2 = inv_denominator * d_x1_x1;

    float later_x1 = inv_d_x1_x1 * d_x1 + inv_d_x1_x2 * d_x2;
    float later_x2 = inv_d_x2_x1 * d_x1 + inv_d_x2_x2 * d_x2;

    *x1 = *x1 - later_x1;
    *x2 = *x2 - later_x2;

}




