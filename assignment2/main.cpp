#include"qrmat.h"

const int g_num = 10;
Mat Init(Mat &mat);

int main(){
    Mat mat_a("mat_a(main)",g_num), mat_input("mat_input(main)",g_num);
    Mat mat_q("mat_q(main)",g_num), mat_input2("mat_input2(main)",g_num);
    Init(mat_a);
    mat_input = mat_a;
    mat_input2 = mat_a;

    QuasiUpTri(mat_input);
    cout << "mat_a after Quasi-upper-triangular transformation:" << endl;
    cout << mat_input << endl;
    Comvec lamda_v(g_num);
    lamda_v = StepQR(mat_input);

    // QR(mat_input2);
    // cout << "mat_a afte QRStep Iteration:" << endl;
    // cout << mat_input2 << endl;

    // mat_q = QRDeposit(mat_input2);
    // cout << "mat_r:" << endl;
    // cout << mat_input2 << endl;
    // cout << "\nmat_r * mat_q:" << endl;
    // cout << mat_input2*mat_q << endl;

    double lamda=0;
    Vec eig_v("eig_v",g_num);
    for(int i=1; i<=lamda_v.num; ++i){
        if(Abs(lamda_v(i).imag)>g_step_comperr){
            cout << "No" << i << " lamda = " << lamda_v(i) << endl;
            continue;
        }
        lamda = lamda_v(i).real;
        eig_v = (eig_v.init(0))/(mat_a-(OutputE(g_num)*lamda));
        cout << "No" << i << " the eigenvector of lamda = " << lamda << ":" << endl;
        cout << eig_v*(-0.239514692166) << endl;
        cout << eig_v << endl;
    }
    
    return 0;
}

Mat Init(Mat &mat){
    if(mat.num!=g_num){
        cout << "Init(" << mat.name << ") error: num != g_num." << endl;
        exit(1);
    }
    for(int i=1; i<=g_num; ++i){
        for(int j=1; j<=g_num; ++j){
            if(i!=j)
                mat(i,j) = sin(0.5*i+0.2*j);
            else
                mat(i,j) = 1.52*cos(i+1.2*j);
        }
    }
    return mat;
}