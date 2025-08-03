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
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

char s[maxn];
int R[maxn][2],_R[maxn],nxt[maxn];
char str[maxn];
int main() {
	int n,i;
	scanf("%d%s",&n,s+1);
	R[n+1][0]=R[n+1][1]=n;
	rFOR(i,1,n) {
		if (s[i]=='1') R[i][1]=i-1;//last_position
		else R[i][1]=R[i+1][1];
		if (s[i]=='0') R[i][0]=i-1;
		else R[i][0]=R[i+1][0];
		_R[i]=max(R[i][0],R[i][1])+1;
		if (s[i]==s[i+1]) nxt[i]=nxt[i+1];
		else nxt[i]=i+1;
	}
	// FOR(i,1,n) printf("%d ",_R[i]); puts(" <- _R");
	FOR(i,1,n) {
		int ans=0;
		// printf("cal %d\n",i);
		for (int now=1;;){
			vector<int> xok;
			while (now!=n+1&&_R[now]-now<i) {
				xok.push_back(now);
				now=nxt[now];
			} for (int v:xok) nxt[v]=now;
			if (now==n+1) break;
			ans+=(_R[now]-now)/i;
			now+=(_R[now]-now)/i*i;
			// printf("i=%d now=%d; R=%d; nxt=%d; ans=%d\n",i,now,_R[now],nxt[now],ans);
			// printf("fin ans-%d\n",ans);
		} printf("%d ",ans);
	}
}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/