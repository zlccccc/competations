#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=(1<<10)+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

LL a,b,c,t;
int main()
{
    while(~scanf("%d%d%d",&a,&b,&c))
    {
    	t=min(a,2ll)+min(b,2ll)+min(c,2ll);
    	printf("%lld\n",t*(t-1)/2+(a+b+c-t)*t);
    }
    return 0;
}
