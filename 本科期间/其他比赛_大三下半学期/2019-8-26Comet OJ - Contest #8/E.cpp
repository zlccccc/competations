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
const LL maxn=1e6+107;
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
	if (a==0) return 0;
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int value[maxn],ind[maxn];
inline void init() {
	ind[1]=0; value[0]=1;
	int r=10,i;
	FOR(i,1,786431) {
		value[i]=value[i-1]*r%786433;
		ind[value[i]]=i;
	}
}
inline int mpow(int a) {
	if (a%786433==0) return 0;
	return value[(ll)ind[a%786433]*a%786432];
}
int ans;
vector<int> edge[maxn];
vector<pii> MP[maxn];//value,count
int A[maxn];
void dfs(int x,int fa) {
	MP[x].push_back(make_pair(A[x],1));
	add_(ans,mpow(A[x]),786433);
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x);
		vector<pii> tmpv,tmpx,nxt;
		tmpv.swap(MP[v]); tmpx.swap(MP[x]);
		for (auto pv:tmpv) for (auto px:tmpx) {
			add_(ans,mpow(pv.first&px.first)*(ll)pv.second%786433*px.second%786433,786433);
		} int i=0,j=0;
		while (i<(int)tmpx.size()||j<(int)tmpv.size()) {
			pii ins;
			if (j==(int)tmpv.size()||(i!=(int)tmpx.size()&&tmpx[i]<tmpv[j])) {
				ins=tmpx[i]; i++;
			} else {
				ins=tmpv[j]; j++; ins.first&=A[x];
			}
			if (MP[x].size()&&MP[x].rbegin()->first==ins.first)
				add_(MP[x].rbegin()->second,ins.second,786433);
			else MP[x].push_back(ins);
		}
		// for (auto now:MP[x]) printf("(%d,%d) ",now.first,now.second); puts("");
	}
}
int main() {
	int n,i;
	init();
	// FOR(i,1,100) printf("%d %d\n",powMM(i,i,786433),mpow(i));
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	printf("%d\n",ans);
}
/*
3
1 2 3
1 2
2 3
*/