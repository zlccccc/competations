#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
const LL maxn=1.1e6+107;
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

typedef unsigned int ui;
void fwtxor(LL *A,int len,int inv) { //对拍对了
    int i,j,k;
    int div=powMM(2ll,M-2);
    for (i=2; i<=len; i<<=1) {
        for (j=0; j<len; j+=i) {
            for (k=j; k<j+i/2; k++) {
                if (inv==1) {
                    LL a=A[k],b=A[k+i/2];
                    A[k]=a+b;
                    A[k+i/2]=a-b;
                } else {
                    LL a=A[k],b=A[k+i/2];
                    A[k]=(a+b)/2;
                    A[k+i/2]=(a-b)/2;
                }
            }
        }
    }
}
void fwtand(ui *A,int len,int inv) {
    int i,j,k;
    for (i=2; i<=len; i<<=1) {
        for (j=0; j<len; j+=i) {
            for (k=j; k<j+i/2; k++) {
                if (inv==1) {
                    ui a=A[k],b=A[k+i/2];
                    A[k]=(a+b);
                } else {
                    ui a=A[k],b=A[k+i/2];
                    A[k]=a-b;
                }
            }
        }
    }
}
inline ui poww(ui a, ui b) {
    ui ret=1;
    for (; b; b>>=1,a=a*a)
        if (b&1) ret=ret*a;
    return ret;
}
const int MAX=20;
int c[22];
ll A[maxn];
void getBase(int n,ui *base) {
    int i,o=1<<MAX,now=0; A[0]=1;
    rep(i,1,o) A[i]=0;
    FOR(i,1,n) {
        int k; scanf("%d",&k);
        k--; now^=(1<<k); A[now]++;
    } fwtxor(A,o,1);
    REP(i,o) A[i]*=A[i];
    fwtxor(A,o,-1);
    A[0]-=n+1;
    // REP(i,o) printf("%lld ",A[i]); puts("");
    REP(i,o) base[i]=A[i]/2;
}
ui value[maxn];
ui baseA[maxn],baseB[maxn];
ui noww[maxn],tmp[maxn];
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    getBase(n,baseA);
    getBase(m,baseB);
    int o=1<<MAX,sta;
    // REP(sta,o) printf("%d ",baseA[sta]); puts(" <- baseA");
    // REP(sta,o) printf("%d ",baseB[sta]); puts(" <- baseB");
    REP(sta,o) {
        ui k=1;
        REP(i,MAX) if ((sta>>i)&1) k*=i+1;
        value[sta]=k;
    } ui ans=0;
    REP(sta,o) noww[sta]=baseB[(o-1)^sta],tmp[sta]=baseA[sta];
    fwtand(noww,o,1); fwtand(tmp,o,1);
    REP(sta,o) noww[sta]*=tmp[sta];
    fwtand(noww,o,-1);
    REP(sta,o) ans+=value[sta]*noww[sta];
    printf("%u\n",ans);
    // REP(sta,o) printf("%d ",noww[sta]); puts("<- noww"); 
    ans=0;
    REP(sta,o) noww[sta]=baseA[(o-1)^sta],tmp[sta]=baseB[sta];
    fwtand(noww,o,1); fwtand(tmp,o,1);
    REP(sta,o) noww[sta]*=tmp[sta];
    fwtand(noww,o,-1);
    REP(sta,o) ans+=value[sta]*noww[sta];
    printf("%u\n",ans);
}
/*
*/