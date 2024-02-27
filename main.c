//default password = 1234

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void password();//writing all functions on the top so that when calling functions in other functions no error happens
void change_password();
int chkpass();
int chkdate();
void program();
void load();
void save();
int quit();
void print();
void SortByDOB();
void SortByLname();
void SortBySalary();
void Sort();
void add();
int chkFloat();
int chkemail();
int chkNumber();
void modify();
void search();
void delete_employee();
void enter();
void error();
void print_sort();
int a_to_i();
int chkID();

typedef struct
{
    int day;
    int month;
    int year;
} dob;
typedef struct//creating structure to save employees' data in
{
    int ID;
    char first_name[20];
    char last_name[20];
    float salary;
    char address[50];
    char phone[15];
    char email[40];
    dob date;
} database;
database employees[1000];//array of structures that the data will be saved in
int array=0;//this global variable is the number of employees inside the system and it will be used in every function that search or sort
int save_state=1;//this global variable is equal to one when changes are saved and it changes to zero when changes are still not saved

void error() //this function changes the color to red and produces a sound for 1.5 seconds and it will be used when there is an error
{
    printf("\a");
    system("color 40");
    sleep(1);
    system("color B1");
}

void load() //this function loads all the data of the employees from the .txt file
{
    system("color B1");
    int i=0,j;
    char c;
    FILE *data;
    data = fopen("Company.txt", "r+");//the file should be in the same project folder and named data.txt , r+ as to read and if the file is not present it will be created
    fscanf(data,"%c",&c);
    if(data==NULL||c=='\0')//if there is no file in the directory or an empty file the file is created and the user can only add new employees' data
    {
        printf("Error... file not found \n\nYou can only add employees\n\n");
        error();
    }
    else if(data!=NULL&&!feof(data)) //if the file is found and data is present the data is loaded into the structure's array
    {
        fseek(data,0,SEEK_SET);
        for(i=0; !feof(data); i++)
        {
            fscanf(data,"%d",&employees[i].ID);
            fseek(data,1,SEEK_CUR);
            for(j=0; employees[i].last_name[j-1]!=','; j++)
            {
                fscanf(data,"%c",&employees[i].last_name[j]);
            }
            employees[i].last_name[j-1]='\0';
            for(j=0; employees[i].first_name[j-1]!=','; j++)
            {
                fscanf(data,"%c",&employees[i].first_name[j]);
            }
            employees[i].first_name[j-1]='\0';
            fscanf(data,"%f",&employees[i].salary);
            fseek(data,1,SEEK_CUR);
            fscanf(data,"%d",&employees[i].date.day);
            fseek(data,1,SEEK_CUR);
            fscanf(data,"%d",&employees[i].date.month);
            fseek(data,1,SEEK_CUR);
            fscanf(data,"%d",&employees[i].date.year);
            fseek(data,1,SEEK_CUR);
            for(j=0; employees[i].address[j-1]!=','; j++)
            {
                fscanf(data,"%c",&employees[i].address[j]);
            }
            employees[i].address[j-1]='\0';
            for(j=0; employees[i].phone[j-1]!=','; j++)
            {
                fscanf(data,"%c",&employees[i].phone[j]);
            }
            employees[i].phone[j-1]='\0';
            for(j=0; employees[i].email[j-1]!='\n'; j++)
            {
                fscanf(data,"%c",&employees[i].email[j]);
            }
            employees[i].email[j-1]='\0';
        }
        fclose(data);
        for(j=0;j<i;j++){//we had some issues if the number is 10 so this is to fix it
            if(employees[j].date.day==0)
                employees[j].date.day=10;
            if(employees[j].date.month==0)
                employees[j].date.month=10;
        }
        printf("\nLoading complete...\n\n");
        array=i;//array = the number of employees in the file
    }
}
void save()//this function is used to write all the employees' data in the file
{
    int i;
    if(!save_state)//it only works if the used has added, modified,deleted or sorted
    {
        FILE *data;
        data = (fopen("Company.txt", "w"));
        char myTxt;
        myTxt = '\0';
        for(i=0; i<array; i++)
        {
            fprintf(data,"%d,",employees[i].ID);
            fprintf(data,"%s,",employees[i].last_name);
            fprintf(data,"%s,",employees[i].first_name);
            fprintf(data,"%.2f,",employees[i].salary);
            fprintf(data,"%d-",employees[i].date.day);
            fprintf(data,"%d-",employees[i].date.month);
            fprintf(data,"%d,",employees[i].date.year);
            fprintf(data,"%s,",employees[i].address);
            fprintf(data,"%s,",employees[i].phone);
            fprintf(data,"%s",employees[i].email);
            if(!(i==array-1))
                fprintf(data,"%c\n",myTxt);//when writing \n in the file it had an error so we created a null character, printed it and then the \n so basically the same thing
        }
        fclose(data);//writing all the employees' data in the file
        printf("\nSaving complete...\n\n");
        save_state=1;
    }
    else//if the used made no changes then nothing to be saved
    {
        printf("\nNo changes made to be saved\n\n");
        error();
    }
}

