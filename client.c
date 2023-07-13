/*Program where client puts various requests to server*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>

typedef struct singleUser 
{
	int userID;
	char name[30];
	char password[10];
	int acc_no; 
	float balance;
	char status[20];
}singleUser;

typedef struct jointUser
{
	int userID;
	char name1[30];
	char name2[30];
	char password[10];
	int acc_no;
	float balance;
	char status[20];
}jointUser;

typedef struct manager 
{
	int userID;
	char username[30];
	char password[10];
}manager;

void attemptSingleUserLogin(int sd);
void attemptJointUserLogin(int sd);
void attemptManagerLogin(int sd);
void chooseOption(int sd);  //
void menu(int sd);  //
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);
int option,currUserID;

//Option to login as single user, joint user, manager
void chooseOption(int sd)
{
	while(1)
    {
		write(1,"1 : Normal-User Login\n",sizeof("1 : Normal-User Login\n"));
		write(1,"2 : Joint Account-User Login\n",sizeof("2 : Joint Account-User Login\n"));
		write(1,"3 : manager Login\n",sizeof("3 : manager Login\n"));
		
		write(1,"Choose an option : ",sizeof("Choose an option : "));
		scanf("%d",&option);
		printf("Option : %d\n",option);

		if(option == 1)
        {
			attemptSingleUserLogin(sd); 
			break;
		}
		else if(option == 2)
        {
			attemptJointUserLogin(sd);
			break;
		}
		else if(option == 3)
        {
			attemptManagerLogin(sd);
			break;
		}
		else write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
	}
	return;
}

//Display various actions based on login
void menu(int sd)
{
	int select;
	if(option==1 || option==2)
    {
		write(1,"1 : Deposit\n",sizeof("1 : Deposit\n"));
		write(1,"2 : Withdraw\n",sizeof("2 : Withdraw\n"));
		write(1,"3 : Balance Enquiry\n",sizeof("3 : Balance Enquiry\n"));
		write(1,"4 : Password Change\n",sizeof("4 : Password Change\n"));
		write(1,"5 : View Details\n",sizeof("5 : View Details\n"));
		write(1,"6 : Exit\n",sizeof("6 : Exit\n"));
	
		write(1,"Choose an option : ",sizeof("Choose an option : "));
		scanf("%d",&select);
		printf("Option : %d\n",select);
		
		switch(select)
        {
            case 1:
                deposit(sd);
                break;

            case 2:
                withdraw(sd);
                break;

            case 3:
                balanceEnquiry(sd);
                break;

            case 4:
                changePassword(sd);
                break;

            case 5:
                viewDetails(sd);
                break;

            case 6:
                write(sd,&select,sizeof(int));
                write(1,"Thank you\n",sizeof("Thank you\n"));
                exit(0);

            default:
                write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
                menu(sd);
                break;
		}
	}
	else if(option==3)
    {
		write(1,"1 : Add Account\n",sizeof("1 : Add Account\n"));
		write(1,"2 : Delete Account\n",sizeof("2 : Delete Account\n"));
		write(1,"3 : Modify Account\n",sizeof("3 : Modify Account\n"));
		write(1,"4 : Search Account\n",sizeof("4 : Search Account\n"));
		write(1,"5 : Exit\n",sizeof("6 : Exit\n"));

		write(1,"Choose an option : ",sizeof("Choose an option : "));
		scanf("%d",&select);
		printf("Option : %d\n",select);
		
		switch(select)
        {
            case 1:
                addAccount(sd);
                break;

            case 2:
                deleteAccount(sd);
                break;

            case 3:
                modifyAccount(sd);
                break;

            case 4:
                searchAccount(sd);
                break;

            case 5:
                write(sd,&select,sizeof(int));
                write(1,"Thank you\n",sizeof("Thank you\n"));
                exit(0);

            default:
                write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
                menu(sd);
                break;
		}
	}
}

//To check if password is correct for single user
void attemptSingleUserLogin(int sd)
{
	bool success;   
	singleUser currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	write(sd,&option,sizeof(int));          //writing to server
	write(sd,&currUser,sizeof(singleUser));

	read(sd,&success,sizeof(success));         //reading from server

	if(!success)
    {
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else
    {
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

//To check if password is correct for joint user
void attemptJointUserLogin(int sd)
{
	bool success;
	jointUser currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(jointUser));

	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else
    {
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

//To check if password is correct for manager
void attemptManagerLogin(int sd)
{
	bool success;
	manager currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(manager));

	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else
    {
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

//Deposit money to account
void deposit(int sd)
{
	float amt;
	int select=1;
	bool success;

	write(1,"Amount to Deposit : Rs.",sizeof("Amount to Deposit : Rs."));
	scanf("%f",&amt);

	while(amt<=0)
    {
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Deposit : Rs.",sizeof("Amount to Deposit : Rs."));
		scanf("%f",&amt);
	}

	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Error depositing your money!!\n\n",sizeof("Error depositing your money!!\n\n"));
	}
	else
    {
		write(1,"Succesfully deposited!!\n\n",sizeof("Succesfully deposited!!\n\n"));
	}
	menu(sd);
	return;
}

//Withdraw money from account
void withdraw(int sd)
{
	float amt;
	int select=2;
	bool success;

	write(1,"Amount to Withdraw : Rs.",sizeof("Amount to Withdraw : Rs."));
	scanf("%f",&amt);

	while(amt<=0)
    {
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Withdraw : Rs.",sizeof("Amount to Withdraw : Rs."));
		scanf("%f",&amt);
	}

	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Error withdrawing your money, please check your balance!!\n\n",sizeof("Error depositing your money, please check your balance!!\n\n"));
	}
	else
    {
		write(1,"Succesfully withdrew!!\n\n",sizeof("Succesfully withdrew!!\n\n"));
	}
	menu(sd);
	return;
}

//To get the current balance in the account
void balanceEnquiry(int sd)
{
	float amt;
	int select=3;
	int len;

	write(sd,&select,sizeof(int));
	
	len=read(sd,&amt,sizeof(float));	

	write(1,"Available Balance :: Rs.",sizeof("Available Balance :: Rs."));
	printf("%0.2f\n\n",amt);

	menu(sd);
	return;
}

//To change the password of the account
void changePassword(int sd)
{
	int select=4;
	char nPassword[10];
	bool success;

	write(1,"Enter the new password(max 10 characters) : ",sizeof("Enter the new password(max 10 characters) : "));
	scanf("%s",nPassword);

	write(sd,&select,sizeof(int));
	write(sd,nPassword,sizeof(nPassword));

	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Error changing your password!!\n\n",sizeof("Error changing your password!!\n\n"));
	}
	else
    {
		write(1,"Succesfully changed your password!!\n\n",sizeof("Succesfully changed your password!!\n\n"));
	}
	menu(sd);
	return;
}

//To get the details of the account
void viewDetails(int sd)
{
	int select=5;

	write(sd,&select,sizeof(int));

	if(option==1)
    {
		singleUser currUser1;
		read(sd,&currUser1,sizeof(singleUser));
		
		printf("User ID : %d\n",currUser1.userID);
		printf("Name : %s\n",currUser1.name);
		printf("Account Number : %d\n",currUser1.acc_no);
		printf("Available Balance : Rs.%0.2f\n",currUser1.balance);
		printf("Status : %s\n\n",currUser1.status);
	}
	else if(option==2)
    {
		jointUser currUser2;
		read(sd,&currUser2,sizeof(jointUser));
		
		printf("User ID : %d\n",currUser2.userID);
		printf("Main Account Holder's Name : %s\n",currUser2.name1);
		printf("Other Account Holder's Name : %s\n",currUser2.name2);
		printf("Account Number : %d\n",currUser2.acc_no);
		printf("Available Balance : Rs.%0.2f\n",currUser2.balance);
		printf("Status : %s\n\n",currUser2.status);
	}
	menu(sd);
	return;
}

//To add a new account (manager operation)
void addAccount(int sd)
{
	int select=1;
	int type;
	bool success;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1)
    {
		singleUser addUser1;
		write(1,"Name of the account holder : ",sizeof("Name of the account holder : "));
		scanf(" %[^\n]",addUser1.name);
		write(1,"Password(max 10 characters) : ",sizeof("Password(max 10 characters) : "));
		scanf("%s",addUser1.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&addUser1.balance);
		write(sd,&addUser1,sizeof(singleUser));
	}

	if(type==2)
    {
		jointUser addUser2;
		write(1,"Name of the primary account holder : ",sizeof("Name of the primary account holder : "));
		scanf(" %[^\n]",addUser2.name1);
		write(1,"Name of the other account holder : ",sizeof("Name of the other account holder : "));
		scanf(" %[^\n]",addUser2.name2);
		write(1,"Password(max 10 characters) : ",sizeof("Password(max 10 characters) : "));
		scanf("%s",addUser2.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&addUser2.balance);
		write(sd,&addUser2,sizeof(jointUser));
	}
	
	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Error adding the account!!\n\n",sizeof("Error adding the account!!\n\n"));
	}
	else
    {
		write(1,"Succesfully added the account!!\n\n",sizeof("Succesfully added the account!!\n\n"));
	}
	menu(sd);
	return;
}

//To delete an existing account (manager operation)
void deleteAccount(int sd)
{
	int select=2;
	int type,userID;
	bool success;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);
	
	write(sd,&type,sizeof(int));

	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&userID);
	write(sd,&userID,sizeof(int));
	
	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Error deleting the account ,please re-check the User ID!!\n\n",sizeof("Error deleting the account ,please re-check the User ID!!\n\n"));
	}
	else
    {
		write(1,"Succesfully deleted the account!!\n\n",sizeof("Succesfully deleted the account!!\n\n"));
	}
	menu(sd);
	return;
}

//To modify an account
void modifyAccount(int sd)
{
	int select=3;
	int type;
	bool success;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1)
    {
		singleUser modUser1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser1.userID);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser1.acc_no);
		write(1,"New Name of the account holder : ",sizeof("New Name of the account holder : "));
		scanf(" %[^\n]",modUser1.name);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser1.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser1.balance);
		write(sd,&modUser1,sizeof(singleUser));
	}

	if(type==2)
    {
		jointUser modUser2;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser2.userID);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser2.acc_no);
		write(1,"New Name of the primary account holder : ",sizeof("New Name of the primary account holder : "));
		scanf(" %[^\n]",modUser2.name1);
		write(1,"New Name of the other account holder : ",sizeof("New Name of the other account holder : "));
		scanf(" %[^\n]",modUser2.name2);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser2.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser2.balance);
		write(sd,&modUser2,sizeof(jointUser));
	}
	
	read(sd,&success,sizeof(success)); 

	if(!success)
    {
		write(1,"Error modifying the account ,please re-check the User ID and Account No!!\n\n",sizeof("Error modifying the account ,please re-check the User ID and Account No!!\n\n"));
	}
	else
    {
		write(1,"Succesfully modified the account!!\n\n",sizeof("Succesfully modified the account!!\n\n"));
	}
	menu(sd);
	return;
}

//To search for an existing account
void searchAccount(int sd)
{
	int select=4;
	int type,len;
	bool success;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1)
    {
		singleUser searchUser1;
		int userID;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser1,sizeof(singleUser));
		if(len==0)
        {
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else
        {
			printf("User ID : %d\n",searchUser1.userID);
			printf("Name : %s\n",searchUser1.name);
			printf("Account Number : %d\n",searchUser1.acc_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
			printf("Status : %s\n\n",searchUser1.status);
		}
	}

	if(type==2)
    {
		jointUser searchUser2;
		int userID1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID1);
		write(sd,&userID1,sizeof(int));
		
		len=read(sd,&searchUser2,sizeof(jointUser));
		if(len==0)
        {
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else
        {
			printf("User ID : %d\n",searchUser2.userID);
			printf("Main Account Holder's Name : %s\n",searchUser2.name1);
			printf("Other Account Holder's Name : %s\n",searchUser2.name2);
			printf("Account Number : %d\n",searchUser2.acc_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.balance);
			printf("Status : %s\n\n",searchUser2.status);
		}
	}
	menu(sd);
	return;
}

int main()
{
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char success;

	//connection establishment
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1"); //implies same machine
	server.sin_port=htons(5555);
	connect(sd,(struct sockaddr *)&server,sizeof(server));

	chooseOption(sd);
	menu(sd);	

	close(sd);

	return 0;
}