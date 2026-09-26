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
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e6+3;
const ll maxn=1e5+7;
const int MAX=2e5+7;
const ll MOD=1e6+3;
const double eps=0.00000001;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b){
    ll ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
const double PI = acos(-1.0);
double s[MAX];
int n;
double r;
void cal()
{
    s[1]=1,s[2]=PI/4.0;
    for(int i=3;i<MAX;i++)
        s[i]=s[i-2]*(i-1)/i;
}
int main()
{
    cal();

    while(~scanf("%d%lf", &n, &r))
    {
        double an=r/(n+1)/s[n];
        printf("%.10f\n",an);
    }
    return 0;
}
