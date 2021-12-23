#ifndef __VEC_H_
#define __VEC_H_

class Vec;

#include"mat.h"
#include<string>
using std::string;

class Vec{
    friend class Mat;
    friend std::ostream & operator<<(std::ostream &os, const Vec &vec);     // 向量输出
public:
    int num;        // 向量个数
    string name;    // 向量名字

    Vec(string name, int num);
    ~Vec();
    double& operator()(const int n);    // 利用vec(i)访问向量元素
    Vec& operator=(const Vec &rhs);     // 向量赋值
    Vec operator+(const Vec &rhs);      // 向量加法
    Vec operator-(const Vec &rhs);      // 向量减法
    Mat operator%(const Vec &rhs);      // 向量乘法，输出矩阵 uT*v
    double operator*(const Vec &rhs);   // 向量点乘
    Vec operator*(const double &rhs);   // 向量数乘
    Vec operator/(const Mat &rhs);      // 求解线性方程组
    
    double norm2();     // 返回二范数
    Vec& init(const double value);  // 向量初始化为一个值
    Vec power(const int pow_num);   // 向量每个数指数运算（不改变原向量）
protected:
    double *p;      // 向量储存首地址
};

#endif