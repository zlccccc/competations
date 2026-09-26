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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
char a[50],b[50];
int num[255],d[255];
int main(){
    scanf("%s%s",a,b);
    n=strlen(a);m=strlen(b);
    if (n<m){
        sort(a,a+n,greater<char>());
        printf("%s",a);
    }else{
        REP(i,n) num[a[i]]++;
        REP(i,m){
            char c;
            rFOR(c,'0',b[i]-1) if (num[c]) break;
//            printf("pos %d:%c  ",i,c);
            if (c>='0'){
                REP(j,i) a[j]=b[j];a[i]=c;
                FOR(j,'0','9') d[j]=num[j];
                d[c]--;c='9';
                rep(j,i+1,m){
                    while (!d[c]) c--;
                    a[j]=c;d[c]--;
                }
            }if (!num[b[i]]) break;
            num[b[i]]--;
        }if (i<m) printf("%s",a);
        else printf("%s",b);
    }
}
/*
10000
10000
*/
