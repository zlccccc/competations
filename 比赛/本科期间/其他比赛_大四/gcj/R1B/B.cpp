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

char str[maxn];
bool ask(int x,int y) {
    printf("%d %d\n",x,y);
    fflush(stdout);
    scanf("%s",str);
    if (str[0]=='M') return 1;
    return 0;
}
int main() {
    int T,_,a,b; T=1;
    scanf("%d%d%d",&T,&a,&b);
    FOR(_,1,T){
        ll l,r,baseL=0,baseR=0;
        ll L=0,R=0,step=5e8;
        for (baseL=-step;baseL<=step;baseL+=step) {
            for (baseR=-step;baseR<=step;baseR+=step) {
                ask(baseL,baseR);
                if (str[0]!='M') break;
            }
            if (str[0]!='M') break;
        }
        if (str[0]=='C') continue;

        l=-1e9-1; r=baseL;//L:maybe_not_in
        while (l+1<r) {
            ll mid=l+(r-l+1)/2;
            if (ask(mid,baseR)) l=mid;//r:inside
            else r=mid;
            if (str[0]=='C') break;
        } L+=r;
        if (str[0]=='C') continue;

        l=baseL; r=1e9+1;
        while (l+1<r) {
            ll mid=l+(r-l)/2;
            if (!ask(mid,baseR)) l=mid;//l:inside
            else r=mid;
            if (str[0]=='C') break;
        } L+=l;
        if (str[0]=='C') continue;

        l=-1e9-1; r=baseR;//L:maybe_not_in
        while (l+1<r) {
            ll mid=l+(r-l+1)/2;
            if (ask(baseL,mid)) l=mid;//r:inside
            else r=mid;
            if (str[0]=='C') break;
        } R+=r;
        if (str[0]=='C') continue;

        l=baseR; r=1e9+1;
        while (l+1<r) {
            ll mid=l+(r-l)/2;
            if (!ask(baseL,mid)) l=mid;//l:inside
            else r=mid;
            if (str[0]=='C') break;
        } R+=l;
        if (str[0]=='C') continue;
        ask(L/2,R/2);
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