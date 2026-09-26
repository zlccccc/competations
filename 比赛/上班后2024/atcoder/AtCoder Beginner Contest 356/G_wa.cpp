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
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
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
typedef array<ll,4> ar4;
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

int solve() {
    // T=[c*(b2-b1)-d*(a2-a1)]/(a1b2-a2b1)
    int n;
    scanf("%d",&n);
    vector<pll> vec(n);
    REP_(i,n) scanf("%lld%lld",&vec[i].first,&vec[i].second);
    sort(vec.begin(),vec.end(),[&](pll x,pll y) {
        ll cur=y.first*x.second-y.second*x.first;
        if (cur!=0) return cur<0;
        else return x.first<y.first;
    });
    pll cur={0,1};
    vector<pll> fin;
    auto merge=[&](pll i,pll j,pll k) {
        auto [c,d]=k;
        auto [a1,b1]=i;
        auto [a2,b2]=j;
        double ret=1.*(c*(b2-b1)-d*(a2-a1))/(a1*b2-a2*b1);
        // printf("%d %d; %d %d; %d %d\n",a1,b1,a2,b2,c,d);
        // printf("ret=%f\n",ret);
        return ret;
    };
    for (auto y:vec) {
        while (fin.size()) {
            // fin的top和后面的那个组成last
            auto x=fin[fin.size()-1];
            if (y.first*x.second-y.second*x.first==0) { // same
                if (x.first<y.first) {
                    fin.pop_back();  // 不如当前
                    continue;
                } else break;
            } else {
                if (fin.size()>=2) {
                    auto z=fin[fin.size()-2];
                    // if (merge(z,x,y)>=1) fin.pop_back();  // 不如merge
                    if (merge(z,y,x)<=1) fin.pop_back();  // 不如merge
                    else {
                        fin.push_back(y);
                        break;
                    }
                } else {
                    fin.push_back(y);
                    break;
                }
            }
        }
        if (!fin.size()) fin.push_back(y);
    }
    // puts(" final:");
    // for (auto y:fin) printf("%lld %lld\n",y.first,y.second);
    int q;
    scanf("%d",&q);
    FOR_(i,1,q) {
        ll c,d;
        scanf("%lld%lld",&c,&d);
        auto ind=lower_bound(fin.begin(),fin.end(),pll{c,d},[&](pll x,pll y) {
            return y.first*x.second-y.second*x.first<0;
        });
        if (ind==fin.end()) {puts("-1"); continue;}
        auto x=pll{c,d},y=*ind;
        if (ind==fin.begin()) {
            printf("%.15f\n",(double)x.second/y.second);
        } else {
            printf("%.15f\n",merge(*prev(ind),*ind,x));
        }
    }
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