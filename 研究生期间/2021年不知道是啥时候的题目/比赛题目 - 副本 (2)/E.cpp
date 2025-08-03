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
const LL maxn=107;
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

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

int XA[1027],XB[1027];
int c[2][17],tot[2];
vector<int> X,Y;
inline void dfs(int op,int val,int A,int B) {
    // printf("dfs %d %d  ",op,val); pr2(A,tot[0]); pr2(B,tot[1]); puts(" <- dfs");
    if (!A&&!B) {X.push_back(val); return;}
    if (op==0) {
        for (int k=A;k;k=A&(k-1)) {
            dfs(op^1,(val+XA[k])%M,A^k,B);
        }
    } else {
        for (int k=B;k;k=B&(k-1)) {
            dfs(op^1,((ll)val*XB[k])%M,A,B^k);
        }
    }
}
int n;
int lg[1027];
int A[27]; char s[27][3];
int solve(int x,int sta) {
    int i;
    tot[0]=tot[1]=0;
    FOR(i,1,n) if (sta>>(i-1)&1) {
        if (s[i][0]=='+') c[0][tot[0]++]=A[i];
        else c[1][tot[1]++]=A[i];
    } XA[0]=0; XB[0]=1;
    rep(i,1,(1<<tot[0])) XA[i]=(XA[i-(i&-i)]+c[0][lg[i&-i]])%M;
    rep(i,1,(1<<tot[1])) XB[i]=(ll)XB[i-(i&-i)]*c[1][lg[i&-i]]%M;
    // rep(i,1,(1<<tot[0])) printf("%d ",XA[i]); puts("<- xa");
    // rep(i,1,(1<<tot[0])) printf("%d ",XB[i]); puts("<- xb");
    if (tot[0]) dfs(0,x,(1<<tot[0])-1,(1<<tot[1])-1);
    if (tot[1]) dfs(1,x,(1<<tot[0])-1,(1<<tot[1])-1);
    return XB[(1<<tot[1])-1];
}
int ans;
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int x,i;
        scanf("%d%d",&n,&x);
        tot[0]=tot[1]=0;
        FOR(i,1,n) {
            lg[1<<(i-1)]=i-1;
            scanf("%s%d",s[i],&A[i]);
        } int ans=M;
        REP(i,(1<<n)) {
            if (__builtin_popcount(i)==n/2) {
                X.clear(); Y.clear();
                int mul=solve(0,i); //second
                X.swap(Y); solve(x,((1<<n)-1)^i); //first
                for (int &v:X) v=(ll)v*mul%M;
                sort(X.begin(),X.end());
                sort(Y.begin(),Y.end());
                // pr2(i,n); printf("  %u %u, ans=%d\n",X.size(),Y.size(),ans);
                // for (int v:X) for (int u:Y) 
                //     ans=min((ll)ans,(u+v)%M);
                for (int v:X) {
                    int now=v+Y[0]; if (now>=M) now-=M;
                    ans=min(ans,now);
                    auto it=lower_bound(Y.begin(),Y.end(),M-v);
                    if (it!=Y.end()) now=v+*it-M;
                    ans=min(ans,now);
                }
            }
        }
        printf("%d\n",ans);
    }
}
/*
*/