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
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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

int ax[4]={0,0,1,-1};
int ay[4]={1,-1,0,0};
int solve() {
    int n,m,q;
    cin>>n>>m>>q;
    vector<string> s(n);
    REP_(i,n) cin>>s[i];
    vector<vector<char>> vec(n+2,vector<char>(m+2));
    FOR_(i,1,n) FOR_(j,1,m) vec[i][j]=s[i-1][j-1];
    vector<vector<int>> dist(n+2,vector<int>(m+2));
    {
        // 最近的v
        queue<pii> Q;
        FOR_(i,1,n) FOR_(j,1,m) dist[i][j]=INF;
        FOR_(i,1,n) FOR_(j,1,m) if (vec[i][j]=='v') Q.push({i,j}),dist[i][j]=0;
        while (Q.size()) {
            int x=Q.front().first,y=Q.front().second; Q.pop();
            REP_(i,4) {
                int dx=x+ax[i],dy=y+ay[i];
                if (dist[dx][dy]==INF) {
                    dist[dx][dy]=dist[x][y]+1;
                    Q.push({dx,dy});
                }
            }
        }
    }

    // FOR_(i,1,n) {FOR_(j,1,m) printf("%d ",dist[i][j]); puts("");}

    vector<string>().swap(s);
    FOR_(i,1,q) {
        int X,Y;
        cin>>X>>Y;  // (x,y)和二分到的在同一个component内
        auto check=[&](int length) {
            vector<vector<int>> limit(n+2,vector<int>(m+2,1));
            {
                FOR_(i,1,n) FOR_(j,1,m) limit[i][j]=0;
                auto could=[&](int x,int y) {
                    return vec[x][y]!='#'&&dist[x][y]>=length;
                };
                queue<pii> Q;
                if (could(X,Y)) Q.push({X,Y});
                while (Q.size()) {
                    int x=Q.front().first,y=Q.front().second; Q.pop();
                    REP_(i,4) {
                        int dx=x+ax[i],dy=y+ay[i];
                        // printf("limit %d %d\n",dx,dy);
                        if (could(dx,dy)&&!limit[dx][dy]) {
                            limit[dx][dy]=1;
                            Q.push({dx,dy});
                        }
                    }
                }
            }
            // printf("length=%d\n",length);
            // FOR_(i,1,n) {FOR_(j,1,m) printf("%d ",limit[i][j]); puts("");}
            {
                vector<vector<int>> mark(n+2,vector<int>(m+2,1));
                queue<pii> Q;
                FOR_(i,1,n) FOR_(j,1,m) mark[i][j]=0;
                FOR_(i,1,n) FOR_(j,1,m) if (i==1||i==n||j==1||j==m) {
                    if (!limit[i][j]) {Q.push({i,j}); mark[i][j]=1;}
                }
                while (Q.size()) {  // 检查是否可以包起来
                    int x=Q.front().first,y=Q.front().second; Q.pop();
                    // if (vec[x][y]=='#') return false;
                    FOR_(ax,-1,1) FOR_(ay,-1,1) if (ax||ay) {
                        int dx=x+ax,dy=y+ay;
                        // printf("%d %d\n",dx,dy);
                        if (!limit[dx][dy]&&!mark[dx][dy]) {  // 可以走
                            mark[dx][dy]=1;
                            Q.push({dx,dy});
                            if (vec[dx][dy]=='#') return false;
                        }
                    }
                }
            }

            // queue<pii> Q;
            // FOR_(i,1,n) FOR_(j,1,m) if (i==1||i==n||j==1||j==m) {
            //     Q.push({i,j}); mark[i][j]=1;
            // }
            // while (Q.size()) {  // 检查是否可以包起来
            //     int x=Q.front().first,y=Q.front().second; Q.pop();
            //     if (vec[x][y]!='#'&&dist[x][y]>=length) continue;  // 可以走
            //     if (vec[x][y]=='#') return false;
            //     REP_(i,4) {
            //         int dx=x+ax[i],dy=y+ay[i];
            //         if (!mark[dx][dy]) {
            //             mark[dx][dy]=1;
            //             Q.push({dx,dy});
            //         }
            //     }
            // }
            return true;
        };
        int l=0,r=n+m+1;
        while (l+1<r) {
            int mid=(l+r)/2;
            if (check(mid)) l=mid;
            else r=mid;
        }
        printf("%d\n",l);
    }
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/