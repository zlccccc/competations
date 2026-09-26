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
const LL maxn=6e6+7;
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

struct PAM {
    int next[maxn][10];
    int fail[maxn];
    int len[maxn];//长度
    int diff[maxn];//length(this-fail)
    int anc[maxn];//diff不同的fail,共log个
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l) {
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=l;//不是1...
        return tot++;
    }
    void init() {
        tot=0; last=n=0;
        newnode(0); newnode(-1);
        S[n]=-1; fail[0]=1;
    }
    int getfail(int x) {
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    mint Num[maxn];
    int add(int c,int op) {
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]) {
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            diff[now]=len[now]-len[fail[now]];
            if (diff[now]==diff[fail[now]])
                anc[now]=anc[fail[now]];
            else anc[now]=now;
            next[cur][c]=now;//这里一定要在fail后边=_=
        }
        last=next[cur][c];
        Num[last]+=op;
        return last;
    }
    void solve(int n) {
        rrep_(i,1,tot) Num[fail[i]]+=Num[i];
        mint res=0;
        rep_(i,1,tot) {
            if (len[i]>n) continue;
            res+=Num[i]*Num[i]*len[i];
            // printf("i=%d: Num=%d; len = %d\n",i,Num[i],len[i]);
        }
        printf("%lld\n",res.x);
    }

    char a[maxn];
    void dfs(int x=0,int len=0){
        // puts("");
        // if (len>=5) return;
        printf("%-20s (p=%-5d, length=%-5d fail=%-5d anc=%-5d diff=%-5d; Num=%d)\n",a,x,this->len[x],fail[x],anc[x],diff[x],Num[x]);
        REP_(i,10){
            if (next[x][i]){
                a[len]=i+'0';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}pam;
char s[maxn];
int main() {
    int n;
    scanf("%d%s",&n,s+1);
    pam.init();
    FOR_(i,1,n-1) pam.add(s[i]-'0',0);
    pam.add(s[n]-'0',1);
    FOR_(i,1,n-1) pam.add(s[i]-'0',1);
    pam.solve(n);
    // pam.dfs(0);
    // pam.dfs(1);
}
/*
*/