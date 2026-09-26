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
const LL maxn=1e6+7;
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

const int mod = 1e9+7;
// const int mod=998244353;
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
// struct comb {
//     vector<mint> f, g; // f:fac; g:inv
//     comb() {}
//     comb(int mx):f(mx+1),g(mx+1) {
//         f[0] = 1;
//         FOR_(i,1,mx) f[i] = f[i-1]*i;
//         g[mx] = f[mx].pow(mod-2);
//         rFOR_(i,1,mx) g[i-1] = g[i]*i;
//     }
//     mint operator()(int a, int b) {
//         if (a < b) return 0;
//         return f[a]*g[b]*g[a-b];
//     }
// } C(maxn);

// unordered_map<int,int> MP;
ll F(ll x) {
    if (x<10) return 0;
    ll y=x,dx=x,a=0,b=1;
    for (;dx;) {
        // printf("dx=%d; a=%d; b=%d; cur=%d\n",dx,a,b,a+b*(dx/10));
        y=min(y,a+b*(dx/10));
        a+=dx%10*b;
        dx/=10; b*=10;
    }
    // printf("x=%d; y=%d; div=%d\n",x,y,x-y);
    return y;
}
ll T[maxn*4],same[maxn*4];
inline void upd(int x,int L,int R,ll val) {
    same[x]=val;
    T[x]=(R-L+1)*same[x];
}
void solve(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r&&same[x]!=-1) {
        upd(x,L,R,F(same[x]));
        return;
    }
    int mid=(L+R)/2;
    if (same[x]!=-1) {
        upd(x<<1,L,mid,same[x]);
        upd(x<<1|1,mid+1,R,same[x]);
        same[x]=-1;
    }
    if (l<=mid) solve(x<<1,l,r,L,mid);
    if (mid<r) solve(x<<1|1,l,r,mid+1,R);
    T[x]=T[x<<1]+T[x<<1|1];
}
void update(int x,int l,int r,ll val,int L,int R) {
    if (l<=L&&R<=r) {
        upd(x,L,R,val);
        return;
    }
    int mid=(L+R)/2;
    if (same[x]!=-1) {
        upd(x<<1,L,mid,same[x]);
        upd(x<<1|1,mid+1,R,same[x]);
        same[x]=-1;
    }
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    T[x]=T[x<<1]+T[x<<1|1];
}
ll query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (same[x]!=-1) {
        upd(x<<1,L,mid,same[x]);
        upd(x<<1|1,mid+1,R,same[x]);
        same[x]=-1;
    }
    ll ret=0;
    if (l<=mid) ret+=query(x<<1,l,r,L,mid);
    if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
    T[x]=T[x<<1]+T[x<<1|1];
    return ret;
}
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    memset(same,0xff,sizeof(same));
    FOR_(i,1,n) {
        int x; scanf("%d",&x);
        update(1,i,i,x,1,n);
    }
    FOR_(i,1,m) {
        int op;
        scanf("%d",&op);
        if (op==1) {
            int l,r;
            scanf("%d%d",&l,&r);
            solve(1,l,r,1,n);
        } else if (op==2) {
            int l,r,x;
            scanf("%d%d%d",&l,&r,&x);
            update(1,l,r,x,1,n);
        } else {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",query(1,l,r,1,n));
        }
    }
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