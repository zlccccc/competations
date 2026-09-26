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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j;
pair<int,LL> a[maxn];
pair<LL,int> p[maxn];
int getMin(int l,int r){
    int ret=INF;
    if (l>=r) return ret;
    if (l+1==r) return 1+(a[r].second-a[l].second)*(a[r].second-a[l].second);
    int mid=(l+r)/2;
    ret=min(getMin(l,mid),getMin(mid+1,r));
    int cn=0,i,j;
    FOR(i,l,r)
        if ((a[i].first-a[mid].first)*(a[i].first-a[mid].first)<ret)
            p[cn++]=make_pair(a[i].second,a[i].first);
    sort(p,p+cn);
    REP(i,cn)
        for(j=i+1;j<cn&&(p[j].first-p[i].first)*(p[j].first-p[i].first)<ret;j++){
            ret=min((LL)ret,(p[j].first-p[i].first)*(p[j].first-p[i].first)+
                            (p[j].second-p[i].second)*(p[j].second-p[i].second));
        }
    return ret;
}
int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%lld",&a[i].second);
        a[i].first=i;
        a[i].second+=a[i-1].second;
    }
    printf("%d",getMin(1,n));
}
/*
*/
