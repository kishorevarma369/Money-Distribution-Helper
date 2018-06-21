#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define mdata "data.dat"
#define tmdata "datatemp.dat"
char s[100];
typedef struct mms members;
typedef struct mms* membersptr;
struct mms
{
  char name[100];
  int value;
};

void Add_members()
{
    system("cls");
    system("title Distribution-Add_Members");
    int note=0,option,incop=0,i=0;
    FILE *fp;
    if((fp=fopen(mdata,"a"))==NULL)
    {
      printf("sorry for inconvinence\nError code:3\n");
      return;
    }
    if(feof(fp)) printf("initially empty\n");
    int n;
    printf("Enter how many members you want to add to present list:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
      scanf("%s",s);
      fprintf(fp,"%s\n",s);
    }
    note=1;
    fclose(fp);
    printf("\n\nAdded %d members successfully \n\n",i);
    system("pause");
}

void View_members()
{
  int note=0,option,incop=0,i=0;
  system("cls");
  system("title Distribution-View_Members");
  FILE *fp;
  if((fp=fopen(mdata,"r"))==NULL)
  {
    printf("sorry for inconvinence\nError code:3\n\npossible reasons\n\n1)You havent added any members yet\n2)file is deleted\n ");
    system("pause");
    return;
  }
  fscanf(fp,"%s\n",s);
  if(strcmp(s,"")==0)
  {
    printf("\n\nIt looks like you havent added any members yet\n\ntry adding and then enter this option\n\n");
    system("pause");
    return;
  }
  rewind(fp);
  if(feof(fp)) printf("No members\n\n");
  else
  {
    printf("Members are \n\n");
    while(!feof(fp))
    {
      fscanf(fp,"%s\n",s);
      printf("%d)%s\n",1+i++,s);
    }
    printf("\n");
  }
  printf("\n\n");
  system("pause");
  fclose(fp);
}


void Remove_members()
{
  int note=0,option,incop=0,i=0,flag=0,n;
  system("cls");
  system("title Distribution-Remove_Members");
  char s1[100],s2[100];
  FILE *fp,*fp1;
  if((fp=fopen(mdata,"r"))==NULL)
  {
    printf("sorry for inconvinence\nError code:3\n\npossible reasons\n\n1)You havent added any members yet\n2)file is deleted\n ");
    system("pause");
    return;
  }
  fscanf(fp,"%s\n",s);
  if(strcmp(s,"")==0)
  {
    printf("\n\nIt looks like you havent added any members yet\n\ntry adding and then enter this option\n\n");
    system("pause");
    return;
  }
  rewind(fp);
  if(feof(fp)) note=1;
  else
  {
    printf("Members are \n");
    while(!feof(fp))
    {
      fscanf(fp,"%s\n",s);
      printf("%d)%s\n",1+i++,s);
    }
    printf("\n");
  }
  rewind(fp);
  printf("Enter id of member:");
  scanf("%d",&n);
  if(n>i||n<=0)
  {
    printf("\n\nYou Didn't Enter a valid Member id returning to main menu\n\n");
    system("pause");
    return;
  }
  if((fp1=fopen(tmdata,"w"))==NULL)
  {
    printf("sorry for inconvinence\nError code:3\n\npossible reasons\n\n1)You havent added any members yet\n2)file is deleted\n ");
    system("pause");
    return;
  }
  i=0;
  if(feof(fp)) note=1;
  else
  {
    while(!feof(fp))
    {
      i++;
      fscanf(fp,"%s\n",s1);
      if(i!=n) fprintf(fp1,"%s\n",s1);
    }
    printf("\nMember %d deleted\n",n);
  }
  fclose(fp);
  fclose(fp1);
  remove(mdata);
  rename(tmdata,mdata);
  printf("\n\n");
  system("pause");
}

void sort(membersptr *arr,int n)
{
  int i,j,flag=0;
  members *temp;
  for(i=0;i<n;i++)
  {
    flag=0;
    for(j=0;j<n-i-1;j++)
    {
      if(arr[j]->value>arr[j+1]->value)
      {
        flag=1;
        temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
    if(flag==0) return;
  }
}

void WMD()
{
  system("cls");
  system("title Distribution-calculator");
  int i=0,n,avg,sum1=0,sum2=0,flag=0,flag1=0;
  FILE* fp;
  if((fp=fopen(mdata,"r"))==NULL)
  {
    printf("sorry for inconvinence\nError code:3\n\npossible reasons\n\n1)You havent added any members yet\n2)file is deleted\n ");
    system("pause");
    return;
  }
  fscanf(fp,"%s\n",s);
  if(strcmp(s,"")==0)
  {
    printf("\n\nIt looks like you havent added any members yet\n\ntry adding and then enter this option\n\n");
    system("pause");
    return;
  }
  else i++;
  while(!feof(fp))
  {
    fscanf(fp,"%s\n",s);
    i++;
  }
  rewind(fp);
  n=i;
  membersptr udata[i];
  printf("\nEnter How Much Each Member Spent :\n\n");
  for(i=0;i<n;i++)
  {
    fscanf(fp,"%s\n",s);
    udata[i]=malloc(sizeof(members));
    strcpy(udata[i]->name,s);
    printf("%s spent:",s);
    scanf("%d",&udata[i]->value);
  }
  fclose(fp);
  sort(udata,n);
  avg=0;
  for(i=0;i<n;i++)
  {
    avg+=udata[i]->value;
  }
  avg=ceil((double)avg/n);
  system("cls");
  for(i=0;i<n;i++)
  {
    if(flag==0)
    {
      printf("\nMoney should be collected from these individuals\n\n%5s %50s\n\n"," AMOUNT","MEMBER");
      flag=1;
    }
    if(udata[i]->value<avg)
    {
      printf("%5d Rs  %50s\n",abs(udata[i]->value-avg),udata[i]->name);
      sum1+=abs(udata[i]->value-avg);
    }
    if(udata[i]->value>avg)
    {
      if(flag1==0)
      {
        printf("\nMoney should be given to these individuals\n\n%5s %50s\n\n"," AMOUNT","MEMBER");
        flag1=1;
      }
      printf("%5d Rs  %50s\n",abs(udata[i]->value-avg),udata[i]->name);
      sum2+=abs(udata[i]->value-avg);
    }
  }
  if(sum1>sum2) printf("\n\nGive %d Rs for writer of this program  :)\n\n\n",sum1-sum2);
  else if(sum1<sum2) printf("\n\nSorry I did my Best for Distribution.Anyway dont Worry about %d.you got what you got\n\n\n",sum2-sum1);
  for(i=0;i<n;i++)
  {
    free(udata[i]);
  }
  printf("\n");
  system("pause");

}
void main()
{
    int option,incop=0;
    while(1)
    {
      system("cls");
      system("title Distribution");
      printf("1) Add members\n");
      printf("2) view members\n");
      printf("3) Remove members\n");
      printf("4) Calculate Weekly Money Distribution\n");
      printf("5) Exit\n");
      if(incop) printf("\tNote: U gave an invalid option previously\n");
      incop=0;
      printf("Enter an option>>");
      scanf("%d",&option);
      switch (option) {
        case 1:Add_members();
                break;
        case 2:View_members();
                break;
        case 3:Remove_members();
                break;
        case 4:WMD();
                break;
        case 5:system("cls");
              printf("Thank you for using\n");
              system("pause");
              exit(0);
        default:printf("incorrect option\n");
                incop=1;
      }
    }
}
