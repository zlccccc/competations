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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[maxn];
vector<pii> now;
int S[maxn],top;
int main() {
	int T,_; scanf("%d",&T);
	FOR(_,1,T){
		int i,k; scanf("%d",&n);
		FOR(i,1,n) scanf("%d",&k),A[k]=i;
		bool okay=1;
		now.clear(); top=0;
		for (i=1;i+1<=n;i+=2) {
			pii p=make_pair(A[i],A[i+1]);
			if (p.first>p.second) swap(p.first,p.second);
			now.push_back(p);
		} sort(now.begin(), now.end());
		for (pii p:now){
			// if (Q.size()) printf(" top=%d  %d-%d\n",Q.top(),p.first,p.second);
			while (top&&S[top]<p.first) top--;
			if (top&&S[top]<p.second) okay=0;
			S[++top]=p.second;
		}
		now.clear(); top=0;
		for (i=2;i+1<=n;i+=2) {
			pii p=make_pair(A[i],A[i+1]);
			if (p.first>p.second) swap(p.first,p.second);
			now.push_back(p);
		} sort(now.begin(), now.end());
		for (pii p:now){
			// if (Q.size()) printf(" top=%d  %d-%d\n",Q.top(),p.first,p.second);
			while (top&&S[top]<p.first) top--;
			if (top&&S[top]<p.second) okay=0;
			S[++top]=p.second;
		}
		// FOR(i,1,n) printf("%d ",A[i]);puts("");
		if (okay) puts("Yes");
		else puts("No");
 	}
}
/*
*/
