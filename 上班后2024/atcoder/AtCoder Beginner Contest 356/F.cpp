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
typedef array<ll,4> ar4;
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

template<bool path_compression=true>
struct DSU {
    vector<int> checkpoint_;
    vector<pii> changes_;
    vector<int> fa; // fa[x]<0: root; and we save its size
    DSU(int n) {fa.resize(n+1,-1);} // fa<0: size; else: real-getfather
    inline int getfa(int x) {
        if (path_compression) {
            if (fa[x]<0) return x;
            int ret=getfa(fa[x]);
            if (ret!=fa[x]) changes_.push_back({x,fa[x]});
            return fa[x]=ret;
        } else {
            while (fa[x]>=0) x=fa[x];
            return x;
        }
    }
    void checkpoint() {
        checkpoint_.push_back(changes_.size());
    }
    inline void undo() { // single undo
        pii p=changes_.back();
        // if (fa[p.first]>=0) printf(" ======= undo %d %d: pushdown tag=%d %d\n",p.first,fa[p.first],tag[p.first],tag[p.second]);
        fa[p.first]=p.second;
        changes_.pop_back();
    }
    void rollback() { // rollback to checkpoint (stack)
        while ((int)changes_.size()!=checkpoint_.back()) undo();
        checkpoint_.pop_back();
    }
    void merge(int x,int y) {
        x=getfa(x); y=getfa(y);
        if (x==y) return;
        if (-fa[x]>-fa[y]) swap(x,y);
        changes_.push_back({x,fa[x]});
        changes_.push_back({y,fa[y]});
        fa[y]+=fa[x]; fa[x]=y; // sz and fa
        // printf(" -- -merge %d %d: pushup tag=%d %d; fa_1=%d\n",x,y,tag[x],tag[y],getfa(1));
    }
};
DSU<true> dsu(maxn);

ll K;
unordered_map<ll,int> ind;
int result[maxn];
void solve(int l,int r,vector<ar4> E,set<ll> &S) {
    // printf("solve %d->%d\n",l,r);
    vector<ar4> el,er;
    dsu.checkpoint();
    int mid=(l+r)/2;
    for (auto e:E) {
        if (e[0]<=l&&r<=e[1]) {
            if (e[3]==0) {
                // printf("solve %d -> %d: insert %d\n",l,r,e[2]);
                S.insert(e[2]);
                auto it=S.find(e[2]);
                auto check=[&](ll x,ll y) {
                    if (x+K>=y) {
                        // printf("solve range %d->%d: merge %lld %lld (%d %d)\n",l,r,x,y,ind[x],ind[y]);
                        dsu.merge(ind[x],ind[y]);
                    }
                };
                check(*prev(it),e[2]);
                check(e[2],*next(it));
            }
            continue;
        }
        if (e[0]<=mid) el.push_back(e);
        if (mid<e[1]) er.push_back(e);
    }
    for (auto e:E) {
        if (e[0]<=l&&r<=e[1]) {
            if (e[3]!=0) {
                // printf("get value %d: %d\n",e[3],e[2]);
                result[e[3]]=-dsu.fa[dsu.getfa(ind[e[2]])];
            }
        }
    }
    if (l!=r) {
        solve(l,mid,el,S);
        solve(mid+1,r,er,S);
    }
    for (auto e:E)
        if (e[0]<=l&&r<=e[1])
            if (e[3]==0) S.erase(e[2]);
    dsu.rollback();
}

int solve() {
    int Q;
    cin>>Q>>K;
    map<ll,int> MP;
    vector<ar4> Queries;
    int tot=0;
    FOR_(i,1,Q) {
        int op; ll x;
        cin>>op>>x;
        if (op==1) {
            if (!ind.count(x)) ind[x]=++tot;
            if (MP.count(x)) {
                // printf("update %d %d; %d %d\n",MP[x],i-1,x,0);
                Queries.push_back({MP[x],i-1,x,0});
                MP.erase(x);
            } else {
                MP[x]=i;
            }
        } else {
            Queries.push_back({i,i,x,i});
        }
    }
    for (auto p:MP) Queries.push_back({p.second,Q,p.first,0});
    set<ll> S;
    S.insert(-K-1); S.insert(1+K+2e18);
    solve(1,Q,Queries,S);
    FOR_(i,1,Q) if (result[i]) printf("%d\n",result[i]);
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