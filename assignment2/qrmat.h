/*  Create: 2021.11.09 23:35        
    Update: 2021.11.09 23:35
        完成了QRDeposit的编写与测试
    Updata: 2021.11.10 3:13
        完成了QuasiUpTri的编写与初步测试，未在matlab上进行测试
    Updata: 2021.11.10 23:49
        QuasiUpTri不能在matlab上测试，重复多次无异常认为正常
        完成StepQR编写，进行复数修改，未进行测试
    Update: 2021/11/11 23:35
        已完成所有代码的测试，运行正常
*/
#ifndef __QRMAT_H_
#define __QRMAT_H_

#include"mymat.h"

Mat QRDeposit(Mat &mat_a);
Mat QuasiUpTri(Mat &mat_a);
Comvec StepQR(Mat &mat_a);

Mat QRDeposit(Mat &mat_a){
// 对输入矩阵进行QR分解，Q（正交）作为函数输出，R（上三角）为输入矩阵修改得
    if(mat_a.num<=0){
        std::cout << "QRDeposit error in " << mat_a.name << " : input num<=0." << endl;
        exit(1);
    }
    Mat mat_q("mat_q(QRDeposit)",mat_a.num);
    mat_q.initE();
    const int n = mat_a.num;
    int r=0, i=0, t=0;
    double a_ir_sum=0, dr=0, cr=0, hr=0;
    Vec ur("ur",n), wr("wr",n), pr("pr",n);
    ur.init(0);

    for(r=1; r<=n-1; ++r){
        for(a_ir_sum=0,i=r+1; i<=n; ++i){
            a_ir_sum += mat_a(i,r) * mat_a(i,r);
        }
        if(Abs(a_ir_sum)<=g_compare_error)
            continue;
        
        dr = sqrt(a_ir_sum + mat_a(r,r)*mat_a(r,r));
        cr = -Sgn(mat_a(r,r))*dr;
        hr = cr*cr - cr*mat_a(r,r);

        ur.zero_num = r-1;
        ur.init(0);
        ur(r)=mat_a(r,r)-cr;
        for(t=r+1; t<=n; ++t)
            ur(t)=mat_a(t,r);
        
        wr = mat_q * ur;
        mat_q = mat_q - (wr%ur)*(1.0/hr);
        pr = mat_a.tranPosition() * ur * (1.0/hr);
        mat_a = mat_a - ur%pr;
    }

    return mat_q; // 返回q矩阵（正交矩阵）
}

