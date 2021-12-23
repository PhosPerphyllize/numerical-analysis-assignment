#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<iomanip>

#include"../include/vec.h"
#include"../include/glo.h"
using std::cin;  using std::cout;  using std::endl;  using std::flush;  using std::string;

std::ostream & operator<<(std::ostream &os, const Vec &vec){
    for(int i=0; i!=vec.num; ++i){
        os << std::setw(16) << std::setiosflags(std::ios::scientific) << std::setprecision(12) << *(vec.p+i) << ' ';
    }
    os << '\n';
    return os;
}
Vec::Vec(string name, int num){
    this->name = name;
    this->num = num;
    if(num<=0){
        cout << "Vec " << name << "(name,num) warnning: try to create a Vec with 0 rnum or cnum. " << endl;
        this->p = NULL;
    }
    else{
        this->p = new double[num];
        if( this->p==NULL ){
            std::cout << "Vec " << name << "(name,num) error: Memory sign failed when creates Vec. " << endl;
            exit(1);
        }
    }
    this->init(0); 
}
Vec::~Vec(){
    // cout << "try to delete Vec: " << name << endl;
    this->num = 0;
    delete [] this->p;
    this->p = NULL;
}
double Vec::norm2(){
    if(this->num<=0){
        std::cout << this->name << ".norm2() error: num <= 0.\n";
        exit(1);
    }
    double temp=0;
    for(int i=0; i!=num; ++i){
        temp += *(this->p + i) * (*(this->p + i));
    }
    return sqrt(temp);
}
Vec& Vec::init(double value){
    if(this->num<=0){
        std::cout << this->name << ".init(value) error: num <= 0.\n";
        exit(1);
    }
    for(int j=0; j!=num; ++j)
        *(this->p + j) = value;
    return *this;
}
Vec Vec::power(const int pow_num){
// 向量每个数指数运算（不改变原向量
    Vec temp("temp(power)", num);
    for(int i=0; i<num; ++i){
        *(temp.p+i) = pow(*(p+i),pow_num);
    }
    return temp;
}