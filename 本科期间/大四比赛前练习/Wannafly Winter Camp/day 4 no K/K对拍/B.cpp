#include<bits/stdc++.h>
#define rre(i,r,l) for(int i=(r);i>=(l);i--)
#define re(i,l,r) for(int i=(l);i<=(r);i++)
#define Clear(a,b) memset(a,b,sizeof(a))
#define inout(x) printf("%d",(x))
#define douin(x) scanf("%lf",&x)
#define strin(x) scanf("%s",(x))
#define op operator
typedef unsigned long long ULL;
typedef const int cint;
typedef long long LL;
using namespace std;
template<typename Q>
void inin(Q &x)
{
	x=0;int f=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	x=f?-x:x;
}
int n;
LL w[100010];
int head[100010],Next[200020],zhi[200020],ed;
LL dis[100010];
void add(int a,int b)
{
	Next[++ed]=head[a],head[a]=ed,zhi[ed]=b;
	Next[++ed]=head[b],head[b]=ed,zhi[ed]=a;
}
LL Max[100010];
void dfs(int x,int f)
{
	Max[x]=max(0LL,dis[x]);
	for(int i=head[x];i;i=Next[i])if(zhi[i]!=f)
	{
		dis[zhi[i]]=dis[x]+w[zhi[i]];
		dfs(zhi[i],x);
		Max[x]=max(Max[x],Max[zhi[i]]);
	}
}
LL sta[100010];
int top;
LL ans[100010];
bool bo[100010];
void wocao(LL x)
{
	if(x<0)cout<<"-";
	x=abs(x);
	int bb=0;
	rre(i,62,0)if(x&(1LL<<i))putchar('1'),bb=1;
	else if(bb)putchar('0');
	if(!bb)cout<<"0";
	cout<<"\n";
}
int main()
{
	inin(n);
	re(i,1,n)inin(w[i]),w[i]=w[i]==0?0:w[i]>=0?(1LL<<(w[i]-1)):-(1LL<<(-w[i]-1));
	re(i,2,n)
	{
		int x,y;
		inin(x),inin(y);
		add(x,y);
	}
	int q;
	inin(q);
	re(i,1,q)
	{
		int x;
		inin(x);
		if(bo[x])
		{
			wocao(ans[x]);
			continue;
		}
		bo[x]=1;
		dis[x]=0;
		dfs(x,0);
		top=0;
		for(int i=head[x];i;i=Next[i])sta[++top]=Max[zhi[i]];
		sort(sta+1,sta+top+1);
		ans[x]=0;
		rre(i,top,max(1,top-3))ans[x]+=sta[i];
		ans[x]+=w[x];
		wocao(ans[x]);
	}
	return 0;
}
