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

int phi[maxn],phisum[maxn];
void init() {
    phi[1]++;
    FOR_(i,1,2000000) {
        for (int j=i+i;j<=2000000;j+=i) phi[j]-=phi[i];
    }
    FOR_(i,1,2000000) phisum[i]=phi[i]+phisum[i-1];
    // FOR_(i,1,10) printf("%d ",phi[i]); puts("<- phi");
    // FOR_(i,1,10) printf("%d ",phisum[i]); puts("<- phi");
}
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    // a=b*(b-1);
    int res=0,prek=0;
    FOR_(k,1,min(n,m)) {
        // gcd(a,b)=k => gcd(a*b*k,(a+b))=(a+b) [gcd(a,b)=1]
        int cn=n/k,cm=m/k;
        int nxtk=min(n/cn,m/cm);
        FOR_(g,1,min(cn,cm)) {
            int a=nxtk/g,b=(k-1)/g;
            if (!a&&!b) break;
            int dn=cn/g,dm=cm/g;
            int nxtg=min({dn/g,dm/g});
            if (a) nxtg=min(nxtg,nxtk/a);
            if (b) nxtg=min(nxtg,(k-1)/b);
            // printf("solve %d -> %d; nxtk=%d; k=%d; d=%d\n",g,nxtg,nxtk,k-1,dn);
            nxtg=max(nxtg,g);
            FOR_(x,1,dn) FOR_(sum,x+1,x+dm) {
                // res+=(a/sum-b/sum)*phi[g];
                int da=a/sum,db=b/sum;
                if (!da&&!db) break;
                int nxtsum=x+dm;
                if (da) nxtsum=min(nxtsum,a/(da));
                if (db) nxtsum=min(nxtsum,b/(db));
                res+=(da-db)*(phisum[nxtg]-phisum[g-1])*(nxtsum-sum+1);
                sum=nxtsum;
            }
            g=nxtg;
            // FOR_(x,1,cn/g) FOR_(y,1,cm/g) res+=(a/(x+y)-b/(x+y))*phi[g];
        }

        k=nxtk;
    }
    printf("%d\n",res);
    return 0;
}
int main() {
    init();
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/