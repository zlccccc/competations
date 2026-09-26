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
const LL maxn=3e5+107;
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

int T[maxn*4];
void update(int x,int pos,int L,int R) {
    T[x]++;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
}
int query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2,ret=0;
    if (l<=mid) ret+=query(x<<1,l,r,L,mid);
    if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
    return ret;
}
int querypos(int x,int k,int L,int R) {
    if (L==R) return L;
    int mid=(L+R)/2;
    if (T[x<<1]<k) return querypos(x<<1|1,k-T[x<<1],mid+1,R);
    else return querypos(x<<1,k,L,mid);
}
int A[maxn],p[maxn];
vector<pair<int,int> > Q[maxn];//front
int ans[maxn];
int main() {
    int n,q,i;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,q) {
        int x,y; scanf("%d%d",&x,&y);
        Q[n-y].push_back(make_pair(x,i));
    }
    FOR(i,1,n) {//前面要删几个; 贪心的remove last
        if (A[i]>i) p[i]=0;
        else p[i]=min(i,querypos(1,A[i],0,n));
        update(1,p[i],0,n);
        // printf("i=%d; k=%d; p=%d\n",i,A[i],p[i]);
        for (auto now:Q[i]) {
            ans[now.second]+=i-query(1,0,now.first,0,n);//first kth
        }
    }
    // FOR(i,1,n) printf("%d ",p[i]); puts("<- p");
    FOR(i,1,q) printf("%d\n",ans[i]);
}
/*
2
2 1
2 1
*/