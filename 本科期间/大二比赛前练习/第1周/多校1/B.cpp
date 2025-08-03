#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+17;
const LL M=1e9+7;
const double eps=0.0000001;
const LL gcd(LL a,LL b){return b?gcd(b,a%b):a;};
using namespace std;

int n;
int i,j;
vector<int> num[27];
bool mark[27];
int val[27];
char a[maxn];
LL MULMOD[maxn];
LL ans;
int main(){
    MULMOD[0]=1;
    FOR(i,1,100007) MULMOD[i]=MULMOD[i-1]*26%M;
    int x=0;
    REP(i,26) num[i].resize(maxn,0);
    while (~scanf("%d",&n)){
        REP(i,26)
            FOR(j,0,100008) num[i][j]=0;
        memset(val,0xff,sizeof(val));
        memset(mark,0,sizeof(mark));
        REP(i,n){
            scanf("%s",a);
            int len=strlen(a);
            mark[a[0]-'a']=1;
            REP(j,len){
                num[a[j]-'a'][100007-len+j+1]++;
//                printf("%d %d\n",a[j]-'a',100007-len+j+1);
            }
        }
        REP(i,26){
            num[i][100010]=i;
            rFOR(j,1,100007) if (num[i][j]>25){
                num[i][j-1]+=num[i][j]/26;
                num[i][j]%=26;
            }
        }
        sort(num,num+26);
//        REP(i,26){
//            printf("%c : ",num[i][100010]+'a');
//            FOR(j,100000,100008) printf("%2d",num[i][j]);puts("");
//        }
//        REP(i,26) printf("%d ",num[i][100010]);puts("");
        i=0;
        while (mark[num[i][100010]]==1) i++;
        val[num[i][100010]]=0;
        j=25;
        rFOR(i,0,25) if (val[num[i][100010]]==-1) val[num[i][100010]]=j--;
//        FOR(i,0,25) printf("%c:%d ",i+'a',val[i]);
        ans=0;
        REP(i,26){
            rFOR(j,1,100007) ans=(ans+MULMOD[100007-j]*num[i][j]%M*val[num[i][100010]])%M;
        }
//        puts("");
        printf("Case #%d: %d\n",++x,ans);
    }
}
/*
*/
