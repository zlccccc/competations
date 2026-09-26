#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
char a[N],b[N],c[N];
int judge[27][27][27][27];
bool use[27];
string s,ss;
int i,ii,j,jj,k;
bool gg(int i,int j,int ii,int jj){
    jj++;
    if (jj>=27) ii++,jj=0;
    for (;ii<27;ii++,jj=0)
        for (;jj<27;jj++){
                if (judge[i][j][ii][jj]){
                if (!use[ii]){
                    use[ii]=1;c[judge[i][j][ii][jj]]=ii+'A';
                    if (gg(i,j,ii,jj)) return 1;
                    use[ii]=0;
                }
                if (!use[jj]){
                    use[jj]=1;c[judge[i][j][ii][jj]]=jj+'A';
                    if (gg(i,j,ii,jj)) return 1;
                    use[jj]=0;
                }
                return 0;
            }
        }
    return 1;
}
int main(){
	scanf("%d",&n);
	FOR(i,1,n){
        cin>>s>>ss;
        if (judge[s[0]-'A'][s[1]-'A'][s[2]-'A'][ss[0]-'A']){
            puts("NO");
            return 0;
        }
        a[i]=s[0];b[i]=s[1];
//        printf("%c%c",a[i],b[i]);
        judge[s[0]-'A'][s[1]-'A'][s[2]-'A'][ss[0]-'A']=i;
//        judge[s[0]-'A'][s[1]-'A'][ss[0]-'A'][s[2]-'A']=i;
	}
    REP(i,27)
        REP(j,27){
            REP(k,27) use[k]=0;
            if (!gg(i,j,0,0)&&!gg(i,j,0,0)){
                puts("NO");
                return 0;
            }
        }
    puts("YES");
    FOR(i,1,n) printf("%c%c%c\n",a[i],b[i],c[i]);
}
/*
*/
