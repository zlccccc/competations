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

int n,m;
int Count[17];//should check
ll mask[17],prefix[17];
ll kth_one[17][47];
vector<int> ids[17];
int dfs(ll x,int depth) {
    int i,k;
    // pr2(x,n); printf("check: %d\n",depth);
    if (depth==m+1) {
        int mark=0;
        REP(i,n) {
            int now=(x>>i)&1;
            if (mark&&!now) return 0*puts("REJECTED");
            mark|=now;
        } return 1;
    } int base=0;
    ll now=x&mask[depth],nxt=x&~mask[depth];
    for (int k:ids[depth]) base+=(now>>k)&1;
    FOR(i,0,Count[depth]) {
        int cnt=base+i;
        nxt=nxt|kth_one[depth][cnt];
        // for (int k:ids[depth]) if (((mask[depth]>>k)&1)&&cnt) nxt|=1ll<<k,cnt--;
        // REP(k,n) cnt+=(now>>k)&1;
        // rREP(k,n) if (((mask[depth]>>k)&1)&&cnt) nxt|=1ll<<k,cnt--;
        if (!dfs(nxt,depth+1)) return 0;
    } return 1;
}
int main() {
    int i,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        scanf("%d",&k);
        while (k--) {
            int x; scanf("%d",&x);
            ids[i].push_back(x-1);
            mask[i]|=1ll<<(x-1);
        } prefix[i]=mask[i]|prefix[i-1];
        ll mor=prefix[i]^prefix[i-1];
        REP(k,n) Count[i]+=(mor>>k)&1;
        sort(ids[i].begin(), ids[i].end());
        reverse(ids[i].begin(), ids[i].end());
        // pr2(prefix[i],n); puts("<- prefix");
        REP(k,(int)ids[i].size()) {
            kth_one[i][k+1]=kth_one[i][k]|(1ll<<ids[i][k]);
        }
    } if (n==1) return 0*puts("ACCEPTED");
    if (prefix[m]!=(1ll<<n)-1) return 0*puts("REJECTED");
    if (dfs(0,1)) return 0*puts("ACCEPTED");
}
/*
*/