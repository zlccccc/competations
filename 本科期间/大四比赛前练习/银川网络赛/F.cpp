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

int r[maxn],id[maxn],d[307][307];
bool cmp(int i,int j) {
	return r[i]<r[j];
}
vector<pair<pii,int> > queries[307];
int ans[maxn];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,q,i,j,o;
		scanf("%d%d",&n,&q);
		FOR(i,0,n) queries[i].clear();
		FOR(i,1,n) scanf("%d",&r[i]);
		FOR(i,1,n) id[i]=i;
		sort(id+1,id+1+n,cmp);
		FOR(i,1,n) FOR(j,1,n) scanf("%d",&d[i][j]);
		FOR(i,1,q) {
			int u,v,k;
			scanf("%d%d%d",&u,&v,&k);
			r[n+1]=k;
			int idx=upper_bound(id+1,id+1+n,n+1,cmp)-id-1;
			// printf("idx=%d\n",idx);
			queries[idx].push_back(make_pair(make_pair(u,v),i));
		}
		FOR(o,0,n) {
			if (o!=0) {
				int k=id[o];
				FOR(i,1,n) FOR(j,1,n) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			} for (auto now:queries[o]) {
				ans[now.second]=d[now.first.first][now.first.second];
			}
		}
		printf("Case #%d:\n",_);
		FOR(i,1,q) printf("%d\n",ans[i]);
	}
}
/*
1
3 4
1 2 3
0 1 8
1 0 1
8 1 0
1 3 0
1 3 1
1 3 2
1 3 3
*/