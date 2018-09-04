#include <bits/stdc++.h>
#include "BigInt.h"
#include "Rational.h"
#include "Complex.h"

using namespace std;
using namespace bigint;
using namespace rational;

namespace complex_h
{
Complex::Complex(){
    Rational a(0,1);
    real=a;
    imag=a;
}

Complex::  Complex(BigInt data1,BigInt data2,BigInt data3,BigInt data4)
{
    Rational a(data1,data2);
    Rational b(data3,data4);
    real=a;
    imag=b;
}
Complex::  Complex(BigInt data1,BigInt data2){
    Rational a(data1,1);
    Rational b(data2,1);
    real=a;
    imag=b;

}

Complex::Complex(const string& real_num, const string& real_den, const string& imag_num, const string& imag_den)
    {
        real=Rational(real_num, real_den);
        imag=Rational(imag_num, imag_den);
    }


//===========================
// + - / * overloading
//===========================
const Complex operator + (Complex& data1 ,Complex& data2){

    Rational tmpReal1,tmpImage1,tmpReal2,tmpImage2;
    tmpReal1=data1.getReal();
    tmpImage1=data1.getImag();
    tmpReal2=data2.getReal();
    tmpImage2=data2.getImag();

    Rational ansReal,ansImag;
    
    ansReal=tmpReal1+tmpReal2;
    normalize(ansReal);
    
    ansImag=tmpImage1+tmpImage2;
    normalize(ansImag);

    BigInt aa,bb,cc,dd;
    aa=ansReal.getNumerator();
    bb=ansReal.getDenominator();
    cc=ansImag.getNumerator();
    dd=ansImag.getDenominator();
    Complex reAns(aa,bb,cc,dd);
    return reAns;
}

const Complex operator -(Complex& data1, Complex& data2){

    Rational tmpReal1,tmpImage1,tmpReal2,tmpImage2;
    tmpReal1=data1.getReal();
    tmpImage1=data1.getImag();
    tmpReal2=data2.getReal();
    tmpImage2=data2.getImag();

    Rational ansReal,ansImag;
    
    ansReal=tmpReal1-tmpReal2;
    normalize(ansReal);
    
    ansImag=tmpImage1-tmpImage2;
    normalize(ansImag);

    BigInt aa,bb,cc,dd;
    aa=ansReal.getNumerator();
    bb=ansReal.getDenominator();
    cc=ansImag.getNumerator();
    dd=ansImag.getDenominator();
    Complex reAns(aa,bb,cc,dd);
    return reAns;
}

const Complex operator -(Complex &data){
    Rational tmp1,tmp2,tmp3,tmp4;
    tmp1 = data.getReal();
    tmp2=data.getImag();
    tmp2=-tmp2;
    BigInt a,b,c,d;
    a=tmp1.getNumerator();
    b=tmp1.getDenominator();
    c=tmp2.getNumerator();
    d=tmp2.getDenominator();
    Complex reAns(a,b,c,d);
    return reAns;
}

const Complex operator *(Complex& data1, Complex& data2){

    /* (a+bi)*(c+di)=(ac-bd)+(bc+ad)i */
    Rational a,b,c,d;
    
    a=data1.getReal();
    b=data1.getImag();

    
    c=data2.getReal();
    d=data2.getImag();

    
    Rational ansReal,ansImag;

    
    Rational e,ee;
    e=a*c;
    ee=b*d;
    ansReal= e-ee;

    
    e=b*c;
    ee=a*d;
    ansImag= e+ee;

    BigInt aa,bb,cc,dd;
    aa=ansReal.getNumerator();
    bb=ansReal.getDenominator();
    cc=ansImag.getNumerator();
    dd=ansImag.getDenominator();
    Complex reAns(aa,bb,cc,dd);
    return reAns;

}

const Complex operator /(Complex& data1, Complex& data2){
    /* (a+bi)/(c+di)=(ac+bd)/(c^2+d^2) + [(bc-ad)/(c^2+d^2)]i */
    Rational a,b,c,d;
    
    a=data1.getReal();
    b=data1.getImag();

    
    c=data2.getReal();
    d=data2.getImag();

    normalize(a);
    normalize(b);
    normalize(c);
    normalize(d);


    Rational share,e,ee;
    e=c*c;
    normalize(e);
    ee=d*d;
    normalize(ee);
    share=e+ee;
    normalize(share);

    Rational real,ra,rb;
    ra=a*c;
    rb=b*d;
    real=ra+rb;


    Rational imag,ia,ib;
    ia=b*c;
    ib=a*d;
    imag=ia-ib;


    Rational ansReal,ansImag;
    ansReal=real/share;
    ansImag=imag/share;

    BigInt aa,bb,cc,dd;
    aa=ansReal.getNumerator();
    bb=ansReal.getDenominator();
    cc=ansImag.getNumerator();
    dd=ansImag.getDenominator();
    Complex reAns(aa,bb,cc,dd);
    return reAns;

}

//===========================
// == overloading
//===========================
const bool operator == (Complex& data1 , Complex& data2)
{
    Rational tmp1,tmp2,tmp3,tmp4;
    tmp1=data1.getReal();
    tmp2=data2.getReal();
    tmp3=data1.getImag();
    tmp4=data2.getImag();
    
    if(tmp1==tmp2 && tmp3==tmp4)
        return true;
    return false;
}

//===========================
// accessor function
//===========================

Rational Complex::getReal(){
    return real;
}
Rational Complex::getImag(){
    return imag;
}

//===========================
// << >> overloading
//===========================
ostream& operator <<(ostream& outputStream, Complex& data)
{
    Rational c=data.getReal();
    Rational d=data.getImag();

    BigInt e=c.getNumerator();
    BigInt f=c.getDenominator();
    BigInt g=d.getNumerator();
    BigInt h=d.getDenominator();
    outputStream << e<<" / "<<f << "  +  ( " << g <<" / "<< h <<" )i";
    return outputStream;
}
istream& operator >>(istream& inputStream, Complex& data)
{
    BigInt data1,data2,data3,data4;
    cout<<"input realNumerator(實部分子): ";
    inputStream >> data1;
    cout<<"input Denominator(實部分母): ";
    inputStream >> data2;
    cout<<"input realNumerator(虛部分子): ";
    inputStream >> data3;
    cout<<"input Denominator(虛部分母): ";
    inputStream >> data4;


    if(data1.getSign()==true && data2.getSign() == false){
        data1=-data1;
        data2=-data2;
    }
    else if(data1.getSign()==false && data2.getSign()==false){
        data1=-data1;
        data2=-data2;
    }
    if(data3.getSign()==true && data4.getSign() == false){
        data3=-data3;
        data4=-data4;
    }
    else if(data3.getSign()==false && data4.getSign()==false){
        data3=-data3;
        data4=-data4;
    }




    Complex tmp3(data1,data2,data3,data4);
    data=tmp3;

    return inputStream;
}
}
