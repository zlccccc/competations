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

struct dsu{
    int fa[maxn];
    inline int get(int x) {
        if (fa[x]==x) return x;
        return fa[x]=get(fa[x]);
    }
}le,ri;
vector<int> V[maxn];
int A[maxn];
int l[maxn],r[maxn];
int S[maxn],top;
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i;
        scanf("%d",&n);
        FOR(i,1,1000000) V[i].clear();
        FOR(i,1,n) scanf("%d",&A[i]),V[A[i]].push_back(i);
        FOR(i,1,n) l[i]=0,r[i]=n+1; top=0;
        FOR(i,0,n+1) le.fa[i]=ri.fa[i]=i;
        FOR(i,1,n) { // first bigger
            while (top&&A[S[top]]<A[i]) r[S[top]]=i,top--;
            l[i]=S[top]; S[++top]=i;
        }
        // FOR(i,1,n) printf("(%d:%d-%d) ",A[i],l[i],r[i]);
        ll ans=0;
        rFOR(i,1,1000000) if (V[i].size()) {
            // limitation (A[a] divisible by A[j]):
            // 1. contains A[a] (by dsu)
            // 2. contains A[j] (by l[a] and r[a])
            // 3. A[a] is min (rFOR)
            // 4. A[j] is max (l[a] and r[a])
            // for (int j=i;j<=1000000;j+=i) for (int b:V[j])
            //     printf("b=%d, minus %d %d\n",b,(b-max(l[b],le.get(b))),(min(r[b],ri.get(b))-b));
            for (int j=i+i;j<=1000000;j+=i) for (int b:V[j])
                ans-=(ll)(b-max(l[b],le.get(b)))*(min(r[b],ri.get(b))-b);
            for (int a:V[i]) {
                le.fa[a]=le.get(a-1);
                ri.fa[a]=ri.get(a+1);
            }
            for (int j=i;j<=1000000;j+=i) for (int b:V[j])
                ans+=(ll)(b-max(l[b],le.get(b)))*(min(r[b],ri.get(b))-b);
            // for (int j=i;j<=1000000;j+=i) for (int b:V[j])
            //     printf("b=%d, add %d %d\n",b,(b-max(l[b],le.get(b))),(min(r[b],ri.get(b))-b));
        }
        printf("%lld\n",ans);
    }
}
/*
2 3
1 2 5
3 4 6
*/