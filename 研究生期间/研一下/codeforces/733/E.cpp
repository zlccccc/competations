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
const LL maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

int n,k;
char str[maxn];
int rig[1<<17|7];
int R[maxn][17];
bool check(int len) {
    if (len==0) return 1;
    int i,j;
    REP(j,k) R[n+1][j]=n+2;
    REP(j,k) {
        int nowlen=0;
        rFOR(i,1,n) {
            if (str[i]=='?'||str[i]=='a'+j) nowlen++;
            else nowlen=0;
            R[i][j]=R[i+1][j];
            if (nowlen>=len) R[i][j]=i+len;//max-length
        }
    }
    // REP(j,k) FOR(i,1,n) printf("%d%c",R[i][j]," \n"[i==n]); puts("<- R");  
    rig[0]=1; int sta;
    rep(sta,1,(1<<k)) {
        rig[sta]=n+2;
        REP(i,k) if ((sta>>i)&1) {
            int remain=sta^(1<<i);
            if (rig[remain]<=n+1) rig[sta]=min(rig[sta],R[rig[remain]][i]);
        }
    }
    // printf("rig=%d\n",rig[(1<<k)-1]);
    if (rig[(1<<k)-1]<=n+1) return 1;
    else return 0;
}
int main() {
    scanf("%d%d",&n,&k);
    scanf("%s",str+1);
    check(2);
    int l=0,r=n+1;
    while (l+1<r) {
        int mid=(l+r)/2;
        if (check(mid)) l=mid;
        else r=mid;
    }
    printf("%d\n",l);
}
/*
10
3 -20 26
4 -3 5
42 -33 55
69 -42 146

*/