int quit()//this function quits the program
{
    int x;
    if(save_state)//if the user has saved data or has not made any modifications then it quits directly
    {
        printf("\nQuitting");
        return 0;
    }
    else
    {
        char c[5];
        printf("Are you sure you want to exit without saving\n");//if the user has made changes without saving it asks him if he wants to save or not
        printf("1-Exit        2-Save and exit\n");
        scanf("%s",&c);
        while(a_to_i(c)>2||!chkNumber(c))//just checking if he entered a right numebr
        {
            printf("enter a valid number: ");
            error();
            scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
        }
        x=a_to_i(c);//returning it to a number to use it
        if(x==1)
        {
            printf("\nQuitting\n");
            return 0;
        }
        else if(x==2)
        {
            save();
            printf("\nQuitting\n");
            return 0;
        }
        else
        {
            printf("Enter a valid number\n");
            quit();
        }

    }
}

void sort(int i)//this function replaces the data of an employee with the next one as asked from another function
{
    database s;
    s=employees[i];
    employees[i]=employees[i+1];
    employees[i+1]=s;
}

void SortByLname()//this function sorts all data according to last name of employees
{
    int i,j;
    for(j=0; j<array-1; j++)
    {
        for(i=0; i<array-1; i++)//using sorting algorithm
        {
            if(strcasecmp(employees[i].last_name,employees[i+1].last_name)>0)
            {
                sort(i);//sending data to be sorted if it needs sortion
            }
        }
    }
}

void SortByDOB()//this function sorts all data according to date of birth of employees
{
    int i,j;
    for(j=0; j<array-1; j++)
    {
        for(i=0; i<array-1; i++)
        {
            if(employees[i+1].date.year<employees[i].date.year)//sorting if year is different
            {
                sort(i);
            }
            else if(employees[i+1].date.year==employees[i].date.year&&employees[i+1].date.month<employees[i].date.month)//sorting if year is same and month is different
            {
                sort(i);
            }
            else if(employees[i+1].date.year==employees[i].date.year&&employees[i+1].date.month==employees[i].date.month&&employees[i+1].date.day<employees[i].date.day)//sorting if year and month are same and day is different
            {
                sort(i);
            }
        }
    }
}

void SortBySalary()//this function sorts all data according to salary of employees
{
    int i,j;
    for(j=0; j<array-1; j++)
    {
        for(i=0; i<array-1; i++)//using sorting algorithm
        {
            if(employees[i+1].salary>employees[i].salary)
            {
                sort(i);//sending to function if needed sortion
            }
        }
    }
}

