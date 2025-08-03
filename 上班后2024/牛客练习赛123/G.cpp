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

const int mod = 1e7+19;
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

int solve() {
    int n,m,k;
    scanf("%d%d",&n,&m);
    scanf("%d",&k);
    vector<mint> A(k);
    REP_(i,k) scanf("%lld",&A[i].x),A[i].fix();
    int q;
    scanf("%d",&q);
    vector<array<mint,3>> Q(q);
    REP_(i,q) {
        scanf("%lld",&Q[i][0].x);
        if (Q[i][0]==2||Q[i][0]==3) scanf("%lld",&Q[i][1].x),Q[i][1].fix();
        if (Q[i][0]==3) Q[i][2]=mint(1)/Q[i][1];
    }
    int direction=0,res=0;  // direction=0: -> else: <-
    deque<pair<mint,int>> Cur;
    mint all=0;
    REP_(i,m) {
        mint &val=A[i%k];
        if (i>=k) val+=i;
        Cur.push_back({val,i});
        all+=val;
        // printf("%lld ",val);
    }
    int lastzero=-1;
    mint mul=1,div=1,add=0;
    REP_(i,n-m+1) {
        int r=i+m;
        auto [op,x,y]=Q[i%q];
        if (op==1) {
            direction^=1;
        } else if (op==2) {
            all+=x*m;
            add+=x;
        } else if (op==3) {
            all*=x;
            add*=x;
            mul*=x; div*=y;
            if (mul==0) lastzero=r,mul=div=1;
        } else if (op==4) {
            // printf("current=%lld\n",all.x);
            res^=all.x;
        }
        mint &val=A[r%k];
        if (r>=k) val+=r;
        if (direction==0) {
            all+=val;
            if (Cur.front().second>=lastzero) all-=Cur.front().first*mul+add; else all-=add;
            Cur.pop_front();
            Cur.push_back({(val-add)*div,r});
        } else {
            all+=val;
            if (Cur.back().second>=lastzero) all-=Cur.back().first*mul+add; else all-=add;
            Cur.pop_back();
            Cur.push_front({(val-add)*div,r});
        }
        // printf("solve %lld %lld; %lld  %lld\n",mul.x,div.x,add.x,(div*mul).x);
    }
    printf("%d\n",res);
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
30 9
5
1 2 3 4 5
6
1
4
2 3
3 0
4
3 2
*/