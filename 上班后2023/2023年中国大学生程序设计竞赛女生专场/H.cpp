// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
#include <functional>
#include <random>
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
struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        for (int i=mx;i>0;i--) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

namespace ACM {
    const int maxn=1e6;
    int next[maxn][26],fail[maxn],len[maxn],tot;
    vector<int> have[maxn];
    void init() {
        tot=0; len[0]=0; fail[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    mint Cnt[maxn],Len[maxn];
    void insert(char s[]) {
        int n=strlen(s),p=0;
        REP_(i,n) {
            int c=s[i]-'a';
            if (!next[p][c]) {
                next[p][c]=++tot; len[tot]=len[p]+1;
                have[tot].clear(); fail[tot]=0;
                memset(next[tot],0,sizeof(next[tot]));
            } p=next[p][c];
        }
        Cnt[p]+=1; Len[p]+=n;
    }
    int Q[maxn],ST,ED;
    void buildAC() {
        ST=0; ED=-1; Q[++ED]=0;
        while (ST<=ED) {
            int p=Q[ST++];
            REP_(c,26) {
                if (next[p][c]) {
                    fail[next[p][c]]=p?next[fail[p]][c]:0;
                    Q[++ED]=next[p][c];
                } else next[p][c]=p?next[fail[p]][c]:0;//否则可能fail=self
            }
            Cnt[p]+=Cnt[fail[p]];
            Len[p]+=Len[fail[p]];
        }
    }
    mint query(char a[]) {
        int p=0;
        int n=strlen(a),i;
        mint ret=0;
        mint cur=0;
        REP_(i,n) {
            int c=a[i]-'a'; p=next[p][c];
            cur+=Cnt[p]*(i+2)-Len[p];
            ret+=cur;
            // printf("i=%d: %d %d; %lld; cur=%lld; ret=%lld\n",i,Cnt[p].x,Len[p].x,(Cnt[p]*(i+2)-Len[p]).x,cur.x,ret.x);
        }
        return ret;
    }
}

char s[maxn];
int solve() {
    int n,m,k;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n) {
        scanf("%s",s);
        ACM::insert(s);
    }
    ACM::buildAC();
    FOR_(i,1,m) {
        scanf("%s",s);
        printf("%lld\n",ACM::query(s).x);
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