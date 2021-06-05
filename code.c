/*BUS TICKET BOOKING SYSTEM*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct ticket
{
	char username[100],email[100],dob[100];
	char mobile_no[100],pwd[100],retype_pwd[100],mob[100];
	char ch[130];
	int available_seats;
	char status_name[32][10];
	struct details
	{
		char name[100];
		int seat_no;
		int age;
	}passenger[32];
}bus[10],user[100];
int temp_seat,temp_age,i=0,flag=0,k,j,l,bus_no;
char temp_name[100],temp_email[100],temp_pwd[100],temp_repwd[100],lname[100],lpwd[100],temp_mob[100],temp_dob[100];
char temp_name[100];
void sign_up();
int signup_validate();
void login();
void validate_username();
int login_validate();
void available_bus();
void ticket_booking();
void cancel_ticket();
void ticket_details();
void bus_status(int bus_no);
void sign_up()
{
	int result;
	printf("\n\n\t\tSIGN UP!\n\n");
	printf("\tEnter username: ");
	scanf("%s",&temp_name);
	strcpy(user[i].username,temp_name);
	printf("\n\tEnter email id: ");
	scanf("%s",&temp_email);
	strcpy(user[i].email,temp_email);
	printf("\n\tEnter password[with minimum 1 special character,1 capital letter and 1 number]: ");
	scanf("%s",&temp_pwd);
	strcpy(user[i].pwd,temp_pwd);
	printf("\n\tRetype password: ");
	scanf("%s",&temp_repwd);
	strcpy(user[i].retype_pwd,temp_repwd);
	printf("\n\tEnter mobile no: ");
	scanf("%s",&temp_mob);
	strcpy(user[i].mob,temp_mob);
	printf("\n\tEnter dob in DD/MM/YYYY format: ");
	scanf("%s",&temp_dob);
	strcpy(user[i].dob,temp_dob);
	result=signup_validate();
	if(result==1)
		validate_username();
}
/*----checking username already exists or not----*/  
void validate_username()
{
	int j=0,y=0;
	while(j<i && i!=j)
	{
		if(!(strcmp(temp_name,user[j].username)))
		{
			printf("\n\tThe username already exits,enter some other username..\n\n");
			sign_up();
			y=1;
			break;	
		}
		j++;
	}
	if(j==i && y!=1)
	{
		printf("\n\n\t\t-----Account created successfully------\n");
		i++;
	}
}
/*  ----validating sign up details-----  */
int signup_validate()
{
	/*----email validation-------*/
	int j=0,flag=0;
	if(strlen(temp_email)<5)
	{
		printf("\n\tPlease enter valid email id...\n");
		return 0;
	}
	while(j<i && i!=j)
	{
		if(!(strcmp(temp_email,user[j].email)))
		{
			printf("\n\tThe email id already exits,enter some other email address..\n\n");
			return 0;
		}
		j++;
	}
	j=0;
	while(temp_email[j]!='\0')
	{
		if(!(temp_email[j]>='A' && temp_email[j]<='Z'))
		{
			if(temp_email[j]=='@' && j>1 && (temp_email[j+1]>='a' && temp_email[j+1]<='z'))
				flag++;
			else if(temp_email[j]=='.' && (temp_email[j-1]>='a' && temp_email[j-1]<='z')&& (temp_email[j+1]>='a' && temp_email[j+1]<='z'))
				flag++;
		}
		else
		{
			printf("\n\tPlease enter valid email with small letters..");
			return 0;
		}
		j++;
	}
	if(flag!=2)
	{
			printf("\n\tPlease enter valid email..");
			return 0;
	}
	/*-----Password validation------*/
	int caps=0,small=0,spl_char=0,nums=0,k;
	if(strlen(temp_pwd)<8)
	{
		printf("\n\nPlease enter password with minimum 8 characters...");
		return 0;
	}
	for(k=0;temp_pwd[k]!='\0';k++)
	{
		if(temp_pwd[k]>='A' && temp_pwd[k]<='Z')
			caps++;
		if(temp_pwd[k]>='A' && temp_pwd[k]<='Z')
			small++;
		if(temp_pwd[k]>='0' && temp_pwd[k]<='9')
			nums++;
		if(temp_pwd[k]>=33 && temp_pwd[k]<=47 || temp_pwd[k]>=58 && temp_pwd[k]<=64)
			spl_char++;
	}
	if(caps==0 || nums==0 ||small==0 || spl_char==0)
	{
		printf("\n\tEnter valid password with special characters...\n");
		return 0;
	}
    /*----Confirm password-----*/
	if(strcmp(temp_repwd,temp_pwd))
	{
		printf("\n\tThe password doesn't matched...\n");
		return 0;
	}
	/*-----Mobile number validation-------*/
	k=0;
	if(strlen(temp_mob)>12)
	{
		printf("\n\tPlease enter valid mobile number..\n");
		return 0;
	}	
	else
	{
		if((strlen(temp_mob)==11 && temp_mob[0]=='0')||(strlen(temp_mob)==10 && temp_mob[0]!='0')||(strlen(temp_mob)==12 && (temp_mob[0]=='9' && temp_mob[1]=='1')))
		{
			while(temp_mob[k]!='\0')
			{
				if(!(temp_mob[k]>='0' && temp_mob[k]<='9'))
					break;
				k++;
			}
			if(k!=strlen(temp_mob))
			{
				printf("\n\tPlease enter valid mobile number...\n");
				return 0;
			}
		}
		else
		{
			printf("\n\tPlease enter valid mobile number...\n");
			return 0;
		}
	}
    /*-----DOB validation and age calculation-------*/
	int mm,dd,yy,age,present_date=06,present_mm=04,present_yy=2021;
	if((strlen(temp_dob)==10))
	{
		dd=((temp_dob[0]-'0')*10)+(temp_dob[1]-'0');
		mm=((temp_dob[3]-'0')*10)+(temp_dob[4]-'0');
		yy=((temp_dob[6]-'0')*1000)+((temp_dob[7]-'0')*100)+((temp_dob[8]-'0')*10)+((temp_dob[9]-'0'));
		if((yy>1900 && yy<2022) && (mm>0 && mm<=12))
		{
			if(mm==2)
			{
				if(yy%4==0 || (yy%100==0 && yy%400==0))
        		{
            		if(!(dd>0 && dd<=29))
            		{
                		printf("\n\tDate Invalid\n");
                		return 0;
           	 		}	
          		}
        		else
        		{
            		if(!(dd>0 && dd<=28))
            		{
                		printf("\n\tDate Invalid\n");
                		return 0;
            		}
            	}
			}
			else if(!(((mm==1 || mm==3 ||mm==5 ||mm==7|| mm==8 || mm==10 || mm==12)&& (dd>=1 && dd<=31))||((mm==4||mm==6||mm==9||mm==11)&& (dd>=1 &&dd<=30))))
			{
				printf("\n\tPlease enter valid date...\n");
				return 0;
			}			
			if(mm>present_mm)
				present_yy-=1;
			age=present_yy-yy;
			printf("\n\tAge : %d\n",age);
			return 1;
		}
		else
		{
			printf("\n\tPlease enter valid dob...\n");
			return 0;
		}
	}
	else
	{
		printf("\n\tPlease enter dob in dd/mm/yyyy format...\n");
		return 0;
	}
}
/*---Displaying available buses----*/
void available_bus()
{
	strcpy(bus[1].ch,"Chennai Express");
	strcpy(bus[2].ch,"Bangalore Express");
	strcpy(bus[3].ch,"Pondichery Express");
	strcpy(bus[4].ch,"Coimbatore Express");
	strcpy(bus[5].ch,"Madurai Express");
    system("cls");
    printf("\n\n    ------------- BUSES AVAILABLE--------------\n\n\t\t");
    printf("1)  =>  %s\n\n\t\t",bus[1].ch);
    printf("2)  =>  %s\n\n\t\t",bus[2].ch); 
	printf("3)  =>  %s\n\n\t\t",bus[3].ch); 
	printf("4)  =>  %s\n\n\t\t",bus[4].ch);
	printf("5)  =>  %s\n\n\t\t",bus[5].ch);	
}
/* ---Booking tickets--- */
void ticket_booking()
{
	system("cls");
	available_bus();
	int booking,count=0;
	printf("Enter bus number: ");
	scanf("%d",&bus_no);
	printf("\t-----There are %d seats available! in %s------\n",bus[bus_no].available_seats,bus[bus_no].ch);
	printf("\t\tEnter the number of Tickets to be booked: ");
	scanf("%d",&booking);
	for(l=0;l<booking;l++)
	{
		if(bus[bus_no].available_seats!=0 && bus[bus_no].available_seats-booking>0)
		{
			printf("\n\n\t\tEnter the person %d name:\t",l+1);
			scanf("%s",&temp_name);
			printf("\t\tEnter the Seat Number(1 to 32) for person %d:\t",l+1);
			scanf("%d",&temp_seat);
			printf("\t\tEnter the age for person %d:\t",l+1);
			scanf("%d",&temp_age);
			if(temp_seat>0 && temp_seat<=32)
			{
			if(bus[bus_no].passenger[temp_seat].seat_no==0)
			{
				count++;
				bus[bus_no].available_seats--;
				strcpy(bus[bus_no].passenger[temp_seat].name,temp_name);
				bus[bus_no].passenger[temp_seat].seat_no=1;
				bus[bus_no].passenger[temp_seat].age=temp_age;
				strcpy(bus[bus_no].status_name[temp_seat],temp_name);
			}
			else
			{
				printf("\n\t-----Oops! Seat No : %d is already booked by someone. Please try another-----\n",temp_seat);
				--l;		
			}
			}
			else
			{
				printf("\n\tOnly numbered upto 32 seats are available....\n\n");
				--l;
			}
		}
		else
		{
			printf("\n\tSorry! Only %d seats are available in %s\n",bus[bus_no].available_seats,bus[bus_no].ch);
			break;
		}
	}
	if(count==booking)
	printf("\n\n\t\tYour Ticket is successfully booked!");			
}
/* --- Ticket cancellation ---- */
void cancel_ticket()
{
	system("cls");
	available_bus();
	int booking,count=0;
	printf("Enter bus number from which ticket should be cancelled: ");
	scanf("%d",&bus_no);
	bus_status(bus_no);
	printf("\n\n\t\tEnter the seat number:\t");
	scanf("%d",&temp_seat);
	if(bus[bus_no].passenger[temp_seat].seat_no==1)
	{
		bus[bus_no].passenger[temp_seat].seat_no=0;
		strcpy(bus[bus_no].status_name[temp_seat],"Empty");
		printf("\n\t -----Hello %s, Your Ticket is cancelled !-----\n\n",bus[bus_no].passenger[temp_seat].name);
		bus[bus_no].available_seats++;
	}
	else
	{
		printf("\n\tPlease Enter the correct information....\n\n");	
	}
}

