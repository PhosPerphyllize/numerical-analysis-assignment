#ifndef __MAT_H_
#define __MAT_H_

class Mat;

#include"vec.h"
#include<string>
using std::string;

class Mat{
    friend class Vec;
    friend std::ostream & operator<<(std::ostream &os, const Mat &mat);   // 矩阵输出
public:  
    int rnum;      // 行数
    int cnum;      // 列数
    string name;   // 矩阵名字（调试输出用）

    Mat(string name, int rnum, int cnum);
    ~Mat();
    double& operator()(const int i, const int j);  // 利用mat(i,j)访问矩阵元素
    Mat& operator=(const Mat &rhs);     // 矩阵赋值
    Mat operator+(const Mat &rhs);      // 矩阵相加
    Mat operator-(const Mat &rhs);      // 矩阵相减
    Mat operator*(const Mat &rhs);      // 矩阵相乘
    Mat operator*(const double &rhs);   // 矩阵数乘
    Vec operator*(const Vec &rhs);      // 矩阵*向量

    Mat& init(const double value);  // 矩阵全部值初始化
    Mat tranPosition();     // 矩阵转置(不改变原矩阵)
    Mat& swapLine(const int i1, const int i2);  // 矩阵两行交换
    Vec takeRow(const int i);   // 取出矩阵i行返回
    Vec takeCol(const int j);   // 取出j列返回
    Mat replaceRow(const Vec &vec_in, const int i);  // 替代矩阵第i行(不改变原矩阵)
    Mat replaceCol(const Vec &vec_in, const int j);  // 替代矩阵第j列
protected:
    double *p;     // 矩阵储存首地址
};

#endif