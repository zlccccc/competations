#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    int N,credit,addcredit;
    double sum;
    string s;
    while(scanf("%d",&N)!=EOF)
    {
        sum=0;
        addcredit=0;
        for(int i=0;i<N;i++)
        {
            scanf("%d",&credit);
            cin>>s;
            if(s=="A")
            {
                addcredit+=credit;
                sum+=4*credit;
            }
            else if(s=="A-")
            {
                addcredit+=credit;
                sum+=3.7*credit;
            }
            else if(s=="B+")
            {
                addcredit+=credit;
                sum+=3.3*credit;
            }
            else if(s=="B")
            {
                addcredit+=credit;
                sum+=3*credit;
            }
            else if(s=="B-")
            {
                addcredit+=credit;
                sum+=2.7*credit;
            }
            else if(s=="C+")
            {
                addcredit+=credit;
                sum+=2.3*credit;
            }
            else if(s=="C")
            {
                addcredit+=credit;
                sum+=2*credit;
            }
            else if(s=="C-")
            {
                addcredit+=credit;
                sum+=1.7*credit;
            }
            else if(s=="D")
            {
                addcredit+=credit;
                sum+=1.3*credit;
            }
            else if(s=="D-")
            {
                addcredit+=credit;
                sum+=1.0*credit;
            }
            else if(s=="F")
            {
                addcredit+=credit;
                sum+=0*credit;
            }
        }
        if(addcredit==0)
            printf("0.00\n");
        else printf("%.2f\n",sum/addcredit);
    }
    return 0;
}
