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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-15;
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

typedef long double LD;
priority_queue<pair<LD,pair<int,int> > > PQ;
int A[maxn];
int main() {
	int _t,T; scanf("%d",&T);
	FOR(_t,1,T){
		int i; scanf("%d%d",&n,&m);
		while (PQ.size()) PQ.pop();
		FOR(i,1,n) {
			scanf("%d",&A[i]);
			PQ.push(make_pair(A[i]*A[i]/2.0,make_pair(A[i]*A[i],2)));
		} FOR(i,1,m-n) {
			pair<LD,pair<int,int> > S=PQ.top(); PQ.pop();
			pair<int,int> now=S.second; now.second++;
			PQ.push(make_pair((LD)now.first*(1.0/(now.second-1)-1.0/now.second),now));
		} LD ans=0;
		FOR(i,1,n) ans+=A[i];
		ans*=ans; ans=-ans; ans/=m;
		while (PQ.size()){
			pair<LD,pair<int,int> > S=PQ.top(); PQ.pop();
			pair<int,int> now=S.second; now.second--;
			ans+=(LD)now.first/now.second;
		}
		printf("Case #%d: %.14f\n",_t,(double)ans/m+eps);
	}
}
/*
*/
