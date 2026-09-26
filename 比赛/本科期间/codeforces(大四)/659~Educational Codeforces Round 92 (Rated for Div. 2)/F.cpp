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
const LL maxn=4e5+107;
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

struct Tree{
    int V[maxn<<4],MAX[maxn<<4];
    void update(int x,int l,int r,int val,int L,int R) {
        if (l<=L&&R<=r) {
            V[x]+=val; MAX[x]+=val;
            return;
        } int mid=(L+R)/2;
        if (l<=mid) update(x<<1,l,r,val,L,mid);
        if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
        MAX[x]=V[x]+max(MAX[x<<1],MAX[x<<1|1]);
    }
    void update_val(int x,int pos,int val,int L,int R) {
        val-=V[x];
        if (L==R) {
            max_(MAX[x],val);
            return;
        } int mid=(L+R)/2;
        if (pos<=mid) update_val(x<<1,pos,val,L,mid);
        if (mid<pos) update_val(x<<1|1,pos,val,mid+1,R);
        MAX[x]=V[x]+max(MAX[x<<1],MAX[x<<1|1]);
    }
    int query(int x,int l,int r,int L,int R) {
        if (l<=L&&R<=r) return MAX[x];
        int ret=0,mid=(L+R)/2;
        if (l<=mid) max_(ret,query(x<<1,l,r,L,mid));
        if (mid<r) max_(ret,query(x<<1|1,l,r,mid+1,R));
        return ret+V[x];
    }
}T[2];
vector<int> V;
inline int getid(int x) {return lower_bound(V.begin(),V.end(),x)-V.begin()+1;}
vector<pair<pair<int,int>,int> > A;
int main() {
    int i,n;
    scanf("%d",&n);
    FOR(i,1,n){
        int l,r,t;
        scanf("%d%d%d",&l,&r,&t);
        A.push_back(make_pair(make_pair(r,l),t-1));
        V.push_back(r); V.push_back(l-1);
    } sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()),V.end());
    sort(A.begin(), A.end());
    int N=V.size();
    for (auto p:A) {
        int r,l,t; t=p.second;
        r=p.first.first; l=p.first.second;
        r=getid(r); l=getid(l-1);
        int now=T[t^1].query(1,1,l,1,N);
        T[t^1].update(1,1,l,1,1,N);
        T[t].update_val(1,r,now+1,1,N);
        // printf("%d %d %d: now=%d+1\n",l,r,t,now);
    } int ans=0;
    max_(ans,T[0].query(1,1,N,1,N));
    max_(ans,T[1].query(1,1,N,1,N));
    printf("%d\n",ans);
}
/*
2
5
01011
11100
*/