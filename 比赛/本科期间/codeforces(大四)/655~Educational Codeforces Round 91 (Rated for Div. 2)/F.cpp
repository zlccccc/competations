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
const LL maxn=5e5+107;
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

//md没交上去
struct matrix{
    int A[2][2];
    matrix(){memset(A,0,sizeof(A));};
    matrix(int a,int b,int c,int d){
        memset(A,0,sizeof(A));
        A[0][0]=a; A[0][1]=b;
        A[1][0]=c; A[1][1]=d;
    }
}T[maxn*4];
matrix mul(matrix &A,matrix &B){
    matrix C;int i,j,k;
    FOR(i,0,1)
        FOR(j,0,1)
            FOR(k,0,1)
                C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%M;
    return C;
}
int one[107],two[107];
int A[maxn];
inline void update(int x,int pos,int L,int R) {
    if (L==R) {//now,nxt
        // printf("%d %d; %d\n",A[pos],A[pos-1],two[A[pos-1]*10+A[pos]]);
        T[x]=matrix(one[A[pos]],1,two[A[pos-1]*10+A[pos]],0);//dp[i+2]
        return;
    } int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
    T[x]=mul(T[x<<1],T[x<<1|1]);//from high to this
    // printf("[%d-%d]: [%d-%d,%d-%d]\n",L,R,T[x].A[0][0],T[x].A[0][1],T[x].A[1][0],T[x].A[1][1]);
}
char str[maxn];
int main() {
    int n,m,i,j;
    FOR(i,0,9) FOR(j,0,9) if (i+j<10) one[i+j]++; else two[i+j]++;//one digit
    scanf("%d%d",&n,&m);
    scanf("%s",str+1);
    FOR(i,1,n) {
        A[i]=str[i]-'0';
        update(1,i,1,n);
    }
    // printf("%d\n",T[1].A[1][0]);
    FOR(i,1,m) {
        int x,y; scanf("%d%d",&x,&y);
        A[x]=y; update(1,x,1,n);
        if (x!=n) update(1,x+1,1,n);
        printf("%d\n",T[1].A[0][0]);
    }
}
/*
*/