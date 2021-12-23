/*  Create: 2021.11.10 23:47        
*   Update: 2021.11.10 23:47
        未进行相关测试
    Update: 2021/11/11 23:35
        已完成所有代码的测试，运行正常
*/
#ifndef __MYCOM_H_
#define __MYCOM_H_

#include<iostream>
#include<cstdlib>
#include<cmath>
#include<string>
#include<iomanip>

using std::string;  using std::cout;  using std::endl;  using std::flush;

class Com;
class Comvec;

std::ostream & operator<<(std::ostream &os, const Com &com);
std::ostream & operator<<(std::ostream &os, const Comvec &comv);

class Com{
    friend std::ostream & operator<<(std::ostream &os, const Com &com);
public:
    double real;
    double imag;

    Com(const double real, const double imag);
    ~Com();
    Com operator-();
    Com operator=(const double &rhs);
    Com operator+(const double &rhs);
    Com operator-(const double &rhs);
    Com operator*(const double &rhs);

    Com operator+(const Com &rhs);
    Com operator-(const Com &rhs);
};
std::ostream & operator<<(std::ostream &os, const Com &com){
    os << "(" << com.real << "," << com.imag << ")";
    return os;
}

class Comvec{
    friend std::ostream & operator<<(std::ostream &os, const Comvec &comv);
public:
    double *p;
    int num;

    Comvec(const int num);
    ~Comvec();
    Com operator()(const int i);
    Com comVecChange(const int i, const Com input);
    Com comVecChange(const int i, const double input);
};
std::ostream & operator<<(std::ostream &os, const Comvec &comv){
    std::cout.precision(12);
    for(int i=0; i!=comv.num; ++i){
        os << "lamda"<< i+1 << ": ";
        if(*(comv.p+comv.num+i)==0)
            os << *(comv.p+i);
        else
            os << "(" << *(comv.p+i) << "," << *(comv.p+comv.num+i) << ")";
        os << "\n";
    }
    return os;
}

// ========= Com 方法 ===========
Com::Com(const double real, const double imag){
    this->real = real;
    this->imag = imag;
}
Com::~Com(){}
Com Com::operator=(const double &rhs){
    (*this) = Com(rhs,0);
    return *this;
}
Com Com::operator-(){
    return Com(-real, -imag);
}
Com Com::operator+(const double &rhs){
    return Com(real+rhs, imag);
}
Com Com::operator-(const double &rhs){
    return Com(real-rhs, imag);
}
Com Com::operator*(const double &rhs){
    return Com(real*rhs, imag*rhs);
}
Com Com::operator+(const Com &rhs){
    return Com(real+rhs.real, imag+rhs.imag);
}
Com Com::operator-(const Com &rhs){
    return Com(real-rhs.real, imag-rhs.imag);
}

// =========== Comvec 方法 ===========
Comvec::Comvec(const int num){
    if(num<0){
        cout << "Comvec create error: num input<0." << endl;
        exit(1);
    }
    if( (this->p=(double*)malloc(2*num*sizeof(double)))==NULL ){
        cout << "Memory sign failed when creates Comvec." << endl;
        exit(1);
    }
    this->num = num;
}
Comvec::~Comvec(){
    free(this->p);
    this->p =NULL;
}
Com Comvec::operator()(const int i){
    if(i<=0||i>num){
        cout << "Comvec(i) overstep when reading." << endl;
        exit(1);
    }
    Com temp(0,0);
    temp.real = *(this->p + i-1);
    temp.imag = *(this->p + num +i-1);
    return temp;
}
Com Comvec::comVecChange(const int i, const Com input){
    if(i<=0||i>num){
        cout << "comVecChange(i,value) overstep when changing." << endl;
        exit(1);
    }
    *(this->p + i-1) = input.real;
    *(this->p + num + i-1) = input.imag;
    return input;
}
Com Comvec::comVecChange(const int i, const double input){
    if(i<=0||i>num){
        cout << "comVecChange(i,value) overstep when changing." << endl;
        exit(1);
    }
    *(this->p + i-1) = input;
    *(this->p + num + i-1) = 0;
    return Com(input,0);
}
#endif