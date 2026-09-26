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
int n;
ll k;
int cnt=0;
int main()
{
    while(~scanf("%d%lld",&n,&k))
    {
        if(k<=(ll)n-1)
            printf("Case #%d: %lld\n",++cnt,k);
        else
        {
            k-=(n-1);
            --k;
            k%=(ll)(2*n-2);
            if(k==0)
                printf("Case #%d: %lld\n",++cnt,(ll)n);
            else
            {
                if(k<=(ll)(n-1))
                    printf("Case #%d: %lld\n",++cnt,k%(ll)n);
                else
                    printf("Case #%d: %lld\n",++cnt,k%(ll)(n-1));
            }
        }
    }
    return 0;
}
