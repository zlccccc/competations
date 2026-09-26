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

int n,m,i,j,k;
int T;int cnt1,cnt2;
vector<LL> X;
LL calc(LL l){
    LL now=0,ret=0;int i;
    REP(i,X.size()){
        LL x=X[i],nxt=min(l,max(now,x));
        ret+=x*(nxt-now);
        now=nxt;
    }return ret;
}
LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int main(){
    X.push_back(0);
    REP(i,X.size()){
        LL x=X[i];
        if (x*10+4<=10000000000) X.push_back(x*10+4);
        if (x*10+7<=10000000000) X.push_back(x*10+7);
    }
//    FOR(i,1,100) printf("%d:%lld all=%lld\n",i,calc(i,i),calc(i));
    LL l,r;
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",calc(l,r));
}
/*
*/
