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
const int MAX=1e5+7;
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
double l,r;
double target_l,target_r;
double x,y;
double st;
double pos_l,pos_r;
int main()
{
    while(~scanf("%lf%lf",&l,&r))
    {
        if(r/l<1.0)
        {
            printf("-1\n");continue;
        }
        int cnt=0;
        x=y=1.0;
        target_l=r/l;
        target_r=(r+1.0)/l;
        cnt=(int)l-1;
        st=1.0;
//        printf("%lf %lf\n",target_l,target_r);
        while(!(st>=target_l-eps&&st<target_r))
        {
            pos_l=x*target_l,pos_r=x*target_r;
            cnt+=(int)(pos_l-y);
            y+=(int)(pos_l-y);
            st=y/x;
            if(st>=target_l-eps&&st<target_r)
                break;
            st=(y+1.0)/x;
            if(st>=target_l-eps&&st<target_r)
            {
                ++cnt;break;
            }
            st=y/x;
            x+=1.0;y=x*st;
        }

        printf("%d\n",cnt);
    }
}
