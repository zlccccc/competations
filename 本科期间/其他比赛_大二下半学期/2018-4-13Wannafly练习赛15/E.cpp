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
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

struct hashmap{
	const static int mul=2333333,seed=999991;
	struct node{
		LL val;int next;
		node(){}
		node(LL v,int n):val(v),next(n){};
	}T[maxn];
	int head[seed],size;
	void clear(){
		memset(head,-1,sizeof(head));
		size=0;
	}
	void insert(int u,int v){
		LL val=(LL)u*mul+v;
		int x=val%seed;
		T[size]=node(val,head[x]);
		head[x]=size++;
	}
	bool find(int u,int v){
		LL val=(LL)u*mul+v;
		for (int i=head[val%seed];~i;i=T[i].next)
			if (T[i].val==val) return 1;
		return 0;
	}
}MP;
int T;
int n,m,q;
int U[maxn],V[maxn];
int A[maxn],mark[maxn];
const int SIZE=250;
int main() {
	int i,j;
	scanf("%d%d",&n,&m);
	MP.clear();
	FOR(i,1,m) {
		scanf("%d%d",&U[i],&V[i]);
		if (U[i]>V[i]) swap(U[i],V[i]);
		MP.insert(U[i],V[i]);
	}
	scanf("%d",&q);
	while(q--){
		int k,ans=0;
		scanf("%d",&k);
		FOR(i,1,k) scanf("%d",&A[i]);
		sort(A+1,A+1+k);
		if (k<=SIZE){
			FOR(i,1,k)
				FOR(j,i+1,k)
					if (MP.find(A[i],A[j]))
						ans++;
		}else{
			FOR(i,1,k) mark[A[i]]=1;
			FOR(i,1,m) if (mark[U[i]]&&mark[V[i]]) ans++;
			FOR(i,1,k) mark[A[i]]=0;
		}printf("%d\n",ans-k);
	}
	return 0;
}
/*
7 10
0 1
1 2
2 3
3 4
4 5
5 6
0 6
0 3
3 6
2 5
4
7 0 1 2 3 4 5 6
5 0 3 2 5 6
5 0 1 2 5 6
3 0 3 6
*/
