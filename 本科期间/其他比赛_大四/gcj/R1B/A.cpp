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
const LL maxn=1007+107;
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

int mask[67];
int val[67];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        ll x,y; int i,j;
        bool flagx=0,flagy=0;
        scanf("%lld%lld",&x,&y);
        printf("Case #%d: ",_);
        if (x<0) flagx=1,x=-x;
        if (y<0) flagy=1,y=-y;
        if ((x&1)+(y&1)!=1) {
            puts("IMPOSSIBLE");
            continue;
        }
        int MAX=0;
        REP(i,40) {
            int now=(x&1)+(y&1);
            if (now==1) {
                if (x&1) val[i]=1;
                else val[i]=2;
                x/=2; y/=2;
            } else {
                x/=2; y/=2;
                int pval=val[i-1];
                val[i-1]=-val[i-1];
                if (now==2) {
                    if (pval==1) x++,val[i]=2;
                    else y++,val[i]=1;
                } else val[i]=pval;
            }
            if (!x&&!y) break;
        // FOR(j,0,i) printf("%d ",val[j]); puts("");
        } MAX=i;
        // FOR(i,0,MAX) printf("%d ",val[i]); puts("");
        FOR(i,0,MAX) {
            if (flagx&&(val[i]&1)) val[i]=-val[i];
            if (flagy&&!(val[i]&1)) val[i]=-val[i];
        }
        x=0,y=0;
        FOR(i,0,MAX) {
            if (val[i]==1) printf("E"),x+=1<<i;
            else if (val[i]==-1) printf("W"),x-=1<<i;
            else if (val[i]==2) printf("N"),y+=1<<i;
            else printf("S"),y-=1<<i;
        } puts("");
        // printf("x,y=%lld,%lld\n",x,y);
    }
}
/*
3
4
1 2 3 4
2 1 4 3
3 4 1 2
4 3 2 1
4
2 2 2 2
2 3 2 3
2 2 2 3
2 2 2 2
3
2 1 3
1 3 2
1 2 3
*/