#include"myMat.h"

#define MAT_NUM 501
#define S_COL 2
#define R_ROW 2

struct Mat Init(void);
double PowerMeth(struct Mat mat);
double InvPowerMeth(struct Mat mat);

const double g_e=2.718281828459045235360287471352662497757247093;
//  69995 95749 66967 62772 40766 30353 54759 45713 82178 52516 64274
const double epsilon=1e-12;
const double compare_error = 1e-7;

int main(void)
{
    struct Mat azip;
    azip=Init();

    //Question 1
    printf("======Question 1======\n");
    double lamda1=0,lamda501=0, lamda_temp=0, lamda_norm_max=0;

    lamda_norm_max = (double)PowerMeth(azip);
    lamda1 = lamda_norm_max;
    lamda501 = (double)PowerMeth(MatPlusE(azip,lamda_norm_max)) - lamda_norm_max;         //会malloc多一个矩阵，但不迭代对内存影响可忽略
    lamda_temp = (double)PowerMeth(MatPlusE(azip,-lamda_norm_max)) + lamda_norm_max;

    if(Abs(lamda1-lamda501)<compare_error)
        lamda501 = lamda_temp;
    if(lamda1 > lamda501)
    {
        lamda_temp = lamda1;
        lamda1 = lamda501;
        lamda501 = lamda_temp;
    }
    printf("lamda1 : %.12E\n",lamda1);
    printf("lamda501 : %.12E\n",lamda501);

    double lamda_norm_min = (double)InvPowerMeth(azip);
    printf("lamda_s (norm min): %.12E\n",lamda_norm_min);

    //Question 2
    printf("======Question 2======\n");
    double lamda_ik=0, miu_k=0;
    struct Mat azip_plus;
    azip_plus = MatNullInit(1);

    for(int k=1; k<=39; k++)
    {
        miu_k = lamda1 + k*(lamda501-lamda1)/40;

        free(azip_plus.p_mat);
        azip_plus.p_mat=NULL;
        azip_plus = MatPlusE(azip, -miu_k);
        lamda_ik = InvPowerMeth(azip_plus)+miu_k;
        printf("lamda_i%d: %.12E\n", k, lamda_ik);
    }
    free(azip_plus.p_mat);
    azip_plus=MatNullInit(0);

    //Question 3
    printf("======Question 3======\n");
    double cond_a2=0, det_a=0;

    //A为非奇异实对称阵
    cond_a2 = Abs(lamda_norm_max/lamda_norm_min);

    //A为方阵，det(A)=|A|=|L|*|U|
    struct Mat azip_lu;
    azip_lu = LUDeposit(azip);

    det_a = MatDiagMuti(azip_lu);

    free(azip_lu.p_mat);
    azip_lu=MatNullInit(1);

    printf("cond(A)2: %.12E\n",cond_a2);
    printf("det(A): %.12E\n", det_a);

    // printf("lamda1 : %.12E\n",(InvPowerMeth(MatPlusE(azip,-lamda1)) + lamda1));
    // printf("lamda501 : %.12E\n",(InvPowerMeth(MatPlusE(azip,-lamda501)) + lamda501));
    
    return 0;
}

struct Mat Init(void)
//输出的是压缩边条矩阵
{
    double *p_azip = NULL;
    if( (p_azip=(double*)malloc((1+S_COL+R_ROW)*MAT_NUM*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:Init() p_azip.\n");
        exit(1);
    }

    int i=0;
    double b = 0.16, c = -0.064;

    for(i=0;i<MAT_NUM;i++)
    {
        *(p_azip+i) = c;
        *(p_azip+MAT_NUM+i) = b;
        *(p_azip+2*MAT_NUM+i) = ( (1.64-0.024*(i+1))*sin(0.2*(i+1))-0.64*pow(g_e,0.1/(i+1)) );
        *(p_azip+3*MAT_NUM+i) = b;
        *(p_azip+4*MAT_NUM+i) = c;
    }

    *(p_azip)=0, *(p_azip+1)=0, *(p_azip+1*MAT_NUM)=0;
    *(p_azip+4*MAT_NUM-1)=0, *(p_azip+5*MAT_NUM-2)=0,  *(p_azip+5*MAT_NUM-1)=0;

    struct Mat azip;
    azip.num = MAT_NUM, azip.col_num = MAT_NUM, azip.row_num = 1+S_COL+R_ROW;
    azip.flag=1; 
    azip.r_row=R_ROW, azip.s_col=S_COL;
    azip.p_mat = p_azip;

    return azip;    
}//double* Init(void)

double PowerMeth(struct Mat mat)
//输入矩阵，根据幂法 输出最大特征值， 矩阵可为普通，也可为边条压缩
{
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("PowerMeth error: matrix input type error.\n");
        exit(1);
    }
    if(mat.col_num!=mat.row_num&&mat.flag!=1)
    {
        printf("PowerMeth error: matrix input shuold be square or azip.\n");
        exit(1);
    }

    struct Vec u;
    u = VecRandInit(mat.num,1,2);

    struct Vec y;
    y.num=u.num;
    y.p_vec=NULL;

    double ita=0, beta=0, beta_pre=0, beta_error=0;
    int i=0, step=0;

    while(step<6000)
    {
        ita = VecNorm2(u);

        free(y.p_vec);    //Null可以被free，注意双free
        y.p_vec=NULL;
        y = VecMutiNum(u,1/ita);

        free(u.p_vec);
        u.p_vec=NULL;
        u = MatMutiVec(mat,y);

        beta = VecDotProduVec(u,y);

        beta_error = Abs( (beta-beta_pre)/beta );
        if(beta_error<epsilon&&step>2)
        {
            printf("PowerMeth: epsilon is reached in step = %d.\n", step);
            return beta;
        }

        beta_pre = beta;
        step++;
    }

    printf("PowerMeth warnning: Max iteration step = %d is reached.\n", step);
    return beta;

}//double PowerMeth(struct Mat mat)

double InvPowerMeth(struct Mat mat)
{
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("InvPowerMeth error: matrix input type error.\n");
        exit(1);
    }   
    if(mat.col_num!=mat.row_num&&mat.flag!=1)
    {
        printf("InvPowerMeth error: matrix input shuold be square or azip.\n");
        exit(1);
    }

    struct Vec u;
    u = VecRandInit(mat.num,1,2);

    struct Vec y;
    y.num=u.num;
    y.p_vec=NULL;

    struct Mat mat_lu;
    mat_lu = LUDeposit(mat);

    double ita=0, beta=0, beta_pre=0, beta_error=0;
    int i=0, step=0;

    while(step<6000)
    {
        ita = VecNorm2(u);

        free(y.p_vec);    //Null可以被free，注意双free
        y.p_vec=NULL;
        y = VecMutiNum(u,1/ita);

        free(u.p_vec);
        u.p_vec=NULL;
        u = LUBackSub(mat_lu,y);

        beta = VecDotProduVec(u,y);

        beta = 1/beta;
        beta_error = Abs( (beta-beta_pre)/beta );
        if(beta_error < epsilon && step > 2)
        {
            printf("InvPowerMeth: epsilon is reached in step = %d.\n", step);
            return beta;
        }

        beta_pre = beta;
        step++;
    }

    printf("InvPowerMeth warnning: Max iteration step = %d is reached.\n", step);
    return beta;
}//long double InvPowerMeth(struct Mat mat)