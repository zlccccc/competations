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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

int fa[maxn][20];
int dep[maxn];
set<int> prefer[maxn];

int sum[maxn];
int up[maxn],down[maxn];  // up的时候加几,down的时候加几(down相当于到这个位置直接-x)
int U[maxn],D[maxn];
int doLca(int x,int y) {
    if (x==y) return x;
    int op=0,initx=x,inity=y;
    if (dep[x]<dep[y]) swap(x,y),op^=1;
    rREP_(i,20) if (dep[x]-dep[y]>1<<i) x=fa[x][i];
    if (fa[x][0]==y) {
        if (op) {  // x->y的时候x是father
            D[x]++;  // 直接放下
            down[inity]--;  // x的下面
        } else { // 返回的时候才会加
            U[x]--;  // y的下面
            up[initx]++;
        }
    }
    if (dep[x]!=dep[y]) x=fa[x][0];
    // printf("x=%d; y=%d; %d %d\n",x,y,dep[x],dep[y]);
    if (x==y) return x; // 下往上或者上往下; 没有顺序
    if (op) swap(x,y),op^=1;
    rREP_(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    // fa[x]需要先向x dfs然后向y dfs
    prefer[fa[x][0]].insert(x);
    // printf("%d -> %d -> %d\n",fa[x][0],x,y);
    up[initx]++; down[inity]--;
    return fa[x][0];
}
int solve() {
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    vector<vector<int>> edge(n+1);
    FOR_(i,2,n) {
        scanf("%d",&fa[i][0]);
        edge[fa[i][0]].push_back(i);
        rep_(k,1,20) fa[i][k]=fa[fa[i][k-1]][k-1];
        dep[i]=dep[fa[i][0]]+1;
    }
    FOR_(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        int f=doLca(x,y);
    }
    FOR_(i,1,n) if (prefer[i].size()==2) return 0*puts("0");
    // FOR_(i,1,n) {
    //     printf("i=%d; down=%d; up=%d; U=%d; D=%d; ",i,down[i],up[i],U[i],D[i]);
    //     for (int v:prefer[i]) printf("prefer %d; ",v);
    //     puts("");
    // }
    // dfs: dp[x][k]:当前身上背着k个物体的时候,可能的方案数量
    function<vector<mint>(int)> dfs=[&](int x) {
        vector<mint> ret(K+1,0);
        if (edge[x].size()==0) {  // 叶子结点
            fill(ret.begin(),ret.end(),1);
        } else if (edge[x].size()==1) {
            int lson=edge[x][0];
            auto lson_val=dfs(lson);
            sum[x]+=down[lson]+sum[lson]+up[lson]+U[lson]+D[lson];
            FOR_(i,0,K) {  // 刚开始的value
                int cur=i;
                cur+=D[lson]; if (cur<0||cur>K) continue;
                cur+=down[lson]; if (cur<0||cur>K) continue;
                mint val=lson_val[cur];
                cur+=sum[lson]; if (cur<0||cur>K) continue;
                cur+=up[lson]; if (cur<0||cur>K) continue;
                cur+=U[lson]; if (cur<0||cur>K) continue;
                ret[i]+=val;
            }
        } else if (edge[x].size()==2) {
            int lson=edge[x][0],rson=edge[x][1];
            if (prefer[x].size()) {
                int val=*prefer[x].begin();
                if (val!=lson) swap(lson,rson);
            }
            auto lson_val=dfs(lson),rson_val=dfs(rson);
            sum[x]+=down[lson]+sum[lson]+up[lson]+U[lson]+D[lson];
            sum[x]+=down[rson]+sum[rson]+up[rson]+U[rson]+D[rson];
            REP_(_,2-prefer[x].size()) {
                FOR_(i,0,K) { // 先lson再rson
                    int cur=i;
                    cur+=D[lson]; if (cur<0||cur>K) continue;
                    cur+=down[lson]; if (cur<0||cur>K) continue;
                    mint val=lson_val[cur];
                    // printf("x=%d -> lson=%d; size=%d->%d val=%d\n",x,lson,i,cur,val.x);
                    cur+=sum[lson]; if (cur<0||cur>K) continue;
                    cur+=up[lson]; if (cur<0||cur>K) continue;
                    cur+=U[lson]; if (cur<0||cur>K) continue;

                    // printf("after dfs lson; size=%d\n",cur);

                    cur+=D[rson]; if (cur<0||cur>K) continue;
                    cur+=down[rson]; if (cur<0||cur>K) continue;
                    val*=rson_val[cur];
                    // printf("x=%d -> lson=%d -> rson=%d; size=%d->%d val=%d\n",x,lson,rson,i,cur,val.x);
                    cur+=sum[rson]; if (cur<0||cur>K) continue;
                    cur+=up[rson]; if (cur<0||cur>K) continue;
                    cur+=U[rson]; if (cur<0||cur>K) continue;
                    assert(cur==i+sum[x]);
                    ret[i]+=val;
                }
                swap(lson,rson);
                swap(lson_val,rson_val);
            }
        } else {
            assert(0);
        }
        // printf("x=%d; sum=%d\n",x,sum[x]);
        // for (mint v:ret) printf("%lld ",v.x); puts("");
        return ret;
    };
    auto res=dfs(1);
    printf("%lld\n",res[0]);
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    // while (1) solve();
    FOR_(_,1,T){
        solve();
    }
}
/*
*/