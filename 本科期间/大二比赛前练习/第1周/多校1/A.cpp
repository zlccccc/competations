#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <stack>
#define mp make_pair
//#define P make_pair
#define MIN(a,b) (a>b?b:a)
//#define MAX(a,b) (a>b?a:b)
typedef long long ll;
typedef unsigned long long ull;
const int MAX=1e5+5;
const int INF=1e8+5;
using namespace std;
//const int MOD=1e9+7;
typedef pair<ll,int> pii;
const double eps=0.00000001;
ll x;
int cnt=0;
int main()
{
//    log()
//    printf("%f\n",log(2.0));
    while(~scanf("%lld",&x))
    {
        printf("Case #%d: %lld\n",++cnt,(ll)((x*log(2.0))/log(10.0)));
    }
    return 0;
}
