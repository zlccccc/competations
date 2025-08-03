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

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=1666;
	const int MAX=3162;
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) break;
			}
		}
	}
}
vector<int> _p;
int A[maxn];
vector<pii> inside[maxn];
struct _query{
	int l,r,id;
}Q[maxn];
const int SIZE=1000;
const int maxvalue=1e7+7;
int block[maxn];
unsigned value[maxvalue],nowans,ans[maxn],pval[maxn];
void insertPos(int id) {
	for (auto now:inside[id]) {
		nowans+=value[now.first]*now.second;
		value[now.first]+=A[id];
	} nowans+=pval[id];
}
void removePos(int id) {
	for (auto now:inside[id]) {
		value[now.first]-=A[id];
		nowans-=value[now.first]*now.second;
	} nowans-=pval[id];
}
int main() {
	seives::init();
	// printf("%d\n",seives::tot);
	int T,_; T=1;
	REP(_,seives::tot) _p.push_back(seives::p[_]);
	scanf("%d",&T);
	FOR(_,1,T){
		int n,q,i;
		scanf("%d%d",&n,&q);
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(i,1,n) {
			vector<pii> &ins=inside[i];
			ins.clear(); int t=A[i]; pval[i]=A[i];
			ins.push_back(make_pair(1,A[i]*2));
			for (int v:_p) if (t%v==0){
				while (t%v==0) t/=v; pval[i]=pval[i]/v*(v-1);
				int maxk=ins.size(),k;
				REP(k,maxk)
					ins.push_back(make_pair(ins[k].first*v,-ins[k].second/v));
			} if (t!=1) {
				int v=t,maxk=ins.size(),k; pval[i]=pval[i]/v*(v-1);
				REP(k,maxk)
					ins.push_back(make_pair(ins[k].first*v,-ins[k].second/v));
			} pval[i]*=A[i];
			for (auto now:ins) value[now.first]=0;
			// for (pii now:ins) printf("(%d,%d)",now.first,now.second); puts("");
		}
		//n*n/SIZE + Q*SIZE; randomly->ok
		FOR(i,1,n) block[i]=i/SIZE;
		FOR(i,1,q) {
			scanf("%d%d",&Q[i].l,&Q[i].r);
			Q[i].id=i;
		}
		sort(Q+1,Q+1+q,[&](const _query &x,const _query &y){
			if (block[x.r]!=block[y.r]) return x.r<y.r;
			return (bool)((x.l<y.l)^(block[x.r]&1));
		});
		int l=1,r=0; nowans=0;
		FOR(i,1,q) {
			_query q=Q[i];
			while (l<q.l) {removePos(l); l++;}
			while (l>q.l) {l--; insertPos(l);}
			while (r<q.r) {r++; insertPos(r);}
			while (r>q.r) {removePos(r); r--;}
			ans[q.id]=nowans;
		}
		FOR(i,1,q) printf("%u\n",ans[i]);
	}
}
/*
2
5 1
1 2 3 4 5
1 5

5 2
10 5 4 7 3
1 5
2 4
*/