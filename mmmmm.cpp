#include<iostream>
#include<fstream>
using namespace std;

struct  Account
{
	int id;
	char name[20];
	double amount;
};

void Create();
void Deposit();
void Withdrawal();
void Transfer();
void Update();
void Search();
void Delete();
void ShowAccount();

int main()
{
	cout<<"-------Bank Management System Project--------"<<endl;
	int choice;
	do
	{
		cout<<"\nEnter 1 to Create Account. \n";
		cout<<"Enter 2 to Deposit into your Account. \n";
		cout<<"Enter 3 to Withdrawal from your Account. \n";
		cout<<"Enter 4 to Transfer Money into Another Account. \n";
		cout<<"Enter 5 to Update Account. \n";
		cout<<"Enter 6 to Search Account. \n";
		cout<<"Enter 7 to Delete Account. \n";
		cout<<"Enter 8 to Show Accounts. \n";
		cout<<"Enter 9 to Exit.\n";
		cout<<"Enter your choice : ";
		cin>>choice;
		switch (choice)
		{
			case 1:
					Create();
					break;
			case 2:
					Deposit();
					break;
			case 3:
					Withdrawal();
					break;
			case 4:
					Transfer();
					break;
			case 5:
					Update();
					break;
			case 6:
					Search();
					break;
			case 7:
					Delete();
					break;
			case 8:
					ShowAccount();
					break;
			case 9:
					cout<<"\nExiting.............";
					break;
			default:
					cout<<"\nYou enter a wrong number."<<endl;
					break;
		}
	}while(choice!=9);
	return 0;
}

