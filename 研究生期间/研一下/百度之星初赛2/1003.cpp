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
const LL maxn=1.2e6+107;
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

char str[1007];
int A[1007][1007];
int fa[1007],d[1007],mk[1007];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,s,ans=0,i,j,k;
        scanf("%d%d",&n,&s);
        FOR(i,1,n) fa[i]=i,d[i]=mk[i]=0; mk[s]=1;
        FOR(i,2,n) {
            scanf("%s",str+1);
            FOR(j,1,i-1) A[i][j]=1-(str[j]-'0');
            FOR(j,1,i-1) if (A[i][j]) {
                d[i]++; d[j]++;
                mk[i]=mk[j]=1;
                ans++;
                int x=getfa(i),y=getfa(j);
                if (x!=y) fa[x]=y;
            }
        } int cnt=0;
        FOR(i,1,n) if (d[i]&1) cnt++;
        // FOR(i,1,n) printf("%d ",d[i]); puts("<- d");
        if (cnt!=0&&cnt!=2) {puts("-1"); continue;}
        if (cnt==2&&!(d[s]&1)) {puts("-1"); continue;}
        ans-=2;
        FOR(i,1,n) if (getfa(i)==i) ans+=mk[i]*2;
        printf("%d\n",ans);
    }
}
/*
10
5 1
0
11
110
1100
4 1
0
00
000
4 1
0
01
011
4 1
1
10
100
4 1
0
00
001
*/