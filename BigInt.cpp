#include <bits/stdc++.h>
#include "BigInt.h"

using namespace std;
namespace bigint
{
    /** default constructor = 0**/
    BigInt::BigInt()
    {
        size=1;
        array = new int[size];
        array[0]=0;
        sign=true;
    }

    /** constructor for int **/
    BigInt::BigInt(const int data)
    {
        /* for the value is 0 */
        if(data == 0)
        {
            size=1;
            array = new int[size];
            array[0] = 0;
            sign = true;

            return;
        }

        /* count digit */
        int i(data), j(data);
        size = 0;
        while(i)
        {
            i/=10;
            size++;
        }

        /* record value */
        array = new int[size];
        for(i=0; i<size; i++)
        {
            array[i] = j%10;
            j/=10;
        }

        clear_zero();

        /* for sign */
        sign = false;
        if(data>=0)
            sign = true;
    }

    /** constructor for string **/
    BigInt::BigInt(const string& str)
    {
        int i;
        bool f(false); // detect whether is factorial
        char *p = new char[str.length()+1];
        strcpy(p, str.c_str());
        char *v=p;

        /* for sign */
        sign = true;
        if(p[0] == '-')
        {
            sign = false;
            v++;
        }

        size = strlen(v);
        if(v[size-1] == '!')
        {
            f=true;
            size--;
        }
        array = new int[size];

        /* record number */
        for(i=0; i<size; i++)
        {
            /* record the value until current char is not a number */
            if(v[i]<'0' || v[i]>'9')
            {
                cout<< "Invalid value at constructor for string"<< endl;
                exit(1);
            }

            array[size-1-i] = v[i] - '0';
        }
        clear_zero();

        /* case of factorial */
        if(f==true) // i == size
        {
            if(sign==false)
            {
                cout<< "Invalid value at constructor for string"<< endl;
                exit(1);
            }

            BigInt tmp(*this);
            *this = tmp.factorial();
        }


        delete [] p;
        p=NULL;
    }

    /** copy constructor **/
    BigInt::BigInt(const BigInt& in)
    {
        int i;

        size = in.size;
        array = new int[size];

        for(i=0; i<size; i++)
            array[i] = in.array[i];

        sign = in.sign;;
    }

    /** destructor **/
    BigInt::~BigInt()
    {
        delete [] array;
        array = NULL;
    }

    /** overloading << **/
    ostream& operator <<(ostream& outputStream, const BigInt& data)
    {
        if(data.sign == false)
            outputStream<< "-";

        int i;
        for(i=data.size-1; i>=0; i--)
            outputStream<< data.array[i];

        return outputStream;
    }

    /** overloading >> **/
    istream& operator >>(istream& inputStream, BigInt& data)
    {
        string str;
        inputStream>> str;

        BigInt tmp(str);
        data = tmp;

        return inputStream;
    }

    /** overloading = **/
    BigInt BigInt::operator = (const BigInt& rValue)
    {
        if(this != &rValue)
        {
            size = rValue.size;
            delete array;
            array = new int[size];
            for(int i=0; i<size; i++)
                array[i] = rValue.array[i];
            sign = rValue.sign;
        }

        return *this;
    }

    /** overloading + **/
    BigInt operator + (const BigInt& in1, const BigInt& in2)
    {
        BigInt sum, tmp1(in1), tmp2(in2);
        int i;

        /* make tmp1.digit >= tmp2.digit */
        if(in1.size < in2.size)
        {
            tmp1 = in2;
            tmp2 = in1;
        }

        delete sum.array;
        sum.size = tmp1.size+1;
        sum.array = new int[sum.size];
        memset(sum.array, 0, sum.size*sizeof(int));

        /* case of the same sign */
        if(tmp1.sign == tmp2.sign)
        {
            sum.sign = tmp1.sign;

            for(i=0; i < tmp2.size; i++)   //do addition for short digit
            {
                sum.array[i] = tmp1.array[i] + tmp2.array[i] + sum.array[i];

                if(sum.array[i] > 9)    //case of carry
                {
                    sum.array[i] -= 10;
                    sum.array[i+1]++;
                }
            }
            for(i = tmp2.size; i < tmp1.size; i++)    //do addition for remaining digit
            {
                sum.array[i] += tmp1.array[i];

                if(sum.array[i] > 9)    //case of carry
                {
                    sum.array[i] -= 10;
                    sum.array[i+1]++;
                }
            }
        }
        /* case of the different sign */
        else
        {
            if(in1.sign == false)
            {
                sum = in2 - (-in1);
            }
            else
            {
                sum = in1 - (-in2);
            }
        }

        sum.clear_zero();

        return sum;
    }

