#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 1.0e-12
double C[5][501];
double u[501];
double x[501];
double y[501];
int N=501;
// double min(double a,double b);
void liezhuyuan();
/********转存矩阵**********
 * ***************** 0  1  2  ...  499  500
 * *******************************************
//          0  *     0  0  c  ...   c    c
//          1  *     0  b  b  ...   b    b
//          2  * C= [a1 a2 a3 ... a500 a501]
//          3  *     b  b  b  ...   b    0
//          4  *     c  c  c  ...   0    0
//A[i][j]=C[i-j+2][j]
**************************/
void initialize_C();

void doolittle(double array[5][501]);

double fanmifa(double u[501], double array[5][501], double p);

void solve_LU(double array[5][501], double B[501]);

int max_3(int a, int b, int c);

int main() {
    int i, j, k, t;
    double a = 0, b = 0, c = 0, uu;
    double bb = 0;//表示前一个b的值
    double lamda_m1, lamda_1, lamda_501, lamda_m2, lamda_s;
    //将矩阵A转成C
    initialize_C();
    //幂法求按模最大特征值lamda_m
    //49-85行求出一个特征值，但不知道该特征值是lamda_1还是lamda_501,之后88-123行对A矩阵作平移求出lamda_m2，
    //与lamda_m1比较可得出1与501的值
    //取初始迭代向量uT=[1 1 1 ... 1]
    for (i = 0; i < 501; ++i) {
        u[i] = 1;
    }

    while (1) {

        //求 a = ηk-1 的值
        a = 0;
        for (i = 0; i < 501; ++i) {
            a = a + u[i] * u[i];
        }
        a = sqrt(a);
        //求 yk-1 的值
        for (i = 0; i < 501; ++i) {
            y[i] = u[i] / a;
        }
        //求 uk=Ak*yk-1
        u[0] = C[2][0] * y[0] + C[1][1] * y[1] + C[0][2] * y[2];
        u[1] = C[3][0] * y[0] + C[2][1] * y[1] + C[1][2] * y[2] + C[0][3] * y[3];
        u[499] = C[4][497] * y[497] + C[3][498] * y[498] + C[2][499] * y[499] + C[1][500] * y[500];
        u[500] = C[4][498] * y[498] + C[3][499] * y[499] + C[2][500] * y[500];
        for (i = 2; i <= 498; ++i) {
            u[i] = C[4][i - 2] * y[i - 2] + C[3][i - 1] * y[i - 1] + C[2][i] * y[i] + C[1][i + 1] * y[i + 1] +
                   C[0][i + 2] * y[i + 2];
        }
        //求b = βk
        b = 0;
        for (i = 0; i < 501; ++i) {
            b = b + y[i] * u[i];
        }

        if (fabs((b - bb) / b) <= E) {//bb 表示前一个b的值
            break;
        }
        bb = b;
    }
    lamda_m1 = b;
    //求出lamda_m1后，可能为lamda_1或lamda_501
    //现对A-lm求特征值lamda_m2
    for (i = 0; i < 501; ++i) {
        C[2][i] = C[2][i] - lamda_m1;
    }
    while (1) {
        //求 a = ηk-1 的值
        a = 0;
        for (i = 0; i < 501; ++i) {
            a = a + u[i] * u[i];
        }
        a = sqrt(a);
        //求 yk-1 的值
        for (i = 0; i < 501; ++i) {
            y[i] = u[i] / a;
        }
        //求 uk=Ak*yk-1
        u[0] = C[2][0] * y[0] + C[1][1] * y[1] + C[0][2] * y[2];
        u[1] = C[3][0] * y[0] + C[2][1] * y[1] + C[1][2] * y[2] + C[0][3] * y[3];
        u[499] = C[4][497] * y[497] + C[3][498] * y[498] + C[2][499] * y[499] + C[1][500] * y[500];
        u[500] = C[4][498] * y[498] + C[3][499] * y[499] + C[2][500] * y[500];
        for (i = 2; i <= 498; ++i) {
            u[i] = C[4][i - 2] * y[i - 2] + C[3][i - 1] * y[i - 1] + C[2][i] * y[i] + C[1][i + 1] * y[i + 1] +
                   C[0][i + 2] * y[i + 2];
        }
        //求b = βk
        b = 0;
        for (i = 0; i < 501; ++i) {
            b = b + y[i] * u[i];
        }

        if (fabs((b - bb) / b) <= E) {//bb 表示前一个b的值
            break;
        }
        bb = b;
    }
    lamda_m2 = lamda_m1 + b;
    //输出lamda_1和lamda_2
    if (lamda_m1 < lamda_m2) {
        printf("lamda_1=%.12e\n", lamda_m1);
        printf("lamda_501=%.12e\n", lamda_m2);
    } else {
        printf("lamda_1=%.12e\n", lamda_m2);
        printf("lamda_501=%.12e\n", lamda_m1);
    }
    //反幂法求按模最小特征值
    initialize_C();
    doolittle(C);
    //取初始迭代向量uT=[1 1 1 ... 1]
    for (i = 0; i < 501; ++i) {
        u[i] = 1;
    }
    bb = 0;
    while (1) {
        //求 a = ηk-1 的值
        a = 0;
        for (i = 0; i < 501; ++i) {
            a = a + u[i] * u[i];
        }
        a = sqrt(a);
        //求 yk-1 的值
        for (i = 0; i < 501; ++i) {
            y[i] = u[i] / a;
        }
        //求 uk

        for ( i = 0; i < 501; ++i) {
            u[i]=y[i];
        }

        for (i = 1; i < 501; ++i) {
            for (t = ((i - 2) > 0 ? i - 2 : 0); t <= i - 1; ++t) {
                u[i] -= C[i - t + 2][t] * u[t];
            }
        }
        u[500] = u[500] / C[2][500];
        for (i = 499; i >= 0; i--) {
            for (t = i + 1; t <= ((i + 2) < 500 ? i + 2 : 500); ++t) {
                u[i] -= C[i - t + 2][t] * u[t];
            }
            u[i] = u[i] / C[2][i];

        }


        //求b = βk
        b = 0;
        for (i = 0; i < 501; ++i) {
            b = b + y[i] * u[i];
        }

        if (fabs((b - bb) / b) <= E) {//bb 表示前一个b的值
            break;
        }
        bb = b;
        lamda_s = 1 / b;

    }printf("lamda_s=%.12e\n", lamda_s);
    /*
    initialize_C();
    lamda_s = fanmifa(u, C, 0);
    printf("lamda_s=%.12e\n", lamda_s);
    for (int k = 1; k < 40; ++k) {
        uu = lamda_1 + k * (lamda_501 - lamda_1) / 40;

        a = fanmifa(u, C, uu);
        printf("lamda_i%d=%.12e\n", k, a);
    }*/
    initialize_C();
    doolittle(C);
    double detA = 1;
    for (int l = 0; l < 501; ++l) {
        detA = detA * C[2][l];
    }
    printf("A矩阵的行列式值为%.12e\n", detA);
    printf("你好\n");
    return 0;
}

