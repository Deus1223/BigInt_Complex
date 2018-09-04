#include <bits/stdc++.h>
#include "BigInt.h"
#include "Rational.h"
#include "Complex.h"

using namespace std;
using namespace bigint;
using namespace rational;
using namespace complex_h;


int main(){

    Complex first,second;
    cout<<"first / second = answer\n";
    cout<<"First number\n";
    cin>>first;
    cout<<"Second number\n";
    cin>>second;

    Complex ans;

    ans=first/second;
    cout<<"the answer is\n"<<ans<<endl;



       return 0;
}
