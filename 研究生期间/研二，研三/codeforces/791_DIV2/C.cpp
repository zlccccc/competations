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

struct BIT{
    int val[maxn];
    BIT() {memset(val,0,sizeof(val));}
    inline int lowbit(int x) {return x&-x;}
    inline void update(int x,int v) {
        for (;x<=100000;x+=lowbit(x)) val[x]+=v;
    }
    int query(int x) {
        int ret=0;
        for (;x;x-=lowbit(x)) ret+=val[x];
        return ret;
    }
    int query(int l,int r) {
        return (query(r)-query(l-1)==r-l+1);
    }
} Tx,Ty;
int Cx[maxn],Cy[maxn];
int main() {
    int n,i,q; scanf("%d%d",&n,&q);
    FOR(i,1,q) {
        int op; scanf("%d",&op);
        int x1,y1; scanf("%d%d",&x1,&y1);
        if (op==1) {
            Cx[x1]++; if (Cx[x1]==1) Tx.update(x1,1);
            Cy[y1]++; if (Cy[y1]==1) Ty.update(y1,1);
        } else if (op==2) {
            if (Cx[x1]==1) Tx.update(x1,-1); Cx[x1]--;
            if (Cy[y1]==1) Ty.update(y1,-1); Cy[y1]--;
        } else {
            int x2,y2;
            scanf("%d%d",&x2,&y2);
            if (Tx.query(x1,x2)||Ty.query(y1,y2)) puts("Yes");
            else puts("No");
        }
    }
}
/*
1 4 6 7

5
7 6 1 8 2
*/