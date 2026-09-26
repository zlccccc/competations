#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int MAXN=200005;
 
struct Point
{
    ll x,y;
    Point() {}
    Point(ll _x,ll _y):x(_x),y(_y) {}
    Point operator - (const Point &t)const
    {
        return Point(x-t.x,y-t.y);
    }
    ll operator * (const Point &t)const
    {
        return x*t.y-y*t.x;
    }
    bool operator < (const Point &t)const
    {
        return x==t.x ? y<t.y : x<t.x;
    }
    bool operator == (const Point &t)const
    {
        return x==t.x && y==t.y;
    }
} p[MAXN],q[MAXN];
 
namespace Geometry
{
int n,m;
Point c[MAXN],ori(0,0);
inline bool cmp(const Point &a,const Point &b)
{
    return a.x==b.x?a.y<b.y:a.x<b.x;
}
inline ll cross(const Point &a,const Point &b)
{
    return 1LL*a.x*b.y-1LL*a.y*b.x;
}
int convexhull(Point *p,int n,Point *q)
{
    int i,k,m;
    for(i=m=0; i<n; q[m++]=p[i++])while(m>1&&cross(q[m-1]-q[m-2],p[i]-q[m-2])<=0)m--;
    k=m;
    for(i=n-2; i>=0; q[m++]=p[i--])while(m>k&&cross(q[m-1]-q[m-2],p[i]-q[m-2])<=0)m--;
    return --m;
}
inline int askl(int l,int r,const Point &p)
{
    int t=l++,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(cross(c[mid]-p,c[(mid-1+n)%n]-c[mid])<=0)l=(t=mid)+1;
        else r=mid-1;
    }
    return t;
}
inline int askr(int l,int r,const Point &p)
{
    int t=r--,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(cross(c[mid]-p,c[(mid+1)%n]-c[mid])>=0)r=(t=mid)-1;
        else l=mid+1;
    }
    return t;
}
Point init(int ca, Point p[])
{
    sort(p,p+ca,cmp);
    n=convexhull(p,ca,c);
    Point o=c[0];
    for(int i=0; i<n; i++)
        c[i]=c[i]-o;
    c[n]=c[0];
    for(int i=(m=0); i<n; i++)
        if(c[i].x>=c[m].x)m=i;
    return o;
}
 
inline int sgn(ll x)
{
    return (x>0)-(x<0);
}
 
int inside(const Point& p)
{
    int s=sgn(p*c[1]);
    if(s>=0) {
        if(!s&&(c[1]<p||p<ori))
            return 1;
        return s;
    }
    s=sgn(p*c[n-1]);
    if(s<=0) {
        if(!s&&(c[n-1]<p||p<ori))
            return 1;
        return -s;
    }
    int l=1,r=n-2;
    while(l<r)
    {
        int m=(l+r+1)/2;
        if(p*c[m]<=0)l=m;
        else r=m-1;
    }
    return sgn((p-c[l])*(c[l+1]-c[l]));
}
}
 
int main()
{
    int n, m;
    scanf("%d", &n);
 
    for(int i=0; i<n; i++)
    {
        scanf("%lld%lld", &p[i].x, &p[i].y);
    }
 
    Point o=Geometry::init(n,p);
 
    scanf("%d", &m);
 
    for(int i=0; i<m; i++)
    {
        scanf("%lld%lld", &q[i].x, &q[i].y);
        q[i]=q[i]-o;
        int s=Geometry::inside(q[i]);
        puts(s>0?"OUT":(!s?"ON":"IN"));
    }
 
    return 0;
}