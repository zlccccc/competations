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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

bitset<4096> S[maxn];//okay的pos,S[][k]=1表示至少max{A[bit(k)]}
int n,k,q,tot;
int i,j;
int a[maxn][17];
vector<pair<int,int> > have;
int main(){
    scanf("%d%d%d",&n,&k,&q);
    tot=k;
    REP(j,k){
        REP(i,(1<<k))
            if ((i>>j)&1) S[j].set(i);
        REP(i,n) scanf("%d",&a[i][j]);
    }
    while(q--){
        int t,x,y;
        scanf("%d%d%d",&t,&x,&y);x--;y--;
        if (t==1) S[tot++]=S[x]|S[y];//max
        if (t==2) S[tot++]=S[x]&S[y];//min
        if (t==3){
            int all=0;have.clear();
            REP(i,k) have.push_back(make_pair(a[y][i],i));
            sort(have.begin(),have.end());
            reverse(have.begin(),have.end());
            REP(i,k){
                all|=1<<have[i].second;
                if (S[x][all]){
                    printf("%d\n",have[i].first);
                    break;
                }
            }
        }
    }
}
/*
5 3 8
1 2 3 4 5
5 1 2 3 4
4 5 1 2 3
1 1 2
1 2 3
2 4 5
3 6 1
3 6 2
3 6 3
3 6 4
3 6 5
*/
