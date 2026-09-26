#include <cstdio>
#include <iostream>
#include <algorithm>
//#include <vector>
//#include <set>
#include <map>
//#include <string>
#include <cstring>
#include <stack>
#include <queue>
//#include <cmath>
//#include <ctime>
//#include <bitset>
//#include <utility>
//#include <assert.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const double INFF=1e24;
const int MAX=2e6+5;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const ll MOD=1000000009;
//const long double pi=acos(-1.0);
const long double eps=1e-9;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<class T> inline
int read(T& num) {
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
//    while (c==' ')c=getchar();
//    cout<<c<<endl;
    if(c=='\n'){
//            printf("??");
    return 1;}
    else if(c==EOF)return 2;
    return 0;
}
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
void open()
{
//    freopen("1009.in","r",stdin);
    freopen("out.txt","w",stdout);
}
double a,b;
double D[30][30];
int d[30][30];
int n=1,m=1,tem;
vector<int>px[30][30];
vector<int>py[30][30];
int main()
{
//    freopen("in.txt","r",stdin);
    scanf("%lf%lf",&a,&b);
//    cout<<a<<" "<<b<<endl;
    while(1)
    {
        tem=read(d[m][n]);
//        cout<<n<<" "<<m<<endl;
        if(tem==1)
        {
            m=1;++n;
        }
        else if(tem==0)++m;
        else break;
    }
//    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)D[i][j]=INFF;
    for(int s=2;s<=n+m;s++)
    {
        for(int i=1;i<=m&&i<s;i++)
        {
            int j=s-i;
            if(i==1&&j==1)
            {
                D[i][j]=d[i][j];
                continue;
            }
            double lin1,lin2,lin3;
            if(i>=3&&j>=2)
            {
                if(i-2<=0||j-1<=0)lin1=0;
                else lin1=D[i-2][j-1];
                lin1+=a*(d[i-1][j]+d[i][j]);
            }
            else lin1=INFF;
            if(i>=2&&j>=2)
            {
                lin2=D[i-1][j-1]+b*d[i][j];
            }
            else lin2=INFF;
            if(j>=3&&i>=2)
            {
                if(j-2<=0||i-1<=0)lin3=0;
                else lin3=D[i-1][j-2];
                lin3+=a*(d[i][j-1]+d[i][j]);
            }
            else lin3=INFF;
            D[i][j]=min(lin1,min(lin2,lin3));
            if(lin1==D[i][j])
            {
                px[i][j].push_back(i-1);px[i][j].push_back(i-2);
                py[i][j].push_back(j);py[i][j].push_back(j-1);
            }
            else if(lin2==D[i][j])
            {
                px[i][j].push_back(i-1);py[i][j].push_back(j-1);
            }
            else{

                px[i][j].push_back(i);px[i][j].push_back(i-1);
                py[i][j].push_back(j-1);py[i][j].push_back(j-2);
            }
        }
    }
    printf("%.2f\n",D[m][n]);
            stack<int>xs,ys;
            int nowx=m,nowy=n;
            while(!(nowx==1&&nowy==1))
            {
                for(int i=0;i<px[nowx][nowy].size();i++)
                {
                    xs.push(px[nowx][nowy][i]);ys.push(py[nowx][nowy][i]);
                    if(px[nowx][nowy][i]==1&&py[nowx][nowy][i]==1)
                   {
                       nowx=nowy=1;break;
                   }
                }
                if(nowx==1&&nowy==1)break;
                else
                {
                    int num=px[nowx][nowy].size();
                    int lox=px[nowx][nowy][num-1];int loy=py[nowx][nowy][num-1];
                    nowx=lox;nowy=loy;
                }
                printf("%d %d\n",nowx,nowy);
            }

puts("OK1"); 
        while(!xs.empty())
        {
            printf("(%d,%d)\n",xs.top(),ys.top());
            xs.pop();ys.pop();
        }
        printf("(%d,%d)\n",m,n);
    return 0;
}
/*

1.0 0.0 0.0 0.0
0.3 0.3 0.3 0.1
0.1 0.1 0.6 0.2
0.1 0.2 0.2 0.5
4
2 1 1 1 3 3 4
1
1

*/

