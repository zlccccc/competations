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
const LL maxn=2e5+7;
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

char s[maxn];
int pref[maxn];
int solve() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s",s+1);
    FOR_(i,1,n) s[i]-='0'; s[n+1]=0; // 最后一个位置是0
    FOR_(i,1,n) pref[i]=pref[i-1]+s[i];
    auto solve=[&](int len) {
        // printf("solve len=%d\n",len);
        vector<int> cur(n+2,INF); // 到1->x为止, 用了k-1段, 最少用了多少个0->1(最后一个位置是0)
        cur[0]=0;
        FOR_(i,1,n+1) min_(cur[i],cur[i-1]); // prefix_min
        REP_(_,k) {
            vector<int> nxt(n+2,INF);
            FOR_(i,len+1,n+1) if (s[i]==0) {
                // i-len->i-1都是1; i是0
                min_(nxt[i],cur[i-len-1]+len-(pref[i-1]-pref[i-len-1]));
            }
            cur.swap(nxt);
            // for (int v:cur) printf("%d ",v); puts("<- nxt");
            FOR_(i,1,n+1) min_(cur[i],cur[i-1]); // prefix_min
        }
        return cur[n+1]<=m;
    };
    int l=-1,r=n+1;
    while (l+1<r) {
        int mid=(l+r)/2;
        if (solve(mid)) l=mid;
        else r=mid;
    }
    if (l==0) l=-1;
    printf("%d\n",l);
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
    return 0;
}
/*
7 2
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
*/