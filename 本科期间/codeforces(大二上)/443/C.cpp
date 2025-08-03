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
const LL M=1e9+7;
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//set中的集合是一个严格递增的序列，所以可以直接来找严格小于或者大于的第一个位置
typedef pair<int,int> pii;
set<pii> L[17],R[17];
int n,k;
int i,j;
int a[17];
int lower[maxn][17],upper[maxn][17],SIZE[maxn];
vector<int> del;
int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n){
        SIZE[i]=1;
        REP(j,k) scanf("%d",&a[j]),lower[i][j]=upper[i][j]=a[j];
        set<pii>::iterator low,high;
        int l,r;//del:l->r
        l=r=a[0];
        REP(j,k){
            low=L[j].lower_bound(make_pair(a[j],0));
            high=R[j].lower_bound(make_pair(a[j],0));
            if (low!=L[j].begin()) r=max(r,lower[(--low)->second][0]);
            if (high!=R[j].end()) l=min(l,lower[high->second][0]);
        }low=L[0].lower_bound(make_pair(l,0));
        high=L[0].lower_bound(make_pair(r+1,0));
        del.clear();
        for(;low!=high;low++)
            del.push_back(low->second);
        for(int v:del){
            SIZE[i]+=SIZE[v];
            REP(j,k){
                lower[i][j]=min(lower[i][j],lower[v][j]);
                upper[i][j]=max(upper[i][j],upper[v][j]);
                L[j].erase(make_pair(lower[v][j],v));
                R[j].erase(make_pair(upper[v][j],v));
            }
        }REP(j,k){
            L[j].insert(make_pair(lower[i][j],i));
            R[j].insert(make_pair(upper[i][j],i));
        }low=L[0].end();low--;
//        REP(j,k) printf("%d ",lower[i][j]);puts("<= lower");
//        REP(j,k) printf("%d ",upper[i][j]);puts("<= higher");
//        for (int v:del) printf("%d ",v);puts(" <= del");
//        printf("end:%d\n",low->second);
        printf("%d\n",SIZE[low->second]);
    }
}
/*
3 2
1 5
5 1
10 10
*/
