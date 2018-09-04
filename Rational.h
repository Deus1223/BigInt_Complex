#ifndef RATIONAL_H
#define RATIONAL_H
#include <bits/stdc++.h>
#include "BigInt.h"

using namespace std;
using namespace bigint;

namespace rational {
    class Rational
    {
        public:
            Rational();   // initialize to 0
            Rational(BigInt num1,BigInt num2); // initialize num1/num2
            Rational(BigInt WoleNumber); // initialize WoleNumber/1
            Rational(const string& str1, const string& str2);

            BigInt getNumerator();
            BigInt getDenominator();

            /* << >> overloading*/
            friend ostream& operator <<(ostream& outputStream, Rational& data);
            friend istream& operator >>(istream& inputputStream, Rational& data);
            /* == * / overloading*/
            friend const bool operator == (Rational& data1 , Rational& data2);
            friend const Rational operator * (Rational& data1, Rational& data2);
            friend const Rational operator / (Rational& data1, Rational& data2);
            /* >  >= < <= [] overloading */
            const bool operator > (Rational& data2 )const;
            const bool operator >= (Rational& data2 )const;
            const bool operator < (Rational& data2 )const;
            const bool operator <= (Rational& data2 )const;
            friend const Rational normalize(Rational& data);
        private:
            BigInt numerator;
            BigInt denominator;
    };
    /* + - - overloading */
    const Rational operator + (Rational& data1 ,Rational& data2);
    const Rational operator - (Rational& data1 ,Rational& data2);
    const Rational operator - (Rational& data);

}
#endif
