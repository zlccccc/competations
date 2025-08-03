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
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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

int T[maxn<<2];
void update(int x,int pos,int val,int L,int R) {
    if (L==R) {T[x]=val; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
    T[x]=max(T[x<<1],T[x<<1|1]);
}
int query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2; int ret=0;
    if (l<=mid) max_(ret,query(x<<1,l,r,L,mid));
    if (mid<r) max_(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
vector<int> edge[maxn];
vector<pii> res;
int A[maxn],B[maxn];
int D[maxn];
int solve() {
    int n;
    scanf("%d",&n);
    FOR_(i,1,n) scanf("%d",&A[i]);
    FOR_(i,1,n) scanf("%d",&B[i]);
    FOR_(i,1,n) update(1,i,0,1,n);
    FOR_(i,1,n) {
        int x=query(1,A[i],n,1,n);
        if (x) res.push_back({A[x],A[i]});
        update(1,A[i],i,1,n);
    }
    FOR_(i,1,n) update(1,i,0,1,n);
    FOR_(i,1,n) {
        int x=query(1,1,B[i],1,n);
        if (x) res.push_back({B[x],B[i]});
        update(1,B[i],i,1,n);
    }
    for (auto &p:res) edge[p.first].push_back(p.second);
    {
        for (auto &p:res) D[p.second]++;
        priority_queue<int> Q;
        FOR_(i,1,n) if (!D[i]) Q.push(-i);
        FOR_(i,1,n) {
            if (!Q.size()) return 0*puts("No");
            int x=-Q.top(); Q.pop();
            if (x!=A[i]) return 0*puts("No");
            for (int v:edge[x]) {
                D[v]--; if (!D[v]) Q.push(-v);
            }
        }
    }
    {
        for (auto &p:res) D[p.second]++;
        priority_queue<int> Q;
        FOR_(i,1,n) if (!D[i]) Q.push(i);
        FOR_(i,1,n) {
            if (!Q.size()) return 0*puts("No");
            int x=Q.top(); Q.pop();
            if (x!=B[i]) return 0*puts("No");
            for (int v:edge[x]) {
                D[v]--; if (!D[v]) Q.push(v);
            }
        }
    }
    puts("Yes");
    printf("%d\n",res.size());
    for (auto &p:res) printf("%d %d\n",p.first,p.second);
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/