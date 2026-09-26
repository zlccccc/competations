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
int g,b,s;
int dp[1<<21];
int num[30][10];
int tem_num[10];
int now_num[10];
int cnt;
int main()
{
    while(scanf("%d%d%d",&g,&b,&s))
    {
//        scanf("");
        memset(num,0,sizeof(num));
        memset(dp,0,sizeof(dp));
        if(g==0&&b==0&&s==0)
            break;
        int n;
        for(int i=0;i<b;i++)
        {
            scanf("%d",&n);
            for(int j=1;j<=n;j++)
            {
                int tem;
                scanf("%d",&tem);
                ++num[i][tem];
            }
        }
        int zong=1<<b;
        for(int i=1;i<zong;i++)
        {
            dp[i]=-INF;
            memset(tem_num,0,sizeof(tem_num));
            for(int j=0;j<b;j++)
            {
//                if(i&(1<<j))
//                {
//                    for(int q=1;q<=g;q++)
//                    {
//                        tem_num[q]+=num[j][q];
//                    }
//                }
                if(!(i&(1<<j)))
                    for(int q=1;q<=g;q++)
                        tem_num[q]+=num[j][q];
            }
            for(int q=1;q<=g;q++)
                tem_num[q]%=s;
            for(int j=0;j<b;j++)
            {
                if(i&(1<<j))
                {
                    cnt=0;
                    for(int q=1;q<=g;q++)
                    {
//                        now_num[q]=(tem_num[q]-num[j][q])%s;
//                        now_num[q]+=num[j][q];
//                        while(now_num[q]>=s)
//                        {
//                            ++cnt;
//                            now_num[q]-=s;
//                        }
                        now_num[q]=tem_num[q]+num[j][q];
                        cnt+=now_num[q]/s;
                    }
//                    printf("%d ",cnt);
                    if(cnt)
                        dp[i]=max(dp[i],dp[i^(1<<j)]+cnt);
                    else
                        dp[i]=max(dp[i],-dp[i^(1<<j)]+cnt);
                }
            }
        }
//        for(int i=0;i<zong;i++)
//            printf("%d ",dp[i]);
        printf("%d\n",dp[zong-1]);
    }
}
