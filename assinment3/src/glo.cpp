#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>

#include"../include/mat.h"
#include"../include/vec.h"
#include"../include/glo.h"
using std::cin;  using std::cout;  using std::endl;  using std::flush;  using std::string;

extern const double e_compare_error = 10e-12;
extern const double e_step_comperr = 10e-8;

const int g_matf_num = 4;

double Abs(const double value){
    if(value>=0)
        return value;
    return -value;
}
int Dou2Int(const double value){
    int output = (int)value;  // (int)向下取整 
    if( Abs(value-output)<Abs(value-(output+1)) )
        return output;
    else
        return output+1;
}

Mat ReturnFdiff(Vec& vecx){
    Mat temp("temp(ReturnFdiff)", g_matf_num, g_matf_num);
    double arr_temp[g_matf_num][g_matf_num] = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {0.5, 1, 0, 1},
        {1, 0.5, 1, 0}};
    for(int i=0; i<temp.rnum; i++){
        for(int j=0; j<temp.cnum; j++){
            temp(i+1,j+1) = arr_temp[i][j];
        }
    }
    temp(1,1) = -0.5*sin(vecx(1));
    temp(2,2) = 0.5*cos(vecx(2));
    temp(3,3) = -sin(vecx(3));
    temp(4,4) = cos(vecx(4));
    return temp;  // temp内有指针，注意深拷贝
}
double g_c1=0, g_c2=0, g_c3=0, g_c4=0;
Vec ReturnF(Vec& vecx){
    Vec temp("temp(ReturnF)",g_matf_num);
    temp(1) = 0.5*cos(vecx(1)) + vecx(2) + vecx(3) + vecx(4) + g_c1;
    temp(2) = vecx(1) + 0.5*sin(vecx(2)) + vecx(3) + vecx(4) + g_c2;
    temp(3) = 0.5*vecx(1) + vecx(2) + cos(vecx(3)) + vecx(4) + g_c3;
    temp(4) = vecx(1) + 0.5*vecx(2) + vecx(3) + sin(vecx(4)) + g_c4;

    return temp;  // temp内有指针，注意深拷贝
}
Vec SolveXY(double num_x, double num_y){
// 对于给定的方程组，输入一个x,y 返回t,u
    Vec x("x(SolveXY)",g_matf_num), deta_x("deta_x(SolveXY)",g_matf_num), b("b(SolveXY)",g_matf_num); //v, w, x, y
    Mat f_diff("f_diff", g_matf_num, g_matf_num);
    double fun1, fun2, fun3, fun4, error_sum;
    
    g_c1 = -num_x -2.67;
    g_c2 = -num_y - 1.07;
    g_c3 = -num_x - 3.74;
    g_c4 = -num_y - 0.79;

    x.init(1);  //t, u, v, w
    int step=0;
    while(1){
        if(step>=100){
            cout << "SolveXY() warning: max step has reached" << endl;
            break;
        }
        f_diff = ReturnFdiff(x);
        b = ReturnF(x)*-1.0;
        deta_x = b/f_diff;
        if(deta_x.norm2()<=e_compare_error){
            fun1 = 0.5*cos(x(1))+x(2)+x(3)+x(4)-num_x;  fun2=x(1)+0.5*sin(x(2))+x(3)+x(4)-num_y;
            fun3 = 0.5*x(1)+x(2)+cos(x(3))+x(4)-num_x;  fun4=x(1)+0.5*x(2)+x(3)+sin(x(4))-num_y;
            error_sum = Abs(fun1-2.67) + Abs(fun2-1.07) + Abs(fun3-3.74) + Abs(fun4-0.79);
            if(error_sum>e_step_comperr*10e2)
                cout << "SolveXY() warning: solve might be wrong with error_sum = " << error_sum << endl;
            break;
        }
        x = x + deta_x;
        step++;
    }
    return x;
}
double Lagra2d(Vec& vec_x, Vec& vec_y, Mat& mat_a, const double num_x, const double num_y){
// 输入数表，进行拉格朗日拟合，数表 x节点数=mat_a行数  y=列数
    if(vec_x.num!=mat_a.rnum||vec_y.num!=mat_a.cnum){
        cout << "Lagra2d() error: input mat,vec not match." << endl;
        exit(1);
    }
    if(vec_x.num<=1||vec_y.num<=1){
        cout << "Lagra2d() error: input mat_a rnum<=1 or cnum <=1." << endl;
        exit(1);
    }
    if(num_x<vec_x(1)||num_x>vec_x(vec_x.num))
        cout << "Lagra2d() warning: num_x out of rank." << endl;
    if(num_y<vec_y(1)||num_y>vec_y(vec_y.num))
        cout << "Lagra2d() warning: num_y out of rank." << endl;
    
    double lk_x=1, lk_y=1, reslu=0;
    for(int k=1; k<=vec_x.num; k++){
        for(int r=1; r<=vec_y.num; r++){
            lk_x=1;
            for(int t=1; t<=vec_x.num; t++){
                if(t==k)
                    continue;
                lk_x *= (num_x - vec_x(t))/(vec_x(k) - vec_x(t));
            }
            lk_y=1;
            for(int t=1; t<=vec_y.num; t++){
                if(t==r)
                    continue;
                lk_y *= (num_y - vec_y(t))/(vec_y(r) - vec_y(t));
            }
            reslu += lk_x * lk_y * mat_a(k,r);
        }
    }
    return reslu;
}

