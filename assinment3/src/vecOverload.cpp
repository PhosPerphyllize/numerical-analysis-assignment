#include<iostream>
#include<string>
#include<cstdlib>

#include"../include/vec.h"
#include"../include/glo.h"
using std::cin;  using std::cout;  using std::endl;  using std::flush;  using std::string;

extern const double e_step_comperr;

double& Vec::operator()(const int n){  //���� vec(n) ������ʶ���
    if(n<=0||n>num){
        std::cout << this->name << "("<< n << ") error: overstep when reading, n<0 or >num." << endl;
        exit(1);
    }
    return *(this->p + n-1);
}
Vec& Vec::operator=(const Vec &rhs){
    if(this==&rhs)
        return *this;
    if( num!=rhs.num ){
        this->num = rhs.num;
        delete [] this->p;
        this->p=NULL;
        if(rhs.num==0){
            cout << name << " = " << rhs.name << " wanning: rhs is empty." << endl;
            return *this;
        }
        this->p = new double[num];
        if( this->p==NULL ){
            std::cout << name << " = " << rhs.name << " error: Memory sign failed when recreates Mat. " << endl;
            exit(1);
        }
    }
    for(int j=0; j!=num; j++)
        *(this->p + j) = *(rhs.p + j);
    return *this;
}
Vec Vec::operator+(const Vec &rhs){  //�������������
    if(this->num!=rhs.num){
        std::cout << this->name << " + " << rhs.name << " error: num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " + " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    Vec temp("temp(vec+vec)", num);
    for(int i=0; i!=num; ++i){
        *(temp.p + i) = *(this->p + i) + *(rhs.p + i);
    }
    return temp;  // ע���ڲ���ָ�룬��Ҫ���
}
Vec Vec::operator-(const Vec &rhs){  //�������������
    if(this->num!=rhs.num){
        std::cout << this->name << " - " << rhs.name << " error: num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " - " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    Vec temp("temp(vec-vec)",num);
    for(int i=0; i!=num; ++i){
        *(temp.p + i) = *(this->p + i) - *(rhs.p + i);
    }
    return temp;  // ע���ڲ���ָ�룬��Ҫ���
}
Mat Vec::operator%(const Vec &rhs){  //������ת��*����  �������
    if(this->num!=rhs.num){
        std::cout << this->name << " % " << rhs.name << " error: num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " % " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    Mat temp("temp(vec\%vec)", num, num);
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; ++j){
            *(temp.p + i*num + j) = *(this->p + i) * (*(rhs.p + j));
        }   
    }
    return temp;  // ע���ڲ���ָ�룬��Ҫ���
}
double Vec::operator*(const Vec &rhs){  //����Vec*Vec �������
    if(this->num!=rhs.num){
        std::cout << this->name << " * " << rhs.name << " error: num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " * " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    double temp = 0;
    for(int i=0; i!=num; ++i){
        temp += *(this->p + i) * (*(rhs.p + i));
    }
    return temp;
}
Vec Vec::operator*(const double &rhs){  //����Vec*num ��������
    if(this->num<=0){
        std::cout << this->name << " error: num <= 0." << endl;
        exit(1);
    }
    Vec temp("temp(vec*num)",num);
    for(int i=0; i!=num; ++i){
        *(temp.p + i) = *(this->p + i) * rhs;
    }
    return temp;  // ע���ڲ���ָ�룬��Ҫ���
}

Vec Vec::operator/(const Mat &rhs){
    if(rhs.rnum!=rhs.cnum){
        cout << name << " / " << rhs.name << " error: num not square." << endl;
        exit(1);  
    }
    if(num!=rhs.cnum){
        cout << name << " / " << rhs.name << " error: num not match." << endl;
        exit(1);  
    }
    if(num<=0||rhs.cnum<=0){
        cout << name << " / " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    Vec vec_x("vec_x(vec/mat)",num), vec_b("vec_b(vec/mat)",num);
    vec_b = *(this);
    Mat mat_a("mat_a(vec/mat)", num, num);
    mat_a = rhs;
    int k=0, i=0, j=0, max_line_no=0;
    double temp=0, m_ik=0;
    for(k=1;k<=num-1;++k){
        temp=0;
        max_line_no=k;
        for(i=k; i<=num; i++){
            if( Abs(mat_a(i,k))>temp ){
                temp = Abs(mat_a(i,k));
                max_line_no = i;
            }
        }
        if(Abs(temp)<e_step_comperr)
            continue;
        if(max_line_no!=k){
            mat_a.swapLine(k,max_line_no);
            temp = vec_b(k);
            vec_b(k) = vec_b(max_line_no);
            vec_b(max_line_no) = temp;
        } // ѡ��Ԫ����
        for(i=k+1; i<=num; ++i){
            m_ik = mat_a(i,k)/mat_a(k,k);
            for(j=k; j<=num; ++j)
                mat_a(i,j) -= m_ik * mat_a(k,j);
            vec_b(i) -= m_ik * vec_b(k);
        }
        // cout << mat_a << endl;
    }
    for(k=num; k>=1; --k){
        for(temp=0,j=k+1; j<=num; j++)
                temp += mat_a(k,j)*vec_x(j);
        if(Abs(mat_a(k,k))<e_step_comperr){
            if(Abs(temp-vec_b(k))>e_step_comperr){
                cout << name << " / " << rhs.name << " error: rank(" << name << ")<num and vec input not match." << endl;
                exit(1);
            }
            vec_x(k)=1;
            continue;
        }
        vec_x(k) = (vec_b(k)-temp)/mat_a(k,k);
    }
    return vec_x;  // ע���ڲ���ָ�룬��Ҫ���
}
