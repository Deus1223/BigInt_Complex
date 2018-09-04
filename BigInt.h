#ifndef BIGINT_H
#define BIGINT_H
#include<bits/stdc++.h>
using namespace std;

namespace bigint
{
    class BigInt
    {
        public:
            BigInt();   //Default Constructor.
            BigInt(const int data); //Constructor for type:int.
            BigInt(const string& userstring); //Constructor for type:string
            BigInt(const BigInt& old); //Copy constructor
            ~BigInt();  //Destructor

            /* overloading << >> */
            friend ostream& operator <<(ostream& outputStream, const BigInt& data);
            friend istream& operator >>(istream& inputStream, BigInt& data);

            /* overloading = + - * / % */
            BigInt operator = (const BigInt& rValue);
            friend BigInt operator + (const BigInt& data1 ,const BigInt& data2);
            friend BigInt operator -(const BigInt& data);
            friend BigInt operator -(const BigInt& data1, const BigInt& data2);
            friend BigInt operator *(const BigInt& data1, const BigInt& data2);
            friend BigInt operator /(const BigInt& data1, const BigInt& data2);
            friend BigInt operator %(const BigInt& data1, const BigInt& data2);

            /* overlaoding > >= == < <= != */
            friend bool operator >(const BigInt& data1, const BigInt& data2);
            friend bool operator ==(const BigInt& data1, const BigInt& data2);
            friend bool operator >=(const BigInt& data1, const BigInt& data2);
            friend bool operator <(const BigInt& data1, const BigInt& data2);
            friend bool operator <=(const BigInt& data1, const BigInt& data2);
            friend bool operator !=(const BigInt& data1, const BigInt& data2);

            BigInt factorial();
            //Make sure the value of calling object is positive.
            //It will return the factorial value of the calling object.

            int getSize();//get the array size
            bool getSign();//get the boolean value
            void setSign(bool);//set the sign of the number

        private:
            int *array;
            int size;
            bool sign;
            void clear_zero();
    };
}
#endif
