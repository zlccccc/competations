#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps=1e-10;
inline int dcmp(double x)
{
    return (x>eps)-(x<-eps);
}
struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    bool operator <(const Point& R)const
    {
        if(dcmp(x-R.x)==0)
            return dcmp(y-R.y)<0;
        return dcmp(x-R.x)<0;
    }
    bool operator ==(const Point& R)const
    {
        return dcmp(x-R.x)==0&&dcmp(y-R.y)==0;
    }
    Point operator +(const Point& R)const
    {
        return Point(x+R.x,y+R.y);
    }
    Point operator -(const Point& R)const
    {
        return Point(x-R.x,y-R.y);
    }
    Point operator *(const double& R)const
    {
        return Point(x*R,y*R);
    }
    Point operator /(const double& R)const
    {
        return Point(x/R,y/R);
    }
    double operator ^(const Point& R)const
    {
        return x*R.y-y*R.x;
    }
    double operator %(const Point& R)const
    {
        return x*R.x+y*R.y;
    }
    double len()
    {
        return sqrt(*this%*this);
    }
};
Point GetLineProjection(Point P,Point A,Point B)
{
    Point v=B-A;
    return A+v*(v%(P-A)/(v%v));
}
bool OnSegment(Point P,Point a1,Point a2)
{
    double len=(P-a1).len();
    double len2=(P-a2).len();
    if(dcmp(len)==0||dcmp(len2)==0)
        return false;
    a1=a1-P,a2=a2-P;
    return dcmp((a1^a2)/len)==0&&dcmp(a1%a2)<=0;
}
Point p[3];
Point t;
Point a,b,c;
double len;
int main()
{
    int T,lm,lg;
    bool ans;
    scanf("%d",&T);
    while(T--)
    {
        ans=false;
        scanf("%d%d",&lm,&lg);
        for(int i=0;i<3;i++)
            p[i].input();
        for(int i=0;i<3&&!ans;i++)
        {
            a=p[i];
            b=p[(i+1)%3];
            c=p[(i+2)%3];
            t=GetLineProjection(a,b,c);
            if(dcmp((t-a).len()-lm)<=0&&dcmp((t-b).len()-lg)<=0&&dcmp((t-c).len()-lg)<=0)
            {
                ans=true;
                break;
            }
            if(!OnSegment(t,b,c))
            {
                if(dcmp((t-a).len()-lg)<=0&&dcmp((t-b).len()-lm)<=0&&dcmp((t-c).len()-lm)<=0)
                {
                    //printf("%d\n",a);
                    ans=true;
                    break;
                }
            }
            if(dcmp((c-a)^(b-a))==0)
            {
                len=0;
                len=max(len,(a-b).len());
                len=max(len,(a-c).len());
                len=max(len,(b-c).len());
                if(dcmp(len-2*lg)<=0||dcmp(len-lm)<=0)
                    ans=true;
            }
        }
        if(ans)
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}