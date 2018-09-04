#ifndef COMPLEX_H
#define COMPLEX_H
#include <bits/stdc++.h>
#include "BigInt.h"
#include "Rational.h"

using namespace std;
using namespace bigint;
using namespace rational;

namespace complex_h {
    class Complex
    {


        public:
            /* constructor */
            Complex();   // initialize to 0 + 0i
            Complex(BigInt data1,BigInt data2,BigInt data3,BigInt data4); //initailize data1/data2 + (data3/data4)i
            Complex(BigInt data1,BigInt data2); // initialize  data1/data2 + 0i;
            Complex(const string& real_num, const string& real_den, const string& imag_num, const string& imag_den);

            /* accessor */
            Rational getReal();
            Rational getImag();

            /* << >> overloading*/
            friend ostream& operator <<(ostream& outputStream, Complex& data);
            friend istream& operator >>(istream& inputputStream, Complex& data);

            /* == * / overloading*/
            friend const bool operator == (Complex& data1 , Complex& data2);
            /*四則運算*/
            friend const Complex operator + (Complex& data1 ,Complex& data2);
            friend const Complex operator -(Complex &data);
            friend const Complex operator -(Complex& data1, Complex& data2);
            friend const Complex operator *(Complex& data1, Complex& data2);
            friend const Complex operator /(Complex& data1, Complex& data2);


        private:
            Rational real;
            Rational imag;
    };

}
#endif
