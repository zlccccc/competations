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

priority_queue<pair<pii,int> > Q;//node; more-ans
ll A[maxn],B[maxn],t[maxn];
void insert(int i) {
    //now-time
    int now_time=(A[i]+B[i]-1)/B[i];
    if (now_time==1) return;
    int nxt_b=(A[i]-1)/(now_time-1)+1;//nxt=r
    // printf("%d: nxt_b=%d\n",i,nxt_b);
    int nxt_time=(A[i]+nxt_b-1)/nxt_b;
    printf("insert %d: %d -> %d; ans= %d -> %d\n",i,B[i],nxt_b,now_time,nxt_time);
    if (nxt_b>t[i]) return;
    Q.push(make_pair(make_pair(B[i]-nxt_b,now_time-nxt_time),i));
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i; int n,m;
        ll ans=0;
        scanf("%d%d",&n,&m);
        // m-=n;
        FOR(i,1,n) scanf("%lld",&A[i]);
        FOR(i,1,n) scanf("%lld",&t[i]);
        while (Q.size()) Q.pop();
        FOR(i,1,n) {
            //need
            B[i]=1; ans+=A[i];
            insert(i);
        }
        while (m&&Q.size()) {
            auto now=Q.top(); Q.pop();
            m+=now.first.first;
            printf("solve fir=%d; %d %d; nowans=%d; m=%d\n",now.first.first,now.first.second,now.second,ans,m);
            if (m<0) break;
            B[now.second]-=now.first.first;//minimize
            ans-=now.first.second;//maximize
            insert(now.second);
        }
        // printf("last=%d\n",m);
        printf("%lld\n",ans);
    }
}
/*
10
1 29
31
30
1 30
31
30
3 10
10 20 30
1 1 1
3 817
1926 2000 1210
2021 2004 304
*/