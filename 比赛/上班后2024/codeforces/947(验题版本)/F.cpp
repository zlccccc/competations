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
    comb(int mx) : f(mx + 1), g(mx + 1) {
        f[0] = 1;
        FOR_(i, 1, mx) f[i] = f[i - 1] * i;
        g[mx] = f[mx].pow(mod - 2);
        rFOR_(i, 1, mx) g[i - 1] = g[i] * i;
    }
    mint operator()(int a, int b) {
        if (b < 0 || a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} Comb(maxn); // Combination(x,y)

// Arrange(x,y)
mint Arra(int a, int b) { return Comb.f[a] * Comb.g[a - b]; }
// the number of way from (0, 0) to (w, h) which dosn't exceed line y = x + bound (y-x<=bound)
mint Catalan(int w, int h, int bound) { return Comb(w + h, h) - Comb(w + h, h - bound - 1); }

string solve(deque<pair<string,bool>> &remain,string &suffix) {
    if (!remain.size()) return suffix;
    // printf("sz=%d; str=%s\n",remain.size(),suffix.c_str());
    // if (remain.size()==1) return remain[0];
    int k=1;  // suffix
    auto sol=remain.back();  // 'z'
    while (remain.size()&&remain.back()==sol) remain.pop_back(),k++;
    // cout<<"start to solve k= " << k << " str " << sol.first << " suffix " << suffix << " larger = " << sol.second << "\n";
    // for (auto [cur,larger]:remain) cout<<cur<<"("<<larger<<") "; puts(" <<- remain");

    if (!sol.second) return suffix;  // the largest less than last item

    // k: split-number
    int split=min(k,(int)remain.size()+1);
    int len=(k+split-1)/split;
    // a个zz...zz...zz...(任意长); b个zzz...zzz...zzz
    int a=split*len-k,b=split-a;

    // printf("a=%d; b=%d\n",a,b);

    string cur;
    REP_(i,len-1) cur+=sol.first;
    suffix=cur+suffix;
    if (!a&&b==1) return suffix;  // cannot split
    // if (b==1) return suffix;
    if (a) {
        deque<pair<string,bool>> inside;
        REP_(x,a) {  // delete suffix
            auto [c,larger]=remain.back(); c=cur+c;
            remain.pop_back();
            inside.push_front({c,larger});  // largest
        }
        cur+=sol.first;
        REP_(x,b-1) {
            auto [c,larger]=remain.back(); c=cur+c;
            inside.push_back({c,1});
            remain.pop_front();
        }
        return solve(inside,suffix);
    } else {
        cur+=sol.first;
        deque<pair<string,bool>> inside;
        while (remain.size()) {
            auto [c,larger]=remain.front();
            int cnt=0;
            while (remain.size()&&remain.front().first==c) cnt++,remain.pop_front();
            // printf("remain size=%d; str=%s; larger=%d cnt=%d\n",remain.size(),c.c_str(),larger,cnt);
            if (larger&&b==2) continue;
            while (cnt>=b-1) cur+=c,cnt-=b-1;
            REP_(i,cnt) inside.push_back({cur+c,1});
            b-=cnt;
        }
        REP_(i,b-1) inside.push_back({cur,1});
        return solve(inside,suffix);
    }
}
int solve() {
    int n,q;
    string s;
    // cin>>n;
    cin>>s;
    sort(s.begin(),s.end());
    deque<pair<string,bool>> remain;
    for (char c:s) {
        string cur; cur+=c;
        remain.push_back({cur,0});
    }
    string suffix=remain.back().first;  // 'z'
    remain.pop_back();
    for (auto &[c,larger]:remain) if (c==suffix) larger=1;
    string result;
    if (remain.size()&&remain.back().first==suffix) result=solve(remain,suffix);
    else result=suffix;
    cout<<result;
    cout<<"\n";
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
100
babb
abczzzzzzzzz
abbczzzzzzzzz
abbcccdzzdddeeeeezzz
abbcccc
abaaabbbbbbb

100
abbcccc
*/