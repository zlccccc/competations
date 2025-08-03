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

struct Point {
    ll x , y;
    Point (ll x = 0 , ll y = 0) : x(x) , y(y) {}
    void input() {
        scanf("%lld%lld",&x,&y);
    }
    bool operator < (const Point& R) const {
        if (x - R.x == 0)
            return (y - R.y) < 0;
        return (x - R.x) < 0;
    }
    bool operator == (const Point& R) const {
        return (x - R.x) == 0 && (y - R.y) == 0;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const ll& R) const {
        return Point(x * R , y * R);
    }
    Point operator / (const ll& R) const {
        return Point(x / R , y / R);
    }
    ll operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    ll operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
} P[307];

int solve() {
    int n,m;
    scanf("%d",&n);
    vector<int> res(n+1),A(n+1);
    FOR_(i,1,n) scanf("%d",&A[i]);
    FOR_(i,1,n) res[i]=INF;
    // f1和fn单独算; 其他的话考虑是否有相连的[大大]或者[小小]就可以了
    { // f1
        int cur=0; res[1]=1;
        for (int k=2;;) {
            if (k>n) {res[1]=-1; break;}
            if (A[k]>A[1]) cur++; else cur--; k++;
            if (k>n) {res[1]=-1; break;}
            if (A[k]>A[1]) cur++; else cur--; k++;
            res[1]+=2;
            if (cur) break;
        }
    }
    { // fn
        int cur=0; res[n]=1;
        for (int k=n-1;;) {
            if (k<1) {res[n]=-1; break;}
            if (A[k]>A[n]) cur++; else cur--; k--;
            if (k<1) {res[n]=-1; break;}
            if (A[k]>A[n]) cur++; else cur--; k--;
            res[n]+=2;
            if (cur) break;
        }
    }
    FOR_(i,2,n-1) {
        int cur=0;
        if (A[i-1]>A[i]) cur++; else cur--;
        if (A[i+1]>A[i]) cur++; else cur--;
        if (cur) res[i]=3;
    }
    vector<int> pos(n+1);
    FOR_(i,1,n) pos[A[i]]=i;
    {  // 找连着的k个same; small
        set<int> S,In;
        FOR_(i,1,n) {
            int x=pos[i];
            // find比x小的
            if (x!=1&&x!=n) {
                auto it=In.lower_bound(x);
                int cur=INF;
                if (it!=In.end()) cur=min(cur,*it-x+2);
                if (it!=In.begin()) cur=min(cur,x-*prev(it)+2);
                if (!(cur&1)) cur++;
                assert(cur>=3);
                // printf("smaller x=%d: cur=%d\n",x,cur); // distance
                min_(res[x],cur);
            }
            S.insert(x);
            if (S.count(x+1)) In.insert(x+1),In.insert(x);
            if (S.count(x-1)) In.insert(x-1),In.insert(x);
        }
    }
    {  // 找连着的k个same; larger
        set<int> S,In;
        rFOR_(i,1,n) {
            int x=pos[i];
            // find比x大的
            if (x!=1&&x!=n) {
                auto it=In.lower_bound(x);
                int cur=INF;
                if (it!=In.end()) cur=min(cur,*it-x+2);
                if (it!=In.begin()) cur=min(cur,x-*prev(it)+2);
                if (!(cur&1)) cur++;
                assert(cur>=3);
                // printf("larger x=%d: cur=%d\n",x,cur); // distance
                min_(res[x],cur);
            }
            S.insert(x);
            if (S.count(x+1)) In.insert(x+1),In.insert(x);
            if (S.count(x-1)) In.insert(x-1),In.insert(x);
        }
    }
    FOR_(i,1,n) if (res[i]>n) res[i]=-1;
    FOR_(i,1,n) printf("%d ",res[i]);
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