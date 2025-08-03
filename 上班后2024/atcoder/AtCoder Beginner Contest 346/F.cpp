// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (ll I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (ll I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (ll I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (ll I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (ll I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (ll I=(N),START=(S);I>=START;I--)

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
const LL maxn=1e5+7;
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

// ll same[maxn][62];  // ->to right
ll nxt[maxn][26];  // 当前位置已经选择了
char s[maxn],t[maxn];
int id[maxn];
vector<int> vec[26]; // number
int solve() {
    ll N;
    scanf("%lld",&N);
    scanf("%s",s);
    scanf("%s",t);
    int n=strlen(s),m=strlen(t);
    { // end of x
        vector<ll> p(26,INFF);
        REP_(i,n) if (p[s[i]-'a']==INFF) p[s[i]-'a']=i+n;
        REP_(i,n) id[i]=vec[s[i]-'a'].size(),vec[s[i]-'a'].push_back(i);  // id: this is which
        rREP_(i,n) {
            // same[i][0]=p[s[i]-'a']-i;
            p[s[i]-'a']=i;
            REP_(k,26) nxt[i][k]=p[k]-i;  // 还要多远才能到下一个k
        }
        // rep_(k,1,62)
        //     REP_(i,n)
        //         same[i][k]=min(INFF,same[i][k-1]+same[(i+same[i][k-1])%n][k-1]);
        // // REP_(i,n) printf("%lld ",same[i][0]); puts("< same 0");
        // // REP_(i,n) printf("%lld ",same[i][1]); puts("< same 1");
    }
    ll last=(ll)N*n;
    ll l=0,r=last/m+1;
    // printf("solve %lld %lld\n",l,r);
    while (l+1<r) {
        auto check=[&](ll cnt) {
            cnt--;
            ll cur=0;
            REP_(p,m) {
                int c=t[p]-'a';
                cur+=nxt[cur%n][c];  // 到第一个same的位置
                if (cur>=last) return false;
                ll idx=id[cur%n]+cnt+cur/n*vec[c].size();
                // printf("idx=%lld  cir=%lld\n",idx,idx/vec[c].size());
                __int128 curr=n*(idx/vec[c].size())+vec[c][idx%vec[c].size()];
                if (curr>=last) return false;
                // printf("solve first %lld; p=%lld: cur=%lld(%lld)\n",cnt+1,p,cur,cur%n);
                // rREP_(k,62) if ((cnt>>k)&1) {
                //     cur+=same[cur%n][k];  // need
                //     if (cur>=last) return false;
                // }
                // if (cur!=curr) printf("%lld %lld\n",cur,curr);
                cur=curr;
                // printf("solve %lld; p=%lld: cur=%lld\n",cnt+1,p,cur);
                cur++;
            }
            return true;
        };
        ll mid=(l+r)/2;
        if (check(mid)) l=mid;
        else r=mid;
    }
    printf("%lld\n",l);
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