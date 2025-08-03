
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
const int MAX=2e5+5;
const ll MOD=998244353;
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
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int t,n,m;
int fi[MAX],inv[MAX];
int C(int x,int y){
    return mul(fi[x],mul(inv[y],inv[x-y]));
}
int dp[10009];
int main(){

    read(t);
    fi[0]=inv[0]=1;
    for(int i=1;i<=10005;i++)fi[i]=mul(fi[i-1],i);
    inv[10005]=powMM(fi[10005],MOD-2,MOD); 
    for(int i=10004;i>=1;i--)inv[i]=mul(i+1,inv[i+1]);

    while(t--){
        read(n);read(m);
        int sum=0;
        for(int k=1;k<=n/m;k++){
        	if (k==1) {
        		addi(sum,n-m+1);
        		continue;
        	}
            int base=1;
            for (int tt=m;tt<=min(m+1,n/k);tt++) {
            	// printf("add: k=%d; %d %d ",tt,k,C(2*k+n-tt*k,2*k));
            	addi(sum,mul(C(2*k+n-tt*k,2*k),base));
            	base=MOD-base;
            }
            // puts("");
        }

        printf("%d\n",sum);
    }
}
/*
*/
