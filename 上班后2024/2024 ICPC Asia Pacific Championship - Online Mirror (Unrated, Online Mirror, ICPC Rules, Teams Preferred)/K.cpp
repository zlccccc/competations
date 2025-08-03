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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a) return b;
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
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    
// const int mod = 1e9+7;
const int mod=998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this; }
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this; }
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this; }
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this; }
    mint operator+(const mint &a)const { return mint(*this) += a; }
    mint operator-(const mint &a)const { return mint(*this) -= a; }
    mint operator*(const mint &a)const { return mint(*this) *= a; }
    mint operator/(const mint &a)const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x; }
    bool operator==(const mint &a)const { return x == a.x; }
};
istream & operator>>(istream &o,mint &a) { o>>a.x; a=a.fix(); return o; }
ostream & operator<<(ostream &o,const mint &a) { o<<a.x; return o; }
    
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
    
struct node{
    int l,r,val;
}T[maxn*80];
int tot;
vector<int> edge[maxn];
vector<pll> Qx[maxn];
void update(int &x,int pos,int val,int L,int R) {
    if (!x) x=++tot,T[x]=T[0];
    T[x].val+=val;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,val,L,mid);
    if (mid<pos) update(T[x].r,pos,val,mid+1,R);
}
void merge(int &x,int y) {
    if (!x) { T[++tot]=T[y]; x=tot; return; }
    T[++tot]=T[x]; x=tot;
    if (!y) return;
    T[x].val+=T[y].val;
    merge(T[x].l,T[y].l);
    merge(T[x].r,T[y].r);
}
int query(int x,int y,ll &k,int L,int R) {
    // printf("query %d %d %d %d %d: Count=%d; %d\n",x,y,k,L,R,T[x].val,T[y].val);
    if (L==R) return L;
    int mid=(L+R)/2;
    if (T[T[x].l].val-T[T[y].l].val<k) {
        k-=T[T[x].l].val-T[T[y].l].val;
        return query(T[x].r,T[y].r,k,mid+1,R);
    } else {
        return query(T[x].l,T[y].l,k,L,mid);
    }
}
    
int n;
int sz[maxn];
int root[maxn],allroot;
void dfs1(int x) {
    sz[x]=1;
    update(root[x],x,1,1,n);
    for (int v:edge[x]) {
        dfs1(v);
        sz[x]+=sz[v];
        merge(root[x],root[v]);
    }
}
int sub[maxn];
ll res[maxn];
void dfs2(int x) {
    update(allroot,x,sz[x],1,n);
    for (auto [kth,i]:Qx[x]) {
        // printf("lca kth=%d\n",kth);
        int lca=query(allroot,0,kth,1,n);
        // printf("y kth=%d\n",kth);
        int y=query(root[lca],root[sub[lca]],kth,1,n);
        // printf("answer %d: %d %d %d\n",i,x,lca,y);
        res[i]=(ll)(x-1)*n*n+(ll)(lca-1)*n+y-1;
    }
    for (int v:edge[x]) {
        update(allroot,x,-sz[v],1,n);
        sub[x]=v;
        dfs2(v);
        update(allroot,x,sz[v],1,n);
    }
    update(allroot,x,-sz[x],1,n);
}
int fa[maxn];
int solve() {
    int q;
    cin>>n>>q;
    int rt=0;
    FOR_(i,1,n) {
        cin>>fa[i];
        if (!fa[i]) rt=i;
        else edge[fa[i]].push_back(i);
    }
    FOR_(i,1,q) {
        ll cur;
        cin>>cur; cur--;
        ll kth=cur%n+1,x=cur/n+1;
        // cout<<"Asking: "<<x<<" "<<kth<<endl;
        Qx[x].push_back({kth,i});
    }
    dfs1(rt);
    dfs2(rt);
    FOR_(i,1,q) cout<<res[i]<<"\n";
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
5 3
3 0 2 2 3
1 18 25
*/