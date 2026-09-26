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
typedef unsigned long long ull;
typedef long long ll;
//const int INF=0x3f3f3f3f;
const int INF=1e9;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e9+7;
const ll maxn=1e5+7;
const int MAXN=1005;
const int MAX=2e4+5;
const int MAX_N=MAX;
const ll MOD=1e9+7;
//const double eps=0.00000001;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
void open()
{
    freopen("1007.in","r",stdin);
    freopen("out.txt","w",stdout);
}
int n,t;
ll an;
int a[MAX];
ll he[MAX];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        if (n==1){
        	printf("%d\n",a[0]);
        	continue;
		}
        if (n==2){
        	printf("%d\n",a[0]+a[1]);
        	continue;
		}
		sort(a,a+n);
		he[0]=a[0];
        for(int i=1;i<n;i++)
            he[i]=he[i-1]+a[i];
        an=INFF;
        ll sum=0;
        for(int i=n/3-1;i<n-2;i++)
            for(int j=i+(n-i)/2;j<n-1;j++)
        {
            sum=(i+1LL)*he[i]+(ll)(j-i)*(he[j]-he[i])+(n-1LL-j)*(he[n-1]-he[j]);
//            printf("%d %d %d\n",i,j,sum);
            an=min(an,sum);
        }
        printf("%lld\n",an);
    }

    return 0;
}
/*
4
4
1 8 4 2
*/
