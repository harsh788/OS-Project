/*Program where server will perform and respond to the actions requested by clients*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <pthread.h>

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

//To get single user account details
singleUser getSingleUser(int ID)
{
	int i=ID-1000;
	singleUser currUser;
	int fd=open("singleUserData",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(singleUser);    	     
	lock.l_len=sizeof(singleUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
	read(fd,&currUser,sizeof(singleUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

//To get joint user account details
jointUser getJointUser(int ID)
{
	int i=ID-1000;
	jointUser currUser;
	int fd=open("jointUserData",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&currUser,sizeof(jointUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

//To get manager details
manager getManager(int ID)
{
	int i=ID-1000;
	manager currUser;
	int fd=open("adminData",O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(manager);    	     
	lock.l_len=sizeof(manager);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(manager),SEEK_SET);  
	read(fd,&currUser,sizeof(manager));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

//To check if password is correct for single user login
bool checkSingleUser(singleUser currUser)
{
	int i=currUser.userID-1000;
	int fd=open("singleUserData",O_RDONLY,0744);
	bool success;
	singleUser temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(singleUser);    	     
	lock.l_len=sizeof(singleUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
	read(fd,&temp,sizeof(singleUser));
	if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))	
		success=true;
	else	
		success=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return success;
}

//To check if password is correct for joint user login
bool checkJointUser(jointUser currUser)
{
	int i=currUser.userID-1000;
	int fd=open("jointUserData",O_RDONLY,0744);
	bool success;
	jointUser temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&temp,sizeof(jointUser));
	if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))	
		success=true;
	else						
		success=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return success;
}

//To check if password is correct for manager login
bool checkManager(manager currUser)
{
	int i=currUser.userID-1000;
	int fd=open("adminData",O_RDONLY,0744);
	bool success;
	manager temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(manager);    	     
	lock.l_len=sizeof(manager);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(manager),SEEK_SET);  
	read(fd,&temp,sizeof(manager));
	if(!strcmp(temp.password,currUser.password))	
		success=true;
	else						
		success=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return success;
}

//To deposit money to an account
bool depositMoney(int accType,int ID,float amt)
{
	int i=ID-1000;
	if(accType==1)
	{
		int fd=open("singleUserData",O_RDWR,0744);
		bool success;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(singleUser);    
		lock.l_len=sizeof(singleUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		singleUser currUser;
		lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
		read(fd,&currUser,sizeof(singleUser));
		
		if(!strcmp(currUser.status,"ACTIVE"))
		{
			currUser.balance+=amt;
			lseek(fd,sizeof(singleUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(singleUser));
			success=true;
		}
		else	
			success=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;		
	}
	else if(accType==2)
	{
		int fd=open("jointUserData",O_RDWR,0744);
		bool success;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&currUser,sizeof(jointUser));
		
		if(!strcmp(currUser.status,"ACTIVE"))
		{
			currUser.balance+=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			success=true;
		}
		else	
			success=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;	
	}
	return false;
}

//To wothdraw money from an account
bool withdrawMoney(int accType,int ID,float amt)
{
	int i=ID-1000;
	if(accType==1)
	{
		int fd=open("singleUserData",O_RDWR,0744);
		bool success;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(singleUser);    
		lock.l_len=sizeof(singleUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		singleUser currUser;
		lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
		read(fd,&currUser,sizeof(singleUser));
		
		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amt)
		{
			currUser.balance-=amt;
			lseek(fd,sizeof(singleUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(singleUser));
			success=true;
		}
		else	
			success=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;	
	}
	else if(accType==2)
	{
		int fd=open("jointUserData",O_RDWR,0744);
		bool success;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&currUser,sizeof(jointUser));
		
		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amt)
		{
			currUser.balance-=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			success=true;
		}
		else	
			success=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;
	}
	return false;
}

//To get current balance of an account
float getBalance(int accType,int ID)
{
	int i=ID-1000;
	float success;
	if(accType==1)
	{
		int i=ID-1000;
		int fd=open("singleUserData",O_RDONLY,0744);
		singleUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(singleUser);    	     
		lock.l_len=sizeof(singleUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
		read(fd,&temp,sizeof(singleUser));
		if(!strcmp(temp.status,"ACTIVE"))	
			success=temp.balance;
		else					
			success=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;
	}
	else if(accType==2)
	{
		int i=ID-1000;
		int fd=open("jointUserData",O_RDONLY,0744);
		jointUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    	     
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&temp,sizeof(jointUser));
		if(!strcmp(temp.status,"ACTIVE"))	
			success=temp.balance;
		else					
			success=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;
	}
	return 0;
}

//To change password for an account
bool modifyPassword(int accType,int ID,char newPwd[10])
{
	int i=ID-1000;
	if(accType==1)
	{
		int fd=open("singleUserData",O_RDWR,0744);
		bool success;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(singleUser);    
		lock.l_len=sizeof(singleUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		singleUser currUser;
		lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
		read(fd,&currUser,sizeof(singleUser));
		
		if(!strcmp(currUser.status,"ACTIVE"))
		{
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(singleUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(singleUser));
			success=true;
		}
		else	
			success=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;
	}
	else if(accType==2)
	{
		int fd=open("jointUserData",O_RDWR,0744);
		bool success;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&currUser,sizeof(jointUser));
		
		if(!strcmp(currUser.status,"ACTIVE"))
		{
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			success=true;
		}
		else	
			success=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return success;
	}
	return false;
}

//To add new single user account (manager operation)
bool addsingleUser(singleUser record)
{
	int fd=open("singleUserData",O_RDWR,0744);
	bool success;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(singleUser);    
	lock.l_len=sizeof(singleUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	singleUser endUser;
	lseek(fd,(-1)*sizeof(singleUser),SEEK_END);  
	read(fd,&endUser,sizeof(singleUser));
		
	record.userID=endUser.userID+1;
	record.acc_no=endUser.acc_no+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(singleUser));
	if(j!=0)	
		success=true;
	else	
		success=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return success;	
}

//To add new joint user account (manager operation)
bool addJointUser(jointUser record)
{
	int fd=open("jointUserData",O_RDWR,0744);
	bool success;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser endUser;
	lseek(fd,(-1)*sizeof(jointUser),SEEK_END);  
	read(fd,&endUser,sizeof(jointUser));
		
	record.userID=endUser.userID+1;
	record.acc_no=endUser.acc_no+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(jointUser));
	if(j!=0)	
		success=true;
	else	
		success=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return success;	
}

//To delete existing single user account (manager operation)
bool deletesingleUser(int ID)
{
	int i=ID-1000;
	int fd=open("singleUserData",O_RDWR,0744);
	bool success;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(singleUser);    
	lock.l_len=sizeof(singleUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	singleUser currUser;
	lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
	read(fd,&currUser,sizeof(singleUser));
	
	if(!strcmp(currUser.status,"ACTIVE"))
	{	
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;
		
		lseek(fd,(-1)*sizeof(singleUser),SEEK_CUR); 
		int j=write(fd,&currUser,sizeof(singleUser));
		if(j!=0)	
			success=true;
		else		
			success=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return success;	
}

//To delet existing joint user account (manager operation)
bool deleteJointUser(int ID)
{
	int i=ID-1000;
	int fd=open("jointUserData",O_RDWR,0744);
	bool success;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser currUser;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&currUser,sizeof(jointUser));
	
	if(!strcmp(currUser.status,"ACTIVE"))
	{	
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;
		
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&currUser,sizeof(jointUser));
		if(j!=0)	
			success=true;
		else		
			success=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return success;	
}

//To modify existing single user account
bool modifysingleUser(singleUser modUser)
{
	int i=modUser.userID-1000;
	int fd=open("singleUserData",O_RDWR,0744);
	bool success=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(singleUser);    
	lock.l_len=sizeof(singleUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	singleUser currUser;
	lseek(fd,(i)*sizeof(singleUser),SEEK_SET);  
	read(fd,&currUser,sizeof(singleUser));
	
	if(!strcmp(currUser.status,"ACTIVE") && (modUser.acc_no==currUser.acc_no))
	{	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(singleUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(singleUser));
		if(j!=0)	
			success=true;
		else		
			success=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return success;	
}

//To modify existing joint user account
bool modifyJointUser(jointUser modUser)
{
	int i=modUser.userID-1000;
	int fd=open("jointUserData",O_RDWR,0744);
	bool success=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser currUser;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&currUser,sizeof(jointUser));
	
	if(!strcmp(currUser.status,"ACTIVE")  && (modUser.acc_no==currUser.acc_no))
	{	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(jointUser));
		if(j!=0)	
			success=true;
		else		
			success=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return success;	
}

//Server execution
void serverTask(int nsd)
{
	int msgLength,select,type,option,accType,currUserID;
	bool success;
	while(1)
	{
		read(nsd,&option,sizeof(option));		//reading from client
		printf("Option : %d\n",option);

		if(option==1)
		{
			singleUser currUser1;
			accType=1;
			msgLength=read(nsd,&currUser1,sizeof(singleUser));
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			currUserID=currUser1.userID;
			success=checkSingleUser(currUser1);
			write(nsd,&success,sizeof(success));			//writing to client
		}
		else if(option==2)
		{
			jointUser currUser2;
			accType=2;
			msgLength=read(nsd,&currUser2,sizeof(jointUser));
			currUserID=currUser2.userID;
			printf("Username : %d\n",currUser2.userID);
			printf("Password : %s\n",currUser2.password);
			success=checkJointUser(currUser2);
			write(nsd,&success,sizeof(success));
		}
		else if(option==3)
		{
			manager currUser3;
			accType=3;
			msgLength=read(nsd,&currUser3,sizeof(manager));
			currUserID=currUser3.userID;
			printf("Username : %d\n",currUser3.userID);
			printf("Password : %s\n",currUser3.password);
			success=checkManager(currUser3);
			write(nsd,&success,sizeof(success));
		}
		else
		{
			success=false;
			write(nsd,&success,sizeof(success));
		}
		if(success)	
			break;		
	}

	while(1)
	{
		read(nsd,&select,sizeof(int));
		if(option==1 || option==2)
		{
			if(select==1)
			{
				float amt;
				read(nsd,&amt,sizeof(float));
				success=depositMoney(accType,currUserID,amt);
				write(nsd,&success,sizeof(success));
			}
			else if(select==2)
			{
				float amt;
				read(nsd,&amt,sizeof(float));
				success=withdrawMoney(accType,currUserID,amt);
				write(nsd,&success,sizeof(success));
			}
			else if(select==3)
			{
				float amt;
				amt=getBalance(accType,currUserID);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4)
			{
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				success=modifyPassword(accType,currUserID,pwd);
				write(nsd,&success,sizeof(success));
			}
			else if(select==5)
			{
				if(option==1)
				{
					singleUser user1=getSingleUser(currUserID);
					write(nsd,&user1,sizeof(singleUser));
				}
				else if(option==2)
				{
					jointUser user2=getJointUser(currUserID);
					write(nsd,&user2,sizeof(jointUser));
				}
			}
			else if(select==6)	
				break;
		}
		else if(option==3)
		{
			read(nsd,&type,sizeof(int));
			if(select==1)
			{
				if(type==1)
				{
					singleUser newUser1;
					read(nsd,&newUser1,sizeof(singleUser));
					success=addsingleUser(newUser1);
					write(nsd,&success,sizeof(success));
				}
				else if(type==2)
				{
					jointUser newUser2;
					read(nsd,&newUser2,sizeof(jointUser));
					success=addJointUser(newUser2);
					write(nsd,&success,sizeof(success));
				}
			}
			else if(select==2)
			{
				if(type==1)
				{
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					success=deletesingleUser(delUserID1);
					write(nsd,&success,sizeof(success));
				}
				else if(type==2)
				{
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					success=deleteJointUser(delUserID2);
					write(nsd,&success,sizeof(success));
				}
			}
			else if(select==3)
			{
				if(type==1)
				{
					singleUser modUser1;
					read(nsd,&modUser1,sizeof(singleUser));
					success=modifysingleUser(modUser1);
					write(nsd,&success,sizeof(success));
				}
				else if(type==2)
				{
					jointUser modUser2;
					read(nsd,&modUser2,sizeof(jointUser));
					success=modifyJointUser(modUser2);
					write(nsd,&success,sizeof(success));
				}
			}
			else if(select==4)
			{
				if(type==1)
				{
					singleUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=getSingleUser(userID1);
					write(nsd,&searchUser1,sizeof(singleUser));
				}
				else if(type==2)
				{
					jointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=getJointUser(userID2);
					write(nsd,&searchUser2,sizeof(jointUser));
				}
			}
			else if(select==5)	
				break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

void *connection_handler(void *nsd) 
{
	int nsfd = *(int*)nsd;
	serverTask(nsfd);
}


int main()
{
	struct sockaddr_in server,client;
	int sd,nsd,clientLen;
	pthread_t threads;
	bool success;
	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);

	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);
	
	write(1,"Waiting for the client.....\n",sizeof("Waiting for the client.....\n"));
	while(1)
	{
		clientLen=sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&clientLen);

		write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));
		if(pthread_create(&threads,NULL,connection_handler,(void*) &nsd)<0)
		{
			perror("could not create thread");
			return 1;
		}		
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}