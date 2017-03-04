#ifndef BINDEC_H
#define BINDEC_H
#include <bits/stdc++.h>
#define ll long long int

using namespace std;

class convert{

public:
  ll btod(ll n);
  ll dtob(ll n);
  ll octod(ll octalNumber);
  ll dtooc(ll decimalNumber);
  ll hextod(string hexstr);
  string dtohex(ll decimalNumber);
};


class Num :public virtual convert{
  int a,base;
  
  public:
  string s;
  int b;
  
  public:
    Num();
    Num(int z);
    Num(int x,int y);
    Num(string st);
    Num(string st,int y);
    Num operator+(Num ob);
    Num operator-(Num ob);
    Num operator*(Num ob);
    Num operator/(Num ob);
    void operator=(Num obj);
    void display();
};

#endif
