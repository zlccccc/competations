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
typedef array<ll,3> arll3;
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
vector<int> V;
ar3 val[maxn];
int fa[maxn];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i;
        scanf("%d",&n);
        V.clear();
        FOR(i,1,n) scanf("%d%d%d",&val[i][2],&val[i][0],&val[i][1]);
        sort(val+1,val+1+n);
        set<pii> S[2]; //remove-time,id
        FOR(i,1,n) {
            // printf("first i=%d\n",i);
            fa[i]=i;
            int o;
            REP(o,2) {
                while (S[o].size()&&S[o].begin()->first<val[i][0]) // l,r,c
                    S[o].erase(S[o].begin());
            }
            // printf("i=%d\n",i);
            o=val[i][2];
            if (S[o^1].size()) {
                pii fin;
                for (auto now:S[o^1]) {
                    fin=now;
                    int x=getfa(now.second),y=getfa(i);
                    if (x!=y) fa[x]=y;
                }
                S[o^1].clear();
                S[o^1].insert(fin);
            }
            // printf("final i=%d\n",i);
            S[o].insert({val[i][1],i});
        }
        int ans=0;
        FOR(i,1,n) if (getfa(i)==i) ans++;
        printf("%d\n",ans);
    }
}
/*
*/