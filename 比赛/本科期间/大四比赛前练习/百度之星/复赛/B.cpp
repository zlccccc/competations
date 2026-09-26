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

set<pair<int,int> > S;
void dfs(int x,int y) {
	if (x<0||y<0) return;
	if (S.count(make_pair(x,y))) return;
	printf("%d %d\n",x,y);
	if (x<0||y<0) return;
	system("pause");
	S.insert(make_pair(x,y));
	if (x<y) dfs(x,2*x-y);
	else dfs(2*y-x,y);
}
char op[107];
int main() {
	// dfs(17,23);
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		ll a,b,c,d;
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		if (a==c&&d==b) {
			puts("Yes\n");
			continue;
		}
		c-=a; d-=b;
		// a+?; b-?
		if (a==b) {//刚刚已经yes
			puts("No"); continue;
		} else {
			ll k=abs(a-b);
			if (c%k!=0||d%k!=0) {
				puts("No"); continue;
			} ll ma=c/(a-b),mb=d/(b-a);
			if (ma<0||mb<0) {
				puts("No"); continue;
			} int i;
			REP(i,63) {
				if ((ma>>i)&1) {op[i]='B'; ma^=1ll<<i;}//a+=
				else if ((mb>>i)&1) {op[i]='A'; mb^=1ll<<i;}//b-=
				else {op[i]=0; break;}
			} if (ma||mb) {
				puts("No"); continue;
			} puts("Yes");
			puts(op);
		}
	}
}