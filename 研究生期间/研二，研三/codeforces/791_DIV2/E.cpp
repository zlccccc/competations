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

char str[maxn];
int Ans[1<<17|7][18];
int pw[20][1007];
int main() {
    int n,q;
    int i,t,k;
    scanf("%d",&n);
    scanf("%s",str+1);
    scanf("%d",&q);
    FOR(t,1,17) FOR(i,0,1000) pw[t][i]=powMM(t,i);
    int allcnt=0;
    FOR(i,1,n) if (str[i]=='?') allcnt++;
    FOR(i,1,n) { // start from A[i]
        int cnt,mask;
        cnt=allcnt; mask=0;
        FOR(k,0,n) {
            int l=i-k,r=i+k;
            if (l<1||r>n) break;
            if (str[l]=='?'&&str[r]=='?') {if (l!=r) cnt--;}
            else if (str[r]=='?') mask|=1ll<<(str[l]-'a'),cnt--;
            else if (str[l]=='?') mask|=1ll<<(str[r]-'a'),cnt--;
            else if (str[l]!=str[r]) break;
            FOR(t,1,17) add_(Ans[mask][t],pw[t][cnt]);
            // pr2(mask,17); printf(" %d (%d 1-center)\n",cnt,i);
        }
        cnt=allcnt; mask=0;
        FOR(k,0,n) {
            int l=i-k,r=i+k+1;
            if (l<1||r>n) break;
            if (str[l]=='?'&&str[r]=='?') cnt--;
            else if (str[r]=='?') mask|=1ll<<(str[l]-'a'),cnt--;
            else if (str[l]=='?') mask|=1ll<<(str[r]-'a'),cnt--;
            else if (str[l]!=str[r]) break;
            FOR(t,1,17) add_(Ans[mask][t],pw[t][cnt]);
            // pr2(mask,17); printf(" %d (%d 2-center)\n",cnt,i);
        }
    }
    REP(k,17) REP(i,(1<<17)) if ((i>>k)&1) {
        FOR(t,1,17) add_(Ans[i][t],Ans[i^(1<<k)][t]);
    }
    while (q--) {
        scanf("%s",str); n=strlen(str);
        int mask=0;
        REP(i,n) mask|=1<<(str[i]-'a');
        printf("%d\n",Ans[mask][n]);
    }
}
/*
1 4 6 7

5
7 6 1 8 2
*/