void print_sort()//this function is the main for sortion as it asks the user how he wants the data to be sorted and then call the other functions
{
    int x,i;
    char c[5];
    save_state=0;
    printf("\n1-Sort by last name\n2-sort by date of birth\n3-sort by salary\n");
    printf("How do you want to sort the data: ");
    scanf("%s",&c);//
    while(!chkNumber(c)||a_to_i(c)>3)
    {
        printf("\nPlease enter a valid number: ");
        error();
        scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
    }
    x=a_to_i(c);//converting input to integer to use
    switch(x)
    {
    case 1:
        SortByLname();
        break;
    case 2:
        SortByDOB();
        break;
    case 3:
        SortBySalary();
        break;
    }
    for(i=0; i<array; i++)
    {
        printf("For employee number %d",i+1);
        print(i);//sending data to be printed on screen after sortion
    }
    printf("\n");
}

void print(int i)//this function prints employees' data on screen
{
    printf("\nEmployee's ID: %d\n",employees[i].ID);
    printf("Employee's last name: %s\n",employees[i].last_name);
    printf("Employee's first name: %s\n",employees[i].first_name);
    printf("Employee's salary: %.2f\n",employees[i].salary);
    printf("Employee's date of birth: %d-%d-%d\n",employees[i].date.day,employees[i].date.month,employees[i].date.year);
    printf("Employee's address: %s\n",employees[i].address);
    printf("Employee's phone: %s\n",employees[i].phone);
    printf("Employee's E-mail: %s\n\n",employees[i].email);
}

int chkFloat(char c[]) //this function checks if the number is float
{
    int flag=0,i,flag2=0;
    int len=strlen(c);
    for(i=0; i<len; i++)
    {
        if((c[i]>'9' || c[i]<'0') && c[i]!='.')
        {
            flag=1;//if found anything other than numbers or . it breaks and flag will be 1
            break;
        }
        if(c[i]=='.') //this checks if there is more than one .
        {
            flag2++;
        }
    }
    if(flag||flag2>1)
        return 0;//if number is not valid it returns 0
    else
        return 1;//if number is valid it returns 1
}

void enter(int i)//this function is used to take employees' data from the user and validate it
{
    char ids[10],s[10],c[5];
    printf("enter the ID of employee %d: ",i+1);
    getchar();
    gets(ids);
    while(!chkNumber(ids)||strlen(ids)<1)//checking id to be numbers only
    {
        printf("enter a proper ID: ");
        error();
        gets(ids);//taking it as a char to easily detect all alphabets and symbols
    }
    while(!chkID(ids)){
        printf("This ID is already taken please enter another ID: ");
        error();
        gets(ids);
    }
    employees[i].ID=a_to_i(ids);//converting it to integer to be saved as integer
    printf("enter the last name of employee %d: ",i+1);
    gets(employees[i].last_name);
    while(!chkName(employees[i].last_name)||strlen(employees[i].last_name)<1)//checking names to be only alphabets or -
    {
        printf("enter a proper last name: ");
        error();
        gets(employees[i].last_name);
    }
    printf("enter the first name of employee %d: ",i+1);
    gets(employees[i].first_name);
    while(!chkName(employees[i].first_name)||strlen(employees[i].first_name)<1)
    {
        printf("enter a proper first name: ");
        error();
        gets(employees[i].first_name);
    }
    printf("enter the salary of employee %d: ",i+1);//cheking salary to be numbers only
    gets(s);
    while(!chkFloat(s)||strlen(s)<1)
    {
        printf("enter a proper salary: ");
        error();
        gets(s);//taking it as a char to easily detect all alphabets and symbols
    }
    employees[i].salary=atof(s);//converting it to integer
    printf("enter the day of birth of employee %d: ",i+1);
    scanf("%s",&c);
    while(a_to_i(c)>31 || a_to_i(c)<1||!chkNumber(c))//validating birthday to be from 1 to 31 only
    {
        printf("enter a proper day of birth: ");
        error();
        scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
    }
    employees[i].date.day=a_to_i(c);//converting to integer
    printf("enter the month of birth of employee %d: ",i+1);
    scanf("%s",&c);
    while(a_to_i(c)>12 || a_to_i(c)<1||!chkNumber(c))//validating month to be from 1 to 12 only
    {
        printf("enter a proper month of birth: ");
        error();
        scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
    }
    employees[i].date.month=a_to_i(c);//converting to integer
    printf("enter the year of birth of employee %d: ",i+1);
    scanf("%s",&c);
    while(a_to_i(c)>2010 || a_to_i(c)<1900||!chkNumber(c))//validating year to be from 1900 to 2022 only
    {
        printf("enter a proper year of birth: ");
        error();
        scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
    }
    employees[i].date.year=a_to_i(c);//converting to integer
    printf("enter the address of employee %d: ",i+1);
    getchar();
    gets(employees[i].address);//address can be anything
    while(strlen(employees[i].address)<1)
    {
        printf("Please enter proper address: ");
        error();
        gets(employees[i].address);
    }
    printf("enter the phone number of employee %d: ",i+1);
    gets(employees[i].phone);
    while(!chkNumber(employees[i].phone)||strlen(employees[i].phone)!=11)//checking phone number to be 11 numbers only
    {
        printf("enter a proper phone number: ");
        error();
        gets(employees[i].phone);
    }
    printf("enter the e-mail of employee %d: ",i+1);//checking email to contain @ and after it a .
    gets(employees[i].email);
    while(!chkemail(employees[i].email))
    {
        printf("enter a proper e-mail: ");
        error();
        gets(employees[i].email);
    }
}

