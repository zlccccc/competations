#include<cstdio>
#define ll long long
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
#define MN 1000000
ll c[MN+5];
void add(int l,int r,int a,int b)
{
	c[l]+=a;
	c[l+1]+=b-a;
	c[r+1]-=a+1LL*(r-l+1)*b;
	c[r+2]+=a+1LL*(r-l)*b;
}
int main()
{
	int n=read(),i,x;ll mn=0;
	for(i=1;i<=n;++i)
	{
		x=read();
		if(x>=i)
		{
			add(0,x-i,x-i,-1);
			add(x-i,n-i,0,1);
			add(n-i+1,n-1,x-1,-1);
		}
		else
		{
			add(0,n-i,i-x,1);
			add(n-i+1,n-i+x,x-1,-1);
			add(n-i+x,n-1,0,1);
		}
	}
	for(i=1;i<n;++i)c[i]+=c[i-1];
	for(i=1;i<n;++i)if((c[i]+=c[i-1])<c[mn])mn=i;
	printf("%I64d %d",c[mn],mn);
}
