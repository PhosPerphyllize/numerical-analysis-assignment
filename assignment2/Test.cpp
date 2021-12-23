#include"mymat.h"
#include"qrmat.h"
#include<iomanip>

using std::cout;
using std::endl;
using std::flush;

int main(){
    //Mat≤‚ ‘
    double mat_1[4][4] = {
        {8.1, 2.3, -1.5, 0},
        {0.5, -6.23, 0.87, -15.1},
        {2.5, 1.5, 10.2, 0.23},
        {-3.4, 1.2, 0.8, 7.62}};
    Mat mat1("mat1",4);
    mat1.p = &mat_1[0][0];
    // cout << mat1 << endl;

    double mat_2[4][4] = {
        {1, 2, 3, 4},
        {0.1, 0.3, 0.5, 0.7},
        {0.2, -0.4, 0.6, -0.8},
        {0, 3, -5, 7}};
    Mat mat2("mat2",4);
    mat2.p = &mat_2[0][0];
    // cout << mat2 << endl;

    double mat_3[6][6] = {
        {8.1, 2.3, -1.5, 0, 2.5, 7.8},
        {0.5, -6.23, 0.87, -15.1, 0.1, -2.89},
        {2.5, 1.5, 10.2, 0.23, 0, 7},
        {-3.4, 1.2, 0.8, 7.62, -0.23, 0},
        {9.58, 7.45, -8.15, -6.24, -0.75, 0},
        {0.126, 7.58, -0.45, -2.54, 3.1, 0.987}};
    Mat mat3("mat3",6);
    mat3.p = &mat_3[0][0];
    // cout << mat3 << endl;
    cout << mat_3[1][2] << endl;

    double mat_4[4][4] = {
        {1, 2, 3, 4},
        {0.1, 0.3, 0.5, 0.7},
        {0.2, 0.4, 0.6, 0.8},
        {0, 3, -5, 7}};
    Mat mat4("mat4",4);
    mat4.p = &mat_4[0][0];
    // cout << mat4 << endl;

    // // ‰≥ˆ£¨∑µªÿ∂‘œÛ≤‚ ‘
    // std::cout << mat1 << std::endl;
    // for(int i=1; i<=mat1.num; ++i){
    //     for(int j=1; j<=mat1.num; ++j){
    //         cout << mat1(i,j) << ' ' << flush;
    //     }
    //     cout << endl;
    // }
    
    // cout << mat2 << endl;
    // for(int i=1; i<=mat2.num; ++i){
    //     for(int j=1; j<=mat1.num; ++j){
    //         cout << mat2(i,j) << ' ' << flush;
    //     }
    //     cout << endl;
    // }

    // // –ﬁ∏ƒ∂‘œÛ≤‚ ‘ mat(i,j)
    // for(int i=1; i<=mat1.num; ++i){
    //     for(int j=1; j<=mat1.num; ++j){
    //         mat1(i,j) = i-j;
    //     }
    // }
    // std::cout << mat1 << std::endl;

    // for(int i=1; i<=mat2.num; ++i){
    //     for(int j=1; j<=mat1.num; ++j){
    //         mat2(i,j) = i+j;
    //     }
    // }
    // cout << mat2 << endl;

    // // æÿ’Û ˝º”ºı≤‚ ‘
    // cout << mat1 + mat2 << endl;
    // cout << mat1 - mat2 << endl;
    // cout << mat2 - mat1 << endl;
    
    // // æÿ’Û≥À∑®≤‚ ‘
    // cout << mat1 * mat2 << endl; 
    // cout << mat2 * mat1 << endl;

    // // æÿ’Û ˝≥À≤‚ ‘
    // cout << mat1*(1.0/2) << endl;
    // cout << mat2*-0.25 << endl;

    // Vec≤‚ ‘
    double vec_1[4] = {6.38, -0.3, 1.75, 0.382};
    Vec vec1("vec1",4);
    vec1.p = vec_1;

    double vec_2[4] = {-0.45, 0, 8.07, 5.1};
    Vec vec2("vec2",4);
    vec2.p = vec_2;

    double vec_3[4] = {0.95, -11.5, 1.28, 4.23};
    Vec vec3("vec3",4);
    vec3.p = vec_3;


    double vec_4[4] = {0, 0, 0, 8.92};
    Vec vec4("vec4",4);
    vec4.p = vec_4;
    vec4.zero_num = 3;
    
    double vec_5[4] = {0, 0, -1.45, 12.92};
    Vec vec5("vec5",4);
    vec5.p = vec_5;
    vec5.zero_num = 2;

    double vec_6[6] = {0.95, -1.5, 1.28, 4.23, 0.25, 0};
    Vec vec6("vec6",6);
    vec6.p = vec_6;
    vec6.zero_num = 0;

    // // Mat*Vec ≤‚ ‘
    // cout << vec4 << endl;
    // cout << mat1*vec4 << endl;

    // // Vec º”°¢ºı°¢ ˝≥À≤‚ ‘
    // std::cout.precision(12);
    // cout << vec1 + vec2  + vec3*0.3 << endl;

    // // ∂˛∑∂ ˝≤‚ ‘
    // cout << vec1.norm2() << endl;
    // cout << std::setprecision(18) << sqrt(vec1*vec1) << endl;

    // // Mat◊€∫œ≤‚ ‘
    // cout << mat2*0.5 + vec3%vec4 << endl;

    // // ¡„œÚ¡ø≤‚ ‘
    // cout << vec5 % vec4 << endl;

    // // ◊™÷√≤‚ ‘
    // cout << mat1.tranPosition() << endl;

    // // qr∑÷Ω‚
    // Mat mat_q("mat_q",4), mat_r("mat_r",4);
    // mat_r = mat3;
    // mat_q = QRDeposit(mat_r);

    // std::cout.precision(12);
    // cout << mat_q << "\n" << endl;
    // cout << mat_r << "\n" << endl;
    // cout << mat_q*mat_r << "\n" << endl;
    // cout << mat_q*mat_q.tranPosition() << "\n" << endl; 

    // // ƒ‚…œ»˝Ω«ªØ
    // Mat mat_q("mat_q",4), mat_a("mat_a",4);
    // mat_a = mat3;
    // mat_q = QuasiUpTri(mat_a);

    // std::cout.precision(12);
    // cout << mat_q << "\n" << endl;
    // cout << mat_a << "\n" << endl;
    // cout << mat_q*mat_a*mat_q.tranPosition() << "\n" << endl;
    // cout << mat_q*mat_q.tranPosition() << "\n" << endl;

    // // æÿ’ÛΩµŒ¨≤‚ ‘
    // cout << mat3.lowDemi(2) << endl;
    // cout << mat3.num << endl;

    // // SolveTwoFun Ω‚∂˛‘™“ª¥Œ∑Ω≥Ã≤‚ ‘
    // // cout << sqrt(-1) << endl;
    // Com root1(1,2), root2(3,4);
    // SolveTwoFun(1,0,2, root1, root2);
    // cout << "root1:" << root1 << endl;
    // cout << "root2:" << root2 << endl;

    // StepQR≤‚ ‘
    // cout << StepQR(mat3) << endl;
    // cout << QR(mat3) << endl;

    // // –È ˝≤‚ ‘
    // Com com1(0.1,0.2), com2(1.3,-0.5), com3(0,0.05), com4(4,0);
    // com3 = 3;

    // // cout << com1+com2*5 - com3 + com4 << endl;
    // // cout << -com3 + com4 +5.21 << endl;

    // // Comvec≤‚ ‘
    // Comvec comv(6);
    // comv.comVecChange(1,root1);
    // comv.comVecChange(2,root2);
    // comv.comVecChange(3,com3);
    // comv.comVecChange(4,com4);
    // comv.comVecChange(5,5.2);
    // comv.comVecChange(6,0.5);

    // cout << comv << endl;
    // cout << comv(1) << " "<< comv(6) << endl;

    // // matµ˜ªª≤‚ ‘
    // cout << mat1 << endl;
    // cout << mat1.swapLine(1,2) << endl;

    // // // mat/vec test
    // // Vec ans("ans", vec.num);
    // // ans = mat1/vec1
    // // vec4.init(0);
    // cout << vec4 << endl;
    // cout << mat4/vec4 << endl;
    // cout << mat4 * (mat4/vec4) << endl;
    // cout << vec5 << endl;

    // // Mat.initE()≤‚ ‘
    // free(NULL);
    // free(NULL);
    // Mat mat_t("mat_t(Test)",mat1.num);
    // mat_t = mat1.initE();
    // cout << mat_t << endl;


    cout << "\n =======test end========." << endl;
    return 0;
}