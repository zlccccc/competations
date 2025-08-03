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

char str[maxn];
int pref[maxn];
int vx[18];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        int i,n,w,m;
        scanf("%s",str+1);
        n=strlen(str+1);
        FOR(i,1,n) pref[i]=(pref[i-1]+str[i]-'0')%9;
        FOR(i,0,17) vx[i]=INF;
        scanf("%d%d",&w,&m);
        rFOR(i,1,n-w+1) {
            int k=(pref[i+w-1]-pref[i-1]+9)%9;
            vx[k+9]=vx[k]; vx[k]=i;
        }
        // FOR(i,0,8) printf("%d ",vx[i]); puts("<- vx");
        FOR(i,1,m) {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            int sec=(pref[r]-pref[l-1]+9)%9;
            // printf("sec=%d\n",sec);
            int u,v;
            pii ans=make_pair(INF,INF);
            FOR(u,0,17) FOR(v,0,17) if (u!=v&&vx[u]!=INF&&vx[v]!=INF) {
                if ((u*sec+v)%9==k) ans=min(ans,{vx[u],vx[v]});
            }
            if (ans.first==INF) ans={-1,-1};
            printf("%d %d\n",ans.first,ans.second);
        }
    }
}
/*
2 3
1 2 5
3 4 6
*/