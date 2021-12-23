#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>

#include"include/glo.h"
#include"include/mat.h"
#include"include/vec.h"
using std::cin;  using std::cout;  using std::endl;  using std::flush;  using std::string;

extern const double g_compare_error;
extern const double g_step_comperr;

double fun(double x, double y);

int main(){
    int i,j;
    //Mat≤‚ ‘
    double mat_1[4][4] = {
        {8.1, 2.3, -1.5, 0},
        {0.5, -6.23, 0.87, -15.1},
        {2.5, 1.5, 10.2, 0.23},
        {-3.4, 1.2, 0.8, 7.62}};
    Mat mat1("mat1",4,4);
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            mat1(i+1,j+1) = mat_1[i][j];
        }
    }
    // cout << mat1 << endl;

    double mat_2[4][2] = {
        {1, 2},
        {0.1, 0.3},
        {0.2, -0.4},
        {0, 3}};
    Mat mat2("mat2",4,2);
    for(i=0; i<4; i++){
        for(j=0; j<2; j++){
            mat2(i+1,j+1) = mat_2[i][j];
        }
    }
    // cout << mat2 << endl;

    double mat_3[4][2] = {
        {0.23, 7},
        {-0.23, 0},
        {-0.75, 0},
        {3.1, 0.987}};
    Mat mat3("mat3",4,2);
    for(i=0; i<mat3.rnum; i++){
        for(j=0; j<mat3.cnum; j++){
            mat3(i+1,j+1) = mat_3[i][j];
        }
    }
    // cout << mat3 << endl;

    double mat_4[2][4] = {
        {1, 2, 3, 4},
        {0, 3, -5, 7}};
    Mat mat4("mat4",2,4);
    for(i=0; i<2; i++){
        for(j=0; j<4; j++){
            mat4(i+1,j+1) = mat_4[i][j];
        }
    }
    // cout << mat4 << endl;

    // Vec≤‚ ‘
    double vec_1[4] = {6.38, -0.3, 1.75, 0.382};
    Vec vec1("vec1",4);
    for(i=0; i<vec1.num; i++){
        vec1(i+1) = vec_1[i];
    }

    double vec_2[4] = {-0.45, 0, 8.07, 5.1};
    Vec vec2("vec2",4);
    for(i=0; i<vec2.num; i++){
        vec2(i+1) = vec_2[i];
    }

    double vec_3[4] = {0, 1, 2, 3};
    Vec vec3("vec3",4);
    for(i=0; i<vec3.num; i++){
        vec3(i+1) = vec_3[i];
    }

    // // ‰≥ˆ£¨∑µªÿ∂‘œÛ≤‚ ‘
    // std::cout << mat1 << std::endl;
    // for(int i=1; i<=mat1.rnum; ++i){
    //     for(int j=1; j<=mat1.cnum; ++j){
    //         cout << mat1(i,j) << ' ' << flush;
    //         mat1(i,j) = i+j;
    //     }
    //     cout << endl;
    // }
    // cout << mat1 << endl;
    
    // cout << mat2 << endl;
    // for(int i=1; i<=mat2.rnum; ++i){
    //     for(int j=1; j<=mat2.cnum; ++j){
    //         cout << mat2(i,j) << ' ' << flush;
    //         mat2(i,j) = i-j;
    //     }
    //     cout << endl;
    // }
    // cout << mat2 << endl;

    // // æÿ’Û ˝º”ºı≤‚ ‘
    // cout << mat3 + mat2 << endl;
    // cout << mat3 - mat2 << endl;
    // cout << mat2 - mat4.tranPosition() << endl;
    
    // // æÿ’Û≥À∑®≤‚ ‘
    // cout << mat2 * mat4 << endl; 
    // cout << mat4 * mat2 << endl;
    // cout << mat2 * mat3.tranPosition() << endl; 
    // cout << mat3 * mat2.tranPosition() << endl;

    // // æÿ’Û ˝≥À≤‚ ‘
    // cout << mat1*(1.0/2) << endl;
    // cout << mat2*-0.25 << endl;

    // // Mat*Vec ≤‚ ‘
    // cout << vec1 << endl;
    // cout << mat1*vec1 << endl;

    // // Vec º”°¢ºı°¢ ˝≥À≤‚ ‘
    // std::cout.precision(12);
    // cout << vec1 + vec2  + vec3*0.3 << endl;

    // // ∂˛∑∂ ˝≤‚ ‘
    // cout << vec1.norm2() << endl;
    // cout << sqrt(vec1*vec1) << endl;

    // // Mat◊€∫œ≤‚ ‘
    // cout << mat1*0.5 + vec3%vec2 << endl;
    // cout << mat2*mat4 - mat1*0 + vec3%vec2 << endl;

    // // matµ˜ªª≤‚ ‘
    // cout << mat1 << endl;
    // cout << mat1.swapLine(4,2) << endl;
    // cout << mat2.swapLine(1,2) << endl;

    // // takeRow takeCol ≤‚ ‘
    // for(i=1; i<=mat1.rnum; ++i){
    //     cout << mat1.takeRow(i) << endl;
    // }
    // for(i=1; i<=mat1.cnum; ++i){
    //     cout << mat1.takeCol(i) << endl;
    // }

    // // mat/vec test
    // cout << vec1/mat1 << endl;
    // cout << mat1 * (vec1/mat1) << endl;

    // // æÿ’Û––ÃÊ¥˙≤‚ ‘
    // cout << "mat1: " << mat1 << endl;
    // cout << "vec1: " << vec1 << endl;
    // cout << mat1.replaceRow(vec1,1) << endl;
    // cout << mat1.replaceCol(vec1,1) << endl;
    // cout << mat1.replaceCol(vec1,2) << endl;
    // cout << mat1.replaceCol(vec1,4) << endl;

    // mat3 = mat3.replaceCol(vec1,1);
    // mat3 = mat3.replaceCol(vec1,2);
    // mat1 = mat1.replaceCol(vec1,4);

    // mat2 = mat2.replaceCol(vec2,2);

    // // œÚ¡ø’˚ÃÂ÷∏ ˝
    // cout << vec1.power(1) << endl;
    // cout << vec1.power(2) << endl;
    // cout << vec1.power(3) << endl;
    // cout << vec2.power(3) << endl;


    // double vec_x[4] = {0, 1, 2, 3};
    // Vec vecx("vecx",4);
    // for(i=0; i<vecx.num; i++){
    //     vecx(i+1) = vec_x[i];
    // }

    // double vec_y[4] = {2, 2, 4, 8};
    // Vec vecy("vecy",4);
    // for(i=0; i<vecy.num; i++){
    //     vecy(i+1) = vec_y[i];
    // }

    // // “ªŒ¨œﬂ–‘ªÿπÈ≤‚ ‘
    // cout << OneDimRegres(vecx, vecy, 2) << endl;

    // // ∂˛Œ¨œﬂ–‘ªÿπÈ≤‚ ‘
    // double vec_x[5] = {0.2, 0.5, 1.8, 2.6, 3.5};
    // Vec vecx("vecx",5);
    // for(i=0; i<vecx.num; i++){
    //     vecx(i+1) = vec_x[i];
    // }
    // double vec_y[6] = {-1.8, -0.8, 0, 0.8, 1.2, 1.8};
    // Vec vecy("vecy",6);
    // for(i=0; i<vecy.num; i++){
    //     vecy(i+1) = vec_y[i];
    // }
    // Mat mat_a("mat_a(main)", vecx.num, vecy.num);
    // for(int i=1; i<=mat_a.rnum; i++){
    //     for(int j=1; j<=mat_a.cnum; j++){
    //         mat_a(i,j)=fun(vecx(i),vecy(j));
    //     }
    // }
    // Mat mat_c("mat_c(main)",3,3);
    // mat_c = TwoDimRegres(vecx, vecy, mat_a, 2, 2);
    // cout << mat_c << endl;
    // cout << Err2dRegres(mat_a, mat_c, vecx, vecy) << endl;

    // // ¿≠∏Ò¿ »’≤Â÷µ≤‚ ‘
    // double vec_x[3] = {-1, 0, 1};
    // Vec vecx("vecx",3);
    // for(i=0; i<vecx.num; i++){
    //     vecx(i+1) = vec_x[i];
    // }
    // double vec_y[2] = {0.5, 1};
    // Vec vecy("vecy",2);
    // for(i=0; i<vecy.num; i++){
    //     vecy(i+1) = vec_y[i];
    // }

    // double mat_a[3][2] = {
    //     {0.25, 0.43},
    //     {0.5, 0.87},
    //     {1, 1.73}};
    // Mat mata("mata",3,2);
    // for(i=0; i<mata.rnum; i++){
    //     for(j=0; j<mata.cnum; j++){
    //         mata(i+1,j+1) = mat_a[i][j];
    //     }
    // }
    // cout << Lagra2d(vecx, vecy, mata,0.3,0.8) << endl;

    cout << Dou2Int(1.99) << endl;
    cout << Dou2Int(2.01) << endl;
    cout << Dou2Int(2.0) << endl;

    cout << "Code end~~" << endl;
    return 0;
}
double fun(double x, double y){
    // double a[3][3]={
    //     {-1.7, 2, 1.45},
    //     {-1, 4, 0.5},
    //     {-3.5, 2, 1.88}};
    return 1.88*x*x*y*y + 2*x*x*y -3.5*x*x + 0.5*x*y*y + 4*x*y -1*x + 1.45*y*y + 2*y + 1.7; 
}