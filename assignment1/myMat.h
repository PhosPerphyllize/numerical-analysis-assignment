#ifndef _MYMAT_H_
#define _MYMAT_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct Mat
{
    double* p_mat;  //矩阵首地址
    int flag;      //矩阵类型，0-普通矩阵， 1-带状矩阵（压缩模式）
    int num;       //大小（方阵）
    int row_num;    //行数
    int col_num;    //列数
    int s_col;    //带状矩阵的上半带宽，不是带状则为num-1
    int r_row;    //带状矩阵的下半带宽，不是带状则为num-1
};

struct Vec
{
    double* p_vec;  //向量地址
    int num;      //向量元素个数
};
//将来可以将Vec归类为Mat,统一

double RandTime(double min, double max);   //返回min-max的随机值，以时间为随机种子
int Max3(int a, int b, int c);      //返回3个数max
int Min3(int a, int b, int c);      //返回3个数min
double Abs(double a);           //求绝对值

struct Mat MatNullInit(int flag);     //Mat置零
int MatPrint(struct Mat mat);         //打印矩阵
struct Mat MatCopy(struct Mat mat);   //矩阵复制
struct Mat MatPlusE(struct Mat mat, double plus_num);   //矩阵与单位阵相加
double MatDiagMuti(struct Mat mat);         //矩阵对角元素相乘
struct Vec MatMutiVec(struct Mat mat, struct Vec vec);   //矩阵与向量相乘

struct Vec VecRandInit(int num, double buttom, double top);  //向量的随机初始化
int VecPrint(struct Vec vec);          //打印向量
struct Vec VecCopy(struct Vec vec);    //向量复制
struct Vec VecMutiNum(struct Vec v, double alpha);         //向量的数乘
double VecDotProduVec(struct Vec vec1, struct Vec vec2);   //向量与向量的点乘
double VecNorm2(struct Vec vec);        //向量求二范数

double AzipShow(struct Mat mat, int i, int j);      //带状压缩矩阵访问
int AzipChange(struct Mat mat, int i, int j, double value);     //带状压缩矩阵修改
struct Mat AzipDeCompress(struct Mat azip);         //带状矩阵解压缩

struct Mat LUDeposit(struct Mat mat);       //对输入矩阵进行LU分解，输出LU分解的矩阵（上三角下三角合一起）
struct Vec LUBackSub(struct Mat mat, struct Vec vec);   //输入LU分解矩阵，与解向量，输出求解向量

int Max3(int a, int b, int c)
{
    if(a>b)
        return (a>c)?a:c;
    else
        return (b>c)?b:c;
}

int Min3(int a, int b, int c)
{
    if(a<b)
        return (a<c)?a:c;
    else
        return (b<c)?b:c;
}

double Abs(double a)
{
    if(a>0)
        return a;
    else
        return -a;
}

int MatPrint(struct Mat mat)
{
    for(int i=0; i<mat.row_num; i++)
    {
        for(int j=0; j<mat.col_num; j++)
        {
            printf("%f ", (double)*(mat.p_mat+i*mat.col_num+j));
        }
        putchar('\n');
    }

    return 0;
}

int VecPrint(struct Vec vec)
{
    for (int j = 0; j < vec.num; j++)
    {
        printf("%f ", (double)*(vec.p_vec + j));
    }
    putchar('\n');
    return 0;
}

double AzipShow(struct Mat mat, int i, int j)
//输入的i，j从0开始
{
    if(mat.flag!=1)
    {
        printf("AzipShow error:input type error.\n");
        exit(1);
    }
    if(i<0||j<0||i>=mat.num||j>=mat.num)
    {
        printf("AzipShow error:i or j overstep.\n");
        exit(1);
    }
    if((i-j+mat.s_col)>=(mat.s_col+mat.r_row+1)||(i-j+mat.s_col)<0)
    {
        printf("AzipShow warning:try to read over bank.\n");
        return 0;
    }

    return *(mat.p_mat+(i-j+mat.s_col)*mat.num+j);
}

