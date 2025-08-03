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

int solve() {
    int n,m1,m2;
    scanf("%d%d%d", &n,&m1,&m2);
    set<pii> S1,S2;
    vector<pii> res;
    FOR_(i,1,m1) {
        int x,y;
        scanf("%d%d",&x,&y);
        if (x>y) swap(x,y);
        S1.insert({x,y});
    }
    FOR_(i,1,m2) {
        int x,y;
        scanf("%d%d",&x,&y);
        if (x>y) swap(x,y);
        S2.insert({x,y});
    }
    vector<int> fa1(n+1),fa2(n+1),free;
    set<pii> useful2;
    function<int(vector<int>&,int)> getfa=[&](vector<int> &fa,int x) {
        if (fa[x]==x) return x;
        return fa[x]=getfa(fa,fa[x]);
    };
    FOR_(i,1,n) fa1[i]=fa2[i]=i;

    {
        for (auto p:S2) {  // useful2: 选择了的
            int x=p.first,y=p.second;
            int a=getfa(fa2,x),b=getfa(fa2,y);
            if (a!=b) {
                fa2[a]=b;
                if (x>y) swap(x,y);
                useful2.insert({x,y});
            }
        }
        // 需要特判S2中, 一个点度数为n-1, 其他都为1的图
        { // 
            vector<int> D(n+1);
            for (auto [x,y]:useful2) {D[x]++; D[y]++;}
            bool okay=false;
            int X=0,Y=0;
            FOR_(i,1,n) if (D[i]==n-1) X=i; // 存在这种点
            if (X) {
                FOR_(j,1,n) if (X!=j) {
                    int x=X,y=j;
                    if (x>y) swap(x,y);
                    if (!S1.count({x,y})) {Y=j; break;}
                }
                if (Y==0) return 0*printf("Yes\n0\n"); // A所有点和i都已经连通
                {
                    int x=X,y=Y;
                    if (x>y) swap(x,y);
                    useful2.erase({x,y});
                    // printf("p-solve1: %d %d\n",x,y);
                    // if (!S2.count({x,y})) {  // 一定要删
                        res.push_back({x,y});
                        S2.erase({x,y});
                        S1.insert({x,y}); // S1至少有一个连通块; 后面加的边最多n-2
                    // }
                }
                FOR_(k,1,n) if (k!=X&&k!=Y) {  // 一定存在
                    int x=k,y=Y;
                    if (x>y) swap(x,y);
                    useful2.insert({x,y});
                    // printf("p-solve2: %d %d\n",x,y);
                    if (!S2.count({x,y})) {
                        res.push_back({x,y});
                        S2.insert({x,y});
                        if (S1.count({x,y})) S1.erase({x,y});
                        else S1.insert({x,y});
                    }
                    break;
                }
            }
        }
    }


    {
        // 不用管m1内已有连好的~
        for (auto p:S1) {
            int x=p.first,y=p.second;
            // printf("%d %d\n",x,y);
            int a=getfa(fa1,x),b=getfa(fa1,y);
            if (a!=b) {
                fa1[a]=b;
            }
        }
        // FOR_(i,1,n) printf("%d ",getfa(fa1,i)); puts("<- fa1");
        FOR_(i,1,n) if (getfa(fa1,i)==i) free.push_back(i);
    }

    {
        // for (int v:free) printf("%d ",v); puts("?<- free");
        set<int> no;
        FOR_(i,1,n) no.insert(i);
        queue<int> Q;
        Q.push(1);
        while (Q.size()) {
            int now=Q.front(); Q.pop();
            vector<int> remove;
            for (int v:no) {
                int x=now,y=v;
                if (x>y) swap(x,y);
                int a=getfa(fa1,x),b=getfa(fa1,y);
                if (a==b) {
                    remove.push_back(v);
                    Q.push(v);
                } else if (!useful2.count({x,y})) {
                    res.push_back({x,y});
                    Q.push(v);
                    fa1[a]=b;
                }
            }
            for (int v:remove) no.erase(v);
        }
        if (no.size()) return 0*puts("No");
    }
    puts("Yes");
    printf("%d\n",res.size());
    reverse(res.begin(),res.end());
    for (auto [x,y]:res) printf("%d %d\n",x,y);
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d%*d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
100 0
3 1 2
2 3
1 2
1 3
3 1 3
2 3
1 2
1 3
2 3
3 1 3
1 2
1 2
1 3
2 3

100 0
4 0 5
1 2
3 4
2 3
4 5
4 1
*/