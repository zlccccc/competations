#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//struct node{
//    LL a,b,c;
//    bool operator < (const node &A)const{
//        if (a!=A.a) return a<A.a;
//        if (b!=A.b) return b<A.b;
//        return c<A.c;
//    }
//};
typedef pair<pair<LL,LL>,LL> P;
map<P,int> S;
int main() {
    freopen("astronomy.in","r",stdin);
    freopen("astronomy.out","w",stdout);
    LL x[3007],y[3007],d[3007];
    int n,m;
    while(scanf("%d",&n)!=EOF&&n){
        for(int i=0;i<n;i++)
            scanf("%I64d%I64d",&x[i],&y[i]);
        S.clear();
        for(int i=0;i<n;i++)
            d[i]=x[i]*x[i]+y[i]*y[i];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j)
                    S[make_pair(make_pair(d[i],d[j]),(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))]++;
        scanf("%d",&m);
        for(int i=0;i<m;i++){
            LL a,b,c;
            scanf("%I64d%I64d%I64d",&a,&b,&c);
            int ans=S[make_pair(make_pair(a,b),c)];
            if (a==b) ans/=2;
            printf("%d\n",ans);
        }
    }
    return 0;
}
/*
*/
