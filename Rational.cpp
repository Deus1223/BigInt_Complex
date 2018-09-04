#include <bits/stdc++.h>
#include "BigInt.h"
#include "Rational.h"

using namespace std;
using namespace bigint;
namespace rational
{
// constructor
    Rational::Rational()
    {
        numerator=0;
        denominator=1;
    }

    Rational::Rational(BigInt num1,BigInt num2)
    {
        if(num2!=0)
        {
            numerator=num1;
            denominator=num2;

            if(num1.getSign() == num2.getSign())
            {
                numerator.setSign(true);
                denominator.setSign(true);
            }
            else
            {
                numerator.setSign(false);
                denominator.setSign(true);
            }
        }
        else
        {
            cout<<"Error input\n";
            exit(1);
        }
    }
    Rational::Rational(BigInt WoleNumber)
    {
        numerator=WoleNumber;
        denominator=1;
    }

    Rational::Rational(const string& str1, const string& str2)
    {
        numerator=BigInt(str1);
        denominator=BigInt(str2);

        if(numerator.getSign() == denominator.getSign())
        {
            numerator.setSign(true);
            denominator.setSign(true);
        }
        else
        {
            numerator.setSign(false);
            denominator.setSign(true);
        }
    }

    // + - / * overloading

    const Rational operator + (Rational& data1 ,Rational& data2)
    {
        
        BigInt denominator = data1.getDenominator()*data2.getDenominator();

        
        BigInt numerator = (data1.getNumerator()*data2.getDenominator()) + (data2.getNumerator()*data1.getDenominator());

        return Rational(numerator,denominator);;
    }

    const Rational operator - (Rational&  data1 ,Rational& data2)
    {
        BigInt denominator;
        denominator=data1.getDenominator()*data2.getDenominator();
        
        BigInt numerator = (data1.getNumerator()*data2.getDenominator()) - (data2.getNumerator()* data1.getDenominator());

        return Rational(numerator,denominator); 
    }

    const Rational operator - (Rational& data)
    {
        return Rational( (-data.getNumerator()), data.getDenominator());
    }

    const Rational operator * (Rational& data1, Rational& data2)
    {
        return Rational(data1.getNumerator() * data2.getNumerator(), data1.getDenominator()*data2.getDenominator());
    }

    const Rational operator / (Rational& data1, Rational& data2)
    {
        Rational tmp(data1.getNumerator() * data2.getDenominator(), data1.getDenominator()*data2.getNumerator());

        if(tmp.numerator.getSign() == tmp.denominator.getSign())
        {
            tmp.numerator.setSign(true);
            tmp.denominator.setSign(true);
        }
        else
        {
            tmp.numerator.setSign(false);
            tmp.denominator.setSign(true);
        }


        return tmp;
    }



// == > < >= <=  overloading

const bool operator == (Rational& data1,Rational& data2)
{
    BigInt denominator,numerator;
    numerator=data1.getNumerator() * data2.getDenominator();
    denominator=data1.getDenominator()*data2.getNumerator();
    if( numerator == denominator)
        return true;
    else
        return false;
}
const bool Rational::operator > (Rational& data2 ) const
{
    BigInt tmp1,tmp2;
    tmp1=numerator * data2.getDenominator();
    tmp2=denominator * data2.getNumerator();
    if(tmp1 > tmp2)
        return true;
    else
        return false;
}

const bool Rational::operator >= (Rational& data2 ) const
{
    BigInt tmp1,tmp2;
    tmp1=numerator * data2.getDenominator();
    tmp2=denominator * data2.getNumerator();
    if(tmp1 >= tmp2)
        return true;
    else
        return false;
}


const bool Rational::operator < (Rational& data2 ) const
{
    BigInt tmp1,tmp2;
    tmp1=numerator * data2.getDenominator();
    tmp2=denominator * data2.getNumerator();
    if(tmp1<tmp2)
        return true;
    else
        return false;
}

const bool Rational::operator <= (Rational& data2 ) const
{
    BigInt tmp1,tmp2;
    tmp1=numerator * data2.getDenominator();
    tmp2=denominator * data2.getNumerator();
    if(tmp1<=tmp2)
        return true;
    else
        return false;
}


// << >> overloading

ostream& operator <<(ostream& outputStream, Rational& data)
{
    outputStream << data.getNumerator() << " / " << data.getDenominator();
    return outputStream;
}

istream& operator >>(istream& inputStream, Rational& data)
{
    char temp;
    cout<<"input numerator(分子): ";
    inputStream >> data.numerator;
    cout<<"input denominator(分母): ";
    //inputStream >> temp;
    inputStream >> data.denominator;
    return inputStream;
}


// accessor function

BigInt Rational::getNumerator()
{
    return numerator;
}

BigInt Rational::getDenominator()
{
    return denominator;
}



const Rational normalize(Rational& data)
{

    BigInt tempDenominator=data.getDenominator();
    BigInt tempNumerator=data.getNumerator();
    BigInt tempDenominator2=data.getDenominator();
    BigInt tempNumerator2=data.getNumerator();


    if(tempNumerator.getSign()==false)tempNumerator = -tempNumerator;
    if(tempDenominator.getSign()==false)tempDenominator=-tempDenominator;

    BigInt tmp;
    if(tempDenominator>tempNumerator){
        tmp=tempDenominator;
        tempDenominator=tempNumerator;
        tempNumerator=tmp;
    }


    if(tempDenominator==1||tempNumerator==1){
        return Rational(data);
    }


    if((tempNumerator%tempDenominator)==0){
        data.numerator=data.numerator / tempDenominator;
        data.denominator= data.denominator /tempDenominator;
        return Rational(data);

    }

    BigInt tmp3,tmp4;
    while(tempDenominator!=0){
        BigInt tmp2 = tempNumerator % tempDenominator;
        tempNumerator = tempDenominator;
        tempDenominator = tmp2;
        if(tmp2==1){
            tempNumerator=tempDenominator;
            break;
        }
    }

    data.numerator=data.numerator / tempNumerator;
    data.denominator= data.denominator /tempNumerator;


    return Rational(data);
}
}