void initialize_C() {
    int i;
    for (i = 2; i < 501; ++i) {
        C[0][i] = -0.064;
    }
    for (i = 1; i < 501; ++i) {
        C[1][i] = 0.16;
    }
    for (i = 1; i <= 501; ++i) {
        C[2][i - 1] = (1.64 - 0.024 * i) * sin(0.2 * i) - 0.64 * exp(0.1 / i);
    }
    for (i = 0; i < 500; ++i) {
        C[3][i] = 0.16;
    }
    for (i = 0; i < 499; ++i) {
        C[4][i] = -0.064;
    }
}

// double min(double a,double b){
//     if(a<b)
//         return a;
//     else
//         return b;
// }
void doolittle(double array[5][501]) {/*
    int i, j, k, t;
    double temp;
    for (k = 0; k < 501; ++k) {
        for (j = k; j <= ((k + 2) < 500 ? (k + 2) : 500); ++j) {
            temp=0;
            for (t = max_3(k - 2, j - 2, 0); t <= k - 1; ++t) {
                temp+= array[k - t + 2][t] * array[t - j + 2][j];
            }
            array[k-j+2][j]=array[k-j+2][j]-temp;
        }
        if (k == 500)break;
        for (i = k + 1; i <= ((k + 2) < 500 ? (k + 2) : 500); ++i) {
            temp=0;
            for (t = max_3(k - 2, i - 2, 0); t <= k - 1; ++t) {
                temp+= array[i - t + 2][t] * array[t - k + 2][k];
            }
            array[i - k + 2][k] = (array[i - k + 2][k] -temp)/ array[2][k];
        }

    }
    /*int k, i, j, t, S = 2;

    double temp;

    for (k = 1; k <= N; k++) {


        for (j = k; j <= min(k+2,N); j++) {

            temp = 0;

            for (t = max_3(k - 2, j - 2, 1); t <= k - 1; t++) {
                temp += A[k - t + S][t - 1] * A[t - j + S][j - 1];
            }
            A[k - j + S][j - 1] = A[k - j + S][j - 1] - temp;
        }

        for (i = k + 1; i <= min(k+2,N); i++) {

            temp = 0;

            for (t = max_3(k - 2, i - 2, 1); t <= k - 1; t++) {
                temp += A[i - t + S][t - 1] * A[t - k + S][k - 1];
            }

            A[i - k + S][k - 1]= (A[i - k + S][k - 1] - temp) / A[S][k - 1];
        }
    }*/
    int i, j, k, t;
    int N=501,S=2;
    double temp;
    for (k = 1; k <= N; ++k) {
        for (j = k; j <= ((k + S) < N ? (k + S) : N); ++j) {
            temp=0;
            for (t = max_3(k - S, j - S, 1); t <= k - 1; ++t) {
                temp+= array[k - t + S][t-1] * array[t - j + S][j-1];
            }
            array[k-j+S][j-1]=array[k-j+S][j-1]-temp;
        }

        for (i = k + 1; i <= ((k + S) < N ? (k + S) : N); ++i) {
            temp=0;
            for (t = max_3(k - S, i - S, 1); t <= k - 1; ++t) {
                temp+= array[i - t + S][t-1] * array[t - k + S][k-1];
            }
            array[i - k + S][k-1] = (array[i - k + S][k-1] -temp)/ array[S][k-1];
        }

    }
}


