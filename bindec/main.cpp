#include "Bindec.h"
#include <bits/stdc++.h>
#include <stdlib.h>
#define ll long long int

using namespace std;

string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}



struct number
{
	string num;
	int base;
};

struct histo
{
	number num1;
	string oper;
	number num2;
	number num3;
};

vector<histo> v;

int main(){
  int choice;

  enum choice{conversion,addition,substraction,multiplication,division,history,quit};



 cout<<"1.conversion"<<"    "<<"2.addition"<<endl;
 cout<<"3.substraction"<<"  "<<"4.multiplication"<<endl;
 cout<<"5.division"<<"      "<<"6.history"<<endl;
 cout<<"7.quit"<<endl;

while(1){

 cout<<"Enter your choice : ";

 cin>>choice;
 cout<<endl;


  choice--;

  switch(choice){
  case conversion:
    {   cout<<"Enter your Number and Base respectively :";
       string s;
       int base;
       cin>>s>>base;
       Num n1(s,base);
       cout<<"Enter your output Base:";
       int base2;
       cin>>base2;
       Num n2(base2);
       n2=n1;
       cout<<"Number in Base"<<base2<<":";
       n2.display();
       cout<<endl;
    histo his;
    his.num1.num=s;
    his.num1.base=base;
    his.oper="-->";
    his.num2.base=base2;
    //his.num2.num=n2.s;
    if(base2==16)
    his.num2.num=n2.s;
    else 
    his.num2.num=to_string(n2.b);	
    his.num3.num="";
    his.num3.base=0;
    v.push_back(his);
       break;
}
case addition:
  {    cout<<"Enter your first Number and Base respectively :";
      string s1;
      int base1;
      cin>>s1>>base1;
      Num n11(s1,base1);
      cout<<"Enter your second Number and Base respectively :";
      string s21;
      int base21;
      cin>>s21>>base21;
      Num n21(s21,base21);
      cout<<"Enter your output Number Base :";
      int base31;
      cin>>base31;
      Num n31(base31);
      n31=n11+n21;
      cout<<"answer in Base"<<base31<<":";
      n31.display();
      cout<<endl;
      histo his;
    his.num1.num=s1;
    his.num1.base=base1;
    his.oper="+";
    his.num2.num=s21;
    his.num2.base=base21;
    if(base31==16)
    his.num3.num=n31.s;
    else 
    his.num3.num=to_string(n31.b);	
    his.num3.base=base31;
    v.push_back(his);
      break;
}
case substraction:
  {  cout<<"Enter your first Number and Base respectively :";
    string s3;
    int base3;
    cin>>s3>>base3;
    Num n13(s3,base3);
    cout<<"Enter your second Number and Base respectively :";
    string s23;
     int base23;
    cin>>s23>>base23;
    Num n23(s23,base23);
    cout<<"Enter your output Number Base :";
    int base33;
    cin>>base33;
    Num n33(base33);
    n33=n13-n23;
    cout<<"answer in Base"<<base33<<":";
    n33.display();
    cout<<endl;
    histo his;
    his.num1.num=s3;
    his.num1.base=base3;
    his.oper="-";
    his.num2.num=s23;
    his.num2.base=base23;
    if(base33==16)
    his.num3.num=n33.s;
    else 
    his.num3.num=to_string(n33.b);
    his.num3.base=base33;
    v.push_back(his);
    break;
}
case multiplication:
{  cout<<"Enter your first Number and Base respectively :";
  string s4;
  int base4;
  cin>>s4>>base4;
  Num n14(s4,base4);
  cout<<"Enter your second Number and Base respectively :";
  string s24;
  int base24;
  cin>>s24>>base24;
  Num n24(s24,base24);
  cout<<"Enter your output Number Base :";
  int base34;
  cin>>base34;
  Num n34(base34);
  n34=n14*n24;
  cout<<"answer in Base"<<base34<<":";
  n34.display();
  cout<<endl;
  histo his;
  his.num1.num=s4;
    his.num1.base=base4;
    his.oper="*";
    his.num2.num=s24;
    his.num2.base=base24;
   if(base34==16)
    his.num3.num=n34.s;
    else 
    his.num3.num=to_string(n34.b);
    his.num3.base=base34;
    v.push_back(his);
  break;
}
case division:
{  cout<<"Enter your first Number and Base respectively :";
  string s5;
  int base5;
  cin>>s5>>base5;
  Num n15(s5,base5);
  cout<<"Enter your second Number and Base respectively :";
  string s25;
  /*if(s25="0"){
  cout<<"Not Valid!"<<endl;
  exit(0);
    }*/
  int base25;
  cin>>s25>>base25;
  Num n25(s25,base25);
  cout<<"Enter your output Number Base :";
  int base35;
  cin>>base35;
  Num n35(base35);
  n35=n15/n25;
  cout<<"answer in Base"<<base35<<":";
  n35.display();
  cout<<endl;
  histo his;
  his.num1.num=s5;
    his.num1.base=base5;
    his.oper="/";
    his.num2.num=s25;
    his.num2.base=base25;
   if(base35==16)
    his.num3.num=n35.s;
    else 
    his.num3.num=to_string(n35.b);
    his.num3.base=base35;
    v.push_back(his);
  break;
}
case history:
{   for(int i=0;i<v.size();i++){
	if(v[i].num3.base==0)
		cout<<v[i].num1.num<<"--->"<<v[i].num2.num<<endl;
	else
    cout<<v[i].num1.num<<v[i].oper<<v[i].num2.num<<"="<<v[i].num3.num<<endl;
}
}
case quit:
  exit(0);

default:
  cout<<"Invalid choice!"<<endl;

  }

}
return 0;
}
