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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int nxt[maxn][27],tot;
LL cnt[maxn],all[maxn];
int STACK[maxn];
int Ins(char A[],int len,LL k){
    int i,now=0;
    REP(i,len){
        int c=A[i]-'a';
        if (!nxt[now][c]) {
            nxt[now][c]=++tot;
        }now=nxt[now][c];
        all[now]+=k;
    }return now;
}
int getid(char A[],int len){
    int i,now=0;
    REP(i,len){
        int c=A[i]-'a';
        now=nxt[now][c];
        if (!now||!all[now]) return 0;
    }return now;
}
char C[maxn];
void dfs(int x,int len){
    int i;C[len]=0;
//    if (cnt[x])
        printf("%-5lld %-5lld %s\n",cnt[x],all[x],C);
    REP(i,26) if (nxt[x][i]){
        C[len]=i+'a';
        dfs(nxt[x][i],len+1);
    }
}
int n;
char op[20];
char A[maxn];
char B[maxn];
int main() {
    int i,j,T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        REP(i,n){
            scanf("%s",op);
            if (op[0]=='i'){
                int k;
                scanf("%s%d",A,&k);
                int len=strlen(A);
                reverse(A,A+len);
                int now=Ins(A,len,k);
                cnt[now]+=k;
            }if (op[0]=='d'){
                scanf("%s",A);
                int len=strlen(A);
                reverse(A,A+len);
                int pos=getid(A,len);
                if (pos==0||!cnt[pos]) puts("Empty");
                else Ins(A,len,-cnt[pos]),cnt[pos]=0;;
            }if (op[0]=='q'){
                scanf("%s",A);
                int len=strlen(A);
                reverse(A,A+len);
                int pos=getid(A,len);
                if (pos==0) puts("0");
                else printf("%lld\n",all[pos]);
            }if (op[0]=='u'){
                scanf("%s",A);
                int lenA=strlen(A);
                reverse(A,A+lenA);
                int posA=getid(A,lenA);
                scanf("%s",B);
                int lenB=strlen(B);
                reverse(B,B+lenB);
                int posB=getid(B,lenB);
                if (posA==0||all[posA]==0) {
                    puts("Empty");
                    continue;
                }if (posB!=0&&all[posB]!=0) {
                    puts("Conflict");
                    continue;
                }int pre=Ins(A,lenA-1,-all[posA]);
                int c=A[lenA-1]-'a';
                nxt[pre][c]=0;pre=Ins(B,lenB-1,all[posA]);
                c=B[lenB-1]-'a';
                nxt[pre][c]=posA;
            }
//            dfs(0,0);
        }FOR(i,0,tot){
            cnt[i]=all[i]=0;
            REP(j,26) nxt[i][j]=0;
        }tot=0;
    }
}
/*
1
20
update y ty
insert barty 8
delete shawn
update ty tied
query tied
insert party 9
update y tied
query ty
delete barty
query tied
update d tied
update d ty
*/
