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
#include <unordered_map>
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
const LL M=1000000007;
const LL maxn=60000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int block[maxn];
struct node{
	int l,r,id;
}Q[maxn];
int cmp(node a,node b){
	if (block[a.l]==block[b.l]) return a.r<b.r;
	return block[a.l]<block[b.l];
}
int MP[maxn*27];
int A[maxn],B[27][maxn];
char a[maxn];
int ans[maxn];
int n,m,k;
int i,j;
int now;
int L=1,R=0;
const int SIZE=300;
void add(int x){
	int i;
//	printf("add: %d:",x);
//	REP(i,27) printf("%d ",B[i][x]);puts("");
	REP(i,27) if (B[i][x]) now+=MP[B[i][x]]; else break;
	MP[A[x]]++;
}
void del(int x){
	MP[A[x]]--;
	int i;
//	printf("del: %d:",x);
//	REP(i,27) printf("%d ",B[i][x]);puts("");
	REP(i,27) if (B[i][x]) now-=MP[B[i][x]]; else break;
}
unordered_map<int,int> MAP;
int tot;
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",a+1);
	FOR(i,1,m)
		scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
	FOR(i,1,n) block[i]=i/SIZE;
	FOR(i,1,n){
		A[i]=A[i-1]^(1<<(a[i]-'a'));
		if (!MAP.count(A[i])) MAP[A[i]]=++tot;
	}
	FOR(i,0,n){
		if (!MAP.count(A[i])) MAP[A[i]]=++tot;
		int t=0;
		REP(j,26){
			if (!MAP.count(A[i]^(1<<j))) continue;
			else B[t++][i]=MAP[A[i]^(1<<j)];
		}B[t++][i]=MAP[A[i]];
//		REP(j,27) printf("%d ",B[j][i]);printf("  ;  A[i]=%d",A[i]);puts("");
	}
	FOR(i,0,n) A[i]=MAP[A[i]];
//	FOR(i,1,n) printf("%d ",A[i]);puts("");
	sort(Q+1,Q+1+m,cmp);
	MP[MAP[0]]++;
	FOR(i,1,m){
		while (L<Q[i].l){del(L-1);L++;}
		while (L>Q[i].l){L--;add(L-1);}
		while (R<Q[i].r){R++;add(R);}
		while (R>Q[i].r){del(R);R--;}
//		printf("%d %d - %d\n",L,R,now);
		ans[Q[i].id]=now;
	}
	FOR(i,1,m) printf("%d\n",ans[i]);
}
/*
*/ 
