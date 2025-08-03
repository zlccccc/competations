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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,int> pii;
int n,m;
int i,j,k;
vector<pii> odd,even;
int premin[maxn],premax[maxn],sufmin[maxn],sufmax[maxn];
int ans;
LL solve(vector<pii> &A){
    sort(A.begin(),A.end());
    LL ret=0;
//    puts(":");for (auto v:A) printf("%d %d\n",v.first,v.second);puts("");
    if (!A.size()) return 0;
    premin[0]=premax[0]=A[0].second;
    rep(i,1,A.size()){
        premin[i]=min(premin[i-1],A[i].second);
        premax[i]=max(premax[i-1],A[i].second);
    }sufmin[A.size()-1]=sufmax[A.size()-1]=A[A.size()-1].second;
    rREP(i,A.size()-1){
        sufmin[i]=min(sufmin[i+1],A[i].second);
        sufmax[i]=max(sufmax[i+1],A[i].second);
    }REP(i,A.size()-1){
        ret+=max(0ll,(LL)(A[i+1].first-A[i].first)*(min(premax[i],sufmax[i+1])-max(premin[i],sufmin[i+1])));
//             printf("%d %d %d %d; ret=%lld; %d %d\n",premin[i],sufmin[i],premax[i],sufmax[i],ret,(A[i+1].first-A[i].first),(min(premax[i],sufmax[i+1])-max(premin[i],sufmin[i+1])));
    }
//    REP(i,A.size()) printf("%d %d %d %d\n",premin[i],sufmin[i],premax[i],sufmax[i]);
    return ret;
}
int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        int x,y;
        scanf("%d%d",&x,&y);
        if ((x+y)&1) odd.push_back(make_pair((x-y+1)/2,(x+y+1)/2));
        else even.push_back(make_pair((x-y)/2,(x+y)/2));
    }if (n<4) return 0*puts("0");
    printf("%I64d\n",solve(even)+solve(odd));
}
/*
*/
