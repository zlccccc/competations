#include<cstdio>
#include<cstring>
struct
{
      long l,r,c,rc,lc,s;
} t[2100000];
long n,m,i,k,f,x,y,v;
char d;
void build(long l,long r,long k)
{
     long m;
     t[k].l=l;
     t[k].r=r;
     t[k].s=1;
     if (l==r) return;
     m=(l+r)/2;
     build(l,m,k*2);
     build(m+1,r,k*2+1);
}
void treat(long &x,long &y)
{
     if (f==-1)
     {
         i=x;
         x=y;
         y=i;
         x=(n-x+1)%n+1;
         y=(n-y+1)%n+1;
     }
     x=(x-k+n-1)%n+1;
     y=(y-k+n-1)%n+1;
}
long color(long i)
{
     long k;
     for (k=1;t[k].c==-1;) if (i<=t[k*2].r) k*=2; else k=k*2+1;
     return(t[k].c);
}
void paint(long x,long y,long c,long k)
{
     long l,r;
     if (t[k].l==x && t[k].r==y)
     {
        t[k].s=1;
        t[k].c=t[k].rc=t[k].lc=c;
        return;
     }
     l=k*2;
     r=k*2+1;
     if (t[k].c!=-1)
     {
        paint(t[l].l,t[l].r,t[k].c,l);
        paint(t[r].l,t[r].r,t[k].c,r);
        t[k].c=-1;
     }
     if (y<=t[l].r) paint(x,y,c,l);
     else if (x>=t[r].l) paint(x,y,c,r);
     else
     {
         paint(x,t[l].r,c,l);
         paint(t[r].l,y,c,r);
     }
     t[k].s=t[l].s+t[r].s;
     if (t[l].rc==t[r].lc) t[k].s--;
     t[k].lc=t[l].lc;
     t[k].rc=t[r].rc;
}
long sum(long x,long y,long k)
{
     long l,r,ans;
     if (t[k].c!=-1) return(1);
     if (x==t[k].l && y==t[k].r) return(t[k].s);
     l=k*2;
     r=k*2+1;
     if (y<=t[l].r) return(sum(x,y,l));
     if (x>=t[r].l) return(sum(x,y,r));
     ans=sum(x,t[l].r,l)+sum(t[r].l,y,r);
     if (color(t[l].r)==color(t[r].l)) ans--;
     return(ans);
}
long count(long x,long y)
{
     long ans;
     if (y<x)
     {
        ans=sum(x,n,1)+sum(1,y,1);
        if (color(n)==color(1)) ans--;
        if (x+1==y && color(x)==color(y)) ans--;
     }
     else
     {
         ans=sum(x,y,1);
         if (x==1 && y==n && color(x)==color(y)) ans--;
     }
     if (ans==0) ans=1;
     return(ans);
}
void swap(long x,long y)
{
     long a,b;
     a=color(x);
     b=color(y);
     paint(x,x,b,1);
     paint(y,y,a,1);
}
int main()
{
    freopen("necklace.in","r",stdin);
    freopen("necklace.out","w",stdout);
    memset(t,0,sizeof(t));
    scanf("%ld%*ld",&n);
    build(1,n,1);
    for (i=1;i<=n;i++)
    {
        scanf("%ld",&v);
        paint(i,i,v,1);
    }
    k=0;
    f=1;
    for (scanf("%ld%*c",&m);m>0;m--)
    {
        scanf("%c",&d);
        switch (d)
        {
               case 'R':scanf("%ld%*c",&x);
                        k=(k+f*x)%n;
                        break;
               case 'F':scanf("%*c");f=-f;
                        break;
               case 'S':scanf("%ld%ld%*c",&x,&y);
                        treat(x,y);
                        swap(x,y);
                        break;
               case 'P':scanf("%ld%ld%ld%*c",&x,&y,&v);
                        treat(x,y);
                        if (x>y)
                        {
                           paint(x,n,v,1);
                           paint(1,y,v,1);
                        }
                        else paint(x,y,v,1);
                        break;
               case 'C':scanf("%c",&d);
                        if (d=='S')
                        {
                           scanf("%ld%ld%*c",&x,&y);
                           treat(x,y);
                        }
                        else
                        {
                            x=1;
                            y=n;
                        }
                        printf("%ld\n",count(x,y));
                        break;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return(0);
}
