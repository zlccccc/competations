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
const LL maxn=3e5+107;
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

inline int lowbit(int x) {
    return x&-x;
}
inline void update(int x,int val,ll A[]) {
    for (;x<=300000;x+=lowbit(x)) A[x]+=val;
}
inline ll query(int x,ll A[]) {
    ll ret=0;
    for (;x;x-=lowbit(x)) ret+=A[x];
    return ret;
}

ll sum[maxn],cnt[maxn];
int A[maxn];
int main() {
    int i;
    int n;//A[i]%A[j]=A[i]-A[i]/A[j]*A[j];
    scanf("%d",&n);
    // FOR(i,1,n) A[i]=(rand()<<16|rand())%300000+1;
    FOR(i,1,n) scanf("%d",&A[i]);
    ll ans=0,prefsum=0; int _;
    int start=clock();
    FOR(_,1,n) {
        ll v=A[_];
        ll nowans=v*(_-1)-query(v,sum)+prefsum;//v*(_-1)-v*(_-1)
        // printf("nowans=%lld; f1=%lld\n",nowans,v*(_-1)-query(v,sum));
        // nowans-=(_-1-query(v-1,cnt))*v;
        for (int k=v;k<=300000;k+=v) nowans-=(_-1-query(k-1,cnt))*v;
        // for (int k=v;k<=300000;k+=v) nowans-=(query(k+v-1,cnt)-query(k-1,cnt))*k;
        for (int k=v;k<=300000;k+=v) update(k,v,sum);
        update(v,1,cnt);// update(v,v,sum);//more than
        ans+=nowans; prefsum+=v;
        printf("%lld",ans); putchar(' ');
    }
    // printf("time=%d\n", clock()-start);
}
/*
200000
*/