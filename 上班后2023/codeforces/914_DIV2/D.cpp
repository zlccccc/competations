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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
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

int A[maxn],B[maxn];
int val[maxn];
int solve() {
    int n;
    scanf("%d",&n);
    FOR_(i,1,n) scanf("%d",&A[i]);
    FOR_(i,1,n) scanf("%d",&B[i]);
    FOR_(i,1,n) if (A[i]>B[i]) return 0*puts("No");
    vector<vector<pii>> val(n+2);
    {
        vector<int> l(n+1,1),r(n+1,n);
        vector<vector<int>> ids(n+1);
        FOR_(i,1,n) ids[A[i]].push_back(i);
        // FOR_(i,1,n) printf("%d ",A[i]); puts("<- A");
        {
            vector<vector<int>> limit(n+1);
            set<int> S;
            S.insert(0); S.insert(n+1);
            FOR_(i,1,n) limit[B[i]].push_back(i);
            FOR_(i,1,n) {  // l->r: A<=x; B>=x
                for (int x:ids[i]) {
                    auto it=S.lower_bound(x);
                    min_(r[x],(*it)-1); it--; max_(l[x],(*it)+1);
                }
                for (int x:limit[i]) S.insert(x);
            }
        }
        // FOR_(i,1,n) printf("col %d: %d->%d\n",i,l[i],r[i]); puts("<- fir");
        {
            vector<vector<int>> limit(n+1);
            set<int> S;
            S.insert(0); S.insert(n+1);
            FOR_(i,1,n) limit[A[i]].push_back(i);
            rFOR_(i,1,n) {  // l->r: A<=x; B>=x
                for (int x:ids[i]) {
                    auto it=S.lower_bound(x);
                    min_(r[x],(*it)-1); it--; max_(l[x],(*it)+1);
                    // printf("col %d: %d->%d\n",i,l,r);
                }
                for (int x:limit[i]) S.insert(x);
            }
        }
        FOR_(i,1,n) {
            val[l[i]].push_back({A[i],1});
            val[r[i]+1].push_back({A[i],-1});
            // printf("col %d: %d->%d\n",i,l[i],r[i]);
        }
    }
    multiset<int> S;
    FOR_(i,1,n) {
        for (auto &cur:val[i]) {
            if (cur.second==1) S.insert(cur.first);
            else S.erase(S.lower_bound(cur.first));
        }
        if (!S.size()||*S.rbegin()!=B[i]) return 0*puts("No");
    }
    puts("Yes");
    return 0;
}
int main() {
    int T; T=1;
    scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
    return 0;
}
/*
*/