void modify()//this function is used to modify an employee's data
{
    int i,x,f=0,j,s;
    char id[10];
    char c[10];
    printf("Enter number of employees you want to modify: ");//asking user if he wants to modify more than one employee
    scanf("%s",&c);
    while(!chkNumber(c)) //validating that he entered a number
    {
        printf("\nPlease enter a valid number: ");
        error();
        scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
    }
    x=a_to_i(c);
    for(j=0; j<x; j++)
    {
        f=0;
        printf("Enter ID of employee you want to modify: ");
        scanf("%s",&id);
        while(!chkNumber(id))
        {
            printf("enter a proper ID: ");
            error();
            scanf("%s",&id);
        }
        s=a_to_i(id);
        for(i=0; i<array; i++)//searching for the entered ID
        {
            if(s==employees[i].ID)//if found the user will then enter the new data
            {
                save_state=0;//if modified the save state will be 0 as mentioned before
                f=1;
                enter(i);
                printf("\nModified successfully\n\n");
            }
        }
        if(!f)//if not found it will print a message that no employees found
        {
            printf("\nNo employees with entered ID\n\n");
            error();
        }
    }
}


void search()//this function is used to search for an employee using his last name and printing all his data
{
    int i,f;
    char c[20];
    f=0;
    printf("Enter last name: ");
    getchar();
    gets(c);
    while(!chkName(c))//checking last name to be only alphabets or -
    {
        printf("enter a proper last name: ");
        error();
        gets(c);
    }
    f=0;
    for(i=0; i<array; i++)//searching for the entered name
    {
        if(!strcasecmp(employees[i].last_name,c))//if found his data will be printed
        {
            f=1;
            print(i);
        }
    }
    printf("\n");
    if(!f)//if not found a message will appear that no employees has this last name
    {
        printf("No employees with entered last name\n\n");
        error();
    }
}

