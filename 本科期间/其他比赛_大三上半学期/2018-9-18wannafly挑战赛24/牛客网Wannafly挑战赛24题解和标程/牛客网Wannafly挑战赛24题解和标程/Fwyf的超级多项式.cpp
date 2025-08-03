#include<bits/stdc++.h>
using namespace std;
const int mod=1004535809;
int Pow(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=1ll*ret*a%mod;
		a=1ll*a*a%mod;
		b/=2;
	}
	return ret;
}

const int MAXN=(1<<18)+10;

struct NumberTheoreticTransform{
	int n,rev[MAXN];
	int g;
	void ini(int lim)
	{
		g=3;
		n=1;
		int k=0;
		while(n<=lim)
		{
			n<<=1;
			k++;
		}
		for(int i=0;i<n;i++)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	}
	void dft(int *a,int flag)
	{
		for(int i=0;i<n;i++)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
		for(int l=2;l<=n;l<<=1)
		{
			int m=l>>1;
			int wn=Pow(g,flag==1?((mod-1)/l):(mod-1-(mod-1)/l));
			for(int *p=a;p!=a+n;p+=l)
			{
				int w=1;
				for(int k=0;k<m;k++)
				{
					int t=1ll*w*p[k+m]%mod;
					p[k+m]=(p[k]-t+mod)%mod;
					p[k]=(p[k]+t)%mod;
					w=1ll*w*wn%mod;
				}
			}
		}
		if(flag==-1)
		{
			long long inv=Pow(n,mod-2);
			for(int i=0;i<n;i++)
				a[i]=1ll*a[i]*inv%mod;
		}
	}
	void mul(int *a,int *b,int m)
	{
		ini(m);
		dft(a,1);
		dft(b,1);
		for(int i=0;i<n;i++)
			a[i]=1ll*a[i]*b[i]%mod;
		for(int i=0;i<n;i++)
			b[i]=0;
		dft(a,-1);
	}
}f;
int a[808080];
int b[101010],F[102020];
void calc(int l,int r)
{
	if(l==r)
	{
		a[l*8]=mod-b[l];
		a[l*8+1]=1;
		return;
	}
	int m=(l+r)/2;
	calc(l,m);
	calc(m+1,r);
	f.mul(a+l*8,a+(m+1)*8,r-l+1);
}


int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++)
	{
		scanf("%d",&b[i]);
		b[i]%=mod;
		b[i]+=mod;
		b[i]%=mod;
	}
	for(int i=1;i<=k;i++)
		scanf("%d",&F[i]);
	calc(0,k-1);
	for(int i=k+1;i<=n;i++)
	{
		F[i]=0;
		for(int j=1;j<=k;j++)
		{
			F[i]-=1ll*F[i-j]*a[k-j]%mod;
			if(F[i]<0)
				F[i]+=mod;
		}
	}
	printf("%d\n",F[n]);
	return 0;
}
