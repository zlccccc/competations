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
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+107;
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

int SIZE=200;
const ll MAXN=4.2e7,BASE=4.1e7;
char str[maxn];
int A[maxn],MP[MAXN];
int main() {
    int T,_; T=1;
    FOR(_,1,T){
        ll ans=0;
        int i,k;
        // FOR(i,1,200000) str[i]='1';
        scanf("%s",str+1);
        int n=strlen(str+1);
        FOR(i,1,n) A[i]=A[i-1]+str[i]-'0';
        //r-(l-1)=k(A[r]-A[l-1])
        FOR(k,1,SIZE) {
            FOR(i,1,n) {
                MP[i-1-k*A[i-1]+BASE]++;
                ans+=MP[i-k*A[i]+BASE];
            }
            FOR(i,1,n) MP[i-1-k*A[i-1]+BASE]--;
        }
        // printf("%d\n",ans);
        FOR(k,1,n/SIZE) {
            int l=1,r=1;
            FOR(i,1,n) { //length
                while (l<=n&&A[l]-A[i-1]<k) l++;
                while (r<=n&&A[r]-A[i-1]<=k) r++;
                ans+=max(0,(r-i)/k-SIZE)-max(0,(l-i)/k-SIZE); //length
                // printf("%d %d: %d %d\n",k,i,l,r);
            }
        }
        printf("%lld\n",ans);
    }
}
/*
4
0 1
0 -1
1 0
-1 0
*/