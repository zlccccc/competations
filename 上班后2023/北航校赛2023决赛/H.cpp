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
const double eps=1e-9;
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

// 250*250*40*1600*2 / 64
const int mid=1607;
typedef bitset<mid*2> bit;
int MID2[257];
vector<bit> arr[257];
int main() {
    int c;
    cin>>c;
    double s,g;
    cin>>s>>g;
    vector<int> sum1,sum2;
    FOR_(i,0,c*40) {  // sum of (100-s)
        if (abs(100-i/(1.*c)-s)<=eps) sum1.push_back(i);
    }
    FOR_(i,0,c*40*40) {  // sum of (100-s)^2
        if (abs(4-i*3/(1600.*c)-g)<=eps) sum2.push_back(i);
    }
    // for (int v:sum1) printf("%d ",v); puts("<- sum1");
    // for (int v:sum2) printf("%d ",v); puts("<- sum2");
    if (sum1.empty()||sum2.empty()) return 0*puts("NO");

    FOR_(i,1,c) MID2[i]=sum2[0]*i/c;  // current MID-Value
    arr[0].resize(1);
    arr[0][0].set(mid);

    FOR_(i,1,(c+1)/2) {
        REP_(x,min(sum1.back()+1,(int)arr[i-1].size())) {
            if (!arr[i-1][x].count()) continue;
            FOR_(o,0,40) {
                int cur=MID2[i-1]-MID2[i]+o*o;
                if (cur<-mid*2||cur>=mid*2) continue;

                if (arr[i].size()<x+o+1) arr[i].resize(x+o+1);
                // printf("x=%d; o=%d; cur=%d\n",x,o,cur);
                if (cur<0) arr[i][x+o]|=arr[i-1][x]>>(-cur);
                else arr[i][x+o]|=arr[i-1][x]<<(cur);
            }
            // REP_(o,mid*2) if (arr[i][x][o]) printf("%d %d %d\n",i,x,o-mid);
        }
    }
    int cur=mid;
    vector<int> vec;
    for (int s1:sum1) for (int s2:sum2) {
        auto GetRes=[&](int c,int s1,int s2) {
            rFOR_(i,1,c) {
                FOR_(o,0,min(40,s1)) {
                    int cur=MID2[i-1]-MID2[i]+o*o;
                    if (s2-cur<0||s2-cur>=mid*2) continue;
                    if (s1-o<arr[i-1].size()&&arr[i-1][s1-o][s2-cur]) {
                        // printf("s1=%d; o=%d\n",s1,o);
                        printf("1 %d\n",100-o);
                        s1-=o; s2-=cur; break;
                    }
                }
            }
        };
        int c1=c/2,c2=c-c/2;
        FOR_(s1_1,0,s1) {
            int s1_2=s1-s1_1;
            if (s1_1>=arr[c1].size()) continue;
            if (s1_2>=arr[c2].size()) continue;
            FOR_(s,0,s2) {
                int s2_1=s-MID2[c1]+mid;
                int s2_2=s2-s-MID2[c2]+mid;
                if (s2_1<0||s2_1>=mid*2) continue;
                if (s2_2<0||s2_2>=mid*2) continue;
                if (arr[c1][s1_1][s2_1]&&arr[c2][s1_2][s2_2]) {
                    puts("YES");
                    printf("%d\n",c);
                    GetRes(c1,s1_1,s2_1);
                    GetRes(c2,s1_2,s2_2);
                    return 0;
                }
            }
        }
    }
    puts("NO");
}
/*
*/