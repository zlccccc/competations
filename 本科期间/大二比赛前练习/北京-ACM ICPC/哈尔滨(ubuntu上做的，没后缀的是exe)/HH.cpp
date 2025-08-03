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
//const int INF=0x3f3f3f3f;
const int INF= 0x7fffffff;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=0x3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+5;
const int maxn=1e5+5;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
//const ll MOD=1e15+37;
//const long double pi=acos(-1.0);
//const double eps=0.00000001;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
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
int t,n;
int a[maxn];
ll sum,dive,an,he;
priority_queue<int>pri;
ll check(ll who)
{
    ll re=0;
    he=0;
    for(int i=1;i<=n;i++)
        he+=a[i]%who;
    ll ge=he/who;
//    pri.clear();
    for(int i=1;i<=n;i++)
    {
        pri.push(-(a[i]%who));
        if(pri.size()>ge)pri.pop();
    }
    if(pri.size()!=ge)return INFF;
    else
    {
        re=he;
        while(!pri.empty())
        {
            re+=pri.top();pri.pop();
        }
//        cout<<re<<"!!"<<endl;
        return re;
    }
}

const int MAXN=100005;
int prime[MAXN+1];
void getPrime()
{
    memset(prime,0,sizeof(prime));
    for(int i=2;i<=MAXN;i++)
    {
        if(!prime[i])prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i;j++)
        {
            prime[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}

int main()
{
    scanf("%d",&t);
    getPrime();
//    printf("%d!!\n",prime[0]);
    while(t--)
    {
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        dive=1;
        an=INFF;
        while(sum>1&&sum>=prime[dive]&&dive<=prime[0])
        {
            ll who=prime[dive];
            if(sum%who==0)
                an=min(an,check(who));
            while(sum%who==0)
                sum/=who;
            dive++;
        }
        if(sum>1)
            an=min(an,check(sum));
        printf("%lld\n",an);
    }
	return 0;
}

/*
3
3
1 1 1
*/
