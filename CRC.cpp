#include <bits/stdc++.h>
#include<conio.h>
using namespace std;
int n,k;

 void checker()
{
    return;
}
string XOR(string data,string div,int i)
{
   for(int k=i;k<i+div.length();k++)
   {
       if(div[k-i]!=data[k])
         data[k]='1';
       else
         data[k]='0';

        checker();

   }
 return data;

}

string xor1(string a, string b)
{

	string result = "";

	int n = b.length();

	for(int i = 1; i < n; i++)
	{
		if (a[i] == b[i])
			result += "0";
		else
			result += "1";
	}
	return result;
}

string mod2div(string divident, string divisor)
{

	int pick = divisor.length();

	string tmp = divident.substr(0, pick);

	int n = divident.length();

	while (pick < n)
	{
		if (tmp[0] == '1')

			tmp = xor1(divisor, tmp) + divident[pick];
		else

			tmp = xor1(std::string(pick, '0'), tmp) +
				divident[pick];

		pick += 1;
	}

	if (tmp[0] == '1')
		tmp = xor1(divisor, tmp);
	else
		tmp = xor1(std::string(pick, '0'), tmp);

	return tmp;
}

string encodeData(string data, string key)
{
	int l_key = key.length();

	string appended_data = (data +
							std::string(
								l_key - 1, '0'));

	string remainder = mod2div(appended_data, key);


	string codeword = data + remainder;
//	cout << "Remainder : "
//		<< remainder << "\n";
//	cout << "Encoded Data (Data + Remainder) :"
		return codeword;
}
//
//string encode(string data,string div)
//{
//  n= data.length(),k=div.length();
// for(int i=1;i<k;i++)//n-1 0 added
//   data+='0';
//checker();
// string rem=data;
// for(int i=0;i<n;i++)
//  {
//      if(rem[i]=='0')
//        continue;
//      else
//        rem= XOR(rem,div,i);}
//     cout<<endl;
//
// string code=XOR(data,rem.substr(n,k-1),n);
// checker();
// return code;
// }

int decode(string code,string div)
{
 n= code.length();
 k= div.length();
 for(int i=0;i<n-k+1;i++)
 {
     if(code[i]=='0')
      continue;
     else
      code= XOR(code,div,i) ;
    checker();
 }

int zeroes=0,err=0;
for(int i=n-k;i<n;i++)
{
    if(code[i]=='0')
     zeroes++;

}
 if(zeroes!=k)
 {
     cout<<" ERROR detected using CRC"<<"\n";
     err=1;
     checker();
 }
 else
 {
     cout<<" NO ERROR detected using CRC"<<"\n";
     checker();
 }
return err;

}

string error(string data,float a)
{
float p=a;

for(int i=0;i<data.length();i++)
{
    float r = 0.5;
    if(r<p)
    {
      if(data[i]=='0')
         data[i]='1';
      else
         data[i]='0';}
    }
    checker();
    return data;
}

int main() {

 string data,div="100000111",code;
 cout<<"Enter Data Word of length of 32 bit or more: "<<endl;
 cin >> data;
 if(data.length()<32)
 {
     cout<<"Length of input was less than specified length.Exiting the program."<<endl;
     return 0;
 }
 checker();



   n= data.length(),k=div.length();

    int token_length=16;
    int data_length=data.length();
    int no_of_blocks=(int)ceil((float)data_length/token_length);
    string arr[no_of_blocks];
    int rem=data_length-((data_length/token_length)*token_length);
    int temp=rem;
    for(int i=1;i<no_of_blocks;i++)
    {
        arr[i]=data.substr(temp,16);
        temp+=16;
    }
    arr[0]=data.substr(0,rem);
    for(int i=0;i<16-rem;i++)
    {
        arr[0]='0'+arr[0];
    }

string codearr[no_of_blocks];
checker();
for(int i=0;i<no_of_blocks;i++)
{
    codearr[i]=encodeData(arr[i],div);
    cout<<token_length<<" Bit Tokenized data "<<i+1 << " is   : "<<arr[i]<<endl;
    cout<<"CodeWord "<<i+1<<" at sender site is : "<< codearr[i]<< endl;
     cout<<endl;

}

int hops;
cout<<"Enter no of hops in binary symmetric channel :  ";
cin>>hops;
cout<<endl;
string errarr[no_of_blocks];
for(int i=0;i<no_of_blocks;i++)
  errarr[i]=codearr[i];

cout<<"Enter Crossover Probability: "<<endl;
float a;
cin>>a;
for(int i=0;i<hops;i++)
{
    for(int i=0;i<no_of_blocks;i++)
      errarr[i]=error(errarr[i],a);
}
int errno;
for(int i=0;i<no_of_blocks;i++)
{
    cout<<"Code Word sent     "<<i <<" is " <<codearr[i]<<endl;
    cout<<"Code Word received "<<i <<" is "<<errarr[i]<<endl;
    errno+=decode(errarr[i],div);
    checker();
    cout<<endl;
}

if(errno>0)
   cout<<"Discarded"<<endl;
else
{
    cout<<"NO Error in received data & Extracted Data from Code Word is "<<endl;
    for(int i=0;i<no_of_blocks;i++)
     cout<<errarr[i].substr(0,token_length);
     cout<<endl;
}

     cout<<"  "<<data;
     cout<<" was our original data     ";


 }
