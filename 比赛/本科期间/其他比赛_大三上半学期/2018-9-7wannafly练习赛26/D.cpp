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


struct L_B{
    LL A[63];bool have_0;
    void clear(){memset(A,0,sizeof(A));have_0=0;}
    LL XORMIN(LL x){
        int i;
        rREP(i,63) if ((A[i]^x)<x) x^=A[i];
        return x;
    }
    LL XORMAX(LL x){
        int i;
        rREP(i,63) if ((A[i]^x)>x) x^=A[i];
        return x;
    }
    void insert(LL x){
        int i;
        if (!have_0&&!XORMIN(x)) have_0=1;
        rREP(i,63) if ((x>>i)&1){
            if (!A[i]) A[i]=x;x^=A[i];
        }
    }
    void rebuild(){
        int i,j;
        rREP(i,63) rREP(j,i) if ((A[i]>>j)&1) A[i]^=A[j];
    }
    LL querykth(LL k){
        LL ret=0;int i;k-=have_0;
        REP(i,63) if (A[i]) {if(k&1) ret^=A[i];k>>=1;}
        if (k) return -1;
        return ret;
    }
}A;
int main() {
	scanf("%d",&n);
	int i;
	FOR(i,1,n){
		int k;
		scanf("%d",&k);
		A.insert(k);
	} scanf("%d",&q);
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		x^=y;
		if (A.XORMIN(x)) puts("NO");
		else puts("YES");
	}
}
/*
*/