int AzipChange(struct Mat mat, int i, int j, double value)
//输入的i，j从0开始
{
    if(mat.flag!=1)
    {
        printf("AzipChange error:input type error.\n");
        exit(1);
    }
    if(i<0||j<0||i>=mat.num||j>=mat.num)
    {
        printf("AzipChange error:i or j overstep.\n");
        exit(3);
    }
    if((i-j+mat.s_col)>=(mat.s_col+mat.r_row+1)||(i-j+mat.s_col)<0)
    {
        printf("AzipChange error:write over bank.\n");
        exit(4);
    }
    *(mat.p_mat+mat.num*(i-j+mat.s_col)+j) = value;
    return 0;
}

struct Mat AzipDeCompress(struct Mat azip)
{
    if(azip.flag!=1)
    {
        printf("AzipDeCompress error: input matrix type error.\n");
        exit(1);
    }
    struct Mat output;
    output.flag=0;
    output.num = azip.num;
    output.col_num = azip.num, output.row_num = azip.num;
    output.r_row = output.row_num, output.s_col = output.col_num; 
    if ((output.p_mat = (double *)malloc(output.num * output.num * sizeof(double))) == NULL)
    {
        printf("Memory sign fail: AzipDeCompress output.\n");
        exit(1);
    }
    for(int i=0; i<output.row_num; i++)
    {
        for(int j=0; j<output.col_num; j++)
        {
            *(output.p_mat + i*output.col_num + j) = AzipShow(azip, i, j);
        }
    }
    return output;
}

struct Mat MatNullInit(int flag)
{
    struct Mat mat;
    mat.flag = flag;
    mat.num = 0;
    mat.col_num = 0, mat.row_num = 0;
    mat.r_row = 0, mat.s_col = 0;
    mat.p_mat = NULL;

    return mat;
}

double MatDiagMuti(struct Mat mat)
//返回矩阵的对角线元素相乘之积
{
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("PowerMeth error: matrix input type error.\n");
        exit(1);
    }
    if(mat.col_num!=mat.row_num&&mat.flag!=1)
    {
        printf("MatDiagMuti error: matrix input shuold be square or azip.\n");
        exit(1);
    }

    double output=1;
    int i=0;
    
    if(mat.flag==0)
    {
        for(i=0,output=1; i<mat.num; i++)
        {
            output = output * (*(mat.p_mat + i * mat.col_num +i));
        }
    }
    if(mat.flag==1)
    {
        for(i=0,output=1; i<mat.num; i++)
        {
            output = output * (*(mat.p_mat + mat.s_col * mat.col_num +i));
        }
    }

    return output;
}//double MatDiagMuti(struct Mat mat)

struct Vec MatMutiVec(struct Mat mat, struct Vec vec)
//矩阵输入可为普通矩阵，也可为带状压缩矩阵
//注意该函数malloc新的向量，迭代时注意free
{
    if(mat.num!=vec.num)
    {
        printf("MatMutiVec error: mat vec not match.\n");
        exit(1);
    }
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("MatMutiVec error: matrix type(mat.flag).\n");
        exit(1);
    }

    double *v_new = NULL;
    struct Vec v;
    v.num = 0;
    v.p_vec=NULL;

    if (mat.flag == 0)
    //正常矩阵
    {
        
        if ((v_new = (double *)malloc(mat.row_num * sizeof(double))) == NULL)
        {
            printf("Memory sign fail:MatMutiVec v_new.\n");
            exit(1);
        }
        v.num = mat.col_num;

        int i=0, j=0;
        double sum=0;
        for (i=0; i < mat.row_num; i++)
        {
            for (j=0, sum=0; j < vec.num; j++)
            {
                sum += *(mat.p_mat+i*mat.col_num+j) * (*(vec.p_vec+j));
            }
            *(v_new + i) = sum;
        }
    }

    if(mat.flag == 1)
    //带状矩阵
    {
        //当边条中间便密，无法分成三种情况，未加判断。
        if(mat.r_row > (mat.num-mat.s_col-1))
        {
            printf("MatMutiVec error: mat too dense.\n");
            exit(1);
        }

        if ((v_new = (double *)malloc(mat.num * sizeof(double))) == NULL)
        {
            printf("Memory sign fail:MatMutiVec v_new.\n");
            exit(1);
        }
        v.num = mat.num;

        int i=0,j=0;
        double sum=0;
        for(i=0; i<=mat.r_row-1; i++)
        {
            for (j=0, sum=0; j<=mat.s_col+i; j++)
            {
                sum += AzipShow(mat,i,j) * (*(vec.p_vec+j));
            }
            *(v_new + i) = sum;
        }

        for(i=mat.r_row; i<=vec.num-mat.s_col-1; i++)
        {
            for (j=i-mat.r_row, sum=0; j<=mat.s_col+i; j++)
            {
                sum += AzipShow(mat,i,j) * (*(vec.p_vec+j));
            }
            *(v_new + i) = sum;
        }

        for(i=vec.num-mat.s_col; i<=vec.num-1; i++)
        {
            for (j=i-mat.r_row, sum=0; j<=vec.num-1; j++)
            {
                sum += AzipShow(mat,i,j) * (*(vec.p_vec+j));
            }
            *(v_new + i) = sum;
        }
    }

    v.p_vec = v_new;

    return v;
}//double* MatMutiVec(struct Mat mat, struct Vec vec)

