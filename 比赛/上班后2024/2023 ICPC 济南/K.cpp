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
typedef array<int,2> ar2;
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
    int l,r;
    int cnt; ll sum;
}T[maxn*32];
int tot;
void update(int &x,int pos,int c,int L,int R) {
    if (!x) T[++tot]=T[0],x=tot;
    // printf("x=%d; pos=%d; c=%d; L,R=%d %d\n",x,pos,c,L,R);
    T[x].cnt+=c; T[x].sum+=c*pos;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,c,L,mid);
    else update(T[x].r,pos,c,mid+1,R);
}
int getmid(int x,int k,int L,int R) {  // mid
    // printf("getmid x=%d; k=%d; L=%d; R=%d; cnt^val=%d %lld; %d\n",x,k,L,R,T[x].cnt,T[x].sum,T[T[x].l].cnt);
    if (L==R) return L;
    int mid=(L+R)/2;
    if (T[T[x].l].cnt>=k) return getmid(T[x].l,k,L,mid);
    return getmid(T[x].r,k-T[T[x].l].cnt,mid+1,R);
}
ll getval(int x,ll val,int L,int R) {
    if (L==R) return 0;
    ll mid=(L+R)/2;
    if (val<=mid) return T[T[x].r].sum-val*T[T[x].r].cnt+getval(T[x].l,val,L,mid);
    else return val*T[T[x].l].cnt-T[T[x].l].sum+getval(T[x].r,val,mid+1,R);
}

int A[maxn];
int solve() {
    tot=0; int root=0;
    int n,m; ll k;
    scanf("%d%lld",&n,&k);
    FOR_(i,1,n) scanf("%d",&A[i]),A[i]+=n-i;
    // FOR_(i,1,n) printf("%d ",A[i]); puts("<-A");
    int j=0,ans=0;
    FOR_(i,1,n) {
        while (j<=n) {
            if (j>=i) {
                int pos=getmid(root,(j-i+1+1)/2,1,1.1e9);
                ll val=getval(root,pos,1,1.1e9);
                // printf("i=%d: j=%d:: pos=%d; val=%lld\n",i,j,pos,val);
                if (val>k) break;
                ans=max(ans,j-i+1);
            }
            if (j<n) {
                j++; update(root,A[j],1,1,1.1e9);
            } else break;
        }
        update(root,A[i],-1,1,1.1e9);
        // printf("solve i=%d; j=%d\n",i,j);
    }
    printf("%d\n",ans);
    return 0;
}
int main() {
    int T; T=1;
    scanf("%d",&T);
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/