/*  Create: 2021/11/03 17:14        
*   Update: 2021/11/03 23:55
        �Ѿ���������
    Update: 2021/11/09 23:35
        ����ת�ã���дMat.init()
    Update: 2021/11/11 23:35
        ��������д���Ĳ��ԣ���������
*/
#ifndef __MYMAT_H_
#define __MYMAT_H_

#include"basefun.h"

class Mat;
class Vec;
std::ostream & operator<<(std::ostream &os, const Mat &mat);
std::ostream & operator<<(std::ostream &os, const Vec &vec);
Mat OutputE(const int num);

class Mat{
    friend std::ostream & operator<<(std::ostream &os, const Mat &mat);   // �������
    friend Mat OutputE(const int num);  // ���ص�λ���� 
public:  
    int num;      // ����ά��
    double *p;    // ���󴢴��׵�ַ
    string name;  // �������֣���������ã�

    Mat(string name, int num);
    ~Mat();
    double & operator()(const int i, const int j);  // ����mat(i,j)���ʾ���Ԫ��
    Mat operator=(const Mat &rhs);      // ����ֵ
    Mat operator+(const Mat &rhs);      // �������
    Mat operator-(const Mat &rhs);      // �������
    Mat operator*(const Mat &rhs);      // �������
    Mat operator*(const double &rhs);   // ��������
    Vec operator*(const Vec &rhs);      // ����*����

    Mat init(double flag);  // ����ȫ��ֵ��ʼ��
    Mat initE();            // ������תΪ��λ��
    Mat tranPosition();     // ����ת��
    Mat lowDemi(const int low);     // ����ά
    Mat charLow2(const int tar, Com &root1, Com &root2);    // ��������½����������ֵ
    Mat swapLine(const int i1, const int i2);           // �������н���
protected:
};

std::ostream & operator<<(std::ostream &os, const Mat &mat){
    for(int i=0; i!=mat.num; ++i){
        for(int j=0; j!=mat.num; ++j){
            if( Abs(*(mat.p + i*mat.num +j))<g_compare_error*100000 )
                *(mat.p + i*mat.num +j) = 0;
            os << std::setw(16) << std::setprecision(12) <<  *(mat.p + i*mat.num +j) << " "; 
        }
        os << '\n';
    }
    return os;
}
Mat OutputE(const int num){
    if(num<=0){
        cout << "OutputE(num) error: num<=0." << endl;
        exit(1);
    }
    Mat temp("temp(OutputE)",num);
    temp.initE();
    return temp;
}

class Vec{
    friend std::ostream & operator<<(std::ostream &os, const Vec &vec);     // �������
public:
    int num;        // ��������
    int zero_num;   // ������ͷ 0 �ĸ���
    double *p;      // ���������׵�ַ
    string name;    // ��������

    Vec(string name, int num);
    ~Vec();
    double & operator()(const int n);   // ����vec(i)��������Ԫ��
    Vec operator=(const Vec &rhs);      // ������ֵ
    Vec operator+(const Vec &rhs);      // �����ӷ�
    Vec operator-(const Vec &rhs);      // ��������
    Mat operator%(const Vec &rhs);      // �����˷���������� uT*v
    double operator*(const Vec &rhs);   // �������
    Vec operator*(const double &rhs);   // ��������
    Vec operator/(const Mat &rhs);      // ������Է�����
    
    double norm2();     // ���ض�����
    Vec init(double flag);  // ������ʼ��Ϊһ��ֵ
protected:
};

std::ostream & operator<<(std::ostream &os, const Vec &vec){
    if(vec.zero_num > vec.num){
        std::cout << "os << " << vec.name << " error: zero_num > num." << std::endl;
        exit(1);
    }
    int i=0;
    for(i=0; i!=vec.zero_num; ++i){
        os << 0 << ' ';
    }
    for(i=vec.zero_num; i!=vec.num; ++i){
        os << *(vec.p+i) << ' ';
    }
    os << '\n';
    return os;
}

