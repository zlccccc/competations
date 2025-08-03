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
#include <functional>
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
typedef array<int,4> ar4;

char s[maxn];
ll A[maxn];
ll brute_force(int l,int r) {
    ll MIN=0,i;
    FOR(i,l-1,r) min_(MIN,A[i]-A[l-1]);
    // if (A[r]-A[l-1]>0) return -MIN+A[r]-A[l-1];
    // else return -MIN;
    return -MIN; // BIT solve part
}

inline int lowbit(int x) {return x&-x;}
ll C[maxn],V[maxn];
void update(int x,int val) {
    for (;x<=4e5;x+=lowbit(x)) C[x]++,V[x]+=val;
}
pll query(int x) {
    ll c=0,v=0;
    for (;x;x-=lowbit(x)) c+=C[x],v+=V[x];
    return {c,v};
}
int S[maxn],top;
ll SUM[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,i,j,m;
        scanf("%d%s",&n,s+1);
        A[0]=n;
        FOR(i,1,n+n) C[i]=V[i]=0;
        ll ans=0;
        FOR(i,1,n) {
            A[i]=A[i-1];
            if (s[i]=='(') A[i]++; else A[i]--;
            update(A[i-1],A[i-1]);
            auto p=query(A[i]);
            ans+=p.first*A[i]-p.second;
        }
        S[0]=n+1; SUM[0]=0;
        top=0; S[++top]=n; SUM[1]=A[n];
        // FOR(i,1,n) printf("%d ",A[i]); puts("<- A");
        rFOR(i,1,n) {
            while (top&&A[S[top]]>=A[i-1]) top--;
            S[++top]=i-1;
            SUM[top]=SUM[top-1]+A[i-1]*(S[top-1]-S[top]);
            ans+=(n+1-i+1)*A[i-1]-SUM[top];
            // printf("val=%d; more=%d\n",A[i-1],(n+1-i+1)*A[i-1]-SUM[top]);
            // FOR(j,1,top) printf("(stk=%d %d sum=%lld) ",S[j],A[S[j]],SUM[j]); puts("<= stack");
        }
        // FOR(i,1,n) FOR(j,i,n) ans+=brute_force(i,j);
        // A[r]>A[l-1]: ans+=
        printf("%lld\n",ans);
    }
}
/*
10
10
)(())))())
*/