    /** overloading subtraction - **/
    BigInt operator - (const BigInt& in1, const BigInt& in2)
    {
        BigInt sum, tmp1(in1), tmp2(in2);
        int i;
        bool sign_reverse(false);

        // create empty sum
        sum.size = in1.size+1;
        if(in1.size < in2.size)
            sum.size = in2.size+1;
        delete sum.array;
        sum.array = new int[sum.size];
        memset(sum.array, 0, sum.size*sizeof(int));

        /* case of the same sign */
        if(in1.sign == in2.sign)
        {
            // let tmp1 and tmp2 be positive
            if(in1.sign==false)
            {
                sum = (-in2) - (-in1);
                return sum;
            }

            // let tmp1 >= tmp2
            if(tmp1 < tmp2)
            {
                BigInt tmp(tmp1);
                tmp1 = tmp2;
                tmp2 = tmp;
                sign_reverse = !sign_reverse;
            }

            sum.sign = true;

            for(i=0; i< tmp2.size; i++)    //do subtraction for short digit
            {
                sum.array[i] = tmp1.array[i] - tmp2.array[i] + sum.array[i];

                if(sum.array[i] < 0)    // case of borrow
                {
                    sum.array[i] += 10;
                    sum.array[i+1]--;
                }
            }
            for(i = tmp2.size; i < tmp1.size; i++)    //do addition for remaining digit
                sum.array[i] += tmp1.array[i];

            if(sign_reverse)
                sum.sign = !sum.sign;
        }
        /* case of the different sign */
        else
        {
            in1.sign ? sum = in1 + (-in2) : sum = (-in1) + in2;
            sum.sign = in1.sign;
        }

        sum.clear_zero();

        return sum;
    }

    /** overloading negative - **/
    BigInt operator -(const BigInt& data)
    {
        BigInt tmp(data);
        tmp.sign = !data.sign;

        return tmp;
    }

    /** overloading * **/
    BigInt operator *(const BigInt& data1, const BigInt& data2)
    {
        BigInt tmp1(data1), tmp2(data2);
        BigInt sum;

        if(data1==0 || data2==0)
            return 0;

        if(data1.size < data2.size)
        {
            tmp1=data2;
            tmp2=data1;
        }

        bool finSign;
        // check positive or negative
        if(data1.sign==true&&data2.sign==true) finSign=true;
        else if(data1.sign==false && data2.sign==true) finSign=false;
        else if(data1.sign==true && data2.sign==false) finSign=false;
        else if(data1.sign==false && data2.sign==false) finSign=true;

        sum.size = tmp1.size*2+1;
        delete [] sum.array;
        sum.array = new int[sum.size];
        memset(sum.array, 0, sum.size*sizeof(int));

        int i(0), j(0);
        for(i=0; i<tmp2.size; i++)
        {
            for(j=0; j<tmp1.size; j++)
            {
                sum.array[i+j] = tmp2.array[i] * tmp1.array[j] + sum.array[i+j];

                if(sum.array[i+j] > 9)
                {
                    sum.array[i+j+1] += sum.array[i+j] / 10;
                    sum.array[i+j] %= 10;
                }
            }
        }

        for(i = tmp1.size + tmp2.size - 1; i<sum.size-1; i++)
        {
            if(sum.array[i] > 9)
            {
                sum.array[i+1] += sum.array[i] / 10;
                sum.array[i] %= 10;
            }
        }

        sum.sign = finSign;

//        sum.sign = (data1.sign==data2.sign) ? true : false;
        sum.clear_zero();
        return sum;
    }

