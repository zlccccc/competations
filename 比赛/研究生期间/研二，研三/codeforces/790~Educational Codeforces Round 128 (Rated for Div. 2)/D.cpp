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

int A[maxn];
ll s[maxn],c[maxn];
int main() {
    int n,i,j,k;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) s[i]=A[i]+s[i-1],c[i]=(A[i]==0)+c[i-1];
    ll ans=-1;
    FOR(i,1,n) FOR(j,i+1,n) {
        ll sr=s[n]-s[j],sl=s[i],sm=s[j]-s[i];//s:sum
        ll cr=c[n]-c[j],cl=c[i],cm=c[j]-c[i];//s:sum
        ll minl=sl-cl*k,maxl=sl+cl*k; // l
        ll minr=sr-cr*k,maxr=sr+cr*k; // r; -r
        swap(minr,maxr); minr=-minr; maxr=-maxr;
        // printf("cr=%d\n",cr);
        ll midmin=sm-cm*k,midmax=sm+cm*k; // mid
        ll divmin=minr-maxl,divmax=maxr-minl;
        // printf("sm=%d cm=%d\n",sm,cm);
        // printf("i=%d; j=%d;",i,j);
        // printf("minl=%lld,maxl=%lld; minr,maxr=%lld %lld; ",minl,maxl,minr,maxr);
        // printf("midmax=%lld,midmin=%lld; divmin,divmax=%lld %lld\n",midmax,midmin,divmin,divmax);
        if (divmin<=midmax&&midmax<=divmax) max_(ans,midmax);
        if (midmin<=divmax&&divmax<=midmax) max_(ans,divmax);

        if (divmin<=midmin&&midmin<=divmax) max_(ans,-midmin);
        if (midmin<=divmin&&divmin<=midmax) max_(ans,-divmin);
    }
    if (n==1) {
        if (A[1]==0) ans=0;
    }
    if (ans>=0) ans++; // ar-al+1;
    printf("%lld\n",ans);
}
/*
*/