// ===========================Mat ��ķ�������=======================
Mat::Mat(string name, int num){
    this->num = num;
    this->name = name;
    if(num<=0){
        this->p = NULL;
    }
    else{
        if( (this->p=(double*)malloc(num*num*sizeof(double)))==NULL ){
            std::cout << "Mat " << name << "(name,num) error: Memory sign failed when creates Mat. " << endl;
            exit(1);
        }
    }  
}
Mat::~Mat(){
    cout << "try to free Mat: " << name << endl;
    free(this->p);
    this->p = NULL;
}
double & Mat::operator()(const int i, const int j){  //Mat(i,j) ������ʶ���
    if(i<=0||i>this->num||j<=0||j>this->num){
        std::cout << name << "(i,j) error: overstep when reading in, i,j<0 or >num." << endl;
        exit(1);
    }
    return *(this->p + (i-1)*this->num + (j-1));
}
Mat Mat::operator=(const Mat &rhs){
    if(this->num!=rhs.num){
        this->num = rhs.num;
        free(this->p);
        this->p=NULL;
        if(rhs.num==0){
            return *this;
        }
        if( (this->p=(double*)malloc(num*num*sizeof(double)))==NULL ){
            std::cout << name << " = rhs error: Memory sign failed when recreates Mat. " << endl;
            exit(1);
        }
    }
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; j++)
            *(this->p + i*num + j) = *(rhs.p + i*num +j);
    }
    return *this;
}
Mat Mat::operator+(const Mat &rhs){     //����+���� ����
// +-*����������ʱ����� (a+b)+c Ҳ�������ڴ�й©���⣬ϵͳ���Զ�������ɼ�����м����
    if(this->num!=rhs.num){
        std::cout << this->name << " + " << rhs.name << " error: two Mat num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " + " << rhs.name << " error:" << name << ".num <=0" << endl;
        exit(1);
    }
    Mat temp("temp",num);
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; ++j){
            *(temp.p + i*num + j) = *(this->p + i*num + j) + *(rhs.p + i*num + j);
        }
    }
    return temp;
}
Mat Mat::operator-(const Mat &rhs){     //����-���� ����
    if(this->num!=rhs.num){
        std::cout << this->name << " - " << rhs.name << " error: two Mat num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " - " << rhs.name << " error:" << name << ".num <=0" << endl;
        exit(1);
    }
    Mat temp("temp",num);
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; ++j){
            *(temp.p + i*num + j) = *(this->p + i*num + j) - *(rhs.p + i*num + j);
        }
    }
    return temp;
}
Mat Mat::operator*(const Mat &rhs){     //����˷� ����*����
    if(this->num!=rhs.num){
        std::cout << this->name << " * " << rhs.name << " error: two Mat num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << this->name << " - " << rhs.name << " error:" << name << ".num <=0" << endl;
        exit(1);
    }
    Mat temp("temp",num);
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; ++j){
            *(temp.p + i*num + j) = 0;
            for(int t=0; t!=num; ++t){
                *(temp.p + i*num + j) += *(this->p + i*num + t) * (*(rhs.p + t*num + j));
            }  
        }
    }
    return temp;
}
Mat Mat::operator*(const double &rhs){     //��������� ÿһ��Ԫ�س�����
    if(this->num<=0){
        std::cout << name << " * " << rhs << " error: " << this->name << ".num <= 0." << endl;
        exit(1);
    }
    Mat temp("temp",num);
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; ++j){
        *(temp.p + i*num + j) = *(this->p + i*num + j) * rhs; 
        }
    }
    return temp;
}
Vec Mat::operator*(const Vec &rhs){     //��������������������
    if(this->num!=rhs.num){
        std::cout << "Mat*Vec error in " << this->name << " * " << rhs.name << " : num not match." << endl;
        exit(1);
    }
    if(this->num<=0){
        std::cout << "Mat*Vec error in " << this->name << " * " << rhs.name << " : num <= 0." << endl;
        exit(1);
    }
    Vec temp("temp",num);
    for(int i=0; i!=num; ++i){
        *(temp.p + i) = 0;
        for(int t=rhs.zero_num; t!=num; ++t){
            *(temp.p + i) += *(this->p + i*num + t) * (*(rhs.p + t));
        }
    }
    return temp;
}
Mat Mat::init(double flag){
    if(this->num<=0){
        std::cout << "Mat itin() error in " << this->name << " : num <= 0." << endl;
        exit(1);
    }
        for(int i=0; i!=num; ++i){
            for(int j=0; j!=num; ++j)
                *(this->p + i*num + j) = flag;
        } 
    return *(this);
}
Mat Mat::initE(){
    Mat temp("temp(mat.initE())",this->num);
    (*this).init(0);
    for(int i=0; i!=num; ++i){
        *(this->p + i*num + i) = 1;
    }
    temp = (*this);
    return temp;
}
Mat Mat::tranPosition(){
    Mat temp("temp(mat.tranPosition)",num);
    for(int i=0; i!=num; ++i){
        for(int j=0; j!=num; ++j)
            *(temp.p + j*num +i) = *(p + i*num +j);
    }
    return temp;
}
Mat Mat::lowDemi(const int low){
    if(num<=0){
        std::cout << "lowDemi error of " << name << ".lowDemi(): num<=0." << std::endl;
        exit(1);
    }
    if(low<=0||low>num){
        std::cout << "lowDemi wanning of " << name << ".lowDemi(): low num <=0 or >num." << std::endl;
        return (*this);
    }
    
    Mat temp("temp(mat.lowDemi)",num);
    temp = *this;
    num = num - low;
    free(this->p);
    this->p = NULL;
    if(num==0)
        return *this;
    if( (this->p=(double*)malloc(num*num*sizeof(double)))==NULL ){
        std::cout << "Memory sign failed in "<< name << ".lowDemi(): when recreates Mat."<< std::endl;
        exit(1);
    }
    for(int i=1; i<=num; ++i){
        for(int j=1; j<=num; ++j)
            (*this)(i,j) = temp(i,j);
    }
    return (*this);
}
Mat Mat::charLow2(const int tar, Com &root1, Com &root2){
// tarΪ��ȡ2*2�������½ǵ�����
    if(tar<2||tar>num){
        cout << name << ".charLow2() error: tar<2 or tar>num." << endl;
        exit(1); 
    }
    const double a=1;
    const double b=(*this)(tar-1,tar-1) + (*this)(tar,tar);
    const double c=(*this)(tar-1,tar-1) * (*this)(tar,tar) - (*this)(tar-1,tar) * (*this)(tar,tar-1);
    if( (SolveTwoFun(a,-b,c,root1,root2))==1 ){
        cout << name << ".charLow2() error: SolveTwoFun return 1, don't have two real charcter rinda." << endl;
        exit(1);
    }
    Mat temp("temp(in charLow2)",2);
    temp(1,1) = (*this)(tar-1,tar-1),  temp(1,2) = (*this)(tar-1,tar);
    temp(2,1) = (*this)(tar,tar-1),    temp(2,2) = (*this)(tar,tar);
    return temp;
}
Mat Mat::swapLine(const int i1, const int i2){
    if(this->num<=0){
        cout << name << ".swapLine(i1,i2) error: this.num<=0." << endl;
        exit(1);
    }
    if(i1<1||i1>num||i2<1||i2>num){
        cout << name << ".swapLine(i1,i2) error: i1,i2 <0 or >num." << endl;
        exit(1);
    }
    double temp;
    for(int t=0; t!=num; t++){
        temp = *(this->p + (i1-1)*num +t);
        *(this->p + (i1-1)*num +t) = *(this->p + (i2-1)*num +t);
        *(this->p + (i2-1)*num +t) = temp;
    }
    return *(this);
}

