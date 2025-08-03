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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int a,b;
bool mark[maxn];
vector<int> p;
int f[maxn];
int A[maxn];
int ans[maxn];
int cnt[maxn];
int main() {
    int n,k,i,j,t;
    FOR(i,2,10000) if (!mark[i]){
        for (j=i;j<=10000;j+=i) mark[j]=1;
        p.push_back(i*i);
    }
//    printf("%d\n",(int)p.size());
//    for (int v:p) printf("%d ",v);puts("");
    scanf("%d",&n);//maximum:k
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) if (A[i]){
        for (int v:p)
            while (A[i]%v==0) A[i]/=v;
    }FOR(i,1,n){
        int now=1,have_0=0;
        rFOR(j,1,i){
//            if ((LL)A[i]*A[j]<0) break;
            if (A[j]==0) have_0=1;
            if (A[i]==A[j]) cnt[j]=0;
            now+=cnt[j];
            ans[max(1,now-have_0)]++;
//            printf("%d-%d: %d %d\n",j,i,now,have_0);
        }cnt[i]=1;
    }
//    FOR(i,1,n) printf("%d ",A[i]);puts("");
    FOR(i,1,n) printf("%d ",ans[i]);
    return 0;
}
/*
10
0 0 5 0 0 5 0 0 5 0
*/
