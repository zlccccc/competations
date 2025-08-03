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
#include <bitset>
#include <utility>
#include <assert.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=5e4+1000;
//const ll MAXN=2e8;
const int MAX_N=MAX;
const ll MOD=1e9+7;
//const long double pi=acos(-1.0);
//const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
inline ll powMM(ll a,ll b,ll M){
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

ll quick(ll a,ll b)
{
    ll an=1LL;
    while(b)
    {
        if(b&1)
        {
            an=an*a%MOD;
        }
        a=a*a%MOD;
        b/=2;
    }
    return an%MOD;
}
ll n,an;
ll mi[80],num[80],inv,s[80],dp[80];
ll check(ll x,ll i)
{
    ll ret=0;//i是位数
    ll j;
//	rrep(j,i+1,60)
    for(j=60;j>=i+1;j--)
        if (x&(1LL<<j)) ret+=1LL<<(j-1),x^=(1LL<<j);
	cout<<ret<<"  ";
	if (x&(1LL<<i)) ret+=(x^(1LL<<i))+1;
//    cout<<ret<<endl;
	return ret;
}
ll solve(ll x)
{
    for(ll i=0;i<=60;i++)
        s[i]=(x>>i)&1;//s记录x各位是1还是0
    memset(dp,0,sizeof(dp));
    for(ll i=0;i<=60;i++)
    {
        if(s[i]==0)
            an=(an+check(x,i)*mi[i]%MOD)%MOD;
        else
            an=(an+(x-check(x,i)*mi[i]%MOD))%MOD;
    }

}


int main()
{
    cout<<check(3,2);
    mi[0]=1;
    inv=quick(2LL,MOD-2);
    for(ll i=1;i<=63;i++)mi[i]=2LL*mi[i-1]%MOD;
    for(ll i=0;i<=63;i++)num[i]=(mi[i]-1LL)*mi[i]%MOD*inv%MOD;
//    printf("!!%lld\n",num[0]);
    while(~scanf("%lld",&n))
    {
        an=0;--n;
        ll tem=1,cnt=0;
        while(tem<=n)
        {
            tem<<=1;++cnt;
        }
        --cnt;tem>>=1;
        an=(an+num[cnt]+n)%MOD;// 0到 2^mi-1 全部考虑
        if(tem<n)
            solve(n-tem);
        printf("%lld\n",an);
    }
    return 0;
}

/*
1000000000000000000
*/

