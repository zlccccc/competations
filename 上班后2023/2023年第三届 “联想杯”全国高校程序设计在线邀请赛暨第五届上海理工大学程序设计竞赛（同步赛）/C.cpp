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
const LL maxn=2e6+7;
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

int f[maxn],last[maxn],cnt[maxn];
int nxt[maxn][27],tot;
char s[maxn];
char str[]="lenovo";
int okay=0;
// 感觉自己在梦游...
int update(int x,int i) {
    if (i&&okay!=1) {
        okay=1;
        REP_(k,6) if (s[i+k-1]!=str[k]) okay=0;
    }
    if (s[i]=='\0') last[x]+=okay,cnt[x]+=okay;
    if (s[i]=='\0') return 0;
    if (!nxt[x][s[i]-'a']) nxt[x][s[i]-'a']=++tot;
    int ret=update(nxt[x][s[i]-'a'],i+1);
    if (i&&ret!=1) {
        ret=1;
        REP_(k,6) if (s[i+k-1]!=str[k]) ret=0;
        // if (str[ret]!=s[i]&&ret==2) ret=4; // *o
        // if (str[ret]!=s[i]) ret=5;
        // if (str[ret]==s[i]) ret--;
    }
    cnt[x]+=okay;
    if (ret) f[x]++;  // 注意长度不能大于x...
    // printf("update x=%d: %d cnt=%d\n",x,f[x],cnt[x]);
    return ret;
}
int query(int x,int i) {
    if (!x) return 0;
    int ret=0;
    if (s[i]=='\0') {
        REP_(k,26) ret+=f[nxt[x][k]];
        // ret+=last[x];
    } else {
        REP_(k,26) if (k!=s[i]-'a') ret+=cnt[nxt[x][k]];
        ret+=last[x];  // 以x结束
        ret+=query(nxt[x][s[i]-'a'],i+1);
    }
    // printf("query x=%d: f=%d; last=%d; ret=%d\n",x,f[x],last[x],ret);
    return ret;
}
int solve() {
    int n;
    scanf("%d",&n);
    ++tot;
    FOR_(i,1,n) {
        int op;
        okay=0;
        scanf("%d%s",&op,s);
        if (op==1) update(1,0);
        else printf("%d\n",query(1,0));
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
100
1 lenovo
2 l
2 i

1 lenovol
2 lenovol
2 lenovo

1 llenovo
2 l
2 i
2 lle
*/