int chkName(char n[])//this function is used to check names to contain only alphabets and -
{
    int flag=0,i;
    int len=strlen(n);
    for(i=0; i<len; i++)
    {
        if(!(n[i]>='a' && n[i]<='z' || n[i]>='A' && n[i]<='Z' || n[i]=='-')||n[i]=='\n')
        {
            flag=1;//if it found anything other than alphabets and - flag will be 1 and it will break
            break;
        }
    }
    if(flag)
        return 0;//it will return 0 if the name is not valid
    else
        return 1;//it will return 1 if the name is valid
}
int a_to_i(char s[])//this function converts number characters to integer
{
    int i, n;
    for (i = 0; s[i] == ' '; i++);
    for (n = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n= 10 * n + (s[i] - '0');
    return n;
}//note that the charachter is validated to be a number before being sent to this function so no need to be validated here

int chkNumber(char c[])//this function checks that the string sent to it is only numbers
{
    int flag=0,i;
    int len=strlen(c);
    for(i=0; i<len; i++)
    {
        if(c[i]>'9' || c[i]<'0')
        {
            flag=1;//if found anything other than numbers it breaks and flag will be 1
            break;
        }
    }
    if(flag)
        return 0;//if number is not valid it returns 0
    else
        return 1;//if number is valid it returns 1
}

int chkemail(char e[])//this function checks that an email contains @ and . after it
{
    int len,flag=0, flag1=0,flag2=1,i,j,c=0;
    len=strlen(e);
    for(j=0; j<len; j++)
    {
        if (e[j]==' ')
        {
            flag2=0;
            break;
        }
    }
    for(j=1; j<len; j++)
    {
        if (e[j]=='@')
        {
            c++;
            i=j+2;
        }
    }
    if(c>1 || c==0)
        return 0;
    else
        flag=1;
    for(i; i<len; i++)//after @ searching for .
    {
        if(e[i]=='.')
        {
            flag1=1;
            break;
        }
    }
    if(flag && flag1 && flag2)
        return 1;//if email is valid it returns 1
    else
        return 0;//if email is not valid it returns 0
}

void add()//this function is used to add new employees to the database
{
    int n,i;
    char c[10];
    save_state=0;//when adding the save state becomes 0 as mentioned before
    printf("How many employees you want to add: ");
    scanf("%s",&c);//asking the user how many employees he want to add
    while(!chkNumber(c)) //checking that he entered a number
    {
        printf("\nPlease enter a valid number: ");
        error();
        scanf("%s",&c);//taking it as a char to easily detect all alphabets and symbols
    }
    n=a_to_i(c);
    for(i=array; i<array+n; i++)
    {
        enter(i);//taking the data from the user
        printf("\nAdded successfully...\n\n");
    }
    array=i;//increasing the number of the employees after adding
}

int chkID(char c[]){
    int i,flag=1;
for(i=0;i<array;i++){
if(a_to_i(c)==employees[i].ID){
flag=0;
break;
}
}
return flag;
}

void delete_employee()//this function is used to delete employees from the database from first and last name
{
    int j,k,f=0;
    char first[20],last[20];
    printf("Enter the last name of the employee: ");//taking last name from user and validating it
    getchar();
    gets(last);
    while(!chkName(last))
    {
        printf("enter a proper last name: ");
        error();
        gets(last);
    }
    printf("Enter the first name of the employee: ");//taking first name from user and validating it
    gets(first);
    while(!chkName(first))
    {
        printf("enter a proper first name: ");
        error();
        gets(first);
    }
    for(j=0; j<array; j++)//searching for entered names
    {
        if(!strcasecmp(last,employees[j].last_name)&&!strcasecmp(first,employees[j].first_name))
        {
            save_state=0;//when deleting the save state becomes 0
            for(k=j; k<array-1; k++)
            {
                employees[k]=employees[k+1];//deleting the employee
            }
            array--;//decreasing number of employees
            f=1;
            printf("\nDeleted successfully...\n\n");
            j=0;
        }
    }
    if(!f)//if no matches for names message is printed
    {
        printf("\nNo employees found with this name\n\n");
        error();
    }
}

void program()//this function lets the user choose the operation he wants to do and then calls its function
{
    int op;
    char opp[3];
    printf("Welcome to the employees database\n\n");
    printf("Here are the operations you can do:-\n\n");
    printf("1-Search for an employee\n");
    printf("2-Add an employee\n3-Delete an employee\n");
    printf("4-Modify an employee's data\n5-Sort and print data of all employees\n");
    printf("6-Save changes made\n7-Quit\n8-Change password\n\n");
    printf("Enter the number of the operation you want to perform: ");
    scanf("%s",&opp);
    while(!chkNumber(opp)||a_to_i(opp)>8)
    {
        printf("\nPlease enter a valid number: ");
        error();
        scanf("%s",&opp);//taking it as a char to easily detect all alphabets and symbols
    }
    op=a_to_i(opp);//converting the entered number to integer to use
    switch(op)
    {
    case 1:
        search();
        system("pause");//this line and the below line is added to let the user read without many things appearing to him
        system("cls");
        program();
        break;
    case 2:
        add();
        system("pause");
        system("cls");
        program();
        break;
    case 3:
        delete_employee();
        system("pause");
        system("cls");
        program();
        break;
    case 4:
        modify();
        system("pause");
        system("cls");
        program();
        break;
    case 5:
        print_sort();
        system("pause");
        system("cls");
        program();
        break;
    case 6:
        save();
        system("pause");
        system("cls");
        program();
        break;
    case 7:
        quit();
        break;
    case 8:
        change_password();
        system("pause");
        system("cls");
        program();
        break;
    }

}

void password()//this function asks the user to enter the system's password to access the database
{
    system("color B1");
    FILE *pass;
    pass = (fopen("password.txt", "r"));//reading from file called password.txt
    char p[100],f[100],c;
    int k;
    fscanf(pass,"%c",&c);
    if(pass!=NULL&&c!='\0')//if the file exist the user is asked for the password
    {
        fseek(pass,0,SEEK_SET);
        printf("Please enter the password to access the database: ");
        gets(p);
        fgets(f,99,pass);
        fclose(pass);
        if(!strcmp(p,f))
        {
            printf("\nCorrect password ... Access granted\n\n");
            load();
            program();
        }
        else
        {
            printf("\nAccess denied ... Incorrect password ... Please try again\n\n");
            error();
            password();
        }
    }
    else//if no files present a file is created with default password 1234
    {
        printf("Welcome to the employees' database for the first time \n\nPlease note that the default password = 1234\n\n");
        FILE *pass;
        pass = (fopen("password.txt", "w"));
        fputs("1234",pass);
        fclose(pass);
        password();
    }
}

int chkpass(char c[])//this function checks that new password must contain numbers, alphabets in both cases and symbols
{
    int i,fcap=0,fnum=0,fsm=0,fsp=0,len;//creating flag for each type of characters
    len=strlen(c);
    for(i=0; i<len; i++)//checking for each type of characters
    {
        if(c[i]<='z'&&c[i]>='a')
            fsm=1;
        else if(c[i]<='Z'&&c[i]>='A')
            fcap=1;
        else if(c[i]<='9'&&c[i]>='0')
            fnum=1;
        else
            fsp=1;
    }
    if(fcap&&fnum&&fsm&&fsp)
        return 1;//returning 1 if password is valid
    else
        return 0;//returning 0 if password is not valid
}

void change_password()//this function is used to change the system's password
{
    FILE *pass;
    pass = (fopen("password.txt", "r"));
    char p[100],f[100];
    printf("Please enter the old password: ");//it asks the user for the old password then the new password
    getchar();
    gets(p);
    fgets(f,99,pass);
    fclose(pass);
    if(!strcmp(p,f))
    {
        printf("Please enter the new password\n(must contain numbers, alphabets in both cases and special characters at least 8 characters): ");
        gets(f);
        while(!chkpass(f)||strlen(f)<8)
        {
            printf("Please enter a valid password: ");
            error();
            gets(f);
        }
        pass = (fopen("password.txt", "w"));
        fputs(f,pass);
        fclose(pass);
        printf("\nPassword changed successfully\n\n");
        password();
    }
    else
    {
        printf("\nIncorrect password ... Please try again\n\n");
        error();
        program();
    }
}

int main()
{
    password();
    //load();
    //program();//if you want to use it without password uncomment this line and the above line and delete the first line
}
