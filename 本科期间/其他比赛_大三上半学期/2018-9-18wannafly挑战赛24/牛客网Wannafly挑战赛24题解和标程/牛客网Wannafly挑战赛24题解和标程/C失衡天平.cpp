#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int h[6666],h2[6666];
int a[105];

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }

    memset(h,-1,sizeof(h));
    h[0]=0;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        memset(h2,-1,sizeof(h2));
        for(int j=0;j<=m;j++)
        {
            if(h[a[i]+j])ans=max(ans,2*h[a[i]+j]-j);
            if(a[i]>=j&&h[a[i]-j]!=-1)ans=max(ans,2*h[a[i]-j]+j);
        }
        for(int j=0;j<=5555;j++)
        {
            if(h[j]==-1)continue;
            h2[j+a[i]]=max(h2[j+a[i]],h[j]+a[i]);
            if(a[i]<j)h2[j-a[i]]=max(h2[j-a[i]],h[j]);
            else h2[a[i]-j]=max(h2[a[i]-j],a[i]-j+h[j]);
        }
        for(int j=0;j<=5555;j++)h[j]=max(h[j],h2[j]);
    }
    printf("%d\n",ans);
    return 0;
}
