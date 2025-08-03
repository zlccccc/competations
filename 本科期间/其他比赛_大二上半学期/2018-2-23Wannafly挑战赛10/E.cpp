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
const LL maxn=1e5+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,int> pii;
int n,q;
int i,j,k;
pii P[maxn];//前与后对应
vector<pii> ans;
pii add(pii A,pii B){
    return make_pair(A.first+B.first,A.second+B.second);
}
int judge(pii x){
    int l=1,r=n,cnt=0;
    while (l<=r){
        if (add(P[l],P[r])==x) l++,r--;
        else if (add(P[l],P[r])<x) l++,cnt++;
        else r--,cnt++;
        if (cnt>k) return 0;
    }return 1;
}
int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d%d",&P[i].first,&P[i].second);
    if (n<=k) return 0*puts("-1");
    sort(P+1,P+1+n);
    FOR(i,1,k+1){
        FOR(j,n-k,n){
            if (judge(add(P[i],P[j]))) ans.push_back(add(P[i],P[j]));
        }
    }sort(ans.begin(),ans.end());
//    for (pii now:ans) printf("%d %d\n",now.first,now.second);
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    printf("%d\n",ans.size());
}
/*
*/