void Create()
{
	bool AccMatch;
	ofstream write;
	write.open("data.txt", ios::app);
	Account NewPerson;
	do
	{
		AccMatch=false;
		cout<<"\nEnter Account ID : ";
		cin>>NewPerson.id;
		ifstream read;
		read.open("data.txt");
		Account PersonExist;
		read>>PersonExist.id;
		read>>PersonExist.name;
		read>>PersonExist.amount;
		while(!read.eof())
		{
			if(PersonExist.id==NewPerson.id)
			{
				AccMatch=true;
				cout<<"\nAccount id already taken."<<endl;
				cout<<"Please! Change your Account ID. "<<endl;
			}
			read>>PersonExist.id;
			read>>PersonExist.name;
			read>>PersonExist.amount;
		}
		read.close();
	}while(AccMatch);
	cout<<"Enter Account Name : ";
	cin>>NewPerson.name;
	cout<<"Enter Account Balance : ";
	cin>>NewPerson.amount;
	
	cout<<"\nAccount Created Successfully."<<endl;
	write<<NewPerson.id<<"\t"<<NewPerson.name<<"\t"<<NewPerson.amount<<endl;
	write.close();
}
void Deposit()
{
	ifstream read;
	read.open("data.txt");
	ofstream write;
	write.open("temp.txt");
	int id;
	double amount;
	bool Deposit=false;
	cout<<"\nEnter Account ID for Deposit Money: ";
	cin>>id;
	Account Person;
	read>>Person.id;
	read>>Person.name;
	read>>Person.amount;
	while(!read.eof())
	{
		if(id==Person.id)
		{
			do
			{
				cout<<"Enter Amount for Deposit:";
				cin>>amount;
				if(amount<0)
				{
					cout<<"\nEnter Positive Amount."<<endl;
				}
			}while(amount<0);
			Deposit=true;
			Person.amount =Person.amount +amount;
			write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;	
		}
		else
		{
			write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;	
		}
		read>>Person.id;
		read>>Person.name;
		read>>Person.amount;
	}
	if(!Deposit)
	{
		cout<<"\nAccount not Found."<<endl;
	}
	else
	{
		cout<<"\nDeposit Successfully."<<endl;
	}
	read.close();
	write.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
}
void Withdrawal()
{
	ifstream read;
	read.open("data.txt");
	ofstream write;
	write.open("temp.txt");
	int id;
	double amount;
	bool Withdraw=false;
	cout<<"\nEnter Account ID for Withdrawal Money: ";
	cin>>id;
	Account Person;
	read>>Person.id;
	read>>Person.name;
	read>>Person.amount;
	while(!read.eof())
	{
		if(id==Person.id)
		{
			do
			{
				cout<<"Enter Amount for Withdrawal:";
				cin>>amount;
				if(amount<0)
				{
					cout<<"\nEnter Positive Amount."<<endl;
				}
			}while(amount<0);
			if(Person.amount-amount>=0)
			{
				Withdraw=true;
				Person.amount =Person.amount - amount;
				write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;
				cout<<"\nWithdrawal Successfully."<<endl;
			}
			else
			{
				Withdraw=true;
				write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;
				cout<<"\nYou have Insufficient Balnace."<<endl;
			}
		}
		else
		{
				write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;	
		}
		read>>Person.id;
		read>>Person.name;
		read>>Person.amount;
	}
	if(!Withdraw)
	{
		cout<<"\nAccount not Found!"<<endl;
	}
	read.close();
	write.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
	
}
void Update()
{
	ifstream read;
	read.open("data.txt");
	ofstream write;
	write.open("temp.txt");
	int id;
	bool Update=false;
	cout<<"\nEnter Account ID to Change Account Detail: ";
	cin>>id;
	Account Person;
	read>>Person.id;
	read>>Person.name;
	read>>Person.amount;
	while(!read.eof())
	{
		if(id==Person.id)
		{
			Update=true;
			cout<<"\nAccount ID does not change"<<endl;
			cout<<"Enter New Account Name : ";
			cin>>Person.name;
			cout<<"\nAccount ID:"<<Person.id<<"\nAccount Name:"<<Person.name<<"\nAccount Balance:"<<Person.amount<<endl;
			write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;
		}
		else
		{
			write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;	
		}
		read>>Person.id;
		read>>Person.name;
		read>>Person.amount;
	}
	if(!Update)
	{
		cout<<"\nAccount not found!"<<endl;
	}
	read.close();
	write.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
}
void Transfer()
{
	ifstream read;
	read.open("data.txt");
	int SenderId,ReceiverId,count=0;
	double amount;
	bool SenderAccounnt=false,Balance=false,ReceiverAccounnt=false;
	do
	{
		cout<<"\nEnter Amount to Transfer: ";
		cin>>amount;
		if(amount<0)
		{
			cout<<"\nEnter Positive Amount"<<endl;
		}
	}while(amount<0);
	cout<<"Enter Account ID of Sender Account to Transfer Money: ";
	cin>>SenderId;
	cout<<"Enter Account ID of Reciever Account to Transfer Money: ";
	cin>>ReceiverId;
	Account accounts;
	read>>accounts.id;
	read>>accounts.name;
	read>>accounts.amount;
	while(!read.eof())
	{
		if(SenderId==accounts.id||ReceiverId==accounts.id)
		{
			if(ReceiverId==accounts.id)
			{
				ReceiverAccounnt=true;
			}
			if(SenderId==accounts.id)
			{
				SenderAccounnt=true;
				if(accounts.amount-amount>0)
				{
					Balance=true;
				}
			}
		}
		read>>accounts.id;
		read>>accounts.name;
		read>>accounts.amount;
	}
	read.close();
	if(!SenderAccounnt)
	{
		cout<<"\nSender Account not Found!"<<endl;
	}
	else if(!ReceiverAccounnt)
	{
		cout<<"\nReceiver Account not Found!"<<endl;
	}
	else if(!Balance)
	{
		cout<<"\nSender have in Sufficient Balance to Tranfer Money."<<endl;
	}
	else if(SenderAccounnt && ReceiverAccounnt)
	{
		read.open("data.txt");
		ofstream write;
		write.open("temp.txt");
		read>>accounts.id;
		read>>accounts.name;
		read>>accounts.amount;
		while(!read.eof())
		{
			if(SenderId==accounts.id||ReceiverId==accounts.id)
			{
				if(SenderId==accounts.id)
				{
					accounts.amount =accounts.amount -amount;
					write<<accounts.id<<"\t"<<accounts.name<<"\t"<<accounts.amount<<endl;
				}
				else
				{
					accounts.amount =accounts.amount +amount;
					write<<accounts.id<<"\t"<<accounts.name<<"\t"<<accounts.amount<<endl;
				}
			}
			else
			{
				write<<accounts.id<<"\t"<<accounts.name<<"\t"<<accounts.amount<<endl;	
			}
			read>>accounts.id;
			read>>accounts.name;
			read>>accounts.amount;
		}
		cout<<"\nTrnasfer Successfully"<<endl;
		read.close();
		write.close();
		remove("data.txt");
		rename("temp.txt", "data.txt");
	}
	else
	{
		cout<<"\nBoth Accounts not Found!"<<endl;
	}
}
void Search()
{
	ifstream read;
	read.open("data.txt");
	Account Person;
	bool Found=false;
	int id;
	cout<<"\nEnter Account ID to show your Account:";
	cin>>id;
	read>>Person.id;
	read>>Person.name;
	read>>Person.amount;
	while(!read.eof())
	{
		if(id==Person.id)
		{
			Found=true;
			break;	
		}	
		read>>Person.id;
		read>>Person.name;
		read>>Person.amount;
	}
	if(Found)
	{
		cout<<"\nAccount Details:\n";
		cout<<"Account ID:"<<Person.id<<"\nAccount Name:"<<Person.name<<"\nAccount Balance:"<<Person.amount<<endl;
	}
	else
	{
		cout<<"\nAccount not found!\n";
	}
	read.close();
}
void Delete()
{
	ifstream read;
	read.open("data.txt");
	ofstream write;
	write.open("temp.txt");
	int id;
	bool Delete=false;
	cout<<"\nEnter Account id to Delete Account : ";
	cin>>id;
	Account Person;
	read>>Person.id;
	read>>Person.name;
	read>>Person.amount;
	while(!read.eof())
	{
		if(id==Person.id)
		{
			cout<<"\nAccount Successfully deleted!\n";
			Delete=true;
		}
		else
		{
				write<<Person.id<<"\t"<<Person.name<<"\t"<<Person.amount<<endl;	
		}
		read>>Person.id;
		read>>Person.name;
		read>>Person.amount;
	}
	read.close();
	write.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
	if(!Delete)
	{
		cout<<"\nAccount not Found!"<<endl;
	}
	else
	{
		ShowAccount();
	}
}
void ShowAccount()
{
	bool Accounts=false;
	ifstream read;
	read.open("data.txt");
	Account Person;
	read>>Person.id;
	read>>Person.name;
	read>>Person.amount;
	while(!read.eof())
	{
		Accounts=true;
		cout<<"\n-----Account Details----"<<endl;
		cout<<"\nID: "<<Person.id<<"\nName: "<<Person.name<<"\nBalance: "<<Person.amount<<endl;
		read>>Person.id;
		read>>Person.name;
		read>>Person.amount;
	}
	read.close();
	if(!Accounts)
	{
		cout<<"\nThere is no Accounts in the file."<<endl;
	}
}
