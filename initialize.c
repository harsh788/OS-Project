/*Program to create three or more records in a file*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

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

int getNewUserID1();
int getNewUserID2();
int getNewUserID3();

int getNewUserID1()
{
	int fd=open("singleUserData",O_RDONLY,0744);
	singleUser record;
	lseek(fd,-sizeof(singleUser),SEEK_END);
	read(fd,&record,sizeof(singleUser));
	close(fd);
	return record.userID+1;
}

int getNewUserID2()
{
	int fd=open("jointUserData",O_RDONLY,0744);
	jointUser record;
	lseek(fd,-sizeof(jointUser),SEEK_END);
	read(fd,&record,sizeof(jointUser));
	close(fd);
	return record.userID+1;
}

int getNewUserID3()
{
	int fd=open("adminData",O_RDONLY,0744);
	manager record;
	lseek(fd,-sizeof(manager),SEEK_END);
	read(fd,&record,sizeof(manager));
	close(fd);
	return record.userID+1;
}

int main()
{
	//Enter new manager details
	int fd=open("adminData",O_RDWR | O_CREAT,0744);
	int choice=0;
	manager newmanager;
	printf("Please enter the name of the manager: ");
	scanf(" %s",newmanager.username);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %s",newmanager.password);
	newmanager.userID=1000;
	printf("Your userID is : %d\n",newmanager.userID);
	write(fd,&newmanager,sizeof(newmanager));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice)
    {
		printf("Please enter the name of the manager: ");
		scanf(" %[^\n]",newmanager.username);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",newmanager.password);
		newmanager.userID=getNewUserID3();
		printf("Your userID is : %d\n",newmanager.userID);
		write(fd,&newmanager,sizeof(manager));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	//Enter new single user account details
	fd=open("singleUserData",O_RDWR | O_CREAT,0744);
	choice=1;
	singleUser newNUser;
	printf("Please enter the name of the normal user: ");
	scanf(" %[^\n]",newNUser.name);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",newNUser.password);
	newNUser.userID=1000;
	newNUser.balance=1000;
	newNUser.acc_no=(newNUser.userID-1000)+100000;
	printf("Your userID is : %d\n",newNUser.userID);
	strcpy(newNUser.status,"ACTIVE");
	write(fd,&newNUser,sizeof(singleUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice)
    {
		printf("Please enter the name of the normal user: ");
		scanf(" %[^\n]",newNUser.name);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",newNUser.password);
		newNUser.userID=getNewUserID1();
		newNUser.balance=1000;
		newNUser.acc_no=(newNUser.userID-1000)+100000;
		printf("Your userID is : %d\n",newNUser.userID);
		strcpy(newNUser.status,"ACTIVE");
		write(fd,&newNUser,sizeof(singleUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	//Enter new joint user account details
	fd=open("jointUserData",O_RDWR | O_CREAT,0744);
	choice=1;
	jointUser newJUser;
	printf("Please enter the main name of the joint user: ");
	scanf(" %[^\n]",newJUser.name1);
	printf("Please enter the second name of the joint user: ");
	scanf(" %[^\n]",newJUser.name2);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",newJUser.password);
	newJUser.userID=1000;
	newJUser.balance=1000;
	newJUser.acc_no=(newJUser.userID-1000)+100000;
	printf("Your userID is : %d\n",newJUser.userID);
	strcpy(newJUser.status,"ACTIVE");
	write(fd,&newJUser,sizeof(jointUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice)
    {
		printf("Please enter the main name of the joint user: ");
		scanf(" %[^\n]",newJUser.name1);
		printf("Please enter the second name of the joint user: ");
		scanf(" %[^\n]",newJUser.name2);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",newJUser.password);
		newJUser.userID=getNewUserID2();
		newJUser.balance=1000;
		newJUser.acc_no=(newJUser.userID-1000)+100000;
		printf("Your userID is : %d\n",newJUser.userID);
		strcpy(newJUser.status,"ACTIVE");
		write(fd,&newJUser,sizeof(jointUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);
	return 0;
}

