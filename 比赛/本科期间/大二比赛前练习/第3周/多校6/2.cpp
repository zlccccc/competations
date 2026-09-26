#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define mp make_pair
typedef unsigned long long ull;
typedef long long ll;
typedef pair<double,double> pdd;
//const int INF=0x3f3f3f3f;
const int INF=1e9;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll M=1e9+7;
//const ll maxn=1e5+7;
const int MAXN=1005;
const int MAX=2e4+5;
const int MAX_N=MAX;
const ll MOD=1e9+7;
const double eps=1e-7;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
void open()
{
    freopen("1007.in","r",stdin);
    freopen("out.txt","w",stdout);
}
map<pair<double,pdd>,double>re;//d,r  ans
int T;
double d,t,r;
int xa,xb,ya,yb;
double co,co2;
inline double dis(int xl,int yl,int xr,int yr)
{
    return sqrt((double)(xl-xr)*(xl-xr)+(double)(yl-yr)*(yl-yr));
}
inline double dis2(double xl,double yl,double xr,double yr)
{
    return sqrt((double)(xl-xr)*(xl-xr)+(double)(yl-yr)*(yl-yr));
}
inline double san(double xt,double yt,double cof,double ccf)
{
    double sr=ccf,sl=cof,len,smidl,smidr;
    double xr,yr;
    double zhi1,zhi2;
//    double an=0;
    for(int i=1;i<=100;i++)
    {
        len=sr-sl;
        smidl=sl+len/3.0;
        smidr=sr-len/3.0;
        xr=r*smidl;yr=sqrt(r*r-xr*xr);
        zhi1=dis2(xt,yt,xr,yr)+dis2(xt,-yt,xr,yr);
        xr=r*smidr;yr=sqrt(r*r-xr*xr);
        zhi2=dis2(xt,yt,xr,yr)+dis2(xt,-yt,xr,yr);
        if(zhi1<zhi2)
            sr=smidr;
        else
            sl=smidl;
    }
    len=sr-sl;
    smidl=sl+len/3.0;
    smidr=sr-len/3.0;
    xr=r*smidl;yr=sqrt(r*r-xr*xr);
    zhi1=dis2(xt,yt,xr,yr)+dis2(xt,-yt,xr,yr);
    return zhi1;
}
int main()
{
//    scanf("%d",&T);
    read(T);
    while(T--)
    {
//        scanf("%lf",&r);
        read(r);
//        scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
        read(xa);read(ya);read(xb);read(yb);
        d=dis(0,0,xa,ya);t=dis(xa,ya,xb,yb);
        co=(2.0*d*d-t*t)/(2.0*d*d);
        co2=sqrt((1.0+co)/2.0);
        if(re[mp(d,mp(r,co))])
        {
            printf("%.15f\n",re[mp(d,mp(r,co))]);
            continue;
        }
//        if(re(mp()))
        if(d>=r-eps&&d<=r+eps)
        {
            re[mp(d,mp(r,co))]=t;
            printf("%.15f\n",t);
        }
        else
        {
            double xt,yt;
            xt=d*co2;yt=sqrt(d*d-xt*xt);
            double tem1=san(xt,yt,co2,(1.0+co2)/2.0);
            double tem2=san(xt,yt,(1.0+co2)/2.0,1.0);
            re[mp(d,mp(r,co))]=min(tem1,tem2);
//            double tem2=san()
            printf("%.15f\n",re[mp(d,mp(r,co))]);
        }
    }
    return 0;
}

