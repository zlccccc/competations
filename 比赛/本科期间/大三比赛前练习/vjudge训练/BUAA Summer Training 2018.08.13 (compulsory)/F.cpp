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
const LL maxn=1024+7;
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

char mask[1027][1027];
int id[maxn];
int Cid[maxn],tot,mark[maxn];
vector<int> have[maxn];
int solve(){
	int i,j,k;
	FOR(i,1,n) scanf("%s",mask[i]+1);
	FOR(i,1,n) mark[i]=1; tot=0;
	FOR(i,1,n) have[i].clear();
	FOR(i,2,n) if (mask[1][i]=='1'){
		mark[i]=0; Cid[++tot]=i;
		FOR(j,1,n) if (mark[j]&&mask[i][j]=='1'&&mask[1][j]=='0') {
			have[i].push_back(j); mark[j]=0;
		}
	}
	FOR(i,2,n) assert(!mark[i]);
	sort(Cid+1,Cid+1+tot,[](int i,int j){
		return have[i].size()>have[j].size();
	}); int ntot=n;
	// FOR(k,1,tot){
	// 	printf("%d :\n",Cid[k]);
	// 	for (int v:have[Cid[k]]) printf("%d ",v);puts("");
	// }
	FOR(k,1,tot){
		int x=Cid[k],t=1;
		while (t<(int)have[x].size()+1) t<<=1; ntot-=t;
		id[ntot+(t--)]=x;
		for (int v:have[x]) id[ntot+(t--)]=v;
		while (t) id[ntot+(t--)]=Cid[tot--];
	} id[1]=1;
	// FOR(i,1,n) printf("%d ",id[i]);puts("");
	for (int k=n/2;k;k/=2){
		FOR(i,1,k) {
			printf("%d %d\n",id[i*2-1],id[i*2]);
			if (mask[id[i*2-1]][id[i*2]]=='0') id[i]=id[i*2];
			else id[i]=id[i*2-1];
		}
	}
	return 0;
}
int main() {
	while (~scanf("%d",&n)) solve();
}
/*
4
0110
0000
0101
1100
8
00001111
10110000
10000111
10100000
01110000
01011000
01011100
01011110

16
0000000011111111
1000000000000000
1000000000000000
1000000000000000
1000000000000000
1000000000000000
1000000000000000
1000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

*/
