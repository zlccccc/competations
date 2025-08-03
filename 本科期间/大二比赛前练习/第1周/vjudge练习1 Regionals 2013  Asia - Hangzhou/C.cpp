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
const int MAX=40;
const int INF=1e8+5;
using namespace std;
//const int MOD=1e9+7;
typedef pair<ll,int> pii;
const double eps=0.00000001;
int n;
int a[MAX][MAX],b[MAX][MAX];
int an,cnt;
int main()
{
    while(scanf("%d",&n)&&n)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            scanf("%d",&b[i][j]);
        an=0;
        cnt=0;
        int cnt2,cnt3,cnt4;
        cnt2=cnt3=cnt4=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
        {
            if(a[i][j]==b[i][j])
                ++cnt;
            if(a[i][j]==b[j][n-i+1])
                ++cnt2;
            if(a[i][j]==b[n-i+1][n-j+1])
                ++cnt3;
            if(a[i][j]==b[n-j+1][i])
                ++cnt4;
        }
        an=max(cnt2,cnt3);
        an=max(an,cnt);
        an=max(an,cnt4);
        printf("%d\n",an);
        cnt=0;
    }
}
