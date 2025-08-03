// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (auto I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (auto I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (auto I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (auto I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (auto I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (auto I=(N),START=(S);I>=START;I--)

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
    comb(int mx) : f(mx + 1), g(mx + 1) {
        f[0] = 1;
        FOR_(i, 1, mx) f[i] = f[i - 1] * i;
        g[mx] = f[mx].pow(mod - 2);
        rFOR_(i, 1, mx) g[i - 1] = g[i] * i;
    }
    mint operator()(int a, int b) {
        if (a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} C(maxn);

int fa[maxn];
int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
vector<int> sub[maxn];
int subval[maxn];
int needsolve[maxn];  // 质数乘积
int solve() {
    int l,r;
    scanf("%d%d",&l,&r);
    int res=0;
    set<int> S;
    bool haveprime=false,have1=false;
    if (l==1) have1=1;
    FOR_(i,1,r) needsolve[i]=0;
    FOR_(i,l,r) {
        if (S.count(subval[i])) res+=sub[i].size();
        else S.insert(subval[i]),needsolve[subval[i]]=1;  // subval: 都可以和x连
        if (sub[i].size()==1) haveprime=1;
    }
    if (have1) {
        for (int v:S) res+=sub[v].size();  // 连接到1上就行了
    } else {
        vector<int> cur,fin;
        for (int v:S) cur.push_back(v);
        for (int v:cur) if (needsolve[v]) {
            fin.push_back(v);
            for (int j=v+v;j<=r;j+=v) if (needsolve[j]) { // not need to solve
                res+=sub[j].size();
                needsolve[j]=0;
            }
        }
        if (haveprime) {
            // for (int v:fin) printf("%d ",v); puts(" <- solve prime");
            for (int v:fin) res+=sub[v].size()+1;  // 连接到prime上就行了
            res-=2;
        } else {
            // for (int v:fin) printf("%d ",v); puts(" <- solve little");
            vector<ar3> link;
            for (int x:fin) fa[x]=x;
            for (int x:fin) for (int y:fin) if (x<y) {
                set<int> s;
                for (int v:sub[x]) s.insert(v); 
                for (int v:sub[y]) s.insert(v); 
                link.push_back({(int)s.size(),x,y});
            }
            sort(link.begin(),link.end());
            for (auto [l,x,y]:link) {
                x=getfa(x); y=getfa(y);
                if (x!=y) {
                    fa[x]=y;
                    res+=l;
                }
            }
        }
    }
    printf("%d\n",res);
    return 0;
}
int main() {
    FOR_(i,1,1000000) subval[i]=1;
    FOR_(i,2,1000000) if (!sub[i].size()) {
        for (int j=i;j<=1000000;j+=i) {
            sub[j].push_back(i);
            subval[j]*=i;
        }
    }
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
6 3
1 2
3 4
5 6
*/