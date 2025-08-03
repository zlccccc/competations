#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
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
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,int> pii;
int n,k;
int i,j;
int up[maxn],dn[maxn];//->,<-
bool mark[maxn];
vector<int> have[maxn];
set<int> ans;
int all;
int id[maxn];//
bool cmp(int x,int y){
    return up[x]+dn[x]>up[y]+dn[y];
}
int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n){
        ans.insert(i);id[i]=i;
        for (j=i+i;j<=n;j+=i){
            up[i]++;dn[j]++;
            have[j].push_back(i);
        }all+=up[i]+dn[i];
    }up[1]=dn[1]=0;
//    printf("all=%d\n",all);
    all/=2;mark[1]=1;
    if (k>all) return 0*puts("No");
    sort(id+1,id+1+n,cmp);
    FOR(i,1,n-1){
        int x=id[i];mark[x]=1;
        if (all-(up[x]+dn[x])<k) continue;
        all-=up[x]+dn[x];
//        printf("erase : %d\n",x);
        for (int t:have[x]){
            if (mark[t]) continue;
            up[t]--;
        }for (int t=x+x;t<=n;t+=x){
            if (mark[t]) continue;
            dn[t]--;
        }ans.erase(x);
    }
//    printf("all=%d %d\n",all,k);
    puts("Yes");
    printf("%d\n",ans.size());
    for (int v:ans) printf("%d ",v);
}
/*
300000 1
*/
