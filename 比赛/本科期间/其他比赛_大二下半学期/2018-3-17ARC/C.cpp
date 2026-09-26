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
#include <cstdlib>
#include <iomanip>
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

typedef pair<int,int> pii;
int T;
int n,m;
int i,j,k;
pair<pii,int> A[1000];
int mark[maxn];
int ans;
int main(){
    scanf("%d",&n);
    REP(i,n){
        int x,y;
        scanf("%d%d",&x,&y);
        A[i]=make_pair(make_pair(x,y),0);
    }REP(i,n){
        int x,y;
        scanf("%d%d",&x,&y);
        A[i+n]=make_pair(make_pair(x,y),1);
    }sort(A,A+n+n);
    REP(i,n*2){
        auto now=A[i].first;
        if (A[i].second==0){
            mark[now.second]=1;
            continue;
        }rREP(j,now.second) if (mark[j]) break;
        if (j>=0){
            ans++;mark[j]=0;
        }
    }printf("%d\n",ans);
}
/*
*/
