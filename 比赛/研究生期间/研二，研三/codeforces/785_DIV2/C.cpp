#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

char str[maxn];
int val[18];
vector<int> inside,nxt;
int Pre[40007],ans[40007];
void init() {
    int i,j;
    ans[0]=1;
    FOR(i,1,40000) {
        int len=0; bool mark=1; int c=0;
        for (int k=i;k;k/=10) val[++len]=k%10;
        FOR(c,1,len) if (val[c]!=val[len-c+1]) mark=0;
        if (!mark) continue;
        FOR(j,0,40000) Pre[j]=0;
        FOR(j,0,40000) {
            int t=ans[j];
            add_(ans[j],Pre[j%i]);
            add_(Pre[j%i],t);
        }
        // FOR(j,0,20) printf("%d ",ans[j]); puts("<- ans");
        // if (mark) printf("%d ",i);
        // for (int j=i;j<=40000;j+=i) Pre[j]++;
        // nxt.push_back(j);
    }
    // printf("%d\n",nxt.size());
    // FOR(i,1,40000) {
    //     rFOR(j,0,i-1) add_(ans[i],(ll)ans[j]*Pre[i-j]%M);
    // }
    // FOR(i,1,40) printf("%d ",Pre[i]); puts("<- pre");
    // FOR(i,1,40) printf("%d ",ans[i]); puts("<- pre");
}
int main() {
    init();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        int n; scanf("%d",&n);
        printf("%d\n",ans[n]);
    }
}
/*
*/