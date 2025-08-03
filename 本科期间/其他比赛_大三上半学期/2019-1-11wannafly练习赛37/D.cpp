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
// template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
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
char str[maxn];

//喵的没做E根本不会.jpg
int f[3007][3007][2];//0:not;1:ing;2:ed
void add_(int &x,int y){x=min(x+y,INF);}
int getans(int n){
	int i,j;
	REP(i,n+1) REP(j,i+1) f[i][j][0]=f[i][j][1]=0;
	f[0][0][0]=1;//must;
	REP(i,n) {
		REP(j,i+1) {
			if (str[i]!=')'){//( | ?
				add_(f[i+1][j+1][0],f[i][j][0]);
			}
			if (str[i]!='('){//) | ?
				if (j) add_(f[i+1][j-1][0],f[i][j][0]);
			}
		}
	}
	add_(f[n][0][0],f[n][0][1]);
	return f[n][0][0];
}
int n,m,q;
int A[407];
int id[407];
int main() {
	int i,j,k;
	scanf("%d%d%d",&n,&m,&k);
	int len=n+m-1;
	REP(i,len) id[i]=i,A[i]=INF,str[i]='?';
	REP(i,n) REP(j,m){
		int t; scanf("%d",&t);
		A[i+j]=min(A[i+j],t);
	}
	sort(id,id+len,[](int i,int j){
		return A[i]<A[j];
	});
	REP(i,len){
		str[id[i]]='(';
		int x=getans(len);
		// printf("%s : %d\n",str,x);
		if (x<k) k-=x,str[id[i]]=')';
	}
	// puts(str);
	REP(i,n) {
		REP(j,m) printf("%c",str[i+j]);
		puts("");
	}
}
/*
1 1
2
*/