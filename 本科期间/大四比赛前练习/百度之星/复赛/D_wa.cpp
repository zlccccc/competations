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

// #define make_pair mp
//dp[i][j]:在j的有多少count
vector<ll> V;
ll base=0,mul=1;
inline ll getid(ll x) {return mul*(x-base);}//rollback to 1
ll value[maxn],c[maxn];//3e3*某个值
inline void update(ll l,ll r,ll val,int op) {
	// printf("update: %lld %lld %lld\n",l,r,val);
	int i;
	REP(i,(int)V.size()-1) {
		if (l<=V[i]&&V[i]<=r) {
			// printf("%lld->%lld: add=%lld\n",V[i],V[i+1],val);
			if (!op) add_(value[i],val);
			else value[i]=val;
		}
	}
}
inline ll getsum(ll l,ll r) {
	int i; ll ret=0;
	REP(i,(int)V.size()-1) {
		if (l<=V[i]&&V[i]<=r) add_(ret,value[i]*((V[i+1]-V[i])%M)%M);
	}
	// printf("query:%lld-%lld :%lld\n",l,r,ret);
	return ret;
}
inline void print(){
	int i;
	REP(i,(int)V.size()-1) if (value[i]){
		// printf("(%lld,%lld,%lld) ",V[i],V[i+1],value[i]);
		printf("(%lld,%lld,%lld) ",(V[i]-base)*mul,(V[i+1]-base)*mul,value[i]);//roll
	} puts("");
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,i;
		scanf("%d",&n);
		FOR(i,2,n) scanf("%lld",&c[i]);
		V.clear();
		base=0; mul=1;
		FOR(i,2,n) {
			ll o1,o2,l,r;

			o1=getid(c[i]),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			V.push_back(l); V.push_back(r+1);
			o1=getid(1),o2=getid(c[i]-1);
			l=min(o1,o2),r=max(o1,o2);
			V.push_back(l); V.push_back(r+1);

			// printf("%d-%d %d %d\n",getid(0),getid(c[i]),base,mul);
			mul=-mul; base=c[i]-base;
			//1 to c[i]-1; remove_first
			o1=getid(0),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			V.push_back(-INFF); V.push_back(l+1);
			V.push_back(r); V.push_back(INFF+1);
			//1->c-1; nowvalue

			o1=getid(c[i]),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			V.push_back(l); V.push_back(r+1);

			o1=getid(1),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			V.push_back(l); V.push_back(r+1);
			// update(l,r,nowans_c,0);
		} V.push_back(1); V.push_back(INF+1);
		V.push_back(-INFF); V.push_back(INFF+1);
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(), V.end()),V.end());
		REP(i,(int)V.size()) value[i]=0;
		// REP(i,(int)V.size()) printf("%lld ",V[i]); puts("<- v");
		base=0; mul=1;
		update(1,INF,1,0);
		FOR(i,2,n) {
			ll o1,o2,l,r;
			o1=getid(c[i]),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			ll nowans_c=getsum(l,r);//前面是c_i
			o1=getid(1),o2=getid(c[i]-1);
			l=min(o1,o2),r=max(o1,o2);
			ll nowans_all=getsum(l,r);

			// printf("%d-%d %d %d\n",getid(0),getid(c[i]),base,mul);
			mul=-mul; base=c[i]-base;
			// printf("%d-%d %d %d\n",getid(0),getid(c[i]),base,mul);
			//1 to c[i]-1; remove_first
			o1=getid(0),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			update(-INFF,l,0,1); update(r,INFF,0,1);
			o1=getid(c[i]),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			update(l,r,nowans_all,0);
			o1=getid(1),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			update(l,r,nowans_c,0);
			// printf("insert: %lld\n",nowans);
			// print();
			// system("pause");
		}
		printf("%lld\n",getsum(-INFF,INFF)%M);
	}
}