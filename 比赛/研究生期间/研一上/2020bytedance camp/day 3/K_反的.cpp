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

struct node{
    int l,r;
    ll val=-INFF;
}T[maxn*32*8];
int root[2][4],tot;
void update(int &x,int pos,ll val,int L=1,int R=1e8) {
    if (!x) x=++tot;
    T[x].val=max(T[x].val,val);
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,val,L,mid);
    else update(T[x].r,pos,val,mid+1,R);
}
ll query(int x,int l,int r,int L=1,int R=1e8) {
    if (!x) return -INFF;
    if (l<=L&&R<=r) return T[x].val;
    int mid=(L+R)/2; ll ret=-INFF;
    if (l<=mid) ret=max(ret,query(T[x].l,l,r,L,mid));
    if (mid<r) ret=max(ret,query(T[x].r,l,r,mid+1,R));
    // printf("ret=%lld\n",ret);
    return ret;
}
int main() {
    int i,n,A,B,mask;
    scanf("%d%d%d",&n,&A,&B);
    FOR(i,1,n) {
        int l,c,h; ll now;
        scanf("%d%d%d",&l,&c,&h);
        if (i==1) mask=(l+c+h)&1;//op
        else if (((l+c+h)&1)!=mask) return 0*printf("%d",i);
        if ((now=query(root[0][0],1,h)-h-c-l)>0) return 0*printf("%d",i); printf("1~%lld\n",now);
        if ((now=query(root[0][1],1,h)-h-c+l)>0) return 0*printf("%d",i); printf("1~%lld\n",now);
        if ((now=query(root[0][2],1,h)-h+c-l)>0) return 0*printf("%d",i); printf("1~%lld\n",now);
        if ((now=query(root[0][3],1,h)-h+c+l)>0) return 0*printf("%d",i); printf("1~%lld\n",now);
        update(root[0][0],h,h+c+l);
        update(root[0][1],h,h+c-l);
        update(root[0][2],h,h-c+l);
        update(root[0][3],h,h-c-l);

        if ((now=query(root[1][0],h,1e8)+h-c-l)>0) return 0*printf("%d",i);  printf("2~%lld\n",now);
        if ((now=query(root[1][1],h,1e8)+h-c+l)>0) return 0*printf("%d",i);  printf("2~%lld\n",now);
        if ((now=query(root[1][2],h,1e8)+h+c-l)>0) return 0*printf("%d",i);  printf("2~%lld\n",now);
        if ((now=query(root[1][3],h,1e8)+h+c+l)>0) return 0*printf("%d",i);  printf("2~%lld\n",now);
        update(root[1][0],h,-h+c+l);
        update(root[1][1],h,-h+c-l);
        update(root[1][2],h,-h-c+l);
        update(root[1][3],h,-h-c-l);
    }
    puts("bravo komisijo");
}
/*
*/