#include <cstdio>
#include <cmath>
#include <algorithm>
#define eps 1e-6
using namespace std;
double x[100001],y[100001];
double xx,yy,r;
bool isline(int i,int j,int k)
{
    double t=(x[i]-x[j])*(y[i]-y[k])-(y[i]-y[j])*(x[i]-x[k]);
    if(t>-eps&&t<eps)
        return true;
    else return false;
}
double dis(int j)
{
    return sqrt((xx-x[j])*(xx-x[j])+(yy-y[j])*(yy-y[j]));
}
void center(int a,int b,int c)
{
    double a1=x[b]-x[a],b1=y[b]-y[a],c1=(a1*a1+b1*b1)/2;
    double a2=x[c]-x[a],b2=y[c]-y[a],c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    xx=x[a]+(c1*b2-c2*b1)/d;
    yy=y[a]+(a1*c2-a2*c1)/d;
    r=dis(a);
}
int main()
{
    int T,N,p1,p2,p3,cnt;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=0;i<N;i++)
            scanf("%lf%lf",&x[i],&y[i]);
        if(N==1||N==2)
        {
            printf("%lf %lf 0\n",x[0],y[0]);
            continue;
        }
        if(N==3||N==4)
        {
            printf("%lf %lf %lf\n",(x[0]+x[1])/2,(y[0]+y[1])/2,sqrt((x[0]-x[1])*(x[0]-x[1])+(y[0]-y[1])*(y[0]-y[1]))/2);
            continue;
        }
        for(int i=0;i<50;i++)
        {
            p1=rand()%N;
            p2=rand()%N;
            p3=rand()%N;
            if(isline(p1,p2,p3))
            {
                i--;
                continue;
            }
            cnt=0;
            center(p1,p2,p3);
            //printf("%d %d %d %lf %lf %lf\n",p1,p2,p3,xx,yy,r);
            for(int j=0;j<N;j++)
                if(dis(j)-r>-eps&&dis(j)-r<eps)
                    cnt++;
            if(cnt>=(N+1)/2)
            {
                printf("%lf %lf %lf\n",xx,yy,r);
                break;
            }
        }
    }
    return 0;
}