// ===========================Vec ��ķ�������=======================
Vec::Vec(string name, int num){
    this->name = name;
    this->num = num;
    this->zero_num = 0;
    if(num<=0){
        this->p = NULL;
    }
    else{
        if( (this->p=(double*)malloc(num*sizeof(double)))==NULL ){
            std::cout << "Memory sign failed when creates Vec: " << name << '\n';
            exit(1);
        }
    }  
}
Vec::~Vec(){
    free(this->p);
    this->p = NULL;
}
double & Vec::operator()(const int n){  //���� vec(n) ������ʶ���
    if(n<=0||n>this->num){
        std::cout << "Vec overstep when reading in " << this->name << ":n<0 or >num.\n";
        exit(1);
    }
    return *(this->p + n-1);
}
Vec Vec::operator=(const Vec &rhs){
    this->zero_num = rhs.zero_num;
    if(this->num!=rhs.num){
        this->num = rhs.num;
        free(this->p);
        this->p=NULL;
        if(rhs.num==0){
            return *this;
        }
        if( (this->p=(double*)malloc(num*sizeof(double)))==NULL ){
            std::cout << "Memory recreate failed in operator = of Vec: " << name << '\n';
            exit(1);
        }
    }
    for(int j=0; j!=num; ++j)
        *(this->p + j) = *(rhs.p + j);
    
    return *this;
}
Vec Vec::operator+(const Vec &rhs){  //�������������
    if(this->num!=rhs.num){
        std::cout << "Vec + error in " << this->name << " + " << rhs.name << " : num not match.\n";
        exit(1);
    }
    if(this->num<=0){
        std::cout << "Vec + error in " << this->name << " + " << rhs.name << " : num <= 0.\n";
        exit(1);
    }
    Vec temp("temp",num);
    for(int i=0; i!=num; ++i){
        *(temp.p + i) = *(this->p + i) + *(rhs.p + i);
    }
    return temp;
}
Vec Vec::operator-(const Vec &rhs){  //�������������
    if(this->num!=rhs.num){
        std::cout << "Vec - error in " << this->name << " - " << rhs.name << " : num not match.\n";
        exit(1);
    }
    if(this->num<=0){
        std::cout << "Vec - error in " << this->name << " - " << rhs.name << " : num <= 0.\n";
        exit(1);
    }
    Vec temp("temp",num);
    for(int i=0; i!=num; ++i){
        *(temp.p + i) = *(this->p + i) - *(rhs.p + i);
    }
    return temp;
}
Mat Vec::operator%(const Vec &rhs){  //������ת��*����  �������
    if(this->num!=rhs.num){
        std::cout << "Vec\%Vec error in " << this->name << " % " << rhs.name << " : num not match.\n";
        exit(1);
    }
    if(this->num<=0){
        std::cout << "Vec\%Vec error in " << this->name << " % " << rhs.name << " : num <= 0.\n";
        exit(1);
    }
    Mat temp("temp",num);
    temp.init(0);
    for(int i=this->zero_num; i!=num; ++i){
        for(int j=rhs.zero_num; j!=num; ++j){
            *(temp.p + i*num + j) = *(this->p + i) * (*(rhs.p + j));
        }   
    }
    return temp;
}
double Vec::operator*(const Vec &rhs){  //����Vec*Vec �������
    if(this->num!=rhs.num){
        std::cout << "Vec*Vec error in " << this->name << " * " << rhs.name << " : num not match.\n";
        exit(1);
    }
    if(this->num<=0){
        std::cout << "Vec*Vec error in " << this->name << " * " << rhs.name << " : num <= 0.\n";
        exit(1);
    }
    double temp = 0;
    int max_zero = (this->zero_num > rhs.zero_num)?this->zero_num:rhs.zero_num;
    for(int i=max_zero; i!=num; ++i){
        temp += *(this->p + i) * (*(rhs.p + i));
    }
    return temp;
}
Vec Vec::operator*(const double &rhs){  //����Vec*num ��������
    if(this->num<=0){
        std::cout << "Vec*num error in " << this->name << " : num <= 0.\n";
        exit(1);
    }
    Vec temp("temp",num);
    for(int i=zero_num; i!=num; ++i){
        *(temp.p + i) = *(this->p + i) * rhs;
    }
    return temp;
}
Vec Vec::operator/(const Mat &rhs){
    if(num!=rhs.num){
        cout << name << " / " << rhs.name << " error: num not match." << endl;
        exit(1);  
    }
    if(num<=0||rhs.num<=0){
        cout << name << " / " << rhs.name << " error: num <= 0." << endl;
        exit(1);
    }
    Vec vec_x("vec_x(vec/mat)",num), vec_b("vec_b(vec/mat)",num);
    vec_b = *(this);
    Mat mat_a("mat_a(vec/mat)", num);
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
        if(Abs(temp)<g_step_comperr)
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
        if(Abs(mat_a(k,k))<g_step_comperr){
            if(Abs(temp-vec_b(k))>g_step_comperr){
                cout << name << " / " << rhs.name << " error: rank(" << name << ")<num and vec input not match." << endl;
                exit(1);
            }
            vec_x(k)=1;
            continue;
        }
        vec_x(k) = (vec_b(k)-temp)/mat_a(k,k);
    }
    return vec_x;
}
double Vec::norm2(){
    if(this->num<=0){
        std::cout << "Vec norm2 error in " << this->name << " : num <= 0.\n";
        exit(1);
    }
    double temp=0;
    for(int i=zero_num; i!=num; ++i){
        temp += *(this->p + i) * (*(this->p + i));
    }
    return sqrt(temp);
}
Vec Vec::init(double flag){
    if(this->num<=0){
        std::cout << "Vec itin() error in " << this->name << " : num <= 0.\n";
        exit(1);
    }
    Vec temp("temp(vec.init())",num);
    for(int j=0; j!=num; ++j)
        *(this->p + j) = flag;
    temp = *this;
    return temp;
}

#endif