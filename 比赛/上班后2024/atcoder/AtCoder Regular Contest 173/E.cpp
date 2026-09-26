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
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

namespace LB {
    typedef long long BaseType;
    const int MaxBit=63;
    struct L_B {
        BaseType b[MaxBit]; bool have_0;
        L_B() {clear();}
        void clear() {memset(b,0,sizeof(b)); have_0=0;}
        void insert(BaseType x) {
            if (!have_0&&!XORMIN(x)) have_0=1;
            rREP_(i,MaxBit) if ((x>>(ll)i)&1) {
                if (!b[i]) b[i]=x; x^=b[i];
            }
        }
        BaseType XORMIN(BaseType x) {
            rREP_(i,MaxBit) if ((b[i]^x)<x) x^=b[i];
            return x;
        }
        BaseType XORMAX(BaseType x) {
            rREP_(i,MaxBit) if ((b[i]^x)>x) x^=b[i];
            return x;
        }
        void rebuild() {
            rREP_(i,MaxBit) rREP_(j,i) if ((b[i]>>j)&1) b[i]^=b[j];
        }
    };
}
using namespace LB;

int solve() {
    auto solve=[&](vector<ll> A) {
        ll res=0;
        L_B lb;
        // for (ll x:A) printf("%lld ",x); puts("solve <- x");
        for (ll x:A) for (ll y:A) lb.insert(x^y);
        // lb.rebuild();
        // ll cur=0,cnt=0;
        res=lb.XORMAX(0);

        // ll cur=0,cnt=0;
        // for (ll x:A) lb.insert(x);
        // rREP_(i,MaxBit) {
        //     if (lb.b[i]^cur>cur) cur^=lb.b[i],cnt++;
        // }
        // printf("cur=%lld; cnt=%lld\n",cur,cnt);
        // if ((cnt&1)==1&&!lb.have_0) {
        //     rREP_(i,MaxBit) if (lb.b[i]) max_(res,cur^lb.b[i]);
        // } else res=cur;

        // printf("res=%lld\n",res);

        return res;
    };
    int n,m;
    scanf("%d",&n);
    vector<ll> A(n);
    REP_(i,n) scanf("%lld",&A[i]);
    if (n==1) return 0*printf("%lld\n",A[0]);
    ll res=0;
    if (n>=4&&n%4==2) { // 最多取k-1个数字
        // puts("solve 1");
        REP_(i,n) {
            vector<ll> B;
            REP_(j,n) if (j!=i) {
                B.push_back(A[j]);
            }
            res=max(res,solve(B));
        }
    } else {
        // puts("solve 2");
        res=solve(A);
    }
    printf("%lld\n",res);
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
1152905479775702586
837538866691776741
*/