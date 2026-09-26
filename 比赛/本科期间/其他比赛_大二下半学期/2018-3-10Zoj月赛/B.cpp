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
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1000000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

void solve1(){
    int n,m;
    scanf("%d",&n);m=0;
    while ((m+1)*(m+1)<=n) m++;
    printf("%d\n",m&1);
}
char a[maxn];
char b[maxn];

int l,ans;
int work(int o,char *O,int I){//³­µÄ°å×Ó
    char c, *D=O ;
    if(o>0){
        for(l=0;D[l];D[l++]-=10){
            D[l++]-=120;
            D[l]-=110;
            while(!work(0,O,l)) D[l]+=20;
//            putchar((D[l]+1032)/20);
            ans=(D[l]+1032)/20-'0';
        }//putchar(10);
    }else{
        c=o+(D[I]+82)%10-(I>l/2)*(D[I-l+I]+72)/10-9;
        D[I]+=I<0 ? 0 : !(o=work(c/10,O,I-1))*((c+999)%10-(D[I]+92)%10);
    }return o;
}
char s[maxn];
void solve2(){
    int n,m,q,i,j,k;s[0]='0';
    scanf("%s",s+1);
//    if(strlen(s)==1) {solve1(s[0]-'0');return;}
    if(strlen(s)%2 == 1)
        work(2,s+1,0);
    else
        work(2,s,0);
    printf("%d\n",ans%2);
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        solve2();
    }
}
/*
*/
