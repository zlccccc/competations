#include <iostream>
#include <cstdio>
using namespace std;
class heap//小根堆 
{
private:
	long long a[200001];
	inline void _swap(long long *A,long long *B) {*A^=*B^=*A^=*B;}
	void heapup(long long X)
	{
		for (;X!=1&&a[X]<a[X>>1];X>>=1)
			_swap(&a[X],&a[X>>1]);
	}
	void heapdown(long long X)
	{
		while (X<<1<=n)
		{
			int X0=X<<1;
			if ((X0^1)<=n&&a[X0]>a[X0^1]) X0^=1;
			if (a[X]>a[X0]) {_swap(&a[X],&a[X0]); X=X0;}
			else break;
		}
	}
public:
	long long n; 
	void reset()
	{
		n=0;//数据多少
		for (long long i=1;a[i]!=0;i++) a[i]=0;
	}
	void in(long long A)
	{
		a[++n]=A;
		heapup(n);
	}
	long long out()
	{
		long long xx=a[1];
		a[1]=a[n--];
		heapdown(1);
		return xx;
	}
	long long print()
	{
		printf("\n%d       ",n);
		for (int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
	}
};
inline long long MAX(long long A,long long B){return A>B?A:B;}
long long a[200001];
bool b[200001];
long long c[200001];//考虑a[]元素很多 
heap heap1;
long long x;
long long i,j,k,n;
long long sum=0,suml=0;
long long ss,xx;
int main()
{
	scanf("%I64d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%I64d",&x);
		heap1.in(x);
		sum+=x;
	}
	for (i=1;i<=n;i++)
		a[i]=heap1.out();
	ss=a[n];
	for (i=1;i<n&&sum-suml>ss;i++)
	{
		if (b[i]) continue;
		xx=1; c[0]=i;
		for (j=1;j<=a[n]/a[i];j++)
		{
			for (k=MAX(c[j-1],c[j]);k<n&&a[k+1]<a[i]*(j+1);k++);//find
			c[j]=k;
			xx+=j*(c[j]-c[j-1]);
		}
		if (ss<xx*a[i]) ss=xx*a[i];
		suml+=a[i];
//		for (j=0;j<=a[n]/a[i];j++) printf("%I64d ",c[j]);
//		printf("       %I64d\n",xx);
	}
	printf("%I64d",ss);
}