double VecNorm2(struct Vec vec)
{
    double sum = 0;
    for(int i=0; i<vec.num; i++)
    {
        sum += *(vec.p_vec+i) * (*(vec.p_vec+i));
    }
    sum = sqrt(sum);
    return sum;
}

double VecDotProduVec(struct Vec vec1, struct Vec vec2)
{
    if(vec1.num!=vec2.num)
    {
        printf("VecDotProduVec error: vector not match.\n");
        exit(1);
    }
    double output=0;
    int i=0;
    for (i = 0, output = 0; i < vec1.num; i++)
    {
        output += *(vec1.p_vec + i) * (*(vec2.p_vec + i));
    }
    return output;
}

struct Vec VecMutiNum(struct Vec v, double alpha)
//注意该函数无free， 使用时注意外部free
{
    struct Vec v_new;
    if( (v_new.p_vec=(double*)malloc(v.num*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:VecMutiNum v_new.\n");
        exit(1);
    }
    v_new.num = v.num;

    for(int i=0; i<v.num; i++)
    {
        *(v_new.p_vec+i) = *(v.p_vec+i) * alpha;
    }

    return v_new;
}//struct Vec VecMutiNum(struct Vec v, long double alpha)

double RandTime(double min, double max)
{
    int digit = 1e3;
    // srand((unsigned int)time(0));//修改种子
    int a = rand();              //注意rand()返回int类型
    return ( (a%digit)*1.0/digit * (max-min) + min );
}

struct Vec VecRandInit(int num, double buttom, double top)
//随机初始化，值在buttom与top间均匀分布
{
    struct Vec v;
    if( (v.p_vec=(double*)malloc(num*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:VecRandInit v.\n");
        exit(1);
    }
    v.num=num;

    srand((unsigned int)time(0));
    for(int i=0; i<num; i++)
    {
        *(v.p_vec+i)= RandTime(buttom, top);
    }

    return v;
}//struct Vec VecRandInit(int num, double buttom, double top)

struct Mat MatCopy(struct Mat mat)
{
    struct Mat output;
    if( (output.p_mat=(double*)malloc(mat.col_num*mat.row_num*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:MatCopy output.\n");
        exit(1);
    }
    output.flag = mat.flag;
    output.num = mat.num;
    output.col_num = mat.col_num, output.row_num = mat.row_num;
    output.r_row = mat.r_row, output.s_col = mat.s_col;

    for(int i=0; i<mat.row_num; i++)
    {
        for(int j=0; j<mat.col_num; j++)
        {
            *(output.p_mat + i * output.col_num +j) = *(mat.p_mat + i * mat.col_num + j); 
        }
    }

    return output;
}//struct Mat MatCopy(struct Mat mat)

struct Vec VecCopy(struct Vec vec)
{
    struct Vec output;
    if( (output.p_vec=(double*)malloc(vec.num*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:VecCopy output.\n");
        exit(1);
    }
    output.num = vec.num;

    for(int i=0; i<output.num; i++)
    {
        *(output.p_vec + i) = *(vec.p_vec + i);
    }

    return output;
}

struct Mat LUDeposit(struct Mat mat)
//注意LU分解后会多出一个malloc的矩阵，迭代时记得free
{
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("LUDeposit error: matrix input type error.\n");
        exit(1);
    }
    if(mat.col_num!=mat.row_num&&mat.flag!=1)
    {
        printf("LUDeposit error: matrix input shuold be square or azip.\n");
        exit(1);
    }

    struct Mat output=MatCopy(mat);

    int i = 0, j = 0, k = 0, t = 0, n_cur = 0; //n_cur:已经执行到的对角元素
    double *temp = NULL;
    if ((temp = (double *)malloc(2 * sizeof(double))) == NULL)
    {
        printf("Memory sign fail: LUDeposit temp.\n");
        exit(1);
    }

    if (mat.flag == 0)
    //普通矩阵LU,不选主元
    {
        double *A = output.p_mat;
        int N = output.num;

        // 第一行 第一列填入
        for (i = 1; i < N; i++)
        {
            *(A + i * N) /= *A;  //第一列表达式，第一行等于本身
        }
        int k_max = 0;
        for (n_cur = 1; n_cur < N; n_cur++)
        {
            //计算各个l，u值
            for (j = n_cur; j < N; j++)
            {
                for (t = 0, *temp = 0; t <= n_cur - 1; t++)
                {
                    *temp += *(A + n_cur * N + t) * (*(A + t * N + j));
                }
                *(A + n_cur * N + j) -= *temp;
            }
            for (i = n_cur + 1; i < N; i++)
            {
                for (t = 0, *temp = 0; t <= n_cur - 1; t++)
                {
                    *temp += *(A + i * N + t) * (*(A + t * N + n_cur));
                }
                *(A + i * N + n_cur) = (*(A + i * N + n_cur) - *temp) / (*(A + n_cur * N + n_cur));
            }
        }
    }

    if (mat.flag == 1)
    //边条LU
    {
        int s_column = output.s_col, r_row = output.r_row;
        int N = output.num;

        for (n_cur = 0; n_cur <= N - 1; n_cur++)
        {
            for (j = n_cur; j <= Min3(n_cur + s_column, N - 1, N - 1); j++)
            {
                for (t = Max3(0, n_cur - r_row, j - s_column), *temp = 0; t <= n_cur - 1; t++)
                {
                    *temp += AzipShow(output, n_cur, t) * AzipShow(output, t, j);
                }
                *(temp + 1) = AzipShow(output, n_cur, j) - *temp;
                AzipChange(output, n_cur, j, *(temp + 1));
            }
            for (i = n_cur + 1; i <= Min3(n_cur + r_row, N - 1, N - 1); i++)
            {
                if (n_cur >= N - 1)
                    break;

                for (t = Max3(0, i - r_row, n_cur - s_column), *temp = 0; t <= n_cur - 1; t++)
                {
                    *temp += AzipShow(output, i, t) * AzipShow(output, t, n_cur);
                }
                if (AzipShow(output, n_cur, n_cur) == 0)
                {
                    printf("LUDeposit error: Matrix maybe singular(BandMatrix input).\n");
                    exit(1);
                }
                *(temp + 1) = (AzipShow(output, i, n_cur) - *temp) / AzipShow(output, n_cur, n_cur);
                AzipChange(output, i, n_cur, *(temp + 1));
            }
        }
    }

    free(temp);
    return output;
}//struct Mat LUDeposit(struct Mat mat)

struct Vec LUBackSub(struct Mat mat, struct Vec vec)
//多malloc一个output 迭代时注意
{
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("LUBackSub error: matrix input type error.\n");
        exit(1);
    }
    if(mat.col_num!=mat.row_num&&mat.flag!=1)
    {
        printf("LUBackSub error: matrix input shuold be square or azip.\n");
        exit(1);
    }
    if(mat.num!=vec.num)
    {
        printf("LUBackSub error: matrix and vector not match.\n");
        exit(1);
    }

    struct Vec output;
    if( (output.p_vec=(double*)malloc(vec.num*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:LUBackSub x.\n");
        exit(1);
    }
    output.num = vec.num;

    double *temp=NULL;
    if( (temp=(double*)malloc(2*sizeof(double)))==NULL )
    {
        printf("Memory sign fail:LUBackSub temp.\n");
        exit(1);
    }

    if (mat.flag == 0)
    //普通矩阵
    {
        double *A = mat.p_mat;
        double *b = vec.p_vec;
        double *x = output.p_vec;
        int N = mat.num;
        int i=0, j=0, t=0;


        double *y = NULL;
        if ((y = (double *)malloc(N * sizeof(double))) == NULL)
        {
            printf("Memory sign fail:y.\n");
            exit(1);
        }

        *y=*b;
        for(i=1;i<N;i++)
        {
            for(t=0,*temp=0;t<=i-1;t++)
            {
                *temp += *(A+i*N+t) * (*(y+t));
            }
            *(y+i) = *(b+i) - *temp;
        }
        *(x+N-1)=*(y+N-1)/(*(A+N*(N-1)+N-1));
        for(i=N-2;i>=0;i--)
        {
            for(t=i+1,*temp=0;t<=N-1;t++)
            {
                *temp += *(A+i*N+t) * (*(x+t));
            }
            *(x+i) = (*(y+i)-*temp)/(*(A+i*N+i));
        }
        free(y);
    }//if (mat.flag == 0)

    if(mat.flag==1)
    {
        int N=mat.num;
        double *b = vec.p_vec;
        double *x = output.p_vec;
        int i=0, j=0, t=0;

        int r_row=mat.r_row, s_column=mat.s_col;

        double *y=NULL;
        if( (y=(double*)malloc(N*sizeof(double)))==NULL )
        {
            printf("Memory sign fail:y.\n");
            exit(2);
        }
        *y=*b;

        for(i=1;i<=N-1;i++)
        {
            for(t=Max3(0,i-r_row,0),*temp=0;t<=i-1;t++)
            {
                *temp += AzipShow(mat,i,t)* (*(y+t));
            }
            *(y+i) = *(b+i) - *temp;
        }
        *(x+N-1) = (*(y+N-1))/AzipShow(mat,N-1,N-1);
        for(i=N-2;i>=0;i--)
        {
            for(t=i+1,*temp=0;t<=Min3(i+s_column,N-1,N-1);t++)
            {
                *temp += AzipShow(mat,i,t)* (*(x+t));
            }
            *(x+i) = (*(y+i) - *temp)/ AzipShow(mat,i,i);
        }
        free(y);
    }//if(mat.flag==1)

    free(temp);
    return output;
}//struct Vec LUBackSub(struct Mat mat, struct Vec b)

struct Mat MatPlusE(struct Mat mat, double plus_num)
//矩阵对角线上元素统一增大减少, A-lamda*E
//注意矩阵被扩展，迭代注意free
{
    if(mat.flag!=0&&mat.flag!=1)
    {
        printf("MatPlusE error: matrix input type error.\n");
        exit(1);
    }
    if(mat.col_num!=mat.row_num&&mat.flag!=1)
    {
        printf("MatPlusE error: matrix input shuold be square or azip.\n");
        exit(1);
    }

    struct Mat output;
    output = MatCopy(mat);

    if(output.flag==0)
    {
        for(int i=0; i<output.num; i++)
        {
            *(output.p_mat + i * output.col_num + i) += plus_num;
        }
    }
    if(output.flag==1)
    {
        for(int i=0; i<output.num; i++)
        {
            *(output.p_mat + output.s_col * output.col_num + i) += plus_num;
        }
    }

    return output;
}//struct Mat MatPlusE(struct Mat mat, double plus_num)

#endif//#ifndef _MYMAT_H_