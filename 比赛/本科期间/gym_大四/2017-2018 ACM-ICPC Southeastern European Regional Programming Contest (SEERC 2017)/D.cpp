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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int ans;
int id[maxn];//idx
int fa[maxn];
set<int> v[maxn];
int getfa(int x) {
	if (x==fa[x]) return x;
	return fa[x]=getfa(fa[x]);
}
void mergeSet(int x,int y) {
	if (v[x].size()<v[y].size()) swap(v[x],v[y]);
	for (int t:v[y]) {
		if (v[x].count(t)) v[x].erase(t);
		else v[x].insert(t);
	} set<int>().swap(v[y]);
	if (!v[x].size()) ans--;
}
void merge(int x,int y) {
	int fx=getfa(x),fy=getfa(y);
	if (fx==fy) return;
	mergeSet(fx,fy);
	fa[fy]=fx;
}
int main(){
	int n,m,i;
	scanf("%d%d",&m,&n);
	FOR(i,1,m) fa[i]=i;
	FOR(i,1,m) {
		int t,k;
		vector<int> now;
		scanf("%d",&k);
		if (k==0) continue;
		ans++;
		REP(t,k) {
			int x; scanf("%d",&x);
			now.push_back(x);
			v[i].insert(x);
		} for (int x:now) {
			if (!id[x]) id[x]=i;
			else merge(i,id[x]);
		}
	}
	printf("%d\n",ans);
}
/*
3 3 
2 1 3 
2 1 2 
2 2 3

4 3 
1 1 
1 2 
1 3
3 1 2 3 

6 3
1 1
1 2
1 3
1 1
1 2
1 3

6 6
0
0
0
0
0
0

*/