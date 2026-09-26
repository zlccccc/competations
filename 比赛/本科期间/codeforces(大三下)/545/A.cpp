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
const LL maxn=5e5+107;
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

vector<int> row[1007],col[1007];
int A[1007][1007];
int main() {
	int n,m;
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) FOR(j,1,m) {
		int x; scanf("%d",&x); A[i][j]=x;
		row[i].push_back(x);
		col[j].push_back(x);
	} FOR(i,1,n) {
		sort(row[i].begin(), row[i].end());
		row[i].erase(unique(row[i].begin(), row[i].end()),row[i].end());
	} FOR(i,1,m) {
		sort(col[i].begin(), col[i].end());
		col[i].erase(unique(col[i].begin(), col[i].end()),col[i].end());
	}
	FOR(i,1,n) FOR(j,1,m) {
		int l1=lower_bound(row[i].begin(), row[i].end(),A[i][j])-row[i].begin();
		int l2=lower_bound(col[j].begin(), col[j].end(),A[i][j])-col[j].begin();
		int r1=row[i].end()-lower_bound(row[i].begin(), row[i].end(),A[i][j]);
		int r2=col[j].end()-lower_bound(col[j].begin(), col[j].end(),A[i][j]);
		printf("%d%c",max(l1,l2)+max(r1,r2)," \n"[j==m]);
	}
}
/*
*/