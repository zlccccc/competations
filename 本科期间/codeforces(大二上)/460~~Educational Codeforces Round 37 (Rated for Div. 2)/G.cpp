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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> P;
int cnt;
int get(int x,int i){
    if (!x) return 0;
    int ret=x;
    for (;i<P.size();i++)
        ret-=get(x/P[i],i+1);
    return ret;
}
int n,m,k;
int i,j;
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int x,p,k;
        scanf("%d%d%d",&x,&p,&k);
        P.clear();
        for (int i=2;i*i<=p;i++){
            if (p%i==0) P.push_back(i);
            while (p%i==0) p/=i;
        }if (p!=1) P.push_back(p);
//        for (int x:P) printf("%d ",x);puts(" <- P");
        int l=0,r=2e7;
        k+=get(x,0);
//        printf("k=%d\n",k);
        while (l+1<r){
            int mid=(l+r)/2;
            if (get(mid,0)<k) l=mid;
            else r=mid;
        }printf("%d\n",r);
    }
}
/*
*/
