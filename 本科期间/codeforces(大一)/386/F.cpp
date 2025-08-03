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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a; }
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

multiset<LL> S,remain;
multiset<LL>::iterator it;
LL A[maxn],t[maxn];
LL nowtime,ans;
int n,w;LL k;
void resizeSet(){
    while (remain.size()){
        it=remain.end();it--;
        if (*it>*S.begin()){
            S.insert(*it);
            nowtime-=*it;
            remain.erase(it);
        }else break;
    }while (S.size()>w){
        it=S.begin();
        remain.insert(*it);
        nowtime+=*it; S.erase(it);
    }while (remain.size()&&S.size()<w){
        it=remain.end();it--;
        S.insert(*it); nowtime-=*it;
        remain.erase(it);
    }
}
int main() {
    int i,j;
    scanf("%d%d%I64d",&n,&w,&k);
    FOR(i,1,n) scanf("%I64d",&A[i]),A[i]+=A[i-1];
    FOR(i,1,n) scanf("%I64d",&t[i]);
    j=0;t[n+1]=0;
    FOR(i,1,n){
        while (nowtime<=k&&j<=n){
            remain.insert(t[++j]/2);
            nowtime+=t[j];
            resizeSet();
        }
//        printf("%d->%d  time=%d; val=%d\n",i,j,nowtime,A[j-1]-A[i-1]);
        ans=max(ans,A[j-1]-A[i-1]);
        it=remain.lower_bound(t[i]/2);
        if (it!=remain.end()&&*it==t[i]/2)
            remain.erase(it);
        else{
            it=S.lower_bound(t[i]/2);
            nowtime+=*it; S.erase(it);
        }nowtime-=t[i];
        resizeSet();
//        printf("%d->%d  time=%d;\n",i+1,j-1,nowtime);
    }printf("%I64d\n",ans);
    return 0;
}
/*
8 8
1 3 5 7 9 11 13 15
*/
