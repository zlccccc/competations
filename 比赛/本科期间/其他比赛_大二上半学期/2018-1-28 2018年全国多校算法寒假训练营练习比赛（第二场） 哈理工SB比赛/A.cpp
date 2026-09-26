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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i;
char a[maxn],b[maxn];
int main(){
    while (~scanf("%s",a)){
        int n=strlen(a);
//        bool mark=1;
//        while (mark){
//            mark=0;int LEN=0;
//            REP(i,len){
//                if (a[i]!=a[i+1]) b[LEN++]=a[i];
//                else if (a[i]=='o') b[LEN++]='O',i++,mark=1;
//                else i++,mark=1;
//            }b[LEN]='\0';
////            printf(" %s b=%s; len=%d %d\n",a,b,len,LEN);
//            REP(i,len) a[i]=b[i],b[i]=0;
//            len=LEN;
//        }printf("%s\n",a);
        char now=0;int len=0;
        REP(i,n){
            b[len++]=a[i];b[len]='\0';
            while (len>1&&b[len-1]==b[len-2]){
                len-=2;
                if (b[len]=='O') b[len]='\0';
                else b[len++]='O',b[len]='\0';
            }
        }printf("%s\n",b);
    }
}
/*
*/
