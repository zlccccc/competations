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

int A[67][67];
void solve(int l,int r,int L,int R,int k) {
    if (k==-1) return;
    int i,j;
    // FOR(i,l,r) FOR(j,L,R) {
    //     if ((k&1)&&(i>(l+r)/2)) A[i][j]+=1<<k;
    //     else if ((!(k&1))&&(i>(L+R)/2)) A[i][j]+=1<<k;
    // }
    if (k&1) {
        int mid=(l+r)/2;
        solve(l,mid,L,R,k-1);
        FOR(i,l,r) FOR(j,L,R) {
            if (i>mid) A[i][j]=(1<<k)+A[mid+mid+1-i][j];
        }
        // solve(mid+1,r,L,R,k-1);
    } else {
        int mid=(L+R)/2;
        solve(l,r,L,mid,k-1);
        // FOR(i,l,r) FOR(j,L,R) {
        //     if ((k&1)&&(i>(l+r)/2)) A[i][j]+=1<<k;
        //     else if ((!(k&1))&&(i>(L+R)/2)) A[i][j]+=1<<k;
        // }
        FOR(i,l,r) FOR(j,L,R) {
            if (j>mid) A[i][j]=(1<<k)+A[i][mid+mid+1-j];
        }
        // solve(l,r,mid+1,R,k-1);
    }
}
void init() {
    int i,j,tot=0,All=0;
    // FOR(i,1,64) {
    //     FOR(j,1,32) if (1<=i-j&&i-j<=32) {
    //         A[i-j][j]=tot++;
    //     }
    // }
    solve(1,32,1,32,9);
    // FOR(i,1,10) FOR(j,1,10) printf("%d%c",A[i][j]," \n"[j==10]);
    FOR(i,1,32) FOR(j,1,32) {
        if (i!=32) All+=A[i][j]^A[i+1][j];
        if (j!=32) All+=A[i][j]^A[i][j+1];
    }
    // printf("all=%d\n",All);
}
int main() {
    init();
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,n-1) {
        printf("%d%c",A[i][j]^A[i][j+1]," \n"[j==n-1]);
    }
    FOR(i,1,n-1) FOR(j,1,n) {
        printf("%d%c",A[i][j]^A[i+1][j]," \n"[j==n]);
    }
    int all=0;
    FOR(i,1,m) {
        int k,x,y;
        fflush(stdout);
        scanf("%d",&k); all^=k;
        FOR(x,1,n) FOR(y,1,n) if (A[x][y]==all) printf("%d %d\n",x,y);
    }

}
/*
*/