    /** overloading / **/
    BigInt operator /(const BigInt& data1, const BigInt& data2)
    {
        bool finSign;
        //check positive or negative
        if(data1.sign==true&&data2.sign==true) finSign=true;
        else if(data1.sign==false && data2.sign==true) finSign=false;
        else if(data1.sign==true && data2.sign==false) finSign=false;
        else if(data1.sign==false && data2.sign==false) finSign=true;


        BigInt tmp1(data1), tmp2(data2);
        tmp1.sign = tmp2.sign = true;

        if(data2 == 0)
        {
            cout<< "Error for division"<< endl;
            exit(1);
        }

        if(tmp1 < tmp2)
            return BigInt(0);
        else if(tmp1 == tmp2)
        {
            BigInt t(1);
            t.sign = (data1.sign==data2.sign) ? true : false ;
            return t;
        }

        BigInt Q(0), V;
        string v("1");
        int n(0); // delta length of two numbers.
        while(tmp1 >= tmp2*10)
        {
            n = tmp1.size - tmp2.size;

            int s;
            for(s=tmp2.size-1; s>=0; s--)
            {
                if(tmp1.array[s+n] > tmp2.array[s])
                    break;
                else if(tmp1.array[s+n] < tmp2.array[s])
                {
                    n--;
                    break;
                }
            }

            v="1";
            while(n>0)
            {
                v.push_back('0');
                n--;
            }
            if(v.length() > 1)
            {
                V = BigInt(v);
                Q = Q + V;
                tmp1 = (tmp1 - (tmp2 * V));
            }
        }

        while(tmp1 >= tmp2*2)
        {
            Q = Q + 2;
            tmp1 = tmp1 - (tmp2*2);
        }
        while(tmp1 >= tmp2)
        {
            Q = Q + 1;
            tmp1 = tmp1 - tmp2;
        }

        Q.sign=finSign;

        return Q;
    }

    /** overloading % **/
    BigInt operator %(const BigInt& data1, const BigInt& data2)
    {
        BigInt Q(data1 / data2);
        return (data1 - (data2 * Q));
    }

    /** overloading > **/
    bool operator >(const BigInt& data1, const BigInt& data2)
    {
        if(data1.sign==true)    //data1 is positive
        {
            //data2 is negative
            if(data2.sign==false)
                return true;

            //data2 is positive
            if(data1.size > data2.size)
                return true;
            else if(data1.size < data2.size)
                return false;

            for(int i = data1.size-1; i>=0; i--)    // two digits is the same
            {
                if(data1.array[i] > data2.array[i])
                    return true;
                else if(data1.array[i] < data2.array[i])
                    return false;
            }

            return false;
        }
        else    //data1 is negative
        {
            // data2 is positive
            if(data2.sign==true)
                return false;

            // data2 is negative
            if(data1.size > data2.size)
                return false;
            else if(data1.size < data2.size)
                return true;

            for(int i = data1.size-1; i>=0; i--)    // two digits is the same
            {
                if(data1.array[i] < data2.array[i])
                    return true;
                else if(data1.array[i] > data2.array[i])
                    return false;
            }

            return false;
        }
    }

    /** overloading == **/
    bool operator ==(const BigInt& data1, const BigInt& data2)
    {
        if((data1.sign == data2.sign) && (data1.size == data2.size))
        {
            int i;

            for(i = data1.size-1; i>=0; i--)
            {
                if(data1.array[i] != data2.array[i])
                    break;
            }

            if(i==-1)
                return true;
        }

        return false;
    }

    /** overloading >= **/
    bool operator >=(const BigInt& data1, const BigInt& data2)
    {
        return (data1>data2 || data1==data2) ? true : false;
    }

    /** overloading < **/
    bool operator <(const BigInt& data1, const BigInt& data2)
    {
        return (data1>=data2) ? false : true;
    }

    /** overloading <= **/
    bool operator <=(const BigInt& data1, const BigInt& data2)
    {
        return (data1<data2 || data1==data2) ? true : false;
    }

    /** overloading != **/
    bool operator !=(const BigInt& data1, const BigInt& data2)
    {
        return !(data1==data2);
    }

    /** factorial **/
    BigInt BigInt::factorial()
    {
        if(sign==false)
        {
            cout<<"is Negative\n";
            exit(1);
        }

        BigInt sum(1);

        /*0!*/
        if(array[0]==0 && size==1)
            return sum;

        BigInt acc(1);
        do
        {
            sum=sum*acc;
            acc=acc+1;
        }while(acc <= *this);

        return sum;
    }

    /** get the array size **/
    int BigInt::getSize()
    {
        return size;
    }

    /** get the boolean value **/
    bool BigInt::getSign()
    {
        return sign;
    }

    void BigInt::setSign(bool setv)
    {
        sign=setv;
    }

    /** clear remaining zero **/
    void BigInt::clear_zero()
    {
        int v(0), i;

        //count the number of zero
        while(array[size-1-v] == 0)
        {
            // if the number is 0
            if(v == size-1)
            {
                size=1;
                delete [] array;
                array = new int[size];
                array[0]=0;

                return;
            }

            v++;
        }

        if(v)
        {
            BigInt tmp(*this);

            delete [] array;
            size -= v;
            array = new int[size];

            for(i=0; i<size; i++)
                array[i] = tmp.array[i];
        }
    }
}
