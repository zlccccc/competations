#include <bits/stdc++.h>
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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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

pll cal(ll x) {
    return make_pair(x*x,x*x+x);
}
int A[maxn];
vector<pll> all;
int main() {
    int n,i,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    // n=10000;
    // FOR(i,1,n) A[i]=i;
    sort(A+1,A+1+n);
    n=unique(A+1,A+1+n)-A-1;
    // printf("n=%d\n",n);
    FOR(k,1,2000001) all.push_back({cal(k).second,cal(k).first});
    FOR(k,1,2000000) {
        auto p=cal(k);
        p.first-=A[1]; p.second-=A[1];
        max_(p.first,0ll);
        if (p.first>p.second) continue;
        FOR(i,1,n) {
            auto now=all[lower_bound(all.begin(),all.end(),make_pair(A[i]+p.first,0ll))-all.begin()];
            int low=lower_bound(A+1,A+1+n,now.first+1-p.first)-A-1;
            swap(now.first,now.second);
            // printf("i=%d; ai=%d; p=(%lld %lld) %lld %lld\n",i,A[i],p.first,p.second,now.first,now.second);
            now.first-=A[i]; now.second-=A[i];
            max_(p.first,now.first); min_(p.second,now.second);
            if (p.first>p.second) break;
            // printf("i=%d; low=%d\n",i,low);
            if (i<low-1) i=low-1;
        }
        if (p.first<=p.second) {
            printf("%lld\n",p.first);
            return 0;
        }
    }
}
/*
5 4
4 3 2 1
*/