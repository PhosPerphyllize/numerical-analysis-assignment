#include"myMat.h"

// #include<iostream>
// #include <iomanip>

// using namespace std;

double g_e=2.718281828459045235360287471352662497757247093;
double epsilon=1e-12 ; 

int main(void)
{
    // cout.setf(ios::fixed);
    // cout  <<fixed<< setprecision(30) << g_e <<endl; //输出a=0.20

    // printf("%d %d", sizeof(double), sizeof(long double));



    // //LU分解测试
    // long double lutest1[3][3] =
    //     {
    //         {8.1, 2.3, -1.5},
    //         {0.5, -6.23, 0.87},
    //         {2.5, 1.5, 10.2}
    //     };

    // struct Mat lu1;
    // lu1.col_num=3,lu1.row_num=3;
    // lu1.flag=0;
    // lu1.num=3,
    // lu1.p_mat=&lutest1[0][0];
    // lu1.r_row=3,lu1.s_col=3;

    // // PrintMat(LUDeposit(lu1));

    // long double b_lu1[3]={6.1, 2.3, 1.8};
    // struct Vec b1;
    // b1.num=3;
    // b1.p_vec=b_lu1;

    // struct Vec x1;
    // x1 = LUBackSub(LUDeposit(lu1),b1);
    // PrintVec(x1); 


    // long double lutest2[3][5]={  
    //     {0, 1, 1, 1, 1},
    //     {4, 4, 4, 4, 4},
    //     {1, 1, 1, 1, 0},
        
    // };

    // struct Mat lu2;
    // lu2.col_num=5,lu2.row_num=3;
    // lu2.flag=1;
    // lu2.num=5,
    // lu2.p_mat=&lutest2[0][0];
    // lu2.r_row=1,lu2.s_col=1;
    
    // PrintMat(LUDeposit(lu2));

    // long double b_lu2[5]={1, 0.5, -1, 3, 2};
    // struct Vec b2;
    // b2.num=5;
    // b2.p_vec=b_lu2;

    // struct Vec x2;
    // x2 = LUBackSub(LUDeposit(lu2),b2);
    // PrintVec(x2); 


    // //struct Mat MatPlusE(struct Mat mat, double plus_num)测试
    // double test1[3][3] =
    //     {
    //         {8.1, 2.3, -1.5},
    //         {0.5, -6.23, 0.87},
    //         {2.5, 1.5, 10.2}
    //     };

    // struct Mat mat1;
    // mat1.col_num=3,mat1.row_num=3;
    // mat1.flag=0;
    // mat1.num=3,
    // mat1.p_mat=&test1[0][0];
    // mat1.r_row=3,mat1.s_col=3;

    // struct Mat mat1_result = MatPlusE(mat1, 0);
    // PrintMat(mat1_result);

    // double test2[3][5]={  
    //     {0, 1, 1, 1, 1},
    //     {4, 4, 4, 4, 4},
    //     {1, 1, 1, 1, 0},
        
    // };

    // struct Mat mat2;
    // mat2.col_num=5,mat2.row_num=3;
    // mat2.flag=1;
    // mat2.num=5,
    // mat2.p_mat=&test2[0][0];
    // mat2.r_row=1,mat2.s_col=1;

    // struct Mat mat2_result = MatPlusE(mat2, 0);
    // PrintMat(mat2_result);



    // 小特征值LU分解测试

    // double test3[5][8] =
    // {
    //     {0, 0, -0.05, -0.05, -0.05, -0.05, -0.05, -0.05},
    //     {0, 0.1, 0.1,  0.1,   0.1,   0.1,   0.1,  0.1},
    //     {0.002,   1.002,   2.002,     3.002,     4.002,     5.002,     6.002,    7.002},
    //     {0.1,  0.1,  0.1,  0.1,   0.1,    0.1,    0.1,  0},
    //     {-0.05, -0.05, -0.05, -0.05, -0.05, -0.05,  0,  0}
    // };

    // struct Mat mat3;
    // mat3.col_num=8, mat3.row_num=5;
    // mat3.flag=1;
    // mat3.num=8,
    // mat3.p_mat=&test3[0][0];
    // mat3.r_row=2, mat3.s_col=2;

    // double v_test1[8] = {0.0520, 2.2040, 6.3060, 12.4080, 20.5100, 30.6120, 43.1640, 56.4160};

    // struct Vec b1;
    // b1.num=8, b1.p_vec=v_test1; 

    // struct Mat mat3_lu;
    // mat3_lu = LUDeposit(mat3);
    // PrintMat(mat3_lu);
    // putchar('\n');
    // PrintMat(AzipDeCompress(mat3_lu));
    // putchar('\n');
    // PrintVec(LUBackSub(mat3_lu,b1));
    // //边条LU有问题

    // //AzipShow测试
    // putchar('\n');
    // PrintMat(AzipDeCompress(mat3));

    // //AzipChange测试
    // putchar('\n');
    // for(int i=0; i<mat3.num; i++)
    // {
    //     AzipChange(mat3,i,i,3);
    // }
    // for(int i=0; i<mat3.num-1; i++)
    // {
    //     AzipChange(mat3,i,i+1,2);
    //     AzipChange(mat3,i+1,i,4);
    // }
    // for(int i=0; i<mat3.num-2; i++)
    // {
    //     AzipChange(mat3,i,i+2,1);
    //     AzipChange(mat3,i+2,i,5);
    // }
    // PrintMat(mat3);

    // putchar('\n');
    // printf("%f",Min3(1,2,3));
 



    //MatDiagMuti测试
    double test3[5][8] =
    {
        {0, 0, -0.05, -0.05, -0.05, -0.05, -0.05, -0.05},
        {0, 0.1, 0.1,  0.1,   0.1,   0.1,   0.1,  0.1},
        {0.002,   1.002,   2.002,     3.002,     4.002,     5.002,     6.002,    7.002},
        {0.1,  0.1,  0.1,  0.1,   0.1,    0.1,    0.1,  0},
        {-0.05, -0.05, -0.05, -0.05, -0.05, -0.05,  0,  0}
    };

    struct Mat mat3;
    mat3.col_num=8, mat3.row_num=5;
    mat3.flag=1;
    mat3.num=8,
    mat3.p_mat=&test3[0][0];
    mat3.r_row=2, mat3.s_col=2;

    printf("%f", MatDiagMuti(mat3));
    
    return 0;
}