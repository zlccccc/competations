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

// 题意: 删除一个字符之后变成字典序
// 所以直接lcp找第一个不同的位置
// 细节极其多
char str[maxn],nxt[maxn];
int dpnow[maxn],dpnxt[maxn];
int l[maxn],l_suf[maxn],l_pre[maxn];
int main() {
    int _,i,j;
    int n; scanf("%d",&n);
    int lpre,lnow;
    dpnow[1]=1; lpre=lnow=0;
    FOR(_,1,n) {
        scanf("%s",nxt+1);
        lnow=strlen(nxt+1); nxt[lnow+1]=1;
        rFOR(i,1,lnow+1) {//not same position
            if (i>lpre||nxt[i]!=str[i+1]) l_suf[i]=i; else l_suf[i]=l_suf[i+1];
            if (i>lpre||nxt[i]!=str[i-1]) l_pre[i]=i; else l_pre[i]=l_pre[i+1];
            if (i>lpre||nxt[i]!=str[i]) l[i]=i; else l[i]=l[i+1];
        }
        auto cmp=[&](int i,int j) {
            if (i==lnow+1) return l[1]<j?str[l[1]]<=nxt[l[1]]:str[l_suf[j]+1]<=nxt[l_suf[j]];
            if (j==lnow+1) return l[1]<i?str[l[1]]<=nxt[l[1]]:str[l_pre[i+1]-1]<=nxt[l_pre[i+1]];
            if (l[1]<min(i,j)) return str[l[1]]<=nxt[l[1]];
            if (i<=j) return l_pre[i+1]-1<j?str[l_pre[i+1]-1]<=nxt[l_pre[i+1]]:str[l[j+1]]<=nxt[l[j+1]];
            if (j<i) return l_suf[j]<i?str[l_suf[j]+1]<=nxt[l_suf[j]]:str[l[i+1]]<=nxt[l[i+1]];
            return false;
        };
        FOR(i,1,lnow+1) {
            //remove i
            dpnxt[i]=0;
            FOR(j,1,lpre+1) {
                if (cmp(i,j)) add_(dpnxt[i],dpnow[j]);
                // if (ok) printf("move %d->%d %d\n",j,i,dpnxt[i]);
            }
        }
        FOR(i,1,lpre+1) dpnow[i]=str[i]=0;
        FOR(i,1,lnow+1) dpnow[i]=dpnxt[i],str[i]=nxt[i]; str[lnow+1]=0;
        lpre=lnow;
        FOR(i,1,lnow+1) printf("%d ",dpnow[i]); puts("<- dpnow");
    }
    int ans=0;
    FOR(i,1,lnow+1) add_(ans,dpnow[i]);
    printf("%d\n",ans);
}
/*
*/