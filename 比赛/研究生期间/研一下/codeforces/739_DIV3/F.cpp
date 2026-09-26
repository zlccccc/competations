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

int value[27];
bool solve(int x,int ans,int not_0,int flag,int mask,int cnt) {
    int i;
    // printf("dfs: x=%d ans=%d not0=%d flag=%d mask=%d cnt=%d\n",x,ans,not_0,flag,mask,cnt);
    if (x==0) {printf("%d\n",ans); return 1;}
    FOR(i,0,9) {
//        if (not_0||i)//这是与lead_0有关的写法
        int nxtmask=mask,nxtcnt=cnt,nxtflag=flag;
        if ((not_0||i)&&!((mask>>i)&1)) nxtmask|=1<<i,nxtcnt--;
        if (nxtcnt<0) continue;
        if (!flag&&i<value[x]) continue;
        if (i>value[x]) nxtflag|=1;
        int done=solve(x-1,ans*10+i,not_0||i,nxtflag,nxtmask,nxtcnt);
        if (done) return 1;
    } return 0;
}
void solve(int x,int cnt) {
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    value[++length]=0;
    solve(length,0,0,0,0,cnt);
} 
void solve() {
    int n,k;
    scanf("%d%d",&n,&k);
    solve(n,k);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
10
abacabaaacaac
nowyouknowthat
polycarppoycarppoyarppyarppyrpprppp
isi
everywherevrywhrvryhrvrhrvhv
haaha
qweqeewew
aaaaaaaaaba
aaaaaaaaab
*/