Vec OneDimRegres(Vec &vec_x, const Vec &vec_y, const int x_pow_num){
    if(vec_x.num!=vec_y.num){
        cout << "OneDimRegres() error: input Vec not match." << endl;
        exit(1);
    }
    if(x_pow_num<=0||x_pow_num>vec_y.num){
        cout << "OneDimRegres() error: x_pow_num<=0 or >point num." << endl;
        exit(1);
    }
    Mat mat_a("mat_a(OneDimRegres)", vec_x.num, x_pow_num+1);
    Vec temp("temp(OneDimRegres)",vec_x.num);
    for(int t=0; t<=x_pow_num; t++){
        temp = vec_x.power(t);
        mat_a = mat_a.replaceCol(temp,t+1);
    }
    temp = (mat_a.tranPosition() * vec_y)/(mat_a.tranPosition()*mat_a);
    return temp;  // temp内有指针，注意深拷贝
}
Mat TwoDimRegres(Vec &vec_x, Vec &vec_y, Mat &mat_u, const int x_pow_num, const int y_pow_num){
// vec_x为x轴结点，与mat_z的行数相等 vec_y与列数相等
    if(vec_x.num!=mat_u.rnum||vec_y.num!=mat_u.cnum){
        cout << "TwoDimRegres() error: input vec, mat not match." << endl;
        exit(1);
    }
    if(x_pow_num<=0||x_pow_num>vec_x.num){
        cout << "TwoDimRegres() error: x_pow_num<=0 or >point num." << endl;
        exit(1);
    }
    if(y_pow_num<=0||y_pow_num>vec_y.num){
        cout << "TwoDimRegres() error: y_pow_num<=0 or >point num." << endl;
        exit(1);
    }
    Mat mat_a("mat_a(TwoDimRegres)", x_pow_num+1, vec_y.num);
    Vec temp_x("temp_x(TwoDimRegres)",vec_x.num);
    Vec temp_xnum("temp_xnum(TwoDimRegres)",x_pow_num+1);
    for(int i=1; i<=vec_y.num; i++){
        temp_xnum = OneDimRegres(vec_x, mat_u.takeCol(i), x_pow_num);
        mat_a = mat_a.replaceCol(temp_xnum, i);
    }
    Mat mat_g("mat_d(TwoDimRegres)", vec_y.num, y_pow_num+1);
    Mat mat_d("mat_d(TwoDimRegres)", y_pow_num+1, vec_y.num);
    Vec temp_y("temp_y(TwoDimRegres)",vec_y.num);
    Vec temp_ynum("temp_ynum(TwoDimRegres)",y_pow_num+1);
    for(int i=0; i<=y_pow_num; i++){
        temp_y = vec_y.power(i);
        mat_g = mat_g.replaceCol(temp_y,i+1);
    }
    for(int i=1; i<=vec_y.num; i++){
        temp_ynum = mat_g.tranPosition().takeCol(i) / (mat_g.tranPosition() * mat_g);
        mat_d = mat_d.replaceCol(temp_ynum, i);
    }
    Mat mat_c("mat_c(TwoDimRegres)", x_pow_num+1, y_pow_num+1);
    mat_c = mat_a * mat_d.tranPosition();
    double error_sum=0;
   
    return mat_c;
}
double Fun2dRegres(Mat& mat_c, const double x, const double y){
    double sum=0;
    for(int i=1; i<=mat_c.rnum; i++){
        for(int j=1; j<=mat_c.cnum; j++){
            sum += mat_c(i,j)*pow(x,i-1)*pow(y,j-1);
        }
    }
    return sum;
}
double Err2dRegres(Mat& mat_a, Mat& mat_c, Vec& vec_x, Vec& vec_y){
    double error_sum=0;
    for(int i=1; i<=mat_a.rnum; i++){
        for(int j=1; j<=mat_a.cnum; j++){
            error_sum += pow( (Fun2dRegres(mat_c,vec_x(i),vec_y(j))-mat_a(i,j)),2);
        }
    }
    return error_sum;
}