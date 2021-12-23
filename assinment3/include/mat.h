#ifndef __MAT_H_
#define __MAT_H_

class Mat;

#include"vec.h"
#include<string>
using std::string;

class Mat{
    friend class Vec;
    friend std::ostream & operator<<(std::ostream &os, const Mat &mat);   // �������
public:  
    int rnum;      // ����
    int cnum;      // ����
    string name;   // �������֣���������ã�

    Mat(string name, int rnum, int cnum);
    ~Mat();
    double& operator()(const int i, const int j);  // ����mat(i,j)���ʾ���Ԫ��
    Mat& operator=(const Mat &rhs);     // ����ֵ
    Mat operator+(const Mat &rhs);      // �������
    Mat operator-(const Mat &rhs);      // �������
    Mat operator*(const Mat &rhs);      // �������
    Mat operator*(const double &rhs);   // ��������
    Vec operator*(const Vec &rhs);      // ����*����

    Mat& init(const double value);  // ����ȫ��ֵ��ʼ��
    Mat tranPosition();     // ����ת��(���ı�ԭ����)
    Mat& swapLine(const int i1, const int i2);  // �������н���
    Vec takeRow(const int i);   // ȡ������i�з���
    Vec takeCol(const int j);   // ȡ��j�з���
    Mat replaceRow(const Vec &vec_in, const int i);  // ��������i��(���ı�ԭ����)
    Mat replaceCol(const Vec &vec_in, const int j);  // ��������j��
protected:
    double *p;     // ���󴢴��׵�ַ
};

#endif