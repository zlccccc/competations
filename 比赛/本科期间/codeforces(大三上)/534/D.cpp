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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

ll A[maxn];
int e[maxn];
int bit[1<<12|7];
vector<ll> p;
priority_queue<pair<int,int> > id[1<<12|7];//best_id
ll pre[12][1<<12|7],now[12][1<<12|7];//pos,value,used
map<ll,vector<int> > MP;//base; downvalue
vector<int> trans[maxn];//trans
int main() {
	int i;
	int n; ll k;
	scanf("%d%lld",&n,&k);
	FOR(i,1,n) scanf("%lld",&A[i]);
	FOR(i,1,n) scanf("%d",&e[i]);
	ll g=A[1],tmp;
	FOR(i,2,n) g=gcd(g,A[i]); tmp=g;
	for (ll i=2;i<=g/i;i++) if (tmp%i==0){
		while (tmp%i==0) tmp/=i;
		p.push_back(i);
	} if (tmp!=1) p.push_back(tmp);
	// for (int v:p) printf("%d ",v); puts("<- p");

	int N=1<<p.size(),C=p.size();
	rep(i,1,N) bit[i]=bit[i>>1]+(i&1);
	FOR(i,1,n) {
		ll base=1; int j;
		REP(j,C) if (A[i]%p[j]==0)
			while (A[i]%p[j]==0) A[i]/=p[j],base*=p[j];
		MP[base].push_back(i);
	}
	// puts("first: ok");
	for (auto now:MP){//check
		sort(now.second.begin(), now.second.end(),[](int i,int j){
			return e[i]<e[j];
		}); if ((int)now.second.size()>C) now.second.resize(C);
		int sta,j;
		REP(sta,N) {
			ll _k=1,x=now.first;
			REP(j,C) if ((sta>>j)&1)
				while (x%p[j]==0) x/=p[j],_k*=p[j];
			if (_k<=k) {
				for (int v:now.second) {
					id[sta].push(make_pair(e[v],v));
					// printf("%d : ;bit=%d ",v,bit[sta]); pr2(sta,C); puts("<- trans");
					if ((int)id[sta].size()>C) id[sta].pop();
				}
			}
		}
	}
	//transfer
	int sta;
	rep(sta,1,N) {
		while (id[sta].size()){
			// printf("actual_trans %d ",id[sta].top().second); pr2(sta,C); puts("");
			trans[id[sta].top().second].push_back(sta);
			id[sta].pop();
		}
	} memset(now,0x3f,sizeof(now));
	now[0][0]=0;
	FOR(i,1,n) if (trans[i].size()){
		REP(k,C+1) memcpy(pre[k],now[k],N*sizeof(ll));
		for (int v:trans[i]){
			// printf("trans %d :",i); pr2(v,C); puts("");
			int all=(N-1)^v;
			for (int x=all;;x=(x-1)&all) {
				// pr2(x,C); printf("->"); pr2(x|v,C); printf("%lld+%d",pre[k][x],e[i]); puts("");
				REP(k,C+1) min_(now[k+1][x|v],pre[k][x]+e[i]);
				if (!x) break;
			}
		}
	} ll ans=INFF;
	REP(k,C+1) if (now[k][N-1]!=INFF)
		min_(ans,now[k][N-1]*k);
	if (ans==INFF) puts("-1");
	else printf("%lld\n",ans);
}
/*
6 10
599999999862 599999999862 599999999862 599999999862 599999999862 599999999862
1 1 1 1 1 1
*/