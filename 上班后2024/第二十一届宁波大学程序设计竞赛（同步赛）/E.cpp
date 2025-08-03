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
const LL maxn=2e6+7;
const long double pi=acos(-1.0);
const long double eps=1e-8;
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

int solve() {
    int n,m;
    scanf("%d",&n);
    vector<array<ll,4>> items(n);
    REP_(i,n) {
        int x,y,u=0,v=0;
        scanf("%d%d%d%d",&x,&y,&u,&v);
        // scanf("%d%d",&x,&y);
        items[i]={x,y,u,v};
    }
    auto solve=[&](int id,long double t) {
        if (t< -eps) return 0;
        // printf("t=%f\n",(double)t);
        long double cx,cy; int cdir;
        {
            auto cur=items[id];
            cx=cur[0]+cur[2]*t,cy=cur[1]+cur[3]*t;
        }
        // printf("real solve id=%d; t=%f; cx,cy=%f %f\n",id,t,cx,cy);
        int res=0;
        REP_(i,n) {
            auto cur=items[i];
            long double x=cur[0]+cur[2]*t,y=cur[1]+cur[3]*t;
            if (abs(x)<eps&&abs(y)<eps) res++;  // one direction
            else if (abs(cx)<eps&&abs(cy)<eps) continue;  // 这个位置是0; not okay
            else {
                if (abs(y*cx-x*cy)<eps&&cx*x+cy*y>-eps) res++;
                // printf("id=%d; i=%d t=%d; dir=%d cdir=%d; res=%d\n",id,i,t,dir,cdir,res);
            }
        }
        // printf("id=%d; t=%f' res=%d\n",id,(double)t,res);
        return res;
    };
    int cur=0;
    REP_(i,n) {
        auto [x1,y1,u1,v1]=items[i];
        cur=max(cur,solve(i,0));
        if (u1!=0&&v1!=0&&x1*v1==y1*u1) {
            long double t=-1.*x1/u1;  // towards zero
            // printf("zero t=%f\n",t);
            REP_(k,n) cur=max(cur,solve(k,t));
        }
        auto update=[&](int i,int j,__int128 A,__int128 B,__int128 C) {
            if (A==0) {
                if (B==0) return; 
                // printf("type 2 %f\n",(double)-C/B);
                cur=max(cur,solve(i,-(long double)C/B));
                cur=max(cur,solve(j,-(long double)C/B));
            } else {
                if (B*B-4*A*C<0) return;
                __int128_t ac=B*B-4*A*C;
                long double sqrt4ac=__builtin_sqrtl(ac);
                // 这里没有考虑相交在(0,0)的情况
                // printf("type 3 %f %f\n",(double)(-B+sqrt4ac)/2./A,(double)(-B-sqrt4ac)/2./A);
                cur=max(cur,solve(i,(-B+sqrt4ac)/2./A));
                cur=max(cur,solve(i,(-B-sqrt4ac)/2./A));
                cur=max(cur,solve(j,(-B+sqrt4ac)/2./A));
                cur=max(cur,solve(j,(-B-sqrt4ac)/2./A));
            }
        };
        rep_(j,1,n) {
            // printf("solve %d %d\n",i,j);
            auto [x2,y2,u2,v2]=items[j];
            update(i,j,u1*v2-u2*v1,y2*u1+x1*v2-y1*u2-x2*v1,y2*x1-x2*y1);
            update(i,j,u1*u2+v1*v2,y2*v1+x1*u2+y1*v2+x2*u1,y2*y1+x2*x1);
        }
    }
    printf("%d\n",cur);
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
3
0 0
1 1
-1 -1

5
-100000 100000 1 1
-100000 100000 2 2
-100000 100000 -1 -1
-100000 100000 0 0
-100000 100000 1 3

3
1 1 0 1
1 0 0 1
0 1 1 2
*/