Mat QuasiUpTri(Mat &mat_a){
// 对mat_a拟上三角化， 输出Q，拟上三角化后的矩阵在a处修改 
    if(mat_a.num<=0){
        std::cout << "QuasiUpTri(" << mat_a.name << ") error: input num<=0." << endl;
        exit(1);
    }

    Mat mat_q("mat_q(in QuasiUpTri)",mat_a.num);
    // mat_q.initE();
    const int n = mat_a.num;
    int r=0, i=0, t=0;
    double a_ir_sum=0, dr=0, cr=0, hr=0,tr=0;
    Vec vr("vr",n), ur("ur",n), wr("wr",n), pr("pr",n), qr("qr",n);
    ur.init(0);

    for(r=1; r<=n-2; ++r){
        for(a_ir_sum=0,i=r+2; i<=n; ++i){
            a_ir_sum += mat_a(i,r) * mat_a(i,r);
        }
        if(Abs(a_ir_sum)<=g_compare_error)
            continue;
        
        dr = sqrt(a_ir_sum + mat_a(r+1,r)*mat_a(r+1,r));
        cr = -Sgn(mat_a(r+1,r))*dr;
        hr = cr*cr - cr*mat_a(r+1,r);

        ur.zero_num = r;
        ur.init(0);
        ur(r+1)=mat_a(r+1,r)-cr;
        for(t=r+2; t<=n; ++t)
            ur(t)=mat_a(t,r);
        
        vr = ur*(1.0/hr);
        pr = mat_a.tranPosition() * vr;
        qr = mat_a * vr;
        tr = pr * vr;
        wr = qr - ur*tr;
        mat_a = mat_a - wr%ur - ur%pr;

        mat_q = mat_q - (mat_q*ur)%vr;
    }   
    return mat_q;
}
Comvec StepQR(Mat &mat_a){
    if(mat_a.num<=0){
        cout << "StepQR() error: Mat input num<=2." << endl;
        exit(1);
    }
    Comvec output(mat_a.num);
    QuasiUpTri(mat_a);
    int step=0, m=mat_a.num;
    Com root1(0,0), root2(0,0);
    double num_s=0, num_t=0;
    Mat mat_mk("mat_mk(StepQR)",1), mat_temp("mat_temp(StepQR)",1), mat_q("mat_q(StepQR)",1);

    while(1){
        if(step>50){
            cout << "StepQR() warnning: max step reached step = " << step << endl;
            break;
        }
        if(m<0){
            cout << "StepQR() error: m<0" << endl;
            exit(1);
        }
        if(m==0){
            cout << "StepQR() outputs when step = " << step << endl;
            break;
        }

        if(m==1||Abs(mat_a(m,m-1))<=g_step_comperr*0.01){
            output.comVecChange(m,mat_a(m,m));
            m--;
            mat_a.lowDemi(1);
            continue;
        }
        num_s = mat_a(m-1,m-1) + mat_a(m,m);
        num_t = mat_a(m-1,m-1)*mat_a(m,m) - mat_a(m,m-1)*mat_a(m-1,m);
        if( m==2||Abs(mat_a(m-1,m-2))<g_step_comperr*0.01){
            SolveTwoFun(1, -num_s, num_t, root1, root2);
            output.comVecChange(m,root1);
            output.comVecChange(m-1,root2);
            m=m-2;
            mat_a.lowDemi(2);
            continue;
        }
        mat_temp = mat_a;
        mat_mk = mat_a * mat_a - mat_a * num_s + mat_temp.initE() * num_t;
        
        mat_q = QRDeposit(mat_mk);
        mat_a = mat_q.tranPosition() * mat_a * mat_q;

        step++; 
    }
    
    return output;
}
Comvec QR(Mat &mat_a){
    if(mat_a.num<=0){
        cout << "QR() error: Mat input num<=2." << endl;
        exit(1);
    }
    Comvec output(mat_a.num);
    QuasiUpTri(mat_a);
    int step=0, m=mat_a.num;
    Com root1(0,0), root2(0,0);
    double num_s=0, num_t=0;
    Mat mat_mk("mat_mk(QR)",1), mat_q("mat_q(QR)",1);

    while(1){
        if(step>300){
            cout << "QR() warnning: max step reached step = " << step << endl;
            break;
        }
        if(m<0){
            cout << "QR() error: m<0" << endl;
            exit(1);
        }
        if(m==0){
            cout << "QR() outputs when step = " << step << endl;
            break;
        }

        if(m==1||Abs(mat_a(m,m-1))<=g_step_comperr*0.01){
            output.comVecChange(m,mat_a(m,m));
            m--;
            // mat_a.lowDemi(1);
            continue;
        }
        num_s = mat_a(m-1,m-1) + mat_a(m,m);
        num_t = mat_a(m-1,m-1)*mat_a(m,m) - mat_a(m,m-1)*mat_a(m-1,m);
        SolveTwoFun(1, -num_s, num_t, root1, root2);
        if( m==2||Abs(mat_a(m-1,m-2))<g_step_comperr*0.01){
            output.comVecChange(m,root1);
            output.comVecChange(m-1,root2);
            m=m-2;
            // mat_a.lowDemi(2);
            continue;
        }
        
        mat_q = QRDeposit(mat_a);
        mat_a = mat_a * mat_q;

        step++; 
    }
    return output;
}

#endif // #ifndef __QRMAT_H_
