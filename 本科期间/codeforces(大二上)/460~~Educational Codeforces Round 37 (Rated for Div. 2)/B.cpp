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
#include <bitset>
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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,k;
int i,j;
int ans[maxn];
vector<pair<int,int> > have[maxn];
queue<pair<int,int> > Q;
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        FOR(i,1,5000) have[i].clear();
        FOR(i,1,n){
            int l,r;ans[i]=0;
            scanf("%d%d",&l,&r);
            have[l].emplace_back(make_pair(i,r));
        }FOR(i,1,5000) sort(have[i].begin(),have[i].end());
        while (Q.size()) Q.pop();
        FOR(i,1,5000){
            for (auto now:have[i]) Q.push(now);
            while (Q.size()&&Q.front().second<i) Q.pop();
            if (Q.size()){
                ans[Q.front().first]=i;
                Q.pop();
            }
        }FOR(i,1,n) printf("%d ",ans[i]);puts("");
    }
}
/*
*/
