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
#include <cassert>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
int i,j,k;
//priority_queue<int,vector<int>,greater<int> > Q;
priority_queue<int,vector<int>,greater<int> > Q;
LL MAX,ALL,CNT;
int main(){
    int q;
    scanf("%d",&q);
    while (q--){
        int op;
        scanf("%d",&op);
        if (op==1){
            int x;
            scanf("%d",&x);
            Q.push(x);
            if (x>MAX){
                if (!MAX) CNT++;
                ALL+=x;ALL-=MAX;
                MAX=x;
            }while (Q.size()){
                int y=Q.top();
                if (y==MAX) break;
                if (y*CNT<ALL){
                    ALL+=y;CNT++;
                    Q.pop();
                }else break;
            }
//            printf("F: %I64d %I64d %I64d\n",MAX,ALL,CNT);
        }else printf("%.13lf\n",MAX-1.0*ALL/CNT);
    }
}
/*
*/
