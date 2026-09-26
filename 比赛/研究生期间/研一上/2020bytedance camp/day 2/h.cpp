#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=500009;

int nn;
long long b[maxn];
int lowbit(int x){
	return x&(-x);
}
struct BIT{
	int c[maxn];
	void Add(int x,int val){
		while(x<=nn){
			c[x]+=val;
			x+=lowbit(x);
		}
	}
	int Pre(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=lowbit(x);
		}
		return ret;
	}
	int query(int l,int r){
		return Pre(r)-Pre(l-1);
	}
}T[2];//0=green 1=violet

int n,q;
char S[maxn];

int read(){
	int r=0,k=1;
	char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')k=-1;
	for(;c>='0'&&c<='9';c=getchar())r=r*10+c-'0';
	return r*k;
}

int opt[maxn][2];
long long a[maxn];

int main(){
	scanf("%d%d",&n,&q);
	scanf("%s",S+1);
	b[nn=1]=0;
	for(int i=1;i<=q;++i){
		opt[i][0]=read();opt[i][1]=read();
		a[opt[i][0]]+=opt[i][1];
		b[++nn]=a[opt[i][0]];
	}
	sort(b+1,b+1+nn);
	nn=unique(b+1,b+1+nn)-b-1;
	long long ans=0;
	for(int i=1;i<=n;++i){
		a[i]=0;
		if(S[i]=='G')T[0].Add(1,1);
		else T[1].Add(1,1);
	}
	for(int i=1;i<=q;++i){
		int id=opt[i][0];
		int p0=lower_bound(b+1,b+1+nn,a[id])-b;
		a[id]+=opt[i][1];
		int p1=lower_bound(b+1,b+1+nn,a[id])-b;
		if(S[id]=='G'){
			T[0].Add(p0,-1);T[0].Add(p1,1);
			ans-=T[1].query(p0+1,p1);
		}else{
			T[1].Add(p0,-1);T[1].Add(p1,1);
			ans+=T[0].query(p0,p1-1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
