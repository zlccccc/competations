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
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
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

// F[l->r]
int f[21][100007];
// int getres(int l,int r) {
//     if (l==0) return INF;
//     if (l==r) return 0;
//     if (f[l][r]!=-1) return f[l][r];
//     int cur=INF;
//     FOR_(k,l+1,r) min_(cur,max(getres(l-1,k-2),getres(k-1,r-1)+1));
//     return f[l][r]=cur;
// }
// int solve() {
//     int l,r;
//     scanf("%d%d",&l,&r);
//     int res=getres(l,r);
//     if (res==INF) puts("1000000000000000000");
//     else printf("%d\n",res);
//     return 0;
// }

vector<int> sub[maxn];
int getres(int l,int len) {
    if (l==0) return INF;
    if (l>=3&&l<=16) return upper_bound(sub[l].begin(),sub[l].end(),len)-sub[l].begin();
    // printf("%d %d\n",l,len);
    if (l>16) {
        if (len==0) return 0;
        if (len<l) return 1;
        return 2;
    }
    if (len==0) return 0;
    if (l==1) return f[l][len]=INF;
    if (l==2) return f[l][len]=len;
    if (len<l) return f[l][len]=1;

    if (f[l][len]!=-1) return f[l][len];
    int cur=INF;
    FOR_(k,1,len) min_(cur,max(getres(l-1,k-1),getres(l+k-1,len-k)+1));

    // auto get=[&](int k) {
    //     // printf("solve l=%d; k=%d\n",l,k);
    //     return max(getres(l-1,k-1),getres(l+k-1,len-k)+1);
    // };
    // function<void(int,int)> sol=[&](int l,int r) {
    //     // printf("%d -> %d\n",l,r);
    //     int res=INF;
    //     if (r-l<=20) {
    //         FOR_(k,l,r) res=min(res,get(k));
    //     } else {
    //         int len=(r-l)/3,xl=l+len,xr=r-len;
    //         int x=get(xl),y=get(xr);
    //         res=min(res,min(x,y));
    //         // printf("x=%d; y=%d; l=%d; r=%d\n",x,y,l,r);
    //         if (x<y) sol(l,xr-1);
    //         else sol(xl+1,r);
    //     }
    // };
    // sol(1,len);

    // if (cur==3) {
    //     FOR_(k,1,len) printf("%d ",max(getres(l-1,k-1),getres(l+k-1,len-k)+1)); printf("<- value; l=%d\n",l); 
    // }
    return f[l][len]=cur;
}
int solve() {
    int l,r;
    scanf("%d%d",&l,&r);
    int res=getres(l,r-l);
    if (res==INF) puts("1000000000000000000");
    else printf("%d\n",res);
    return 0;
}
int main() {
    FOR_(i,3,100000) {
        sub[i].push_back(1);
        sub[i].push_back(i);
    }
    sub[3].push_back(8); sub[3].push_back(93);
    sub[4].push_back(19);
    sub[5].push_back(42);
    sub[6].push_back(89);
    sub[7].push_back(184);
    sub[8].push_back(375);
    sub[9].push_back(758);
    sub[10].push_back(1525);
    sub[11].push_back(3060);
    sub[12].push_back(6131);
    sub[13].push_back(12274);
    sub[14].push_back(24561);
    sub[15].push_back(49136);
    sub[16].push_back(98287);

    // FOR_(i,1,20) {
    //     FOR_(j,90000,100000) {
    //         int cur=getres(i,j);
    //         if (i==16) printf("j=%d: cur=%d\n",j,cur);
    //         if (i>=5&&cur==3) break;
    //     }
    //     printf("i=%d\n",i);
    //     if (i<=2) continue;
    //     FOR_(j,0,100000) {
    //         if (f[i][j]!=f[i][j-1]) printf("%d(%d) ",j,f[i][j]);
    //     } puts("");

    //     // printf("%d:\n",i);
    //     // FOR_(j,i,1000) printf("%d ",getres(i,j));
    //     // puts("");
    // }

    // puts("??");
    // FOR_(i,58000,100000) if (getres(15,i-15)==3) {printf("i=%d\n",i); break; }
    // puts("??");
    int T; T=1;
    scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
*/