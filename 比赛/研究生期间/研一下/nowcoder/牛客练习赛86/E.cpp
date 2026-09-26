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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

ull Rd0[maxn],Rd1[maxn];
struct Node{
    ull hash; int val;
    int l,r;
}T[maxn*120]; int tot;
void update(int &x,int pos,int val,int L,int R) {
    T[++tot]=T[x]; x=tot;
    if (L==R) {T[x].hash=Rd0[val]; T[x].val=val; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,val,L,mid);
    if (mid<pos) update(T[x].r,pos,val,mid+1,R);
    T[x].hash=(T[T[x].l].hash*Rd1[mid]+T[T[x].r].hash);
}
int query(int x,int y,int L,int R) {
    if (L==R) {
        // printf("calculate pos=%d; %d %d\n",L,T[x].val,T[y].val);
        return T[x].val<T[y].val;
    } int mid=(L+R)/2;
    if (T[T[x].l].hash!=T[T[y].l].hash)
        return query(T[x].l,T[y].l,L,mid);
    else
        return query(T[x].r,T[y].r,mid+1,R);
}
int A[maxn];
int Cnt[maxn];
int root[maxn],id[maxn];
int main() {
    int t;
    int n,m,i;
    scanf("%d%d",&n,&m); m--; n++; A[n]=0;
    FOR(i,1,n) Rd0[i]=rand(),Rd1[i]=rand();
    FOR(i,1,n-1) scanf("%d",&A[i]);
    FOR(i,1,n) update(root[0],i,A[i],1,n);
    FOR(i,0,m) id[i]=i;
    // printf("Seq  "); FOR(t,1,n) printf("%d%c",A[t]," \n"[t==n]);
    FOR(i,1,m) {
        int x,y; scanf("%d%d",&x,&y);
        swap(A[x],A[y]); A[n]=i;
        root[i]=root[i-1];
        update(root[i],x,A[x],1,n);
        update(root[i],y,A[y],1,n);
        update(root[i],n,A[n],1,n);
        // printf("Seq  "); FOR(t,1,n) printf("%d%c",A[t]," \n"[t==n]);
    }
    // FOR(i,0,m) FOR(t,0,m) {
    //     printf("query %d-%d: %d\n",i,t,query(root[i],root[t],1,n));
    // }
    sort(id,id+m+1,[&](int x,int y){ //x-pos,y-pos
        return query(root[x],root[y],1,n);
    });
    FOR(i,0,m) printf("%d%c",id[i]," \n"[i==m]);
}
/*
3 10
3 1 2
1 2
1 2
1 2
1 3
1 3
1 3
2 3
1 2
1 2
1 2
*/