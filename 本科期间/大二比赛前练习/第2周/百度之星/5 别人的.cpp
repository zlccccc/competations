#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<cstdio>
using namespace std;
char tar[100000];
char *p;
int a1[1000000],result[1000000],sum,y;
void Tostring(int array[],int size);
int substring(char *str,char *str1);
int main()
{
    int a[10];
    int n,i,j,k,m,ch0=0,ch1=0,avi=1,total,s=0;
    cin>>total;
    while(s<total)
    {
        cin>>m;
        scanf("%s",tar);
        sum=0;
        y=0;
        for(i=0,n=0; i<m; i++)
        {
            n<<=1;
            n|=1;
        }
        n++;
        for(i=0; i<n; i++)
        {
            for(j=m-1,k=i; j>=0; j--)
            {
                a[j]=k&1;
                k>>=1;
            }
            if(a[0]==0) continue;
            for(int p=0; p<=m-1; p++)
            {
                if(a[p]==0) ch0++;
                else ch1++;
                if(ch0>ch1) avi=0;
            }
            if(avi==1&&ch1==ch0)
            {
                y=1;
                Tostring(a,m);
                continue;
            }
            ch0=0;
            ch1=0;
            avi=1;
        }
        if(sum!=0) result[s]=sum;
        s++;
    }
    for(i=0; i<s; i++) cout<<result[i]<<endl;
    system("pause");
    return 0;
}
void Tostring(int array[],int size)
{
    char *p;
    int i;
    p=(char*)malloc(size+1);
    for(i=0; i<size; i++)
    {
        *(p+i)='0'+array[i];
    } *(p+i)='\0';
    sum+=substring(p,tar);
}
int substring(char *str,char *str1)
{
    int x=0;
    do
    {
        p=strstr(str,str1);
        if(p!=NULL)
        {
            str=p+1;
            x=x+1;
        }
    }
    while(p!=NULL);
    return x;
}
