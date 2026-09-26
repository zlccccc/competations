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

namespace Count{
    struct tnode{
        int l,r,cnt;
    }T[maxn*37]; int tot=0;
    void update(int &x,int y,int pos,int L,int R) {
        T[++tot]=T[y]; T[tot].cnt++; x=tot;
        if (L==R) return;
        int mid=(L+R)/2;
        if (pos<=mid) update(T[x].l,T[y].l,pos,L,mid);
        else update(T[x].r,T[y].r,pos,mid+1,R);
    }
    int query(int x,int pos,int L,int R) {
        if (!x) return 0;
        if (L==R) return T[x].cnt;
        int mid=(L+R)/2;
        if (pos<=mid) return query(T[x].l,pos,L,mid);
        else return query(T[x].r,pos,mid+1,R);
    }
    int qid(int x,int y,int Count,int L,int R) {
        if (T[y].cnt-T[x].cnt<=Count) return -1;
        if (L==R) return R;
        int mid=(L+R)/2;
        int val=qid(T[x].r,T[y].r,Count,mid+1,R);
        if (val>=0) return val;
        return qid(T[x].l,T[y].l,Count,L,mid);
    }
}
int A[maxn];
int root[maxn];
int main() {
    int i,n,m;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) Count::update(root[i],root[i-1],A[i],0,INF);
    // build(1,1,n);
    FOR(i,1,m) {
        int l,r,t;
        scanf("%d%d%d",&l,&r,&t);
        printf("%d\n",Count::qid(root[l-1],root[r],(r-l+1)/t,0,INF));
    }
}
/*
*/