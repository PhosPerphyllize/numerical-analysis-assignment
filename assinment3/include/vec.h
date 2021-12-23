#ifndef __VEC_H_
#define __VEC_H_

class Vec;

#include"mat.h"
#include<string>
using std::string;

class Vec{
    friend class Mat;
    friend std::ostream & operator<<(std::ostream &os, const Vec &vec);     // �������
public:
    int num;        // ��������
    string name;    // ��������

    Vec(string name, int num);
    ~Vec();
    double& operator()(const int n);    // ����vec(i)��������Ԫ��
    Vec& operator=(const Vec &rhs);     // ������ֵ
    Vec operator+(const Vec &rhs);      // �����ӷ�
    Vec operator-(const Vec &rhs);      // ��������
    Mat operator%(const Vec &rhs);      // �����˷���������� uT*v
    double operator*(const Vec &rhs);   // �������
    Vec operator*(const double &rhs);   // ��������
    Vec operator/(const Mat &rhs);      // ������Է�����
    
    double norm2();     // ���ض�����
    Vec& init(const double value);  // ������ʼ��Ϊһ��ֵ
    Vec power(const int pow_num);   // ����ÿ����ָ�����㣨���ı�ԭ������
protected:
    double *p;      // ���������׵�ַ
};

#endif