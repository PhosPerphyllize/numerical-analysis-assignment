#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<iomanip>

#include"include/glo.h"
#include"include/mat.h"
#include"include/vec.h"
using std::cin;  using std::cout;  using std::endl;  using std::string;

extern const double e_compare_error;
extern const double e_step_comperr;
const int g_main_mat_num = 6;
const int g_reg_mat_xnum = 11;
const int g_reg_mat_ynum = 21;
const int g_vec_xp_num = 8;
const int g_vec_yp_num = 5;
const double g_arru[g_main_mat_num]={0, 0.4, 0.8, 1.2, 1.6, 2};
const double g_arrt[g_main_mat_num]={0, 0.2, 0.4, 0.6, 0.8, 1};
const double g_main_arr[g_main_mat_num][g_main_mat_num] = {
    {-0.5, -0.34, 0.14, 0.94, 2.06, 3.5},
    {-0.42, -0.5, -0.26, 0.3, 1.18, 2.38},
    {-0.18, -0.5, -0.5, -0.18, 0.46, 1.42},
    {0.22, -0.34, -0.58, -0.5, -0.1, 0.62},
    {0.78, -0.02, -0.5, -0.66, -0.5, -0.02},
    {1.5, 0.46, -0.26, -0.66, -0.74, -0.5}};

double ReturnFxy(const double num_x, const double num_y);
Vec FindNode(const double num_u, const double num_t);
double ReturnPxy(Mat& mata, const double num_x, const double num_y);

int main(){
    Vec vec_x("vec_x(main)",g_reg_mat_xnum), vec_y("vec_y(main)",g_reg_mat_ynum);
    for(int i=0; i<g_reg_mat_xnum; i++)
        vec_x(i+1) = 0.08*i;
    for(int i=0; i<g_reg_mat_ynum; i++)
        vec_y(i+1) = 0.5 + 0.05*i;
    Mat matxy("matxy(main)", g_reg_mat_xnum, g_reg_mat_ynum);
    for(int i=1; i<=g_reg_mat_xnum; i++){
        for(int j=1; j<=g_reg_mat_ynum; j++){
            matxy(i,j)=ReturnFxy(vec_x(i),vec_y(j));
        }
    }

    cout << std::setw(20) << std::setiosflags(std::ios::scientific) << std::setprecision(12) << std::flush;
    for(int i=1; i<=g_reg_mat_xnum; i++){
        cout << "\n        x        " << "         y        " << "        f(x,y)     " << endl;
        for(int j=1; j<=g_reg_mat_ynum; j++){
            cout << vec_x(i) << " " << vec_y(j)<< " " << matxy(i,j) << endl;
        }
    }

    int k=1;
    int x_pow_num = 1, y_pow_num = 1;
    double error_res=0;
    Mat *mat_temp = NULL;
    cout << endl;
    while(1){
        x_pow_num = k, y_pow_num = k;
        delete mat_temp;
        mat_temp = new Mat("mat_temp(main)", x_pow_num+1, y_pow_num+1);
        *mat_temp = TwoDimRegres(vec_x, vec_y, matxy, x_pow_num, y_pow_num);
        error_res = Err2dRegres(matxy, *mat_temp, vec_x, vec_y);
        cout << "k = " << k << ", sigma = " << error_res << endl;
        if(error_res<=e_step_comperr*10||k>=6){
            break;
        }
        k++;
    }
    Mat mat_c("mat_c(main)", x_pow_num+1, y_pow_num+1);
    mat_c = *mat_temp;
    cout << "\nmat_c:" << endl;
    cout << mat_c << endl;

    Vec vec_xp("vec_xp",g_vec_xp_num), vec_yp("vec_yp", g_vec_yp_num);
    for(int i=0; i<g_vec_xp_num; i++)
        vec_xp(i+1) = 0.1*i;
    for(int i=0; i<g_vec_yp_num; i++)
        vec_yp(i+1) = 0.5 + 0.2*i;
    for(int i=1; i<=g_vec_xp_num; i++){
        cout << "        x*        " << "         y*        " << "       f(x*,y*)     " << "       p(x*,y*)     " << endl;
        for(int j=1; j<=g_vec_yp_num; j++){
            cout << vec_xp(i) <<" "<< vec_yp(j)<<" "<< ReturnFxy(vec_xp(i),vec_yp(j)) <<" "<< ReturnPxy(mat_c, vec_xp(i), vec_yp(j)) << endl;
        }
    }
    return 0;
}
double ReturnFxy(const double num_x, const double num_y){
// 输入x，y 返回经过分片插值的f(x,y)   
    Vec ut("ut(ReturnVecXY)",4); // 解，t u v w
    ut = SolveXY(num_x, num_y);

    Vec no("no",2);
    no = FindNode(ut(1), ut(2));  // 求出9点矩阵的左上角坐标，no求的是数组的序号，0开始
    int no_t = Dou2Int(no(1)), no_u = Dou2Int(no(2));

    Vec vect("vect",3), vecu("vecu",3);
    Mat mata("mata",3,3);
    for(int i=1; i<=3; i++){
        vect(i) = g_arrt[no_t+i-1];
        vecu(i) = g_arru[no_u+i-1];
        for(int j=1; j<=3; j++){
            mata(i,j) = g_main_arr[no_t+i-1][no_u+j-1];
        }
    }
    // if(Abs(vecu(3))<e_compare_error)
    //     cout << ut(1) <<endl;
    // cout << vecu << vect << endl;
    // cout << mata << endl;
    return Lagra2d(vect, vecu, mata, ut(1), ut(2));
}
Vec FindNode(const double num_t, const double num_u){
// 输入t，u 找到到这个坐标最近的插值节点，输出其左上角的坐标
    if(num_t<0||num_t>1)
        cout << "FindNode() warning: num_t out of rank." << endl;
    if(num_u<0||num_u>2)
        cout << "FindNode() warning: num_u out of rank." << endl;

    double t_dis=Abs(num_t-g_arrt[0]);
    int t_no=0;
    for(int i=0; i<g_main_mat_num; ++i){
        if(t_dis>Abs(num_t-g_arrt[i])){
            t_no=i;
            t_dis=Abs(num_t-g_arrt[i]); 
        }      
    }
    if(t_no<=0)
        t_no=1;
    if(t_no>=g_main_mat_num-1)
        t_no=g_main_mat_num-2;

    double u_dis=Abs(num_u-g_arru[0]);
    int u_no=0;
    for(int i=0; i<g_main_mat_num; ++i){
        if(u_dis>Abs(num_u-g_arru[i])){
            u_no=i;
            u_dis = Abs(num_u-g_arru[i]);
        }        
    }
    if(u_no<=0)
        u_no=1;
    if(u_no>=g_main_mat_num-1)
        u_no=g_main_mat_num-2;

    Vec output("output",2);
    output(1) = t_no-1;  // no求的是数组的序号
    output(2) = u_no-1;
    return output;
}
double ReturnPxy(Mat& mata, const double num_x, const double num_y){
    double reslu=0;
    for(int i=1; i<=mata.rnum; i++){
        for(int j=1; j<=mata.cnum; j++){
            reslu += mata(i,j)*pow(num_x,i-1)*pow(num_y,j-1);
        }
    }
    return reslu;
}
