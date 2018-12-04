//
//  main.cpp
//  Calculator
//
//  Created by Marcin Ozimek on 23/11/2018.
//  Copyright © 2018 Marcin Ozimek. All rights reserved.
//

#include <iostream>
#include <list>
#include <string>

using namespace std;

int calculate(const char * expression, double * result)
{
    list<int> list_number;
    list<int> list_out;
    
    string number = "";
    string numberout = "";

    double local_result = 0;
    double result_temp = 0;
    int helper=0;
    int sechelper = 0;
    
    for(int i = 0; expression[i] != '\0'; i++)
    {
//
        if (expression[i] == '(')
        {
            list_number.clear();
            for(int j = i; expression[j] != ')'; j++){
            if(expression[j] == ' ' || expression[j]== '\t' || expression[j] == '\n' || expression[j] == '(')
            {
                try {
                    list_number.push_back(stoi(number));
                } catch (std::invalid_argument e) {
                    
                }
                
                number = "";
                i=j;
                sechelper++;
                continue;
            }
            else if(expression[j] == '+' || expression[j] == '-' || expression[j] == '/' || expression[j] == '*')
            {
                if(expression[j] == '+'){
                    for(list<int>::iterator it=list_number.begin(); it != list_number.end(); ++it)
                    {
                        local_result += *it;
                    }
                    
                    result_temp += local_result;
                    local_result = 0;
                    list_number.clear();
                }
                else if(expression[j] == '-'){
                    for(list<int>::iterator it=list_number.begin(); it != list_number.end(); ++it)
                    {
                        if (sechelper<4){
                            local_result -= *it;
                            continue;
                        }
                        else if (helper==0){
                            local_result = *it;
                            helper++;
                        }
                        else
                        local_result -= *it;
                    }
                    
                    result_temp += local_result;
                    local_result = 0;
                    list_number.clear();
                }
                else if(expression[j]=='*'){
                    local_result=1;
                    for(list<int>::iterator it=list_number.begin(); it != list_number.end(); ++it)
                    {
                        local_result *= *it;
                    }
                    if (result_temp==0)
                    result_temp = 1;
                    result_temp *= local_result;
                    local_result = 0;
                    list_number.clear();
                }
                else if(expression[j]=='/'){
                    for(list<int>::iterator it=list_number.begin(); it != list_number.end(); ++it)
                    {
                        local_result = *it;
                    }
                    result_temp /= local_result;
                    local_result = 0;
                    list_number.clear();
                }
            }
            else{
                number += expression[j];
            }
            }
        }
//
        else if(expression[i] == ' ' || expression[i]== '\t' || expression[i] == '\n')
        {
            try {
                list_out.push_back(stoi(numberout));
            } catch (std::invalid_argument e) {
                
            }
            
            numberout = "";
            continue;
        }
        else if(expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*')
        {
            if(expression[i] == '+'){
                for(list<int>::iterator it=list_out.begin(); it != list_out.end(); ++it)
                {
                    local_result += *it;
                }
                if (result_temp != 0)
                {*result += result_temp;
                    result_temp = 0;
                }
                
            *result += local_result;
            local_result = 0;
            list_out.clear();
            }
            else if(expression[i] == '-'){
                for(list<int>::iterator it=list_out.begin(); it != list_out.end(); ++it)
                {
                    local_result -= *it;
                }
                if (result_temp != 0)
                {*result += result_temp;
                result_temp = 0;
                }
                
                *result += local_result;
                local_result = 0;
                list_out.clear();
            }
            else if(expression[i]=='*'){
                local_result=1;
                for(list<int>::iterator it=list_out.begin(); it != list_out.end(); ++it)
                {
                    local_result *= *it;
                }
                if (*result==0)
                *result = 1;
                
                if (result_temp != 0)
                {*result *= result_temp;
                    result_temp = 0;
                }
                
                *result *= local_result;
                local_result = 0;
                list_out.clear();
            }
            else if(expression[i]=='/'){
                for(list<int>::iterator it=list_out.begin(); it != list_out.end(); ++it)
                {
                    local_result = *it;
                }
                if (result_temp != 0)
                {*result += result_temp;
                    result_temp = 0;
                }
                *result /= local_result;
                local_result = 0;
                list_out.clear();
            }
        }
        else{
            numberout += expression[i];
        }
    }
    
    
    return 0;
}

int main() {
    
    int retval;
    double result;
    if (0 == (retval = calculate("2 5 7 9 +", &result)))
    {
        cout << "Result: " << result << endl;
    } else {
        cout << "Error: " << retval;
    }
    
    return retval;
}

