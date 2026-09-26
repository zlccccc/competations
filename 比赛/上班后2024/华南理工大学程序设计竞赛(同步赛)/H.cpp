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
    scanf("%d",&n);
    vector<vector<pii>> edge(n+1);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back({y,i});
        edge[y].push_back({x,i});
    }
    vector<int> sub(n+1),zerocnt(n+1),res(n+1);
    function<void(int,int)> dfsdown=[&](int x,int fa) {
        for (auto [v,i]:edge[x]) {
            if (v==fa) continue;
            dfsdown(v,x);
            sub[x]+=sub[v];
            zerocnt[x]+=(zerocnt[v]==0);  // zerocnt: 没有装的id数量
        }
        if (zerocnt[x]) sub[x]++; // need one
    };
    dfsdown(1,0);
    function<void(int,int,int,int)> dfs=[&](int x,int fa,int top,int topzero) {
        // printf("dfs %d %d %d %d\n",x,fa,top,topzero);
        for (auto [v,i]:edge[x]) {
            if (v==fa) continue;
            int ntop=top+sub[x]-sub[v]-(zerocnt[x]!=0);
            int ntopzero=zerocnt[x]-(zerocnt[v]==0)+(topzero==0);
            ntop+=(ntopzero!=0);
            // printf("%d -> %d; [%d %d]; [%d %d]\n",x,v,ntop,ntopzero,sub[v],zerocnt[v]);
            dfs(v,x,ntop,ntopzero);
            res[i]=sub[v]+ntop;
        }
    };
    dfs(1,0,0,1);
    FOR_(i,1,n-1) printf("%d ",n-res[i]); puts("");
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/