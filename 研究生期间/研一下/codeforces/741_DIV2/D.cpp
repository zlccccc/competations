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
const LL maxn=1e6+107;
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

char s[maxn];
int A[maxn];
vector<pii> Q[maxn];
vector<int> ans[maxn];
int solve() {
    int n,q,i;
    scanf("%d%d%s",&n,&q,s+1);
    FOR(i,1,q) ans[i].clear();
    FOR(i,1,n) Q[i].clear();
    FOR(i,1,n) if (s[i]=='+') A[i]=1; else A[i]=-1;
    FOR(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        Q[r].push_back(make_pair(l,i));
    }
    map<int,int> MP;
    FOR(i,1,n) {//sum(l->r)=A  --> sum(l->x-1)-sum(x+1->r)=0
        if (i&1) A[i]=-A[i]; A[i]+=A[i-1];
        MP[A[i]+A[i-1]]=i;
        for (auto now:Q[i]) {
            int l=now.first,r=i,id=now.second;
            if (A[r]-A[l-1]==0) continue;
            if ((l&1)!=(r&1)) ans[id].push_back(l),l++;
            // A[x-1]-A[l-1] = A[r]-A[x]
            int pos=MP[A[r]+A[l-1]];
            ans[id].push_back(pos);
        }
    }
    FOR(i,1,q) {
        printf("%d\n",(int)ans[i].size());
        for (int v:ans[i]) printf("%d ",v); puts("");
    }
    return 0;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
*/