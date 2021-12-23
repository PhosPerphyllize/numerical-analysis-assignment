#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>

#include"../include/mat.h"
#include"../include/glo.h"
using std::cin;  using std::cout;  using std::endl;  using std::flush;  using std::string;

extern const double e_compare_error;

std::ostream & operator<<(std::ostream &os, const Mat &mat){
    for(int i=0; i!=mat.rnum; ++i){
        for(int j=0; j!=mat.cnum; ++j){
            if( Abs(*(mat.p + i*mat.cnum +j))<e_compare_error*10e5 )
                *(mat.p + i*mat.cnum +j) = 0;
            os << std::setw(20) << std::setiosflags(std::ios::scientific) << std::setprecision(12) << *(mat.p + i*mat.cnum +j) << " "; 
        }
        os << '\n';
    }
    return os;
}
Mat::Mat(string name, int rnum, int cnum){
    this->name = name;
    this->rnum = rnum;
    this->cnum = cnum;
    if(rnum<=0||cnum<=0){
        cout << "Mat " << name << "(name,rnum,cnum) warnning: try to create a Mat with 0 rnum or cnum. " << endl;
        this->p = NULL;
    }
    else{
        this->p = new double[rnum*cnum];
        if(this->p==NULL){
            std::cout << "Mat " << name << "(name,rnum,cnum) error: Memory sign failed when creates Mat. " << endl;
            exit(1);
        }
    }
    this->init(0);  
}
Mat::~Mat(){
    // cout << "try to delete Mat: " << name << endl;
    this->rnum = 0;
    this->cnum = 0;
    delete [] this->p;
    this->p = NULL;
}
Mat& Mat::init(const double value){
// 输入value值，将this矩阵全部值赋值value, 并返回该矩阵值
    if(this->rnum<=0||this->cnum<=0){
        std::cout << this->name << ".init(" << value << ") error: rnum or cnum <= 0." << endl;
        exit(1);
    }
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=cnum; ++j)
            *(this->p + i*cnum + j) = value;
    } 
    return *this;
}
Mat Mat::tranPosition(){
    Mat temp("temp(mat.tranPosition)", cnum, rnum);
    for(int i=0; i!=rnum; ++i){
        for(int j=0; j!=cnum; ++j)
            *(temp.p + j*rnum +i) = *(p + i*cnum +j);
    }
    return temp;  // 注意内部有指针，需要深复制
}
Vec Mat::takeRow(const int i){
    if(i<=0||i>rnum){
        cout << name << ".takeRow(i) error: i<=0 or >rnum." << endl;
        exit(1);
    }
    Vec temp("temp(mat.takeRow)", cnum);
    for(int j=0; j!=cnum; ++j)
       *(temp.p+j) = *(this->p + (i-1)*cnum + j);
    return temp;  // 注意内部有指针，需要深复制
}
Vec Mat::takeCol(const int j){
    if(j<=0||j>cnum){
        cout << name << ".takeCol(j) error: j<=0 or >rnum." << endl;
        exit(1);
    }
    Vec temp("temp(mat.takeCol)", rnum);
    for(int i=0; i!=rnum; ++i)
       *(temp.p+i) = *(this->p + i*cnum + (j-1));
    return temp;  // 注意内部有指针，需要深复制
}
Mat& Mat::swapLine(const int i1, const int i2){
    if(rnum<=0||cnum<=0){
        cout << name << ".swapLine(i1,i2) error: this.num<=0." << endl;
        exit(1);
    }
    if(i1<1||i1>rnum||i2<1||i2>rnum){
        cout << name << ".swapLine(i1,i2) error: i1,i2 <0 or >num." << endl;
        exit(1);
    }
    double temp;
    for(int t=0; t!=cnum; t++){
        temp = *(this->p + (i1-1)*cnum +t);
        *(this->p + (i1-1)*cnum +t) = *(this->p + (i2-1)*cnum +t);
        *(this->p + (i2-1)*cnum +t) = temp;
    }
    return *(this);
}
Mat Mat::replaceRow(const Vec &vec_in, const int i){
// 替代矩阵第i行
    if(cnum!=vec_in.num){
        cout << name << ".replaceRow("<< vec_in.name <<"," << i <<") error: mat and vec not match." << endl;
        exit(1);
    }
    if(i<=0||i>rnum){
        cout << name << ".replaceRow("<< vec_in.name <<"," << i <<") error: input i<=0 or >rnum." << endl;
        exit(1);
    }
    Mat temp("temp(replaceRow)",rnum, cnum);
    for(int m=0; m<rnum; m++){
        for(int n=0; n<cnum; n++)
            *(temp.p + m*cnum + n) = *(p + m*cnum + n);
    }
    for(int t=0; t!=cnum; ++t){
        *(temp.p + (i-1)*cnum + t) = *(vec_in.p+t);
    }
    return temp;   // 返回对象内含指针
}  
Mat Mat::replaceCol(const Vec &vec_in, const int j){
// 替代矩阵第j列
    if(rnum!=vec_in.num){
        cout << name << ".replaceCol("<< vec_in.name <<"," << j <<") error: mat and vec not match." << endl;
        exit(1);
    }
    if(j<=0||j>cnum){
        cout << name << ".replaceCol("<< vec_in.name <<"," << j <<") error: input j<=0 or >cnum." << endl;
        exit(1);
    }
    Mat temp("temp(replaceCol)",rnum, cnum);
    for(int m=0; m<rnum; m++){
        for(int n=0; n<cnum; n++)
            *(temp.p + m*cnum + n) = *(p + m*cnum + n);
    }
    for(int t=0; t!=rnum; ++t){
        *(temp.p + t*cnum + j-1) = *(vec_in.p+t);
    }
    return temp;   // 返回对象内含指针
}