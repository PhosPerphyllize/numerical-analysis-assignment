/*  Create: 2021.11.10 18:47        
*   Update: 2021.11.10 23:47
        修改后的SolveTwoFun未进行相关测试
    Update: 2021/11/11 23:35
        已完成所有代码的测试，运行正常
*/
#ifndef __BASEFUN_H_
#define __BASEFUN_H_

#include"mycom.h"

const double g_compare_error = 1e-16;
const double g_step_comperr = 1e-6;

int Max3(int a, int b, int c);
int Min3(int a, int b, int c);
int Sgn(double input);
int SolveTwoFun(const double a, const double b, const double c, Com &root1, Com &root2);

int Max3(int a, int b, int c){
    if(a>b)
        return (a>c)?a:c;
    return (b>c)?b:c;
}
int Min3(int a, int b, int c){
    if(a<b)
        return (a<c)?a:c;
    return (b<c)?b:c;
}
int Sgn(double input){
    if(input>=0)
        return 1;
    return -1;
}
double Abs(double input){
    if(input>=0)
        return input;
    return -input;
}
int SolveTwoFun(const double a, const double b, const double c, Com &root1, Com &root2){
    if(Abs(a)<g_compare_error){
        cout << "SovleTwoFun error: a=0." << endl;
        exit(1);
    }
    double delta = b*b-4*a*c;
    if(delta<0){
        root1 = Com(-b/2/a, -sqrt(-delta)/2/a);
        root2 = Com(-b/2/a, +sqrt(-delta)/2/a);
        return 0;
    }
    root1 = (-b-sqrt(delta))/2/a;
    root2 = (-b+sqrt(delta))/2/a;
    return 0;
}

#endif 