void ticket_details()
{
	flag=0;
	system("cls");
	available_bus();
	printf("Enter bus number: ");
	scanf("%d",&bus_no);
	printf("\t\tPlease Enter your Name to check the status\t");
	scanf("%s",&temp_name);
	for(l=1;l<=32;l++)
	{
		if((!strcmp(bus[bus_no].passenger[l].name,temp_name))&& bus[bus_no].passenger[l].seat_no!=0)
		{
			printf("\n\n\tWelcome %s! You booked the seat number %d in %s\n\n",temp_name,l,bus[bus_no].ch);
			flag=1;
			break;	
		}		
	}
	if(flag==0)
	{
		printf("\n\t ----Oops! We coundn't find your ticket details. Please enter correct name----\n");	
	}
}
/* ---- Status of bus is disolayed ---- */
void bus_status(int bus_no)
{
	printf("\n\t\t\t-----There are %d seats available! in %s------\n\n",bus[bus_no].available_seats,bus[bus_no].ch);
	int index=1;
	for(l=0; l<8; l++)
    {
        printf("\t\t\t\t");
        for(j=0; j<4; j++)
        {
        	printf("%d.%s \t",index,bus[bus_no].status_name[index]);
        	index++;
        }
        printf("\n");
	}
}

void login()
{
	system("cls");
	printf("\n\n\t\t\tLOGIN\n");
	printf("\n\t\tEnter username: ");
	scanf("%s",&lname);
	printf("\n\n\t\tEnter password: ");
	scanf("%s",&lpwd);
	login_validate();
}
/* ---- validating login details ----*/          
int login_validate()
{
	int k=0,choice,x=0,success=0;
	while(k<=i)
	{
		if(!(strcmp(lname,user[k].username)))
		{
			if(!(strcmp(lpwd,user[k].pwd)))
			{
				printf("\n\tWelcome %s! Your login was successfull...\n\n",user[k].username);
				success=1;
				break;
			}
			else
			{
				printf("\n\tLogin again and Please enter your correct password...\n");
				login();
				x=1;
			}
		}
		if(k==i && x!=1)
		{
			printf("\n\tThe username is not found...Please sign up to create an account..\n");
			sign_up();
			break;	
		}
		k++;
	}
	if(success==1)
	{
		for(l=1;l<=5;l++)
		{
			bus[l].available_seats=32;
			for(j=1;j<=32;j++)
			{
				strcpy(bus[l].status_name[j],"Empty");
			}
		}
		printf("\n\n   --------WELCOME TO BUS TICKET BOOKING SYSTEM!!--------\n\n");
		do
		{
			printf("\n\n\t------Services Available in Travels------\n\n\t\t1. View buses list\n\n\t\t2. Ticket booking\n\n\t\t3. Ticket cancellation\n\n\t\t4. Know your Ticket details\n\n\t\t5. Status of bus\n\n\t\t6. Exit\n\n\tEnter your choice\t");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
				{
					available_bus();
					break;
				}
				case 2:
				{
					ticket_booking();
					break;	
				}	
				case 3:
				{
					cancel_ticket();
					break;
				}
				case 4:
				{
					ticket_details();
					break;	
				}
				case 5:
				{
					system("cls");
					printf("Enter bus number: ");
					scanf("%d",&bus_no);
					bus_status(bus_no);
					break;
				}
				case 6:
				{
					system("CLS");
    				printf("\n\n\n\t----------------------------------------------------------------------------------------------------------\n");
    				printf("\t\t\t\t\tThank You For Using This System\t\t\t\t\t\t\n");	
					exit(1);	
				}
				default:
				{
					printf("\nEnter the valid choice\n");
					break;	
				}
			}
		}while(choice!=6);
	}
}
int main()
{
	int ch;
	printf("\n\n   --------WELCOME TO BUS TICKET RESERVATION SYSTEM!!--------\n\n");
	printf("\t\tLOGIN SIGNUP PAGE\n");
	while(1)
	{
		printf("\n\t\t1.Sign up\n\t\t2.Login\n\t\t3.Exit\n");
		printf("\tEnter choice for sign up or login: ");
		scanf("%d",&ch);
		printf("\n");
		switch(ch)
		{		
			case 1: 
			{
				sign_up();
				break;
			}
			case 2:
			{
				login();
				break;		
			}
			case 3:
			{
				exit(1);
				break;
			}
			default:
			{
				printf("Invalid choice");
				break;
			}
		}
	}
	return 0;
}
