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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
template<typename T>
inline void add(T &A,ll B){A+=B; (A>=M)&&(A-=M);}
const int SIZE=5000;
int last[257];
int cnt[5007][SIZE+7];
int ans[5007];
char A[5007];
void solve_1(int n){
    int i,j,k;
    cnt[0][0]=1;
    FOR(i,0,n){
        FOR(j,'a','z') last[j]=0;last[A[i]]=i;
        FOR(j,i+1,n) if (!last[A[j]]){
            last[A[j]]=j;
            FOR(k,0,SIZE) add(cnt[j][k+1],cnt[i][k]);
        }
        FOR(k,1,10) printf("%d ",cnt[i][k]);puts("");
    }FOR(i,1,n) FOR(k,1,SIZE) add(ans[k],cnt[i][k]);
}
void solve_2(int n){
    int i,j,k;
    cnt[0][0]=1;
    FOR(i,1,n){
        FOR(k,0,SIZE) {
            add(cnt[i][k],cnt[i-1][k]%M);
            add(cnt[i][k+1],cnt[i-1][k]%M);
            if (last[A[i]]) add(cnt[i][k+1],M-cnt[last[A[i]]][k]);
        }last[A[i]]=i;
//        FOR(k,1,10) printf("%d ",cnt[i][k]);puts("");
    }FOR(k,1,n) add(ans[k],cnt[n][k]);
}
int TaskA(){
    int n,m,i,j,k;
    scanf("%d",&n);
    scanf("%s",A+1);
//    solve_1(n);
    solve_2(n);
    ll Ans=0;
    FOR(k,1,n) add(Ans,ans[k]*C(n-1,k-1)%M);
    printf("%I64d\n",Ans);
    return 0;
}
void initialize(){
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0 0
0 1 1 0 0 0 0 0 0 0
1 2 2 1 0 0 0 0 0 0
0 1 2 2 1 0 0 0 0 0
0 1 4 5 3 1 0 0 0 0
0 0 1 4 5 3 1 0 0 0
*/
