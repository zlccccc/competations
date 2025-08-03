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

int n,m;
vector<int> A[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        scanf("%d%d",&n,&m);
        int i,j;
        FOR(i,1,n) {
            A[i].resize(m+2,0);
            A[i][0]=0;
            FOR(j,1,m) scanf("%d",&A[i][j]);
            A[i][m+1]=INF;
        }
        set<int> NotOK;
        FOR(i,1,n) {
            FOR(j,2,m) {
                if (!(A[i][j-1]<=A[i][j])) {
                    NotOK.insert(j);
                    NotOK.insert(j-1);
                }
            }
        }
        if (NotOK.size()==0) {puts("1 1"); continue;}
        if (NotOK.size()>10) {puts("-1"); continue;}
        int l; bool ans=0;
        for (int k:NotOK) { // swap line k and l
            FOR(l,1,m) {
                // printf("swap line %d %d\n",k,l);
                set<int> check;
                for (int val:NotOK) check.insert(val);
                bool okay=1;
                FOR(i,1,n) swap(A[i][k],A[i][l]);
                check.insert(l);
                if (l!=m) check.insert(l+1);
                check.insert(k);
                if (k!=m) check.insert(k+1);
                FOR(i,1,n) for (int j:check) if (!(A[i][j-1]<=A[i][j])) okay=0;
                // FOR(i,1,n) for (int j:check) printf("check %d %d = %d\n",i,j,(A[i][j-1]<=A[i][j]&&A[i][j]<=A[i][j+1]));
                FOR(i,1,n) swap(A[i][k],A[i][l]);
                if (okay) {printf("%d %d\n",l,k); ans=1; break;}
            }
            if (ans) break;
        }
        if (!ans) puts("-1");
    }
}
/*
1 4 6 7

5
7 6 1 8 2
*/