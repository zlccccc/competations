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
const LL maxn=1e6+7;
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

pii pval[maxn*2];
pii merge(pii x, pii y) {
    if (x.first<y.first) swap(x.first,y.first);
    if (x.second<y.first) swap(x.second,y.first);
    if (x.first<y.second) swap(x.first,y.second);
    if (x.second<y.second) swap(x.second,y.second);
    return x;
}
void update_pos(int pos,int val,int L,int R) {
    int x=(L+R)|(L<R);
    // printf("%d: %d-%d (%d, %d)\n",x,pos,val,L,R);
    if (L==R) {
        pval[x]=merge(pval[x],make_pair(val,-INF));
        return;
    } int mid=(L+R)/2;
    // update_pos(pos,val,L,mid);
    // update_pos(pos,val,mid+1,R);
    if (pos<=mid) update_pos(pos,val,L,mid);
    if (mid<pos) update_pos(pos,val,mid+1,R);
    pval[x]=merge(pval[(L+mid)|(L<mid)],pval[(mid+1+R)|(mid+1<R)]);
}
pii query_pos(int l,int r,int L,int R) {
    int x=(L+R)|(L<R);
    if (l<=L&&R<=r) return pval[x];
    int mid=(L+R)/2; pii ret(-INF,-INF);
    if (l<=mid) ret=merge(ret,query_pos(l,r,L,mid));
    if (mid<r) ret=merge(ret,query_pos(l,r,mid+1,R));
    return ret;
}
int T[maxn*2];
pii rp[maxn];
void update(int l,int r,int L,int R) {
    int x=(L+R)|(L<R);
    if (l<=L&&R<=r) {T[x]++; return;}
    int mid=(L+R)/2;
    if (l<=mid) update(l,r,L,mid);
    if (mid<r) update(l,r,mid+1,R);
}
int query(int pos,int L,int R) {
    int x=(L+R)|(L<R);
    int ret=T[x];
    if (L==R) return ret;
    int mid=(L+R)/2;
    if (pos<=mid) ret+=query(pos,L,mid);
    if (mid<pos) ret+=query(pos,mid+1,R);
    return ret;
}
vector<pair<int,pii> > queries;
int A[maxn];
int main() {
    int i,n;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    // FOR(i,1,n*2) pval[i]=make_pair(-INF,-INF);
    // FOR(i,1,n) {
    //     lp[i]=query_pos(A[i],n,1,n);
    //     lp[i].first=max(lp[i].first,0);
    //     lp[i].second=max(lp[i].second,1);
    //     swap(lp[i].first,lp[i].second);
    //     printf("%d %d-%d\n",lp[i].first,lp[i].second,i);
    //     update_pos(A[i],i,1,n);
    // }
    FOR(i,1,n*2) pval[i]=make_pair(-INF,-INF);
    rFOR(i,1,n) {
        rp[i]=query_pos(1,A[i],1,n);
        // printf("%d %d\n",rp[i].first,rp[i].second);
        rp[i].first=min(-rp[i].first,n+1);
        rp[i].second=min(-rp[i].second-1,n);
        // printf("%d-%d %d\n",i,rp[i].first,rp[i].second);
        if (rp[i].first<=rp[i].second) {
            queries.push_back(make_pair(rp[i].first-1,make_pair(i,-1)));
            queries.push_back(make_pair(rp[i].second,make_pair(i,1)));
        }
        update_pos(A[i],-i,1,n);
    }
    sort(queries.begin(), queries.end());
    FOR(i,1,n*2) pval[i]=make_pair(-INF,-INF),T[i]=0;
    ll ans=0; int k=0;
    FOR(i,1,n) {
        pii lp;
        lp=query_pos(A[i],n,1,n);
        lp.first=max(lp.first,0);
        lp.second=max(lp.second+1,1);
        swap(lp.first,lp.second);
        // printf("%d %d-%d\n",lp.first,lp.second,i);
        update_pos(A[i],i,1,n);

        if (lp.second) update(lp.first,lp.second,1,n);
        while (k<(int)queries.size()&&queries[k].first==i) {
            auto now=queries[k++];
            ans+=now.second.second*query(now.second.first,1,n);
        }
    } printf("%lld\n",ans);
}
/*
6
6 5 4 3 2 1
*/