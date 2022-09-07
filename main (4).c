#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<windows.h>
typedef struct vaccine
{
    char name[20];
    char address [50];
    int age;
    char gender[6];
    char aadharno[13];
    char phno[10];
    struct date
    {
        int da,m,y;
    } d;

} vaccinestruct;

typedef struct account
{
    char id[20],password[20];
} accountstruct;



void SetColor(int ForgC)                 //to change the text color
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

int checklength(char name[],int len)      //to check all the characters in name parameter are digits and also checks weather the name has len digits
{
    for(int i =0; i<=strlen(name); i++)
        if(isalpha(name[i]))
            return 0;
    if(strlen(name)==len)
        return 1;
    else
        return 0;
}

void delay(unsigned int sec)     //to halt the execution of program specific no of seconds
{
    unsigned int rettime= time(0)+sec;
    while(time(0)<rettime);
}

int noofmonth(int a,int yy,int mon[]) //returns the no of days between 1st day of the year to the month given as parameter
{
    int x=0,c;
    for(c=0; c<a-1; c++)
    {
        if(c==1)
        {
            if(yy%4==0)
                x+=29;
            else
                x+=28;
        }
        else
            x+=mon[c];
    }
    return(x);
}

int noofdays(int y1,int y2,int m1,int m2,int d1,int d2,int mon[])   //it calculates the no of days between the system date and the date entered by the user
{
    int count=0,i;
    for(i=y1; i<y2; i++)
    {
        if(i%4==0)
            count+=366;
        else
            count+=365;
    }
    count-=noofmonth(m1,y1,mon);
    count-=d1;
    count+=noofmonth(m2,y2,mon);
    count+=d2;
    return count;
}

