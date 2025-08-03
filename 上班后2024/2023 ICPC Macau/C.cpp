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

int A[maxn],k;
int solve(int n) {
    sort(A+1,A+1+n);
    int cur=0,cnt=0;
    FOR_(i,1,n) if (A[i]>cur) {
        cur=max(cur+k,A[i]);
        cnt++;
    }
    return cnt;
}
int solve() {
    int n;
    scanf("%d%d",&n,&k);
    FOR_(i,1,n) scanf("%d",&A[i]);

    // n=4; k=2;
    // FOR_(i,1,n) A[i]=i;
    // random_shuffle(A+1,A+5);
    // FOR_(i,1,n) printf("%d ",A[i]);

    // FOR_(i,1,n) printf("%d ",solve(i)); puts("");

    set<int> dp; dp.insert(0);  // 前一个
    set<int> S; S.insert(0);  // x,x+k,A[i]

    // complexity: nsqrt
    FOR_(i,1,n) {
        int pre=0;
        {
            auto it=S.lower_bound(A[i]); it--;  // left-max
            pre=*it; S.insert(A[i]);
        }
        // calculate-value
        auto it=dp.lower_bound(pre);
        if (*it<A[i]) {  // fix-right
            int cur=max(A[i],*it+k);
            // printf("pre=%d; cur=%d; %d\n",pre,cur,A[i]);
            auto it=dp.upper_bound(cur);
            while (*it<cur&&it!=dp.end()) it=dp.erase(it);  // 不应该有这种情况
            while (!dp.count(cur)) {
                dp.insert(cur);
                int nxt;
                {
                    auto it=S.upper_bound(cur);  // 对应的value
                    // printf("cur=%d; it=%d\n",cur,*it);
                    if (it==S.end()) break;
                    nxt=max(cur+k,*it);
                }
                auto it=dp.upper_bound(cur); cur=nxt;
                while (it!=dp.end()&&*it<cur) it=dp.erase(it);
                if (cur>=*S.rbegin()) while (*dp.rbegin()>cur) dp.erase(*dp.rbegin());
            }
        }
        // printf("i=%d: ",i);
        // for (int v:dp) printf("%d ",v); puts("<- inside");
        printf("%d ",dp.size()-1);

        // if (dp.size()-1>n/k) exit(0);
    }
    puts("");
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
100
4 2
3 4 1 2
*/