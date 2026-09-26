#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
#include <complex>
#include <assert.h>
#include <limits.h>
#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=2e6+5;
const int MOD=1e9+7;
//int MOD;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-8;
//#define double long double
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//#define double long double
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
inline int powMM(int a,int b,int M){
    int ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int t,n,m,k;
__int128 d[305][105];
__int128 dp[305][105];//第i次到特殊点j 花费的最短时间
void floyd(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
int tot,a[105];
bool sp[105];
__int128 ans,mi;
int ci,st;
int main(){
    read(t); __int128 base=1;
    for (int i=0;i<103;i++) base=base*2; 
    while(t--){
        memset(d,0x3f,sizeof(d));
        memset(sp,0,sizeof(sp));
        for(int i=1;i<=n;i++)d[i][i]=0;
        tot=0;ci=0;
        read(n);read(m);read(k);
        for(int i=1;i<=m;i++){
            int u,v,w;
            read(u);read(v);read(w);
            d[u][v]=d[v][u]=min(d[u][v],w*base);
        }
        floyd();
        for(int u,i=1;i<=k;i++){
            read(u);a[tot++]=u;sp[u]=1;
        }
        if(sp[1]==true){
            mi=2;st=1;
        }
        else mi=1,st=0;
        for(int i=0;i<=300;i++)
            for(int j=1;j<=n;j++)dp[i][j]=800001*base;
        dp[st][1]=0;


//        cout<<"tot="<<tot<<endl;
//        for(int i=0;i<tot;i++)printf("%d ",a[i]);
//        printf("\n");

        //ans=1001*base;
        ans=d[1][n];
        ci=((sp[1])?1:0)+((sp[n])?1:0);
        for(int i=0;i<tot;i++){
            dp[st+1][a[i]]=d[1][a[i]]/mi;
        }
        for(int i=st;i<=102;i++,mi*=2){
            for(int s=0;s<tot;s++){
                int j=a[s];
                __int128 dis=dp[i][j]+d[j][n]/mi;
                if(ans>dis){
                    ans=dis;
                    ci=i+(sp[n]&&j!=n);
                }
                else if(ans==dis){
//                    cout<<"i="<<i<<" ci="<<ci<<endl;
                    ci=max(ci,i+((sp[n]&&j!=n)?1:0));
                }
                for(int q=0;q<tot;q++){
                    int k=a[q];
                    if(k==j)continue;
                    dp[i+1][k]=min(dp[i+1][k],dp[i][j]+d[j][k]/mi);
                }
            }
        }
        printf("%.9Lf",(long double)ans/base);
        if(ci>=101)printf(" Burst!\n");
        else printf(" %d\n",ci);
    }
}

/*
3
2 1 2
1 2 1
1 2
5 4 2
1 2 1
2 3 1
3 4 1
4 5 1
2 3
6 7 2
1 2 2
2 4 2
4 6 2
1 3 2
3 4 2
4 5 4
5 6 4
3 4


3
2 1 1
1 2 1
1
*/
