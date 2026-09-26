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
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e7+107;
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

int P[maxn/10],tot;
int pw[maxn/10],inv[maxn/16];
bool mark[maxn];
int val[maxn],tmp[maxn],fin[maxn];
void solve(int n,int x) {//sigma
    int i,j; val[1]=tmp[1]=fin[1]=1;
    FOR(i,2,n) mark[i]=0; tot=0;
    FOR(i,2,n) {
        if (!mark[i]) {
            pw[tot]=powMM(i,x);
            val[i]=1;
            tmp[i]=fin[i]=(pw[tot]+1)%M;//last_position
            P[tot++]=i;
        }
        REP(j,tot){
            //感觉上不会爆,因为是从小往筛的
            int k=i*P[j];
            if (k>n) break;
            mark[k]=1;
            if (i%P[j]==0) {
                val[k]=val[i];
                tmp[k]=((ll)tmp[i]*pw[j]+1)%M;
                fin[k]=((ll)val[k]*tmp[k])%M;
                break;
            } else {
                val[k]=fin[i];
                tmp[k]=(pw[j]+1)%M;
                fin[k]=((ll)val[k]*tmp[k])%M;
            }
        }
    }
}
int finp[maxn],f[maxn],ans;
int main() {
    int n,p,q; scanf("%d%d%d",&n,&p,&q);
    int i,j;
    double t=clock();
    solve(n,p);
    printf("1 %f\n",clock()-t); t=clock();
    FOR(i,1,n) finp[i]=fin[i];
    solve(n,q);
    // FOR(i,1,n) printf("%d ",finp[i]); puts("<- p");
    printf("2 %f\n",clock()-t); t=clock();
    // FOR(i,1,n) printf("%d ",fin[i]); puts("<- q");
    FOR(i,1,n) {
        add_(f[i],fin[i]);
        for (j=2;j*i<=n;j++) add_(f[j*i],M-((ll)f[i]*finp[j])%M);
        // mul_(f[i],powMM(finp[i],M-2));
    }
    printf("3 %f\n",clock()-t); t=clock();
    FOR(i,1,n) ans^=f[i];
    printf("%d\n",ans);
    // FOR(i,1,n) printf("%d ",f[i]);
}
/*
2
2 1
2 1
*/