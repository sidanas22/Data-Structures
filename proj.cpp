#include <iostream>
#include <fstream>
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
		cout<<"\n\n\n________ENDING___________";
		
	}
	
	
};


class Finite_state_machine
{
	private:
		string pattern;
		fstream myfile;
		string filename;
		SLL wordlist;
	
	public:
		
	
	void get_filename(string file_name)
	{
		this->filename = file_name;
		filename = filename+".txt";
	}
	
	
	void regex(string pattern1)
	{
		string word_from_file;
		this->pattern = pattern1;
		
		
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
			if (result == 1)
			{
			wordlist.add_to_tail(word_from_file);
			}
		}
		myfile.close();
		wordlist.print();
	}
		
	int stringmatch(string a,string b){
		
		
			state currentState = Match;
			int i=0,j=0;
			
			while(1)
			{
			switch (currentState)
			{
			
			
			case Match:
				if (i==a.length() && j==b.length()){return 1;}
				if (a[i]==b[j]){i++;j++; currentState=Match;}
				else if (b[j]=='*'){j++;currentState = Star;} 
				else if (b[j]=='.'){i++;j++;currentState =  Dot;}
				else {currentState = NotMatch;}
				break;
			
			
			case NotMatch:
				return 0;
				break;
			
			
			case Star:
				
				
				while(1)
				{
					if (j>b.length()-1 && i <= a.length()){return 1;}
					
					while(b[j]!=a[i] && i <= a.length()-1)
					{i++;}
					
					if (i==a.length()-1 || b[j+1]=='*' || b[j+1]=='.'){break;}
					
					while (a[i+1]!=b[j+1] && i<=a.length())
					{i++;}
					
					if (i>a.length()){break;}
					
					int  starflag=0,lenb=0,x;
					
					for (x=j;x<b.length();x++)
					{
						if (b[x]=='*'){starflag = 1; break;}
						else{lenb++;}
					}
					int lena = a.length()-i-1;
					if ((starflag==1 && a[x+1]==b[j] && a[x+1]==b[j+1]) || (starflag==0 && lena>lenb)){i++; continue;}
					else
					{break;}
				}
				
				if (i==a.length() && j==b.length()){return 1;}
				if (a[i]==b[j]){i++;j++;currentState=Match;}
				else {currentState = NotMatch;}
				break;
				
			
			
			case Dot:
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




//a is without stars and dots, source string
//b is the string we will compare


int main()
{
	string line1,line2;
	getline(cin,line2);
	
	Finite_state_machine FSM("sample");
	FSM.regex(line2);
	
	
	
	return 0;
}