void check84days2(vaccinestruct *ud)   // it takes the date as input and checks if it is within 30 days and confirms the vaccination slot
{
    int days;
    int mon[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    vaccinestruct sd;
    FILE *fp;
    fp=fopen("fdosefile.bin","rb");

    while(fread(&sd,sizeof(vaccinestruct),1,fp))
        if(strcmp(ud->aadharno,sd.aadharno)==0)
            break;
    fclose(fp);
    days = noofdays(sd.d.y,ud->d.y,sd.d.m,ud->d.m,sd.d.da,ud->d.da,mon);
    if(days<84)
    {
        printf("\nPlease wait for 84 days for your second dose");
        return;
    }
    else
    {
        SetColor(2);
        printf("\nSlot for vaccination successfully scheduled on %d/%d/%d at %s",ud->d.da,ud->d.m,ud->d.y,ud->address);
        SetColor(15);
    }
}

void selectlocation(char location[])   //menu to select the location for vaccination in tumkur
{
    int choice,n=1;
    do
    {
        printf("\nSelect location for vaccination\n");
        printf("1.Government hospital-Tumakuru\n2.Mahatma Gandhi stadium-Tumakuru\n3.Bhadramma kalyana Mantapa-Tumakuru\n4.Sri Siddhaganga hospital-Tumakuru\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            strcpy(location,"Government hospital-Tumakuru");
            n=0;
            break;
        case 2:
            strcpy(location,"Mahatma Gandhi stadium-Tumakuru");
            n=0;
            break;
        case 3:
            strcpy(location,"Bhadramma kalyana Mantapa-Tumakuru");
            n=0;
            break;
        case 4:
            strcpy(location,"Sri Siddhaganga hospital-Tumakuru");
            n=0;
            break;
        default:
            SetColor(4);
            printf("\nInvalid choice\n\n");
            SetColor(15);
        }
    }
    while(n);
}

void selectgender(char gender[])  //stores gender in v.gender according to user choice
{
    int choice,n=1;
    do
    {
        printf("\n1.Male\n2.Female\n3.Rather not say\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            strcpy(gender,"male");
            n=0;
            break;
        case 2:
            strcpy(gender,"female");
            n=0;
            break;
        case 3:
            strcpy(gender,"others");
            n=0;
            break;
        default:
            SetColor(4);
            printf("\nInvalid choice\n");
            SetColor(15);
        }
    }
    while(n);
}

int aadharexitsin(FILE *fp,char aadharno[],int b)   //checks if the aadhar no already exist in the file 2
{
    vaccinestruct v2;
    if(b==1)
        fp=fopen("fdosefile.bin","rb");
    if(b==2)
        fp=fopen("sdosefile.bin","rb");
    while (fread(&v2,sizeof(vaccinestruct),1,fp))
        if(strcmp(aadharno,v2.aadharno)==0)
        {
            fclose(fp);
            return 1;
        }
    fclose(fp);
    return 0;
}

void registerdose2()      //menu for second dose and performs all the operations related to second dose
{
    FILE *fp,*fpp;
    fp=NULL;
    fpp=NULL;
    vaccinestruct v1, v2;
    SetColor(1);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    SetColor(15);
    printf("SECOND DOSE REGISTRATION");
    SetColor(1);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    SetColor(15);
    printf("\nEnter aadhar number\n");
    while(1)
    {
        scanf("%s",v2.aadharno);
        if(!checklength(v2.aadharno,12))
        {
            SetColor(4);
            printf("\nInvalid aadhar number,Enter again(aadhar number is 12-digit number)\n");
            SetColor(15);
            continue;
        }
        else
            break;
    }
    if(aadharexitsin(fp,v2.aadharno,1))
    {
        if(aadharexitsin(fpp,v2.aadharno,2))
        {
            SetColor(2);
            printf("\nRegestration for 2nd dose completed\n");
            SetColor(15);
            return;
        }

        else
        {
            fpp=fopen("fdosefile.bin","rb");
            while(fread(&v1,sizeof(vaccinestruct),1,fpp))
                if(strcmp(v1.aadharno,v2.aadharno)==0)
                {
                    strcpy(v2.name,v1.name);
                    strcpy(v2.gender,v1.gender);
                    strcpy(v2.phno,v1.phno);
                    v2.age=v1.age;
                }
            fclose(fpp);
            selectlocation(v2.address);
            check30days(&v2);
            check84days2(&v2);

            fp=fopen("sdosefile.bin","ab");
            fwrite(&v2,sizeof(vaccinestruct),1,fp);
            fclose(fp);
        }
    }
    else
    {
        SetColor(4);
        printf("\nPlease register for the first dose\n");
        SetColor(15);
    }
}

int displaydetails(vaccinestruct *v)   //displays the details and checks weather the user info is correct
{
    int choice;
    SetColor(14);
    printf("\nYour details:\n");
    printf("\nName:%s\nPH.NO:%s\nAge:%d\nGender:%s\nVaccination location:%s\nVaccination date:%d-%d-%d",v->name,v->phno,v->age,v->gender,v->address,v->d.da,v->d.m,v->d.y);
    SetColor(15);
    while(1)
    {
        printf("\n\nPress 1.save\nPress 2.Re-enter the details\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            return 0;
        case 2:
            return 1;
        default:
            SetColor(4);
            printf("\nInvalid choice:\n");
            SetColor(15);
        }
    }
}

int checkage(int age)    // checks age weather its valid(return 2) || not eligible for vaccination(return 1) || eligible (return 0)
{
    SetColor(4);
    if(age<=0 || age >120)
    {
        printf("\nInvalid age\n");
        SetColor(15);
        return 0;
    }
    else if(age>0 && age <=10)
    {
        printf("\nNot eligible for vaccination\n");
        SetColor(15);
        return 1;
    }
    else
    {
        SetColor(15);
        return 2;
    }
}

void check30days(vaccinestruct *ud)   // it takes the date as input and checks if it is within 30 days and confirms the vaccination slot
{
    int days,n=1;
    int mon[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    vaccinestruct sd;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    sd.d.da = local->tm_mday;
    sd.d.m  = local->tm_mon +1;
    sd.d.y  = local->tm_year + 1900;

    do
    {
        printf("\nEnter date for vaccination, dd mm yyyy formate\n");
        scanf("%d%d%d",&ud->d.da,&ud->d.m,&ud->d.y);
        days = noofdays(sd.d.y,ud->d.y,sd.d.m,ud->d.m,sd.d.da,ud->d.da,mon);
        if((days < 0) || (ud->d.y< sd.d.y)|| (days>30))
        {
            SetColor(4);
            printf("\nINVALID DATE\nschedule date within next 30 days\n");
            SetColor(15);
            n=1;
        }
        else
            n=0;
    }
    while(n);
}

void registerdose1()    //performs all the operations related to first dose and store the details in the file
{
    FILE *fp=NULL;
    int n=1;
    vaccinestruct v;
    SetColor(1);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    SetColor(15);
    printf("FIRST DOSE REGISTRAION");
    SetColor(1);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    SetColor(15);
    printf("\nEnter the Aadhaar number\n");
    while(1)
    {
        scanf("%s",v.aadharno);
        if(!checklength(v.aadharno,12))
        {
            SetColor(4);
            printf("\nInvalid Aadhaar no..re-enter 12-digit aadhar number\n");
            SetColor(15);
            continue;
        }
        else
            break;
    }
    if(aadharexitsin(fp,v.aadharno,1))
    {
        SetColor(2);
        printf("\nRegistration for the first dose completed\n");
        SetColor(15);
        return;
    }
    printf("\nEnter the name\n");
    scanf("%s",v.name);
    printf("\nEnter phone number\n");
    while(1)
    {
        scanf("%s",v.phno);
        if(!checklength(v.phno,10))
        {
            SetColor(4);
            printf("\nInvalid phone number..re-enter 10-digit phone number\n");
            SetColor(15);
            continue;
        }
        else
            break;
    }

    do
    {
        printf("\nEnter your age\n");
        scanf("%d",&v.age);
        switch(checkage(v.age))
        {
        case 0:
            n=1;
            break;
        case 1:
            return;
        case 2:
            n=0;
            break;
        }
    }
    while(n);
    selectgender(v.gender);
    selectlocation(v.address);
    check30days(&v);
    system("cls");
    if(displaydetails(&v))
    {
        system("cls");
        registerdose1();
    }
    else
    {
        fp=fopen("fdosefile.bin","ab");
        fwrite(&v,sizeof(vaccinestruct),1,fp);
        fclose(fp);
        system("cls");
        SetColor(2);
        printf("\nSlot for vaccination successfully scheduled on %d/%d/%d at %s",v.d.da,v.d.m,v.d.y,v.address);
        SetColor(15);
    }
    return;
}

void dosemenu()   //menu for vaccination
{
    int ch;
    while(1)
    {
        delay(3);
        printf("\n\n\n\t\t\t");
        SetColor(1);
        printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf("VACCINE REGISTRATION PORTAL");
        SetColor(1);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
        SetColor(1);
        printf("\n\t\t______________________________"
               "___________________________________");


        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" 1. Registration for 1st dose");
        SetColor(1);
        printf("\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" 2. Registration for 2nd dose");
        SetColor(1);
        printf("\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" 0. Logout");
        SetColor(1);
        printf("\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2_________________________________"
               "______________________________\xB2\n");
        printf("\n");
        SetColor(15);
        printf("Enter your choice:");
        scanf("%d",&ch);
        system("cls");

        switch (ch)
        {
        case 1:
            registerdose1();
            break;
        case 2:
            registerdose2();
            break;
        case 0:
            SetColor(2);
            printf("\nLOGGED OUT");
            SetColor(15);
            loginpagemenue();
        default:
            SetColor(4);
            printf("\nINVALID CHOICE");
            SetColor(15);
            break;
        }
    }
}

int passformat(char pass[])           //it checks if the password is of correct formate.It return '1' if password is of correct formate else '0'
{
    int digf=0,numf=0,splf=0,i=0,len = strlen(pass);
    SetColor(4);
    if(strlen(pass)<7)
    {
        printf("\nPassword is too short");
        SetColor(15);
        return 0;
    }
    if(strlen(pass)>20)
    {
        printf("\nPassword is too long");
        SetColor(15);
        return 0;
    }

    for(i=0; i<len; i++)
    {
        if(pass[i]>='A' && pass[i]<='Z')
        {
            numf=1;
        }
        if(pass[i] == '@' || pass[i] == '&' || pass[i] == '_' || pass[i] == '*' || pass[i] == '(' || pass [i] ==')' || pass[i] == '#' || pass[i] == '$' || pass[i]== '^' || pass[i]== '.' || pass[i]== ',')
        {
            splf =1;
        }
        if(isdigit(pass[i])==0)
            digf=1;
    }
    if(numf && splf && digf )
    {
        SetColor(15);
        return 1;
    }
    else
    {
        printf("\nPassword should contain atleast \none uppercase letter\none digit\none special character('@','#','$','^','&','*','(',')','.',',')");
        SetColor(15);
        return 0;
    }
}

int usernameexists(FILE *fp,char uname[])  //It checks if the username is already present in the file.It returs '1' if exists else '0'
{
    fp =fopen("account.bin","rb");
    accountstruct p2;
    int status=1;
    fseek(fp,0,0);
    SetColor(4);
    if(strcmp(uname,"\n")==0)
    {
        printf("\nUSERNAME CANNOT BE EMPTY\n");
        status =0;
    }

    if(strlen(uname)>20)
    {
        printf("\nUsername is too long\n");
        status=0;
    }
    if(strlen(uname)<4)
    {
        printf("\nEnter valid Username(username is to short)\n");
        status=0;
    }
    else
    {
        while(fread(&p2,sizeof(accountstruct),1,fp))
        {
            if((strcmp(uname,p2.id))==0)
            {
                printf("\nUSERNAME TAKEN....USE DIFFERENT USERNAME\n");
                status =0;
                break;
            }
        }
    }
    SetColor(15);
    return status;
}

void createaccount(FILE *fp)      //it handles the registerations section
{
    char password[20];
    accountstruct *p1;
    p1=(accountstruct*)malloc(sizeof(accountstruct));
    SetColor(5);
    printf("\n\n\n\t\t\t   \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    SetColor(15);
    printf("CREATE ACCOUNT SECTION");
    SetColor(5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    SetColor(15);
    do
    {
        printf("Enter the user name:");
        scanf("%s",p1->id);
    }
    while(!usernameexists(fp,p1->id));
    while(1)
    {
        do
        {
            printf("\nEnter password:");
            scanf("%s",p1->password);
            if(strcmp(p1->password,"0")==0)
            {
                system("cls");
                loginpagemenue();
            }
        }
        while(!passformat(p1->password));
        printf("\nRe-enter Password:");
        scanf("%s",password);
        if(strcmp(password,p1->password))
        {
            SetColor(4);
            printf("\nPasswords are not matching,Re-enter password or press 0 for main menu\n");
            SetColor(15);
        }
        else
            break;
    }
    fp =fopen("account.bin","ab");
    fwrite(p1,sizeof(accountstruct),1,fp);
    system("cls");
    SetColor(2);
    printf ("\nAccount successfully created.Login to proceed\n");
    delay(3);
    SetColor(15);
    fclose(fp);
}

void greetings(char name[])     //to print the greeting based on time
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf("\n\nHello %s,",name);
    if(timeinfo->tm_hour >=0 && timeinfo->tm_hour < 12)
        printf("Good morning");
    else if(timeinfo->tm_hour >=12 && timeinfo->tm_hour < 16)
        printf("Good afternoon\n");
    else if(timeinfo->tm_hour >=16 && timeinfo->tm_hour <19)
        printf("Good evening");
    else if(timeinfo->tm_hour >=19 && timeinfo->tm_hour <24)
        printf("Good night");
}

void displayonlyfirst(int a)
{
    int c,count=0,malecount=0,femalecount=0,otherscount=0;
    vaccinestruct v1,v2;
    FILE *fp1=NULL,*fp2=NULL;
    fp1=fopen("fdosefile.bin","rb");
    fp2=fopen("sdosefile.bin","rb");
    while(fread(&v1,sizeof(v1),1,fp1))
    {
        c=1;
        fseek(fp2,0,0);
        while(fread(&v2,sizeof(v2),1,fp2))
        {

            if(strcmp(v1.aadharno,v2.aadharno)==0)
            {
                c=0;
                break;
            }
        }
        if(c==1)
        {
            count++;
            if(strcmp("male",v1.gender)==0)
                malecount++;
            if(strcmp("female",v1.gender)==0)
                femalecount++;
            if(strcmp("others",v1.gender)==0)
                otherscount++;
            if(a==1)
            {
                printf("\nSI.NO:%d",count);
                printf("\nName:%s\nAge:%d\nGender:%s\nVaccination date:%d-%d-%d\nVaccination location:%s\n\n",v1.name,v1.age,v1.gender,v1.d.da,v1.d.m,v1.d.y,v1.address);
            }
        }
    }
    if(a==1 && count ==0)
        printf("\nThere are no registrations\n");
    if(a==2)
    {
        printf("\nNo of registrations: %d",count);
        printf("\nNo of male:%d    No of female:%d   No of others:%d",malecount,femalecount,otherscount);
    }
    fclose(fp1);
    fclose(fp2);
}

void display(int a,int b)     //it displays  the no of registration for the 2nd dose
{
    vaccinestruct v;
    FILE *fp=NULL;
    int count =0,malecount=0,femalecount=0,otherscount=0;
    if(b==1)
        fp=fopen("fdosefile.bin","rb");
    if(b==2)
        fp=fopen("sdosefile.bin","rb");
    while(fread(&v,sizeof(v),1,fp))
    {
        count++;
        if(a==1)
        {
            printf("\nSI.NO:%d",count);
            printf("\nName:%s\nAge:%d\nGender:%s\nVaccination date:%d-%d-%d\nVaccination location:%s\n\n",v.name,v.age,v.gender,v.d.da,v.d.m,v.d.y,v.address);
        }
        if(strcmp("male",v.gender)==0)
            malecount++;
        if(strcmp("female",v.gender)==0)
            femalecount++;
        if(strcmp("others",v.gender)==0)
            otherscount++;
    }
    if(a==1 && count==0)
        printf("\nThere are no registrations\n");
    if(a==2)
    {
        printf("\nNo of registrations: %d",count);
        printf("\nNo of male:%d    No of female:%d   No of others:%d",malecount,femalecount,otherscount);
    }
    fclose(fp);
}

int login(FILE *fp)       //it handles the login section.It return '1' if the login is successful else '0'
{
    fp=fopen("account.bin","rb");
    int choice,count=0;
    accountstruct p1,p2;
    SetColor(5);
    printf("\n\n\n\t\t\t   \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    SetColor(15);
    printf(" LOGIN SECTION ");
    SetColor(5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    SetColor(15);

    printf("Enter the user name:\n");
    scanf("%s",p1.id);
    printf("\nEnter password\n");
    scanf("%s",p1.password);
    fread(&p2,sizeof(accountstruct),1,fp);
    if((strcmp(p1.id,p2.id)==0) && (strcmp(p1.password,p2.password)==0))
    {
        system("cls");
        printf("\n\n\nWelcome to master password section");
        while(1)
        {
            count++;
            if(count!=1)
                delay(6);
            printf("\n\n\n1.Display all content of 1st dose\n");
            printf("2.Display no of registrations for 1st dose\n");
            printf("3.Display all the contents of 2nd dose\n");
            printf("4.Display no of registrations for 2nd dose\n");
            printf("5.Display all the contents of only 1st dose\n");
            printf("6.Display no of registrations for only 1st dose\n");
            printf("0.Logout\n");
            printf("\nEnter your choice\n");
            scanf("%d",&choice);
            system("cls");

            switch(choice)
            {
            case 1 :
                display(1,1);
                break;
            case 2 :
                display(2,1);
                break;
            case 3 :
                display(1,2);
                break;
            case 4 :
                display(2,2);
                break;
            case 5:
                displayonlyfirst(1);
                break;
            case 6:
                displayonlyfirst(2);
                break;
            case 0:
                loginpagemenue();
            default:
                SetColor(4);
                printf("\nInvalid choice");
                SetColor(15);
            }
        }
    }

    while(fread(&p2,sizeof(accountstruct),1,fp))
    {
        if((strcmp(p1.id,p2.id)==0) && (strcmp(p1.password,p2.password)==0))
        {
            system("cls");
            SetColor(2);
            printf("\nACCESS GRANTED\n");
            SetColor(1);
            greetings(p1.id);
            SetColor(15);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    fp=NULL;
    SetColor(4);
    printf("\nINVALID USER NAME OR PASSWORD\n");
    delay(3);
    system("cls");
    SetColor(15);
    login(fp);
}

int isfileexist(char filename[])  //checks weather the file is already exist or not
{
    FILE *fp = fopen(filename,"r");
    int status =0;
    if(fp!=NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}

void initiliseIdPass()   //if the file doesn't exist already,it creates the file and stores the default username and password
{
    FILE *fp;
    accountstruct a = {"admin","admin1"};
    int status = isfileexist("account.bin");
    if(!status)
    {
        fp=fopen("account.bin","wb");
        if(fp!=NULL)
        {
            fwrite(&a,sizeof(a),1,fp);
            fclose(fp);
        }
        fp =fopen("fdosefile.bin","ab");
        if(fp!=NULL)
        {
            vaccinestruct v1 = {"rakesh","Mahatma Gandhi stadium-Tumakuru",19,"male","123456789008","6362568244",8,8,2021};
            vaccinestruct v2 = {"pradhik","Government hospital-Tumakuru",19,"male","123456789009","6362568243",17,8,2021};
            vaccinestruct v3 = {"sagar","Government hospital-Tumakuru",19,"male","123456789010","6362568242",17,8,2021};
            fwrite(&v1,sizeof(vaccinestruct),1,fp);
            fwrite(&v2,sizeof(vaccinestruct),1,fp);
            fwrite(&v3,sizeof(vaccinestruct),1,fp);
            fclose(fp);
        }
    }
}

void loginpagemenue()                  //it shows the menu for login and register
{
    int choice,b=1;
    FILE *fp=NULL;
    initiliseIdPass();
    while (b==1)
    {
        SetColor(9);
        SetColor(9);
        printf("\n\n\n\t\t\t   \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" WELCOME TO THE MAIN MENU ");
        SetColor(5);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
        SetColor(5);
        printf("\n\t\t______________________________"
               "___________________________________");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" 1. USER LOGIN");
        SetColor(5);
        printf("\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" 2. CREATE NEW ACCOUNT");
        SetColor(5);
        printf("\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\xB2\xB2\xB2\xB2");
        SetColor(15);
        printf(" 0. Exit");
        SetColor(5);
        printf("\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2\t\t\t\t\t\t\t\t\xB2");
        printf("\n\t\t\xB2_________________________________"
               "______________________________\xB2\n");
        printf("\n");
        SetColor(15);
        printf("Enter your choice\n");
        scanf("%d",&choice);
        system("cls");
        switch(choice)
        {
        case 1:
            b = login(fp);
            break;
        case 2:
            createaccount(fp);
            continue;
        case 0:
            exit(0);
        default:
            SetColor(4);
            printf("\nInvalid choice");
            SetColor(8);
        }
    }
}

int main()
{
    loginpagemenue();
    dosemenu();
    return 0;
}

