#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
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
const LL M=998244353;
const LL maxn=5e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> ID[maxn],all;
struct node{
	int l,r,k1,k2,id;
}Q[maxn];
int n,i,j,m;
int a[maxn];
int cnt[maxn];
int tot[maxn],TOT[500];//value
int num[maxn],NUM[500],INUM[500];//block,cnt
const int BLOCK=200;
int block[maxn];
bool cmp(node a,node b){
	if (block[a.l]==block[b.l]) return a.r<b.r;
	return a.l<b.l;
}
void del(int x){
//	printf("Del %d\n",x);
	int _cnt,id;
	if (cnt[a[x]]){
		_cnt=cnt[a[x]],id=ID[a[x]][cnt[a[x]]];
		num[_cnt]--;NUM[_cnt/BLOCK]--;
		if (!num[_cnt]) INUM[_cnt/BLOCK]--;
		tot[id]--;TOT[id/BLOCK]--;
	}cnt[a[x]]--;
	if (cnt[a[x]]){
		_cnt=cnt[a[x]],id=ID[a[x]][cnt[a[x]]];
		if (!num[_cnt]) INUM[_cnt/BLOCK]++;
		num[_cnt]++;NUM[_cnt/BLOCK]++;
		tot[id]++;TOT[id/BLOCK]++;
	}
}
void add(int x){
//	printf("Add %d\n",x);
	int _cnt,id;
	if (cnt[a[x]]){
		_cnt=cnt[a[x]],id=ID[a[x]][cnt[a[x]]];
		num[_cnt]--;NUM[_cnt/BLOCK]--;
		if (!num[_cnt]) INUM[_cnt/BLOCK]--;
		tot[id]--;TOT[id/BLOCK]--;
	}cnt[a[x]]++;
	if (cnt[a[x]]){
		_cnt=cnt[a[x]],id=ID[a[x]][cnt[a[x]]];
		if (!num[_cnt]) INUM[_cnt/BLOCK]++;
		num[_cnt]++;NUM[_cnt/BLOCK]++;
		tot[id]++;TOT[id/BLOCK]++;
	}
}
int ans[maxn];
int L,R;
int main(){
	scanf("%d",&n);
	FOR(i,1,40000) ID[i].push_back(0);
	FOR(i,1,n){
		scanf("%d",&a[i]);
		all.push_back(a[i]+50000*ID[a[i]].size());
		ID[a[i]].push_back(0);
	}sort(all.begin(),all.end());
	FOR(i,1,40000)
		rep(j,1,ID[i].size())
			ID[i][j]=lower_bound(all.begin(),all.end(),i+j*50000)-all.begin()+1;
	FOR(i,1,40000) block[i]=i/BLOCK;
//	for (int v:all) printf("%d ",v);
	scanf("%d",&m);
	FOR(i,1,m) scanf("%d%d%d%d",&Q[i].l,&Q[i].r,&Q[i].k1,&Q[i].k2),Q[i].id=i;
	sort(Q+1,Q+m+1,cmp);
	L=1;R=0;
	FOR(i,1,m){
		int k1=Q[i].k1,k2=Q[i].k2;
//		printf("%d %d %d %d\n",Q[i].l,Q[i].r,k1,k2);
		while (L<Q[i].l){del(L);L++;}
		while (L>Q[i].l){L--;add(L);}
		while (R<Q[i].r){R++;add(R);}
		while (R>Q[i].r){del(R);R--;}
		int now=0;
//		FOR(j,1,10) printf("%d ",num[j]);puts("<- num");
//		FOR(j,1,10) printf("%d ",tot[j]);puts("<- tot");
		while (INUM[now]<k1) k1-=INUM[now],k2+=NUM[now],now++;
		now*=BLOCK;
		while (!(num[now]&&k1==1)){
			if (num[now]) k1--,k2+=num[now];
			now++;
		}now=0;
//		printf("ASK : now= %d, k2=%d\n",now,k2);
		while (TOT[now]<k2) k2-=TOT[now],now++;
		now*=BLOCK;
		while (tot[now]<k2) k2-=tot[now],now++;
//		printf("ASK : now= %d, k2=%d;  ans=%d\n",now,k2,all[now-1]);
		ans[Q[i].id]=all[now-1]%50000;
	}FOR(i,1,m) printf("%d\n",ans[i]);
}
/*
*/