void solve_LU(double array[5][501], double B[501]) {
    int i, t;

    for (i = 1; i < 501; ++i) {
        for (t = ((i - 2) > 0 ? i - 2 : 0); t <= i - 1; ++t) {
            B[i] -= array[i - t + 2][t] * B[t];
        }
    }
    B[500] = B[500] / array[2][500];
    for (i = 499; i >= 0; i--) {
        for (t = i + 1; t <= ((i + 2) < 500 ? i + 2 : 500); ++t) {
            B[i] -= array[i - t + 2][t] * B[t];
        }
        B[i] = B[i] / array[2][i];

    }

}

int max_3(int a, int b, int c) {
    int x;
    x = (a > b ? a : b);
    x = (x > c ? x : c);
    return x;
}

double fanmifa(double u[501], double array[5][501], double p) {
    int i, j, t;
    double a, b, c, d, e;
    double y[501];
    double yy[501];
    for (i = 0; i < 501; ++i) {
        u[i] = 1;
    }
    for (j = 0; j < 501; ++j) {
        array[2][i] = array[2][i] - p;
    }
    doolittle(array);
    c = 0;
    while (1) {
        a = 0, b = 0, d = 0, e = 0;
        //求 a = ηk-1 的值

        for (i = 0; i < 501; ++i) {
            a = a + u[i] * u[i];
        }
        a = sqrt(a);
        //求 yk-1 的值
        for (i = 0; i < 501; ++i) {
            y[i] = u[i] / a;
        }
        //求 uk

        yy[0] = y[0];


        for (i = 1; i < 501; ++i) {
            for (t = ((i - 2) > 0 ? i - 2 : 0); t <= i - 1; ++t) {
                d += C[i - t + 2][t] * yy[t];
            }
            yy[i] = y[i] - d;
            d = 0;
        }
        u[500] = yy[500] / C[2][500];
        for (i = 499; i >= 0; i--) {
            for (t = i + 1; t <= ((i + 2) < 500 ? i + 2 : 500); ++t) {
                e += C[i - t + 2][t] * u[t];
            }
            u[i] = (yy[i] - e) / C[2][i];
            e = 0;

        }
        for (i = 0; i < 501; ++i) {
            b = b + y[i] * u[i];
        }

        if (fabs((b - c) / b) <= E) {//bb 表示前一个b的值
            break;
        }
        c = b;
    }
    return (1 / b);
}
