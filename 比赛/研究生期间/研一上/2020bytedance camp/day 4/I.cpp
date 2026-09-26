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

const int SIZE=1e7;
int S[SIZE],A[maxn];//count
map<int,int> MP;
int mu(int x) {
    int k; int ret=1;
    for (k=2;k*k<=x;k++) if (x%k==0) {
        int cnt=0;
        while (x%k==0) x/=k,cnt++;
        if (cnt>=2) return 0;
        if (cnt==1) ret=-ret;
    } if (x!=1) ret=-ret;
    return ret;
}
int main() {
    int i,n,m;
    // FOR(i,1,100) printf("%d ",mu(i));
    while (~scanf("%d%d",&n,&m)) {
        if (n==0&&m==0) break;
        FOR(i,1,n) scanf("%d",&A[i]);
        vector<int> V;
        for (int k=1;k*k<=m;k++) if (m%k==0){
            V.push_back(k);
            if (k*k!=m) V.push_back(m/k);
        } sort(V.begin(), V.end());
        ll ans=0;
        for (int now:V) {
            // printf("now=%d %d\n",now,mu(now));
            ll nowcnt=0;
            FOR(i,1,n) {
                if (now<SIZE) nowcnt+=S[A[i]%now]++;
                else nowcnt+=MP[A[i]%now]++;
            } FOR(i,1,n) if (now<SIZE) S[A[i]%now]--;
            MP.clear();
            ans+=nowcnt*mu(now);
        } printf("%lld\n",ans);
    }
}
/*
*/