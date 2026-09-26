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
const LL M=998244353;
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

char str[2007][2007];
int p[2007],re[2007];
void solve(int n) {
	int i,j;
	if (n%4==1||n%4==0) {
		puts("Yes");
		REP(i,n/4*4) {
			REP(j,n/4*4) {
				if (i%4==1&&j%4==0) str[i][j]='1';
				else if (i%4==2&&j%4==1)  str[i][j]='1';
				else if (i%4==3&&j%4==2)  str[i][j]='1';
				else if (i%4==0&&j%4==1)  str[i][j]='1';
				else if (i%4==1&&j%4==2)  str[i][j]='1';
				else if (i%4==2&&j%4==3)  str[i][j]='1';
				else if (i%4==3&&j%4==3&&i!=j)  str[i][j]='1';
				else if (i%4==0&&j%4==0&&i!=j)  str[i][j]='1';
				else str[i][j]='0';
			}
			j=n-1; str[i][n]=0;
			if (n%4==1) {
				if (i%4==1||i%4==2)  str[i][j]='1';
				else str[i][j]='0';
			}
		}
		if (n%4==1) {
			i=n-1;
			REP(j,n-1) {
				if (j%4==1||j%4==2) str[i][j]='1';
				else str[i][j]='0';
			} str[i][n-1]='0';
			str[i][n]=0;
		}
		REP(i,n) {
			if (i==n-1&&n%4==1) p[i]=i;
			else if (i%4==0) p[i]=i+1;
			else if (i%4==1) p[i]=i+3-1;
			else if (i%4==2) p[i]=i+0-2;
			else if (i%4==3) p[i]=i+2-3;
		}
		// REP(i,n) re[p[i]]=i;
		// REP(i,n) REP(j,n) {
		// 	if (str[p[i]][p[j]]==str[i][j]&&i!=j) {
		// 		printf("%d(%d) %d(%d) %c\n",i,p[i],j,p[j],str[i][j]); break;
		// 	}
		// }
		REP(i,n) puts(str[i]);
		REP(i,n) printf("%d%c",p[i]+1," \n"[i==n-1]);
	} else puts("No");
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n;
		scanf("%d",&n);
		printf("Case #%d: ",_);
		solve(n);
	}
}
/*
10
1 2 3 4 5 6 7 8 9 10 11 12
*/
