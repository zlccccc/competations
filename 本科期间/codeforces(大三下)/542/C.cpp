#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e7+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//根本就没有subsquence...我怎么就石乐志
int n,m,q;
set<int> no={3,5,14,15};//len=4
int nxt[maxn][2],tot;
int val[maxn],pre[maxn];//end at this
int id[3007],s[3007];//start at pos; nowval
int main() {
	int _,i;
	scanf("%d",&n);
	val[0]=1; int ans=0;
	FOR(_,1,n) {
		scanf("%d",&s[_]);
		FOR(i,1,_) {
			if (!nxt[id[i]][s[_]]) {
				nxt[id[i]][s[_]]=++tot; pre[tot]=id[i]; 
				if (_-i+1>=1) add_(val[tot],val[pre[tot]]);
				if (_-i+1>=2) add_(val[tot],val[pre[pre[tot]]]);
				if (_-i+1>=3) add_(val[tot],val[pre[pre[pre[tot]]]]);
				if (_-i+1>=4&&!no.count((s[_-3]<<3)|(s[_-2]<<2)|(s[_-1]<<1)|(s[_-0]<<0)))
					add_(val[tot],val[pre[pre[pre[pre[tot]]]]]);//4
				// printf("%d : %d;pre=%d; val=%d; %d\n",i,tot,pre[tot],val[tot],(s[_-3]<<3)|(s[_-2]<<2)|(s[_-1]<<1)|(s[_-0]<<0));
				add_(ans,val[tot]);
			} id[i]=nxt[id[i]][s[_]];
		}
		printf("%d\n",ans);
	}
}
/*
3
1
1
1
*/