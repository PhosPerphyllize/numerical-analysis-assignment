#include<iostream>
#include<string>
#include<cstdlib>

#include"../include/mat.h"
#include"../include/glo.h"
using std::cin;  using std::cout;  using std::endl;  using std::flush;  using std::string;

double & Mat::operator()(const int i, const int j){
//Mat(i,j) 输出访问对象
    if(i<=0||i>this->rnum||j<=0||j>this->cnum){
        std::cout << name << "(i,j) error: overstep when reading, i,j<0 or >num." << endl;
        exit(1);
    }
    return *(this->p + (i-1)*cnum + (j-1));
}
Mat& Mat::operator=(const Mat &rhs){
    if(this==&rhs)
        return *this;
    this->rnum = rhs.rnum;
    this->cnum = rhs.cnum;
    if( rnum*cnum!=(rhs.rnum)*(rhs.cnum) ){
        delete [] this->p;
        this->p=NULL;
        if(rhs.rnum==0||rhs.cnum==0){
            cout << name << " = " << rhs.name << " wanning: rhs is empty." << endl;
            return *this;
        }
        this->p = new double[rnum*cnum];
        if( this->p==NULL ){
            std::cout << name << " = " << rhs.name << " error: Memory sign failed when recreates Mat. " << endl;
            exit(1);
        }
    }
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=cnum; j++)
            *(this->p + i*cnum + j) = *(rhs.p + i*cnum +j);
    }
    return *this;
}
Mat Mat::operator+(const Mat &rhs){     //矩阵+矩阵 数加
    if(rnum!=rhs.rnum||cnum!=rhs.cnum){
        std::cout << this->name << " + " << rhs.name << " error: two Mat not match." << endl;
        exit(1);
    }
    if(rnum<=0||cnum<=0){
        std::cout << this->name << " + " << rhs.name << " error:" << name << ".num <=0" << endl;
        exit(1);
    }
    Mat temp("temp(mat+mat)", rnum, cnum);
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=cnum; ++j){
            *(temp.p + i*cnum + j) = *(this->p + i*cnum + j) + *(rhs.p + i*cnum + j);
        }
    }
    return temp;  // 注意内部有指针，需要深复制
}
Mat Mat::operator-(const Mat &rhs){     //矩阵-矩阵 数减
    if(rnum!=rhs.rnum||cnum!=rhs.cnum){
        std::cout << this->name << " - " << rhs.name << " error: two Mat not match." << endl;
        exit(1);
    }
    if(rnum<=0||cnum<=0){
        std::cout << this->name << " - " << rhs.name << " error:" << name << ".num <=0" << endl;
        exit(1);
    }
    Mat temp("temp(mat-mat)", rnum, cnum);
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=cnum; ++j){
            *(temp.p + i*cnum + j) = *(this->p + i*cnum + j) - *(rhs.p + i*cnum + j);
        }
    }
    return temp;  // 注意内部有指针，需要深复制
}
Mat Mat::operator*(const Mat &rhs){     //矩阵乘法 矩阵*矩阵
    if(cnum!=rhs.rnum){
        std::cout << this->name << " * " << rhs.name << " error: two Mat not match." << endl;
        exit(1);
    }
    if(rnum<=0||cnum<=0){
        std::cout << this->name << " * " << rhs.name << " error:" << name << ".num <=0" << endl;
        exit(1);
    }
    Mat temp("temp(mat*mat)", rnum, rhs.cnum);
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=rhs.cnum; ++j){
            *(temp.p + i*temp.cnum + j) = 0;
            for(int t=0; t!=cnum; ++t){
                *(temp.p + i*temp.cnum + j) += *(this->p + i*cnum + t) * (*(rhs.p + t*rhs.cnum + j));
            }  
        }
    }
    return temp;  // 注意内部有指针，需要深复制
}
Mat Mat::operator*(const double &rhs){     //矩阵乘上数 每一个元素乘上数
    if(rnum<=0||cnum<=0){
        std::cout << name << " * " << rhs << " error: " << this->name << ".num <= 0." << endl;
        exit(1);
    }
    Mat temp("temp(mat*num)", rnum, cnum);
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=cnum; ++j){
        *(temp.p + i*cnum + j) = *(this->p + i*cnum + j) * rhs; 
        }
    }
    return temp;  // 注意内部有指针，需要深复制
}
Vec Mat::operator*(const Vec &rhs){     //矩阵乘上向量，输出向量
    if(this->cnum!=rhs.num){
        std::cout << this->name << " * " << rhs.name << " error: num not match." << endl;
        exit(1);
    }
    if(rnum<=0||cnum<=0){
        std::cout << this->name << " * " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    Vec temp("temp(mat*vec)",rnum);
    for(int i=0; i!=rnum; ++i){
        *(temp.p + i) = 0;
        for(int t=0; t!=rhs.num; ++t){
            *(temp.p + i) += *(this->p + i*cnum + t) * (*(rhs.p + t));
        }
    }
    return temp;  // 注意内部有指针，需要深复制
}