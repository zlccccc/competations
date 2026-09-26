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
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
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

ll e[37]; int v[37];
int all[1<<18|7][18];
int main(){
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,p,i;
        scanf("%d%d%d",&n,&m,&p);
        REP(i,n) e[i]=0;
        REP(i,n) scanf("%d",&v[i]);
        FOR(i,1,m) {
            int u,v; scanf("%d%d",&u,&v); u--;v--;
            e[u]|=1ll<<v; e[v]|=1ll<<u;
        } int mid=n/2,_sta;
        ll lmax=(1ll<<mid)-1,rmax=((1ll<<n)-1)^lmax;
        rREP(_sta,(1<<mid)) {
            int base=1;
            int sta=_sta;
            REP(i,mid) {
                if (!((sta>>i)&1)) {
                    if ((e[i]&lmax)&~sta) base=0;
                } else mul_(base,v[i],p);//left
            }
            // if (base) {
            //     pr2(sta,n); printf("base=%d\n",base);
            // }
            REP(i,mid) {
                all[sta][i]=i?all[sta][i-1]:base;
                if (!((sta>>i)&1)) add_(all[sta][i],all[sta^(1<<i)][i],p);
            }
            // printf("all=%d\n",all[sta][mid-1]);
        } int ans=0;
        rREP(_sta,(1<<(n-mid))) {
            int base=1,must=0; ll sta=(ll)_sta<<mid;
            rep(i,mid,n) {
                if (!((sta>>i)&1)) {
                    if ((e[i]&rmax)&~sta) base=0;
                    must|=e[i]&lmax;
                    // pr2(sta,n); pr2(e[i],n); pr2(must,n); printf("!must: %d\n",i);
                } else mul_(base,v[i],p);//left
            } mul_(base,all[must][mid-1],p);
            // if (base) {
            //     pr2(sta,n); pr2(must,n); printf("__base=%d\n",base);
            // }
            add_(ans,base,p);
        } printf("Case #%d: %d\n",_,ans);
    }
}