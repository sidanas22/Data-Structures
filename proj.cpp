#include<iostream>
#include <fstream>
#include<string>
using namespace std;


enum state{
	Match,NotMatch,Star,Dot
};




class node{
	public:
		string data;
		node* next;
	node(string new_s,node *n = NULL )
	{
		data = new_s;
		
		next = n;
	}

};

class SLL{
	public:
	node* head;
	node* tail;
	
	SLL(){
		head=NULL;
		tail=NULL;
	}
	
	void add_to_tail(string new_s)
	{
		if (tail==NULL)
		{
			head=tail=new node(new_s);
		}
		else
		{
			tail->next= new node(new_s);
			tail=tail->next;	
		}
	}
	
	
	void swap( int a,int  b)
	{
		if (a==b){return;}
		else{
	//		if (a==1){swap_head(a,b);return;}
	//		if (b==1){swap_head(b,a);return;}
			a--;b--;
			int count=1;
			node *temp1=NULL,*temp2=NULL;
			node *temp=head;
			while(temp!=NULL)
			{
				if(a==count){temp1=temp;}
				else if(b==count){temp2=temp;}
				count++;
				temp=temp->next;	
			}
			
			if(temp1==NULL || temp2==NULL){cout<<"position to swap nodes is out of bound"<<endl;return;}
			
			temp= temp1->next;
			temp1->next=temp2->next;
			temp2->next=temp;
			
			temp1=temp1->next;
			temp2=temp2->next;
			
			temp= temp1->next;
			temp1->next=temp2->next;
			temp2->next=temp;
		}
		
	}
	
	void print()
	{
		for(node *temp = head;temp!=NULL;temp = temp->next)
		{
			cout<<temp->data<<endl;
		}
		cout<<"\n\n\n________ENDING___________\n";
		
	}
	
	
};


class Finite_state_machine
{
	private:
		string pattern;
		fstream myfile;
		string filename;
		SLL wordlist;
		int count;
	
	public:
		
	
	void get_filename(string file_name)
	{
		this->filename = file_name;
		filename = filename+".txt";
	}
	
	//main function for solving expression matching
	void regex(string pattern1)
	{
		string word_from_file;
		this->pattern = pattern1;
		count=0;
		
		//FILING WORK
		
		myfile.open(filename.c_str(),ios::in);
		
		if(myfile.is_open()==0)
		{
			cout<<"FILE COULD NOT BE OPPENED\n";
			exit(1);
		}
		
		
		while(!myfile.eof())
		{
			getline(myfile,word_from_file);
			int result = stringmatch(word_from_file,pattern);
			if (result == 1)		//pattern founc
			{
			count++;	
			wordlist.add_to_tail(word_from_file);
			}
		}
		myfile.close();
		cout<<endl<<"Results Found: "<<count<<endl<<endl;
		wordlist.print();		//print all words that matches the expression
	}
	
	//function to match the string taken from file and pattern entered by user	
	int stringmatch(string a,string b){

			state currentState = Match;				//initialise finite state machiene using enums
			int i=0,j=0;
			
		while(1)
		{
			switch (currentState)
			{
			
			
			case Match:													//if both the strings have same character
				if (i==a.length() && j==b.length()){return 1;}
				if (a[i]==b[j]){i++;j++; currentState=Match;}
				else if (b[j]=='*'){j++;currentState = Star;} 
				else if (b[j]=='.'){i++;j++;currentState =  Dot;}
				else {currentState = NotMatch;}
				break;
			
			
			case NotMatch:												//if characters dont match
				return 0;												// match not found, move to another string
				break;
			
			
			case Star:													//if pattern has star
				
				
				while(1)
				{
					if (j>b.length()-1 && i <= a.length()){return 1;}			//if both the strings have reached end point
					
					while(b[j]!=a[i] && i <= a.length()-1)						//Till string's character matches the pattern's character after *
					{i++;}
					
					if (i==a.length()-1 || b[j+1]=='*' || b[j+1]=='.'){break;}			//if string has reached its end, or next character of pattern is * or .
					
					while (a[i+1]!=b[j+1] && i<=a.length())					//till next character of string and pattern matches
					{i++;}
					
					if (i>a.length()){break;}								//if string has reached its endpoint
					
					int  starflag=0,lenb=0,x;
					
					for (x=j;x<b.length();x++)								//to check if pattern has any other *'s
					{
						if (b[x]=='*'){starflag = 1; break;}
						else{lenb++;}
					}
					int lena = a.length()-i-1;
					
					//if pattern has star and pattern and string match and next characters of pattern and string matches
					//OR
					//if pattern has no star and length of string is greater than pattern length
					
					if ((starflag==1 && a[x]==b[j] && a[x+1]==b[j+1]) || (starflag==0 && lena>lenb)){i++; continue;}	
					else
					{break;}
				}
				
				if (i==a.length() && j==b.length()){return 1;}
				if (a[i]==b[j]){i++;j++;currentState=Match;}
				else {currentState = NotMatch;}
				break;
				
			
			
			case Dot:														//if pattern has . as its character
				if (i==a.length() && j==b.length()){return 1;}
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
};


int main()
{
	int num,flag=1; 
	string pattern;
	string answer;
	cout<<"\nWelcome!\n";
	while(flag==1)
	{
	
		cout<<"\nPlease enter the option no. ('1','2' or '3') you want to search the pattern from:\n";
		cout<<"1. Names\n2. English Dictionary\n3. Custom\n";
	
		Finite_state_machine fsm;
	
	if(num==1)
	{
		fsm.get_filename("names");
	}
	
	else if(num==2)
	{
		fsm.get_filename("english");
	}
	
	else if (num==3)
	{
		fsm.get_filename("sample");
	}
	else
	{
		std::cout<<"Error! Please enter valid option!";
		flag=1;
		continue;
	}
	cout<<"\nPlease enter the string pattern:\n";
	cin>>pattern;
	fsm.regex(pattern);

    cout<<endl<<endl<<"\nDo you want to search again ? (yes/no)\n";
	cin>>answer;
	if(answer=="yes")
	{
		flag = 1;
		system("CLS");
	}
	else if(answer=="no")
	{
		flag = 0;
	}	
}
	return 0;
}
