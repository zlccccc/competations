// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I, N) for (int I = 0, END = (N); I < END; I++)
#define rREP_(I, N) for (int I = (N)-1; I >= 0; I--)
#define rep_(I, S, N) for (int I = (S), END = (N); I < END; I++)
#define rrep_(I, S, N) for (int I = (N)-1, START = (S); I >= START; I--)
#define FOR_(I, S, N) for (int I = (S), END = (N); I <= END; I++)
#define rFOR_(I, S, N) for (int I = (N), START = (S); I >= START; I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n", str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fll;
const LL maxn = 5e5 + 7;
const double pi = acos(-1.0);
const double eps = 1e-10;
template <typename T> inline void pr2(T x, int k = 64) {
    REP_(i, k) debug("%d", (x >> i) & 1);
    putchar(' ');
}
template <typename T> inline void max_(T &A, T B) { (A < B) && (A = B); }
template <typename T> inline void min_(T &A, T B) { (A > B) && (A = B); }
inline ll fastgcd(ll a, ll b) { // __gcd()
    if (!a)
        return b;
    ll az = __builtin_ctzll(a), bz = __builtin_ctzll(b), z = min(az, bz), diff;
    b >>= bz;
    while (a) {
        a >>= az, diff = b - a, az = __builtin_ctzll(diff);
        (b > a) && (b = a), a = abs(diff);
    }
    return b << z;
}
int startTime;
void startTimer() { startTime = clock(); }
void printTimer() { debug("/--- Time: %ld milliseconds ---/\n", clock() - startTime); }
typedef array<int, 4> ar4;
typedef array<int, 3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<pii> direction8 = {{-1, -1}, {-1, 0}, {1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

struct node{
    int x,l,r;  // x:cnt
}T[maxn*32];
void update(int &x,ll pos,ll L,ll R) {
    static int tot=0;
    // printf("update %d %d %lld %lld\n",x,pos,L,R);
    if (!x) x=++tot; T[x].x++;
    if (L==R) return;
    ll mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,L,mid);
    if (mid<pos) update(T[x].r,pos,mid+1,R);
}
ll query(int x,int k,ll L,ll R) {
    // printf("query %d %d %lld %lld; Cnt=%d\n",x,k,L,R,T[x].x);
    if (L==R) return L;
    ll mid=(L+R)/2;
    if (T[T[x].r].x>=k)
        return query(T[x].r,k,mid+1,R);
    return query(T[x].l,k-T[T[x].r].x,L,mid);
}
ll A[maxn];
int solve() {
    int n,m;
    ll k;
    scanf("%d%d%lld",&n,&m,&k);
    FOR_(i,1,n) scanf("%lld",&A[i]);
    sort(A+1,A+1+n);
    int last=n,root=0;
    ll t=A[last]/k;
    while (last&&A[last]/k==t) update(root,A[last]%k,0,k-1),last--;
    int remain=0;  // root内有remain个位置是t*k+k+val; T[root].x-remain个位置是t*k+val;
    FOR_(_,1,m) {
        char s[2];
        ll x;
        scanf("%s",s);
        scanf("%lld",&x);
        // printf("  --- t=%lld; remain=%d\n",t,remain);
        if (s[0]=='A') {
            ll res;
            if (x<=T[root].x) {  // 在最大的那个树里面
                if (x<=T[root].x-remain) {  // delete
                    // printf("query type 1 k=%lld\n",remain+x);
                    res=query(root,remain+x,0,k-1)+k*t;
                } else {
                    // printf("query type 2 k=%lld\n",remain+x-T[root].x);
                    res=query(root,x+remain-T[root].x,0,k-1)+k*(t-1);
                }
            } else {
                res=A[n-x+1];
            }
            printf("%lld\n",res);
        } else {
            x+=remain; remain=0;
            // printf("update; x=%d\n",x);
            while (last&&x>=(t-A[last]/k)*T[root].x) {
                // printf("merge last; x=%lld; last=%lld\n",x,A[last]/k);
                x-=(t-A[last]/k)*T[root].x; t=A[last]/k;  // delete
                update(root,A[last]%k,0,k-1);  // merge
                last--;
            }
            t-=x/T[root].x; x%=T[root].x; 
            remain=x; // last-delete-times
            ll limit=query(root,remain+1,0,k-1);
            while (last&&A[last]/k==t-1) {
                if (A[last]%k>=limit) {
                    update(root,A[last]%k,0,k-1);
                    remain++; last--;
                } else break;
            }
        }
    }
    return 0;
}
int main() {
    int T;
    T = 1;
    // cin >> T;
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
    // printTimer();
}
/*
 */