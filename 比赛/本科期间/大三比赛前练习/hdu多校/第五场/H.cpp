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

int c1,c2;
pair<int,pii> val[75];
char B[75];
void solve(int l1,int l2){
	int i,j;
	FOR(j,1,l2) val[j]=make_pair(0,make_pair(1,0));
	FOR(i,1,l1){
		FOR(j,1,l2) if (str[i]==B[j]){
			auto nxt=val[j]; nxt.first++;
			if (j<=c1) nxt.second.first=i+1;
			if (j<=c2) nxt.second.second=i;
			val[j]=nxt;
			// printf("%d \"%c\": %d\n",i,str[i],j);
		} FOR(j,1,l2) val[j]=max(val[j],val[j-1]);
		// printf("i=%d  : %d %d %d\n",i,val[l2].first,val[l2].second.first,val[l2].second.second);
	}
}
int main() {
	int T; scanf("%d",&T);
	while (T--){
		int i,j,k;
		scanf("%d%s",&n,str+1);
		pair<int,pii> ans=make_pair(0,make_pair(0,0));
		REP(i,10) rep(j,i+1,10){
		// i=5; j=8;{
			int cnt=0;
			FOR(k,0,i) B[++cnt]=k+'0'; c1=cnt;
			rFOR(k,i,j) B[++cnt]=k+'0'; c2=cnt;
			FOR(k,j,9) B[++cnt]=k+'0';
			solve(n,cnt);
			ans=max(ans,val[cnt]);
			// printf("c1,c2=%d %d\n",c1,c2);
			// printf("%d %d: %d %d %d\n",i,j,val[cnt].first,val[cnt].second.first,val[cnt].second.second);
		} if (ans.second.first>ans.second.second) ans.second.first=ans.second.second;
		printf("%d %d %d\n",ans.first,ans.second.first,ans.second.second);
	}
}
/*
2
9
000000000
*/
