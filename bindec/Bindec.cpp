#include "Bindec.h"
#include <bits/stdc++.h>
#include <stdlib.h>
#define ll long long int

using namespace std;


ll convert::btod(ll n){
     ll decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

ll convert::dtob(ll n){
  ll binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n!=0)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

ll convert::octod(ll octalNumber)
{
    int decimalNumber = 0, i = 0, rem;
    while (octalNumber != 0)
    {
        rem = octalNumber % 10;
        octalNumber /= 10;
        decimalNumber += rem * pow(8, i);
        ++i;
    }
    return decimalNumber;
}

ll convert::dtooc(ll decimalNumber)
{
    int rem, i = 1, octalNumber = 0;
    while (decimalNumber != 0)
    {
        rem = decimalNumber % 8;
        decimalNumber /= 8;
        octalNumber += rem * i;
        i *= 10;
    }
    return octalNumber;
}


ll convert::hextod(string hexstr)
{

    return (long long int)strtol(hexstr.c_str(), 0, 16);

}

string convert::dtohex(ll decimalNumber){
stringstream ss;
ss<< hex << decimalNumber;
string res ( ss.str() );
return res;

}



 Num::Num():base(10){}
 Num::Num(int z):base(z){}
 Num::Num(int x,int y){
        b=x;
        base=y;
        if(y==2) a=btod(b);
        if(y==10) a=b;
        if(y==8)  a=octod(b);
      }
Num::Num(string st){
        base=16;
        s=st;
        a=hextod(s);
      }
Num::Num(string st,int y){
        base=y;
        s=st;
        if(base==16){
        a=hextod(s);
      }else{
          b=(int)atoi(st.c_str());
          if(y==2) a=btod(b);
          if(y==10) a=b;
          if(y==8)  a=octod(b);
        }

      }
Num Num::operator+(Num ob){
  Num t;
  t.a=a+ob.a;
  if(base==2) t.b=dtob(t.a);
  if(base==10) t.b=t.a;
  if(base==8)  t.b=dtooc(t.a);
  if(base==16)  t.s=dtohex(t.a);
  return t;
}

Num Num::operator-(Num ob){
  Num t;
  t.a=a-ob.a;
  if(base==2) t.b=dtob(t.a);
  if(base==10) t.b=t.a;
  if(base==8)  t.b=dtooc(t.a);
  if(base==16)  t.s=dtohex(t.a);
  return t;
}

Num Num::operator*(Num ob){
  Num t;
  t.a=a*ob.a;
  if(base==2) t.b=dtob(t.a);
  if(base==10) t.b=t.a;
  if(base==8)  t.b=dtooc(t.a);
  if(base==16)  t.s=dtohex(t.a);
  return t;
}
Num Num::operator/(Num ob){
  Num t;
  t.a=a/ob.a;
  if(base==2) t.b=dtob(t.a);
  if(base==10) t.b=t.a;
  if(base==8)  t.b=dtooc(t.a);
  if(base==16)  t.s=dtohex(t.a);
  return t;
}


void Num::operator=(Num obj){
  a=obj.a;
  if(base==2) b=dtob(a);
  if(base==10) b=a;
  if(base==8)  b=dtooc(a);
  if(base==16) s=dtohex(a);

}

void Num::display(){
  if(base==16)
  cout<<s<<endl;
  else
  cout<<b<<endl;
}
