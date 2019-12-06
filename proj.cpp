#include <iostream>
#include <fstream>
using namespace std;

enum state{
	Match,NotMatch,Star,Dot
};

//a is without stars and dots, source string
//b is the string we will compare
int stringmatch(string a,string b)
{
	state currentState = Match;
	int i=0,j=0;
	
	while(1)
	{
	switch (currentState)
	{
	case Match:
		if (i==a.length() && j==b.length()){return 1;}
		if (a[i]==b[j]){i++;j++; currentState=Match;}
		else if (b[j]=='*'){i++;j++;currentState = Star;} 
		else if (b[j]=='.'){i++;j++;currentState =  Dot;}
		else {currentState = NotMatch;}
		break;
	case NotMatch:
		return 0;
		break;
	case Star:
		while(1)
		{
		
			while(b[j]!=a[i] && i != a.length())
			{i++;}
//			cout<<a[i]<<" "<<a.length()-i-1;
			int lena=a.length()-i-1;
			int lenb=0;
			int k=j;
			while(k!=b.length()-1)
			{k++;lenb++;}
//			cout<<endl<<"Dubug  "<<lena<<"   "<<lenb<<endl;
			if (lenb>=lena)
			{break;}
			else{i++;}
		}
		if (i==a.length() && j==b.length()){return 1;}
		if (a[i]==b[j]){i++;j++;currentState=Match;}
		else {currentState = NotMatch;}
		break;
	case Dot:
		if (a[i]==b[j]){i++;j++;currentState=Match;}
		else if (b[j]=='*'){j++;currentState = Star;}
		else if (b[j]=='.'){i++;j++;currentState =  Dot;} 
		else {currentState = NotMatch;} 
		break;
	default:
		break;				
	}
	}
	
}

int main()
{
	string line1,line2;
	cin>>line2;
	
	fstream myfile;
	myfile.open("sample.txt",ios::in);
	
	while(!myfile.eof())
	{
		myfile>>line1;
		int result = stringmatch(line1,line2);
		if (result == 1)
		{
			cout<<line1<<endl;
		}
	}
	return 0;
}
