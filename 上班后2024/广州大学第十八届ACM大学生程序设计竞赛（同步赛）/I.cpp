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
const LL maxn=1e7+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a||!b) return a|b;
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
typedef array<int,5> ar5;
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

const int mod = 1e9+7;
// const int mod=998244353;
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

bool mrk[maxn];
int g[maxn];  // gcd(x,i)=k的个数
mint inv[107];
int solve() {
    int n,l,r;
    scanf("%d%d%d",&l,&r,&n);
    for(int i=1;i*i<=n;i++)
        if (n%i==0) mrk[i]=mrk[n/i]=1;
    l--;
    g[0]+=r/n+1; g[r%n+1]--;
    g[0]-=l/n+1; g[l%n+1]++;
    FOR_(i,1,n) g[i]+=g[i-1];
    FOR_(i,1,100) inv[i]=mint(1)/i;
    map<ll,mint> MP;
    MP[1]=1;
    rFOR_(i,1,n) if (mrk[i]) {
        for (int j=i;j<=n;j+=i) if (!mrk[j]) g[i]+=g[j],g[j]=0;
        vector<pair<ll,mint>> vec;
        // printf("start to solve val %d: %d\n",i,g[i]);
        if (i!=1) {
            ll cur=1,prev=0;
            mint oth=mint(2).pow(g[i]);
            mint comb=1;
            FOR_(cnt,0,g[i]) {
                ll curg=fastgcd(n,cur);
                // ll curg=__gcd((ll)n,cur);
                // printf("solve cur=%d; g=%lld; %d %d\n",cur,curg,g[i],cnt);
                if (curg==prev) break; prev=curg;
                if (cnt) {comb*=mint(g[i]-cnt+1); comb*=inv[cnt];}
                vec.push_back({curg,comb});
                oth-=comb;
                cur=curg*i;
            }
            // printf("sz=%lld\n",vec.size());
            vec.back().second+=oth;
        } else {
            vec.push_back({1,mint(2).pow(g[i])});
        }
        // printf("sz=%d\n",MP.size());
        // for (auto [curv,curc]:vec) printf("(%lld: %lld) ",curv,curc); puts(" <- cur");
        map<ll,mint> nxt;
        for (auto &[val,cnt]:MP) {
            for (auto &[curv,curc]:vec) {
                nxt[fastgcd(n,(ll)curv*val)]+=cnt*curc;
            }
        }
        MP.swap(nxt);
    }
    mint res=0;
    for (auto &[val,cnt]:MP) {
        res+=cnt*val;
    }
    printf("%lld\n",res.x);
    // printf("cnt-%d: %d\n",i,g[i]);
    // FOR_(i,1,n) printf("%d ",g[i]); puts("<- Count");
    // int all=0;
    // FOR_(i,1,n) all+=g[i];
    // printf("all=%d\n",all);
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/