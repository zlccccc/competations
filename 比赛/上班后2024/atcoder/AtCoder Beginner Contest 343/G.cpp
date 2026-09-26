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
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
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
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    
// const int mod = 1e9+7;
const int mod=998244353;
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

struct Hash{
    vector<int> px,val; int MOD,P;
    Hash(int n=1,int p=19260817,int mod=1e9+7) {
        // printf("hash %d %d %d\n",n,p,mod);
        px.resize(n+1); val.resize(n+1);
        P=p; MOD=mod; px[0]=1;
        FOR_(i,1,n) px[i]=(LL)px[i-1]*p%MOD;
    }
    void set(const char a[]){ // id start from 0
        val[0]=0; int n=val.size()-1;
        FOR_(i,1,n) val[i]=((LL)val[i-1]*P+a[i-1]-'a')%MOD;
    }
    int get(int l,int r){
        // printf("get %d %d\n",l,r);
        int ret=val[r]-(LL)val[l-1]*px[r-l+1]%MOD;
        (ret<0)&&(ret+=MOD); return ret;
    }
};

int addstr[20][20]; // 串a接串b需要多长
int substr[20][20];
int res[1<<20][20];
int solve() {
    int n,q;
    cin>>n;
    vector<string> s(n);
    REP_(i,n) cin>>s[i];
    REP_(i,n) REP_(j,n) {
        string a=s[i],b=s[j];
        Hash HA(a.size()),HB(b.size());
        HA.set(a.c_str()); HB.set(b.c_str());
        addstr[i][j]=b.length();
        FOR_(len,1,min(a.size(),b.size())) {
            if (HA.get(a.size()-len+1,a.size())==HB.get(1,len)) {
                addstr[i][j]=b.length()-len;
            }
        }
        FOR_(s,1,a.length()-b.length()+1) {
            // printf("Get %d %d\n",s,s+b.length()-1);
            if (HA.get(s,s+b.length()-1)==HB.get(1,b.length())) {
                substr[i][j]=1;
            }
        }
    }
    // REP_(i,n) {
    //     REP_(j,n) cout<<addstr[i][j]<<" ";
    //     cout<<" <- addstr"<<endl;
    // }
    // REP_(i,n) {
    //     REP_(j,n) cout<<substr[i][j]<<" ";
    //     cout<<" <- substr"<<endl;
    // }
    memset(res,0x3f,sizeof(res));
    REP_(sta,1<<n) {
        if (sta==0) {
            REP_(k,n) min_(res[1<<k][k],(int)s[k].size());
        } else {
            REP_(k,n) if ((sta>>k)&1) {
                if (res[sta][k]==INF) continue;
                // if (res[sta][k]!=INF) cout<<sta<<" "<<k<<" is "<<res[sta][k]<<endl;
                REP_(t,n) if (!((sta>>t)&1)) {
                    min_(res[sta|1<<t][t],res[sta][k]+addstr[k][t]);
                    if (substr[k][t]) min_(res[sta|1<<t][k],res[sta][k]);
                }
            }
        }
    }
    int ans=INF;
    REP_(k,n) min_(ans,res[(1<<n)-1][k]);
    cout<<ans<<endl;
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
5 3
3 0 2 2 3
1 18 25
*/