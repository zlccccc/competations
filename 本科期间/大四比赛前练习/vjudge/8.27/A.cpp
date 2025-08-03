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
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;

#define rank rankk
#define mp make_pair
#define pb push_back
#define eb push_back
//#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
typedef pair<double,int> pdi;
typedef long double ld;
const int INF=0x3f3f3f3f;
const ll INFF=1e16;
//const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=4e3+5;
const int MOD=998244353;
//const ll MOD=(ll)998244353;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
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
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
namespace{
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;x%=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);


int t;
ll val[11]={1,5,10,20,50,100,200,500,1000,2000};///10种
ll p;
ll a[11],pr[11];
ll dfs(ll dep,ll sum){
    ll yu=p-sum;///还需选
    if(yu<0)return -1;
    if(pr[dep]<yu)return -1;
    if(dep==0)return a[dep]>=yu?yu:-1;
    ll have=pr[dep-1];
    ll ge=0;
    if(yu<have)ge=0;
    else ge=(yu-have+val[dep]-1)/val[dep];///至少选
//    ll ge=max(0LL,(yu-have+val[dep]-1)/val[dep]);///至少选
//    cout<<dep<<" "<<yu<<" "<<ge<<endl;
//    cout<<ge<<endl;
    if(ge>a[dep])return -1;
//    for(int i=0;i<4;i++){
    ge-=1; ll ret=-1;
    for(int i=0;i<4;i++){
        if(ge<0){
            ++ge;
            continue;
        }
        if(ge>a[dep]) return ret;
        ll flag=dfs(dep-1,sum+ge*val[dep]);
        if(flag!=-1) ret=max(ret,flag+ge);
        // if (ret!=-1) return ret;
        ++ge;
    }
    return ret;
//    ll flag=dfs(dep-1,sum+ge*val[dep]);
//    if(flag==-1)return -1;
//    return flag+ge;
//    return dfs(dep-1,sum-ge*)
}
int main(){
    read(t);
    while(t--){
        read(p);
        for(int i=0;i<10;i++)read(a[i]);
        pr[0]=a[0];
        for(int i=1;i<10;i++)pr[i]=pr[i-1]+val[i]*a[i];
//        for(int i=0;i<10;i++)
//            printf("%lld ",pr[i]);
//        puts("");
        printf("%lld\n",dfs(9,0));

    }
    return 0;
}
/*
300
17 8 4 2 0 0 0 0 0 0 0
100 99 0 0 0 0 0 0 0 0 0
2015 9 8 7 6 5 4 3 2 1 0
17   1 2 1 0 0 0 0 0 0 0
17   2 2 1 0 0 0 0 0 0 0
2017 2 2 1 0 0 0 0 0 0 1
2016 2 2 1 0 0 0 0 0 0 1
2017 1 2 1 0 0 0 0 0 0 1
*/