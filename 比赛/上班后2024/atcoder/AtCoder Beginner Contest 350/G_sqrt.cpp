// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,5> ar5;
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

int solve() {
    int n,q;
    scanf("%d%d",&n,&q);
    vector<vector<int>> edge(n+1),large(n+1);  // large: only sqrt indx
    vector<unordered_map<int,int>> MP(n+1);
    vector<int> tag(n+1);
    int prevres=0;
    const int sqr=1000;
    FOR_(i,1,q) {
        ll A,B,C;
        scanf("%lld%lld%lld",&A,&B,&C);
        int op=1+(((A*(1+prevres))%998244353)%2);
        int u=1+(((B*(1+prevres))%998244353)%n);
        int v=1+(((C*(1+prevres))%998244353)%n);
        // printf("ask %d %d %d\n",op,u,v);
        auto addp=[&](int a,int b,int c) {
            if (a==c) return;
            MP[a][c]=b;
            // printf("addpair %d %d %d\n",a,b,c);
        };
        if (op==1) {
            edge[u].push_back(v);
            edge[v].push_back(u);
            for (int x:large[v]) addp(x,v,u);
            for (int x:large[u]) addp(x,u,v);
            if (edge[u].size()==sqr) {
                for (int x:edge[u]) for (int y:edge[x]) addp(u,x,y);
                for (int x:edge[u]) large[x].push_back(u);
            } else if (edge[u].size()>sqr) large[v].push_back(u);
            if (edge[v].size()==sqr) {
                for (int x:edge[v]) for (int y:edge[x]) addp(v,x,y);
                for (int x:edge[v]) large[x].push_back(v);
            } else if (edge[v].size()>sqr) large[u].push_back(v);
        } else {
            prevres=0;
            if (edge[u].size()<=sqr&&edge[v].size()<=sqr) {
                for (int x:edge[u]) tag[x]=x;
                for (int x:edge[v]) if (tag[x]) prevres=x;
                for (int x:edge[u]) tag[x]=0;
            } else {
                if (MP[u].count(v)) prevres=MP[u][v];
                if (MP[v].count(u)) prevres=MP[v][u];
            }
            printf("%d\n",prevres);
        }
    }
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/