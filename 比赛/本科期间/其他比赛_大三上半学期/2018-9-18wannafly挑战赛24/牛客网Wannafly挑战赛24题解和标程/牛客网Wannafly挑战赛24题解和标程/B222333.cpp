#include<iostream>
#include<string>
using namespace std;
int a[10101010];
int main()
{
	int P;
	while(cin>>P)
	{
		int mm=P-1,nn=P-1;
		for(int i=0;i<=P;i++)
			a[i]=0;
		int _3i=1;
		for(int i=1;i<P;i++)
		{
			_3i=_3i*3%P;
			if(a[_3i]==0)
				a[_3i]=i;
		}
		long long _2=(P+1)/2;
		int _2i=1;
		for(int i=1;i<P;i++)
		{
			_2i=_2i*_2%P;
			if(a[_2i]!=0)
			{
				if(mm+nn>i+a[_2i])
				{
					mm=i;
					nn=a[_2i];
				}
			}
		}
		cout<<mm<<" "<<nn<<endl;
	}
	return 0;
}
