// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (auto I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (auto I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (auto I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (auto I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (auto I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (auto I=(N),START=(S);I>=START;I--)

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
        if (a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} C(maxn);


template <typename T, class Cmp = std::less<T>> struct SparseTable {
    int n;
    vector<vector<T>> sparse; // func: function
    const Cmp cmp = Cmp();
    SparseTable(const vector<T> &vec) {
        n = static_cast<int>(vec.size());
        int max_log = 32 - __builtin_clz(n);
        sparse.resize(max_log);
        sparse[0] = vec;
        for (int level = 1; level < max_log; level++) {
            sparse[level].resize(n - (1 << level) + 1);
            for (int i = 0; i <= n - (1 << level); i++) {
                sparse[level][i] = std::min(sparse[level - 1][i], sparse[level - 1][i + (1 << (level - 1))], cmp);
            }
        }
    }
    T get(int from, int to) const {
        assert(0 <= from && from <= to && to < n);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return std::min(sparse[lg][from], sparse[lg][to - (1 << lg) + 1], cmp);
    }
};

struct SuffixArray {
    vector<int> sa, rnk, lcp_array;
    template <typename T> SuffixArray(const T &str, int length = -1, int bound = -1) {
        if (length == -1)
            length = str.length();
        sa.resize(length);
        rnk.resize(length);
        lcp_array.resize(length - 1); // resize(length-1)
        if (bound == -1) {
            iota(sa.begin(), sa.end(), 0); // 0, 1, ... length-1
            sort(sa.begin(), sa.end(), [&str](int i, int j) { return str[i] < str[j]; });
        } else {
            vector<int> count(bound + 1);
            for (int i = 0; i < length; i++)
                ++count[str[i]];
            for (int i = 1; i <= bound; ++i)
                count[i] += count[i - 1];
            for (int i = 0; i < length; i++)
                sa[--count[i]] = i; // sort(计数排序)
        }
        rnk[sa[0]] = 0;
        for (int i = 1; i < length; i++)
            rnk[sa[i]] = rnk[sa[i - 1]] + (str[sa[i]] != str[sa[i - 1]]);
        int k = 1;
        vector<int> tmp, count(length);
        tmp.reserve(length);
        while (rnk[sa[length - 1]] < length - 1) {
            tmp.clear();
            for (int i = 0; i < k; i++)
                tmp.push_back(length - k + i);
            for (auto i : sa)
                if (i >= k)
                    tmp.push_back(i - k);
            std::fill(count.begin(), count.end(), 0);
            for (int i = 0; i < length; ++i)
                ++count[rnk[i]];
            for (int i = 1; i < length; ++i)
                count[i] += count[i - 1];
            for (int i = length - 1; i >= 0; --i)
                sa[--count[rnk[tmp[i]]]] = tmp[i];
            std::swap(rnk, tmp);
            rnk[sa[0]] = 0;
            for (int i = 1; i < length; ++i)
                rnk[sa[i]] = rnk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == length || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        // calculate lcp_array
        for (int i = 0, j = 0; i < length; ++i) {
            if (rnk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < length && sa[rnk[i] - 1] + j < length && str[i + j] == str[sa[rnk[i] - 1] + j]; ++j)
                    ;
                lcp_array[rnk[i] - 1] = j;
            }
        }
    }
};

// vector<pii> Q[maxn];
int solve() {
    int n,m;
    cin>>n>>m;
    string s,t;
    cin>>s>>t;
    vector<int> length(n+1),lengthR(n+1);
    {
        SuffixArray suf(s+"#"+t);
        SparseTable<int> table(suf.lcp_array);
        auto lcp = [&](int x, int y) {
            // printf("lcp %d -> %d\n", x, y);
            if (x == y || max(x, y) == s.size())
                return (int)s.size() - max(x, y);
            int l = suf.rnk[x], r = suf.rnk[y];
            if (l > r)
                swap(l, r);
            return table.get(l, r - 1);
        };
        FOR_(i,1,n) {
            length[i]=lcp(0,i+n);
            if (length[i]) lengthR[i]=length[i]+i;
        }
        // FOR_(i,1,n) printf("%d ",length[i]); puts("<- length");
        // FOR_(i,1,n) printf("%d ",length[i]?i+length[i]:0); puts("<- length-R");
    }
    SparseTable<int,std::greater<int>> R_table(lengthR);

    vector<ll> w(n+1),sumw(n+1),sumwfail(n+1),sumlength(n+1);
    FOR_(i,1,n) scanf("%lld",&w[i]);
    {
        vector<int> fail(n+1);
        fail[0]=fail[1]=0;
        int j;
        FOR_(i,2,n){
            j=fail[i-1];
            while (j&&s[j-1+1]!=s[i-1]) j=fail[j];
            if (s[j-1+1]==s[i-1]) fail[i]=j+1;
            else fail[i]=0;
        }
        FOR_(i,1,n) sumw[i]=sumw[i-1]+w[i];
        FOR_(i,1,n) sumwfail[i]=w[i]+sumwfail[fail[i]];
        FOR_(i,1,n) sumwfail[i]=sumwfail[i-1]+sumwfail[i];
        // sumw[i]=sumw[i-1]+sumw[i];
        // FOR_(i,1,n) printf("%d ",fail[i]); puts("<- fail");
        // FOR_(i,1,n) printf("%lld ",w[i]); puts("<- w");
    }
    FOR_(i,1,n) sumlength[i]=sumlength[i-1]+sumw[length[i]];

    // FOR_(i,1,n) printf("%lld ",sumlength[i]); puts("<- length");
    // FOR_(i,1,n) printf("%lld ",sumwfail[i]); puts("<- fail");

    FOR_(i,1,m) {
        int l,r;
        scanf("%d%d",&l,&r);
        // {
        //     ll res=0;
        //     FOR_(i,l,r) res+=sumw[min(r-i+1,length[i])];
        //     printf("%lld\n",res);
        // }
        // Q[r].push_back({l,i});
        int mid;
        {
            int L=l-1,R=r+1;
            while (L+1<R) {
                int MID=(L+R)/2;
                // printf("get %d %d: %d\n",l,MID,R_table.get(l,MID));
                if (R_table.get(l,MID)>r) R=MID;
                else L=MID;
            }
            mid=R;
        }
        ll res=sumlength[mid-1]-sumlength[l-1]+sumwfail[r-mid+1];  // sumwfail: border策略
        // printf("%d->%d: mid=%d; len=%d; left=%lld; right=%lld\n",l,r,mid,r-mid+1,sumlength[mid-1]-sumlength[l-1],sumwfail[r-mid+1]);
        printf("%lld\n",res);
    }

    // vector<ll> res(m+1);
    // int curR=0;
    // FOR_(i,1,n) {
    //     while (curR<=length[i]+i) {
    //         for (auto [l,id]:Q[curR]) {
    //             int mid=max(l,i);
    //             res[id]=sumlength[mid-1]-sumlength[l-1]+sumwfail[curR-mid+1];
    //             printf("%d->%d: mid=%d; len=%d\n",l,curR,mid,curR-mid+1);
    //         }
    //         curR++;
    //     }
    // }
    // FOR_(i,1,m) printf("%lld\n",res[i]);
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
12 10
aaabbaaaabaa
aababbaaaaba
1 2 3 4 5 6 7 8 9 10 11 12
1 10
4 10
4 12
4 11
*/