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

#define DEBUG1
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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void multi(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod(T &A,ll B=M) {A%=M;}
template<typename T>inline void maxi(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void mini(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

char pool[maxn*2],*st;
char* A[maxn];
int poolInt[maxn*2],*stInt;
int *B[maxn],*C[maxn];
int fail[maxn];
int cnt[maxn];
void getcir(char S[],int n) {
    fail[0]=fail[1]=0;
    int i,j;
    FOR(i,2,n) {
        j=fail[i-1];
        while (j&&S[j+1]!=S[i]) j=fail[j];
        if (S[j+1]==S[i]) fail[i]=j+1;
        else fail[i]=0;
    } for (n=fail[n]; n; n=fail[n]) cnt[n]++;
}
int Q[maxn],ST,ED;
int TaskA() {
    int i,j; st=pool; stInt=poolInt;
    REP(i,n) A[i]=st,st+=m+1;
    REP(i,n) B[i]=stInt,stInt+=m,C[i]=stInt,stInt+=m;
    REP(i,n) scanf("%s",A[i]);
    REP(i,n) REP(j,m) scanf("%d",&B[i][j]);
    int row=m,col=n;
    REP(i,n) {
        REP(j,m) S[j+1]=A[i][j];
        getcir(S,m);
    } FOR(i,1,m) if (cnt[i]==n) row=m-i;
    FOR(i,1,m) cnt[i]=0;
    REP(j,m) {
        REP(i,n) S[i+1]=A[i][j];
        getcir(S,n);
    } FOR(i,1,n) if (cnt[i]==m) col=n-i;
    FOR(i,1,n) cnt[i]=0;
    int ans=INF;
    REP(i,n) {
        ST=0; ED=-1;
        REP(j,m) {
            if (ST<=ED&&j>=row&&B[i][j-row]==Q[ST]) ST++;
            while (ST<=ED&&Q[ED]<B[i][j]) ED--;
            Q[++ED]=B[i][j]; C[i][j]=Q[ST];
        }
    }
    REP(j,m) {
        ST=0; ED=-1;
        REP(i,n) {
            if (ST<=ED&&i>=col&&C[i-col][j]==Q[ST]) ST++;
            while (ST<=ED&&Q[ED]<C[i][j]) ED--;
            Q[++ED]=C[i][j]; B[i][j]=Q[ST];
        }
    }
    rep(i,col-1,n) rep(j,row-1,m) ans=min(ans,B[i][j]);
    printf("%lld\n",(ll)ans*(row+1)*(col+1));
    return 0;
}
void initialize() {}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_more_n_m();
}
/*
2 5
acaca
acaca
3 9 2 8 7
4 5 7 3 1
1 5
abaab
1 2 3 4 5
1 5
aaaaa
1 2 3 4 5
*/