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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,k;
int T;
int i,j,s;
vector<int> X;
LL fac[maxn];
int calc(int l){
    int ret;int i;
    REP(i,X.size()){
        if (X[i]<=l) ret=i;
    }return ret;
}
set<LL> S;
vector<LL> now,nxt;
int main(){
    fac[0]=1;
    FOR(i,1,20) fac[i]=i*fac[i-1];
//    FOR(i,1,20) printf("%lld ",fac[i]);puts("");
    X.push_back(0);
    REP(i,X.size()){
        LL x=X[i];
        if (x*10+4<=1000000000) X.push_back(x*10+4);
        if (x*10+7<=1000000000) X.push_back(x*10+7);
//        printf("%d ",x);
    }for (int v:X) S.insert(v);
//    for (int v:X) printf("%d ",v);puts("");
    scanf("%d%d",&n,&k);k--;
    if (n<=15&&fac[n]<k) return 0*puts("-1");
    s=max(1,n-20);LL ans=calc(s-1);
//    printf("preans=%d s=%d\n",ans,s);
    FOR(i,s,n) now.push_back(i);
    FOR(i,s,n){
        nxt.clear();
        LL t=now[k/fac[n-i]];k%=fac[n-i];
        for (int v:now) if (v!=t) nxt.push_back(v);
        nxt.swap(now);
        if (S.count(i)&&S.count(t)) ans++;
//        printf("%d :%d\n",i,t);
    }printf("%lld\n",ans);
}
/*
*/
