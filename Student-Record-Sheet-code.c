#include<stdio.h>
#include<conio.h>

void insert_record();
void display_record();
void search_record();
void del_record();
void update_record();

struct student
{
    int roll;
    char sec[10];
    char name[40];
    int marks;
    float grade_point;
};
    struct student s;
void main()
{
    int ch;
    while(ch!=7)
    {
    printf("\t***********************************************\n");
    printf("\t\tWELCOME TO STUDENT MANAGEMENT PROGRAM\n");
    printf("\t***********************************************\n\n\n");

        printf("\t**** AVAILABLE FUNCTIONALITIES ****\n\n\n");
        printf("\t\t1: Insert student record\n");
        printf("\t\t2: Display student record\n");
        printf("\t\t3: Search student record\n");
        printf("\t\t4: Delete student record\n");
        printf("\t\t5: Update student record\n");
        printf("\t\t6: Exit\n\n");
        printf("\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:insert_record();
                break;

            case 2:display_record();
                break;

            case 3:search_record();
                break;

            case 4:del_record();
                break;

            case 5:update_record();
                break;

            case 6:exit(1);

            default:
                printf("\n\t\tWrong choice Entered");
        }
        printf("\n\t\tPress any key to continue \n");
        getch();
       }
}
void insert_record()
{
    FILE *fp;
    fp=fopen("stu.txt","ab+");
    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\t **** Previous Stored Data ****");
    display_record();
    printf("\n\n\t**** ENTER NEW STUDENT DATA ****\n\n");
    printf("\n\t\tEnter Student Roll Number: ");
    scanf("%d",&s.roll);
    fflush(stdin);
    printf("\n\t\tEnter Student Name: ");
    gets(s.name);
    printf("\n\t\tEnter Student Section: ");
    gets(s.sec);
    printf("\n\t\tEnter Student Total marks: ");
    scanf("%d",&s.marks);
    printf("\n\t\tEnter Student Grade Point: ");
    scanf("%f",&s.grade_point);
    fwrite(&s,sizeof(s),1,fp);
    {
        printf("\n\n\t !!! Student Record Inserted Sucessfully\n");
    }
    fclose(fp);
    printf("\n\t\t Updated Record !!\n");
    display_record();

}

void display_record()
{
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\tError : Cannot open the File !!!");
        return;
    }
    printf("\n\n\t **** Students Details Are As Follows ****\n");
    printf("\nRoll.No\tName of Student\tSection\t\tMarks\t\tGrade Point\n\n");
    //printf("a.students roll number\t b.student name\t c.student section\t d.student marks\t e.student grade");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        printf("%d\t%s\t%s  \t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade_point);
    }
    fclose(fp);
}
void search_record()
{
    int ro,flag=0;
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\n\n\tEnter Student Roll Number Which You Want To Search: ");
    scanf("%d",&ro);
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {
        if(s.roll==ro)
        {
        flag=1;
        printf("\n\n\tSearch Sucessfull And Student Records Is as Follows: \n\n");
        printf("\nRoll.No\tName of Student\tSection\t\tMarks\t\tGrade Point\n\n");
        printf("%d\t%s\t%s  \t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade_point);
        }
    }
    if(flag==0)
    {
    printf("\n\n\t\tNo Such Record Found !!!!!\n");
    }
fclose(fp);
}
void del_record()
{
    int ro,flag=0;
    FILE *fp,*ft;
    fp=fopen("stu.txt","rb");
    ft=fopen("stu1.txt","ab+");
    if(fp==NULL)
    {
         printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\n\t **** Previous Stored Data ****");
    display_record();
    printf("\n\n\tEnter Student Roll Number Which You Want to Delete ");
    scanf("%d",&ro);
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {
        if(s.roll==ro)
        {
        flag=1;
        printf("\n\t\tRecord Deleted Sucessfully \n");

        }
        else
        {
        fwrite(&s,sizeof(s),1,ft);
        }
    }
    if(flag==0)
    {
    printf("\n\n\t\tNo Such Record Found !!!");
    }
    fclose(fp);
    fclose(ft);
    remove("stu.txt");
    rename("stu1.txt","stu.txt");
    printf("\n\t\t Updated Record !!\n");
    display_record();
}
void update_record()
{
    int ro,flag=0;
    FILE *fp;
    fp=fopen("stu.txt","rb+");
    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\n\n\tEnter Roll Number of Student Whose Record You Want To Update: ");
    scanf("%d",&ro);
    printf("\n\t\t*** Previously Stored Record Of Given Roll Number ***");

    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {
        if(s.roll==ro)
        {
        flag=1;
        printf("\nRoll.No\tName of Student\tSection\t\tMarks\t\tGrade Point\n\n");
        printf("%d\t%s\t%s  \t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade_point);
        printf("\n\t\t*** Now Enter the New Record ***\n\n");

        printf("\n\t\tUpdated Student Roll Number: ");
        scanf("%d",&s.roll);
        fflush(stdin);
        printf("\n\t\tUpdated Student Name: ");
        gets(s.name);
        printf("\n\t\tUpdated Student Section: ");
        gets(s.sec);
        printf("\n\t\tUpdated Student Marks: ");
        scanf("%d",&s.marks);
        printf("\n\t\tUpdated Student Grade Point: ");
        scanf("%f",&s.grade_point);
        fseek(fp,-(long)sizeof(s),1);
        fwrite(&s,sizeof(s),1,fp);
        printf("\n\n\t\tRecord Updated Successfully Check The Display Section!!\n\t\t");
        }
    }
    if(flag==0)
    {
        printf("\n\t\tError : Something went wrong! Data Not Found!");
    }
fclose(fp);
}


