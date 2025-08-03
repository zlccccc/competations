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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

pair<int,pii> P[307],X[307];
//sort后单调递增!
int fa[307];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
pair<ll,ll> solve(int k,int n,int m) {
    // number, next-position, bias
    int i;
    FOR(i,1,n) fa[i]=i; i=1;
    int l=lower_bound(P+1,P+1+m,make_pair(k,make_pair(0,0)))-P-1,r=l+1;
    while (l!=0||r!=m+1) {
        if (l==0) X[i++]=P[r++];
        else if (r==m+1) X[i++]=P[l--];
        else if (k-P[l].first<P[r].first-k) X[i++]=P[l--];
        else X[i++]=P[r++];
    }
    // sort(P+1,P+1+m,[&](pair<int,pii> &x,pair<int,pii> &y){
    //     return abs(k-x.first)<abs(k-y.first);
    // });//m^2*logm
    ll retk=0,retb=0;
    // printf("solve: %d\n",k);
    FOR(i,1,m) {
        // printf("edge %d %d %d\n",X[i].first,X[i].second.first,X[i].second.second);
        // if (nxt[i]) 
        // for (int j=i+1;abs(P[i].first-k)>abs(P[j].first-k);j++)
        //     swap(P[i],P[j]);
        int u=X[i].second.first,v=X[i].second.second;
        u=getfa(u); v=getfa(v);
        if (u==v) continue;
        fa[u]=v;
        if (k<X[i].first) retk--,retb+=X[i].first;
        else retk++,retb-=X[i].first;
    }
    return make_pair(retk,retb);
}
int Q[(int)(1e7+7)];
vector<int> pos; int nowpos;
int main() {
    int n,m,i,j,p,k,a,b,c;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d%d",&P[i].second.first,&P[i].second.second,&P[i].first);
    FOR(i,1,m) pos.push_back(P[i].first);
    FOR(i,1,m) FOR(j,i+1,m) pos.push_back((P[i].first+P[j].first+1)/2);
    pos.push_back(INF); sort(pos.begin(), pos.end());
    scanf("%d%d%d%d%d",&p,&k,&a,&b,&c);
    sort(P+1,P+1+m);
    FOR(i,1,p) scanf("%d",&Q[i]);
    FOR(i,p+1,k) Q[i]=((ll)Q[i-1]*a+b)%c;
    sort(Q+1,Q+1+k);
    pll nowans=solve(0,n,m);
    ll ans=0;
    FOR(i,1,k) {
        if (Q[i]>=pos[nowpos]) {
            while (Q[i]>=pos[nowpos]) nowpos++;
            // nowans=solve(Q[i],n,m);
            nowans=solve(pos[nowpos-1],n,m);
        } ans^=nowans.first*Q[i]+nowans.second;
        // printf("query %d: k=%lld; b=%lld; ans=%lld\n",Q[i],nowans.first,nowans.second,nowans.first*Q[i]+nowans.second);
    }
    printf("%lld\n",ans);
}
/*
*/