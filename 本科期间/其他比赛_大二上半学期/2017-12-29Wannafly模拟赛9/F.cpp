#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int SIZE=300;
int MID=1000;
int n,m,i,j;
int a[maxn];
bool mark[maxn];
vector<pair<int,int> > QQ[maxn];
vector<int> P;
int t[maxn];
struct node{
	int l,r,id;
}Q[maxn];
LL ans[maxn];
int block[maxn];
bool cmp(node a,node b){
	if (block[a.l]==block[b.l]) return a.r<b.r;
	return a.l<b.l;
}LL now;
int num[maxn];
LL inv[maxn*2];
void add(int x){
	if (a[x]==1) return;
	(now*=inv[num[a[x]]+1])%=M;
	num[a[x]]++;
	(now*=num[a[x]]+1)%=M;
}
void del(int x){
	if (a[x]==1) return;
	(now*=inv[num[a[x]]+1])%=M;
	num[a[x]]--;
	(now*=num[a[x]]+1)%=M;
}
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,m){
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].id=i;ans[i]=1;
		QQ[Q[i].r].push_back(make_pair(Q[i].l,i));
	}FOR(i,2,MID) if (!mark[i]){
		P.push_back(i);
		for (j=i*i;j<=MID;j+=i) mark[j]=1;
	}inv[0]=inv[1]=1;
	FOR(i,2,200000) inv[i]=(M-M/i)*inv[M%i]%M;
//	FOR(i,0,100) printf("%d ",inv[i]);puts("<--");
	for (int v:P){
		FOR(i,1,n){
			t[i]=t[i-1];
			while (a[i]%v==0) a[i]/=v,t[i]++;
			for (auto now:QQ[i])
				(ans[now.second]*=(t[i]-t[now.first-1]+1))%=M;
		}
	}
//	FOR(i,1,m) printf("%d ",ans[i]);puts("");
	FOR(i,1,100000) block[i]=i/SIZE;
	sort(Q+1,Q+1+m,cmp);
	int L=1,R=0;now=1;
	FOR(i,1,m){
		while (L>Q[i].l){L--;add(L);}
		while (R<Q[i].r){R++;add(R);}
		while (L<Q[i].l){del(L);L++;}
		while (R>Q[i].r){del(R);R--;}
//		printf("%d %d %d\n",Q[i].l,Q[i].r,now);
		(ans[Q[i].id]*=now)%=M;
	}FOR(i,1,m) printf("%lld\n",ans[i]);
}
/*
*/
