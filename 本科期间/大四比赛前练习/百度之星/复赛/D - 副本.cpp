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
set<pair<pair<ll,ll>,ll> > S;//values
ll allsum=0;
int c[maxn];
void ins(ll l,ll r,ll x) {
	allsum+=(r-l+1)*x;
	S.insert(make_pair(make_pair(l,r),x));
}
void del(ll l,ll r) {
	puts("start");
	// auto final=make_pair(make_pair(l,r),x);
	while (S.size()&&l<=r) {
		auto it=S.upper_bound(make_pair(make_pair(l,INFF),0));
		if (it==S.begin()) break;
		it--;
		// printf("%d ",it->second);
		if (it->first.second<l) break;//remove_done
		auto now=*it; S.erase(it);
		printf("delete: %lld-%lld\n",l,r);
		printf("get=%lld %lld %lld\n",now.first.first,now.first.second,now.second);
		system("pause");
		ll nxtl=now.first.second+1;
		if (now.first.first<l) {
			printf("insert _left: %lld %lld\n",now.first.first,l);
			pair<ll,ll> remain;
			remain.first=now.first.first;
			remain.second=l-1;
			if (remain.first<=remain.second)
				S.insert(make_pair(remain,now.second));
		}
		if (now.first.second>r) {
			printf("insert _right: %lld %lld\n",now.first.second,r);
			pair<ll,ll> remain;
			remain.first=r+1;
			remain.second=now.first.second;
			if (remain.first<=remain.second)
				S.insert(make_pair(remain,now.second));
			nxtl=r+1;
		}
		allsum-=(nxtl-l)*now.second;
		// update(x,nxtl-l);
		l=nxtl;
	}
}
ll base=0,mul=1;
inline ll getid(ll x) {
	return base+mul*x;
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,i;
		scanf("%d",&n);
		FOR(i,2,n) scanf("%d",&c[i]);
		base=0; mul=1; allsum=0;
		S.clear(); ins(1,INF,1);
		FOR(i,2,n) {
			mul=-mul; base=c[i]-base;
			//1 to c[i]
			ll o1,o2,l,r;
			o1=getid(0),o2=getid(c[i]+1);
			l=min(o1,o2),r=max(o1,o2);
			del(-INFF,l); del(r,INFF);
			ll nowans=allsum;
			//1 to c[i]-1
			o1=getid(0),o2=getid(c[i]);
			l=min(o1,o2),r=max(o1,o2);
			del(-INFF,l); del(r,INFF);

			ins(o2,o2,nowans);
			printf("insert: %lld %lld\n",o2,nowans);
		}
		printf("%lld\n",allsum);
	}
}