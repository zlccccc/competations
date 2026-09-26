#include<bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
using namespace std;
const int maxn=3000+7;
const int mod=1e9+9;

void max_(int &A,int B){(A<B)&&(A=B);}
void add_(int &A,int B){A+=B; (A>=mod)&&(A-=mod);}
int len[maxn][maxn];
int mor[maxn][maxn];
char str[maxn];
int main() {
    int cas=0;
    while (scanf("%s",str+1)) {
        if (str[1]=='-') break;
        cas++; int n=strlen(str+1),i,j;
        FOR(i,0,n+1) FOR(j,0,n+1) mor[i][j]=len[i][j]=0;
        FOR(i,1,n) FOR(j,i+1,n){
            while (str[i+len[i][j]]==str[j+len[i][j]]) len[i][j]++;
            max_(len[i+1][j+1],len[i][j]-1);
        } mor[1][1]=1; int ans=0;
        FOR(i,1,n) {//presum
            int all=0;
            FOR(j,1,n+1-i){//i+j:next
                add_(all,mor[i][j]);//end
                int k=len[i][i+j];
                if (k>=j) {
                    add_(mor[i+j][j+1],all);
                } else {
                    if (str[i+k]<str[i+j+k]) add_(mor[i+j][k+1],all);
                }
//                printf("%d - %d: %d; add=%d;  %d %d; str=%c %c\n",i,j,k,all,i+j,k+1,str[i+k],str[i+j+k]);
            } add_(ans,all);
        } printf("Case #%d: There are %d ways.\n",cas,ans);
    }
    return 0;
}