#ifndef __GLO_H_
#define __GLO_H_

#include"mat.h"
#include"vec.h"

double Abs(const double value);
int Dou2Int(const double value);

Mat ReturnFdiff(Vec& vecx);
Vec ReturnF(Vec& vecx);
Vec SolveXY(double num_x, double num_y);  // 对于给定的方程组，输入一个x,y 返回u,t
double Lagra2d(Vec& vec_x, Vec& vec_y, Mat& mat_a, const double num_x, const double num_y);

Vec OneDimRegres(Vec &vec_x, const Vec &vec_y, const int x_pow_num);
Mat TwoDimRegres(Vec &vec_x, Vec &vec_y, Mat &mat_a, const int x_pow_num, const int y_pow_num);
double Fun2dRegres(const Mat& mat_c, const double x, const double y);
double Err2dRegres(Mat& mat_a, Mat& mat_c, Vec& vec_x, Vec& vec_y);


#endif