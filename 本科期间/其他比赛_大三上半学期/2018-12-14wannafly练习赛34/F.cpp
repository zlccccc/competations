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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];
 
struct node{
    int l,r,val,min;
}T[maxn]; int tot;
int root[maxn];
inline void update(int &x,int y,int pos,int val,int L,int R){//this_value;
    x=++tot; T[x]=T[y];
    if (L==R){
        T[x].val++; T[x].min=val; return;
    } int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,T[y].l,pos,val,L,mid);
    if (mid<pos) update(T[x].r,T[y].r,pos,val,mid+1,R);
    T[x].val=T[T[x].l].val+T[T[x].r].val;
    T[x].min=min(T[T[x].l].min,T[T[x].r].min);
}
int sum,pos;
//x:not ensure
inline void query(int x,int pos,int L,int R){//from L->R
    // printf("%d: %d-%d: %d\n",x,L,R,T[x].min);
    if (L==R) {::pos=L-1; return;}
    int mid=(L+R)/2;
    if (T[T[x].l].min<pos) {
        query(T[x].l,pos,L,mid);
    } else {//l:ensure
        sum+=T[T[x].l].val;
        query(T[x].r,pos,mid+1,R);
    }
}
inline void query(int x,int l,int r,int L,int R){
    // printf("query:%d-%d  %d - %d:  %d\n",L,R,l,r,,);
    if (l>r) return;
    if (l<=L&&R<=r) {
        sum-=T[x].val;
        return;
    } int mid=(L+R)/2;
    if (l<=mid) query(T[x].l,l,r,L,mid);
    if (mid<r) query(T[x].r,l,r,mid+1,R);
}
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n) {
        int x; scanf("%d",&x);
        x=min(x,n+1);
        update(root[i],root[i-1],x,i,1,n+1);
    } scanf("%d",&q);
    while (q--){
        int l,r; sum=0;
        scanf("%d%d",&l,&r);
        query(root[r],l,1,n+1);
        // printf("pos=%d; sum=%d\n",pos,sum);
        query(root[l-1],1,pos,1,n+1);
        printf("%d\n",r-l+1-sum);
    }
}
/*
*/