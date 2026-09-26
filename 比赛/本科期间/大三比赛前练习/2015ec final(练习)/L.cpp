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
const LL maxn=1e7+107;
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
// char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[1007][1007];
inline int read(int &num) {
	char in=getchar();
	if (in==EOF) return false;
	while ((in<'0'||in>'9')&&in!='?') in=getchar();
	if (in=='?') {num=0; return 1;}
	num=in-'0';
	while (in=getchar(),in>='0'&&in<='9')
		num=num*10+in-'0';
	return 1;
}
vector<pair<pair<int,int>,int> > V;
int check(int basex,int basey){
	// printf("check: %d %d\n",basex,basey);
	if (basex<0||basey<0) return 0;
	for (auto now:V)
		if ((ll)(now.first.first+basex)*(now.first.second+basey)!=now.second) return 0;
	return 1;
}
int solve(int _) {
	scanf("%d%d",&n,&m);
	int i,j; V.clear();
	FOR(i,1,n) FOR(j,1,m) read(A[i][j]);
	// FOR(i,1,n) FOR(j,1,m) printf("%d ",A[i][j]);
	FOR(i,1,n) FOR(j,1,m) if (A[i][j]) V.push_back(make_pair(make_pair(i,j),A[i][j]));
	if (V.size()==0) return 0*printf("Case #%d: Yes\n",_);
	for (i=1;i*i<=V[0].second;i++) if (V[0].second%i==0){
		int x=i,y=V[0].second/i;
		if (check(x-V[0].first.first,y-V[0].first.second))
			return 0*printf("Case #%d: Yes\n",_);
		swap(x,y);
		if (check(x-V[0].first.first,y-V[0].first.second))
			return 0*printf("Case #%d: Yes\n",_);
	} return 0*printf("Case #%d: No\n",_);
}
int main() {
	int T,_t; scanf("%d",&T);
	FOR(_t,1,T) {
		solve(_t);
	}
}
/*
5
3 3
4 ? 8
? 9 ?
? ? ?
*/
