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

int solve() {
    int n,q;
    scanf("%d%d",&n,&q); // 每一层除了最左和最右的数字以外,其他都是可以初始化的~
    vector<int> A(n+1);
    vector<deque<int>> ids(n+1);
    FOR_(i,1,n) scanf("%d",&A[i]),ids[0].push_back(i);
    auto check=[&](int x,int y,int id) {
        if (id%2==1) return A[x]>A[y];
        else return A[y]>A[x];
    };
    auto solve=[&](deque<int> pre,int id) {
        deque<int> cur;
        REP_(k,pre.size()) {
            bool okay=true;
            if (k!=0&&!check(pre[k-1],pre[k],id)) okay=false;
            if (k!=pre.size()-1&&!check(pre[k+1],pre[k],id)) okay=false;
            if (okay) cur.push_back(pre[k]);
        }
        return cur;
    };
    FOR_(i,1,n) {
        ids[i]=solve(ids[i-1],i);
        // for (int v:ids[i-1]) printf("%d ",A[v]); puts("<- solve");
    }
    FOR_(_,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        deque<int> pre,suf;
        FOR_(x,1,n) {
            auto &cur=ids[x-1];
            l=lower_bound(cur.begin(),cur.end(),l)-cur.begin();
            r=upper_bound(cur.begin(),cur.end(),r)-cur.begin()-1;
            // for (int v:cur) printf("%d ",v); puts("<- preprocess");
            // printf("get i=%d: l,r=%d %d\n",x,l,r);

            if (l==r) pre.push_back(cur[l]),r--;
            if (l>r) {
                for (int v:suf) pre.push_back(v);
                suf.clear();
                pre=solve(pre,x);
            } else {
                int nl=cur[l+1],pr=cur[r-1];
                l=cur[l]; r=cur[r];
                pre.push_back(l);
                deque<int> nxtpre=solve(pre,x);
                if (nxtpre.back()==l&&!check(nl,l,x)) nxtpre.pop_back();
                suf.push_front(r);
                deque<int> nxtsuf=solve(suf,x);
                if (nxtsuf.front()==r&&!check(pr,r,x)) nxtsuf.pop_front();

                // for (int v:pre) printf("%d ",v);
                // if (l<=r) printf(" | %d (%d -> %d) %d | ",l,nl,pr,r);
                // for (int v:suf) printf("%d ",v); puts("  <- current");

                nxtpre.swap(pre);
                nxtsuf.swap(suf);
                l++; r--;
            }

            if (pre.size()==1&&suf.size()==0&&l>r) {
                printf("%d\n",A[pre[0]]);
                break;
            }
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