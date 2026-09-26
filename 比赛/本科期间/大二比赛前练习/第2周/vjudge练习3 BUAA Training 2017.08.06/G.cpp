#include <cstdio>
#include <algorithm>
using namespace std;
int a[51];
int main()
{
    int T,n;
    double temp,ans;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        sort(a,a+n);
        reverse(a,a+n);
        ans=0;
        temp=1;
        for(int i=0;i<n;i++)
        {
            ans+=temp*a[i];
            temp*=0.95;
        }
        printf("%lf\n",ans);
    }
    return 0;
}
