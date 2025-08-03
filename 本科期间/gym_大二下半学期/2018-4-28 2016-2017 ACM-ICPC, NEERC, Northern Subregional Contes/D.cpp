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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e5+7;
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

int n,m,q;
int row[3][10]={{1,0,1,1,0,1,1,1,1,1},
                {0,0,1,1,1,1,1,0,1,1},
                {1,0,1,1,0,1,1,0,1,1}};
int lef[2][10]={{1,0,0,0,1,1,1,0,1,1},
                {1,0,1,0,0,0,1,0,1,0}};
int rig[2][10]={{1,1,1,1,1,0,0,1,1,1},
                {1,1,0,1,1,1,1,1,1,1}};
void printnum(int x){
    printf("%d :\n",x);
    putchar(' ');
    if (row[0][x]) printf("*");else printf(" ");
    putchar(' ');
    puts("");
    if (lef[0][x]) printf("*");else printf(" ");
    putchar(' ');
    if (rig[0][x]) printf("*");else printf(" ");
    puts("");
    putchar(' ');
    if (row[1][x]) printf("*");else printf(" ");
    putchar(' ');
    puts("");
    if (lef[1][x]) printf("*");else printf(" ");
    putchar(' ');
    if (rig[1][x]) printf("*");else printf(" ");
    puts("");
    putchar(' ');
    if (row[2][x]) printf("*");else printf(" ");
    putchar(' ');
    puts("");
}
struct node{
    int x,y,z;node *next=nullptr;
    node(int _x=0,int _y=0,int _z=0,node *_n=nullptr){
        x=_x;y=_y;z=_z;
        next=_n;
    }
};
int A[107][107],B[107][107];
int okay[107][16][2];
node ans[107][16][2];
int main() {
    int i,j;
//    FOR(i,0,9) printnum(i);
    freopen("digital.in","r",stdin);
    freopen("digital.out","w",stdout);
    scanf("%d",&n);
    int endstatus=0;
    REP(i,4){
        FOR(j,1,n) scanf("%d",&A[j][i]);
        FOR(j,1,n+1) scanf("%d",&B[j][i]);
//        puts("okay");
        if (B[n+1][i]) endstatus|=1<<i;
    }FOR(j,1,n) scanf("%d",&A[j][4]);
//    printf("%d ",endstatus);
//    rFOR(i,1,n+1){
//        REP(j,5) printf("%d" ,A[i][j]);puts("");
//    }
    okay[n+1][endstatus][0]=1;//0:not increase
//    printf("%d %d %d\n",n+1,endstatus,0);
    rFOR(i,1,n){
        int x,y,add;
        FOR(x,0,9){
            FOR(y,0,9){
                FOR(add,0,1){
                    int z=x+y+add,mark=0;
                    if (z>=10) z-=10,mark=1;
                    //not essential
//                    if (rig[1][x]!=rig[0][y]) continue;//1_ins
//                    if (rig[1][y]!=rig[0][z]) continue;//2_ins
//                    if (lef[1][x]!=lef[0][y]) continue;//1_ins
//                    if (lef[1][y]!=lef[0][z]) continue;//2_ins

//                    if (row[1][x]!=row[0][y]) continue;//1_ins
//                    if (row[1][y]!=row[0][z]) continue;//2_ins
//                    if (row[2][x]!=row[0][z]) continue;//3_ins

                    //not essential
//                    if (rig[0][x]&&!B[i+1][0]) continue;//0_not
//                    if (rig[0][y]&&!B[i+1][1]) continue;//1_not
//                    if (rig[1][y]&&!B[i+1][2]) continue;//2_not
//                    if (rig[1][z]&&!B[i+1][3]) continue;//3_not
//                    if (lef[0][x]&&!B[i][0]) continue;//0_not
//                    if (lef[0][y]&&!B[i][1]) continue;//1_not
//                    if (lef[1][y]&&!B[i][2]) continue;//2_not
//                    if (lef[1][z]&&!B[i][3]) continue;//3_not

//                    if (row[0][x]&&!A[i][0]) continue;//0_not
//                    if (row[1][x]&&!A[i][1]) continue;//1_not
//                    if (row[2][x]&&!A[i][2]) continue;//2_not
//                    if (row[3][x]&&!A[i][3]) continue;//3_not

//                    printf("(f0)%d : %d + %d -> %d(%d)\n",i,x,y,z,add);
//                    printf("%d %d %d %d\n",rig[0][x],rig[1][x]|rig[0][y], rig[1][y]|rig[0][z],rig[1][z]);
//                    printf("%d %d %d %d\n",B[i+1][0],B[i+1][1],B[i+1][2],B[i+1][3]);
                    if ((rig[0][x]                    )&&!B[i+1][0]) continue;
                    if ((rig[1][x]|rig[0][y]          )&&!B[i+1][1]) continue;
                    if ((          rig[1][y]|rig[0][z])&&!B[i+1][2]) continue;
                    if ((                    rig[1][z])&&!B[i+1][3]) continue;

                    if ((lef[0][x]                    )&&!B[i][0]) continue;
                    if ((lef[1][x]|lef[0][y]          )&&!B[i][1]) continue;
                    if ((          lef[1][y]|lef[0][z])&&!B[i][2]) continue;
                    if ((                    lef[1][z])&&!B[i][3]) continue;


//                    printf("(f1)%d : %d + %d -> %d(%d)\n",i,x,y,z,add);
//                    printf("%d %d %d %d %d\n",row[0][x],row[1][x]|row[0][y] ,row[2][x]|row[1][y]|row[0][z],row[2][y]|row[1][z], row[2][z]);
//                    printf("%d %d %d %d %d\n",A[i][0],A[i][1],A[i][2],A[i][3],A[i][4]);

                    if ((row[0][x]                    )!=A[i][0]) continue;//0_not
                    if ((row[1][x]|row[0][y]          )!=A[i][1]) continue;//1_not
                    if ((row[2][x]|row[1][y]|row[0][z])!=A[i][2]) continue;//2_not
                    if ((          row[2][y]|row[1][z])!=A[i][3]) continue;//3_not
                    if ((                    row[2][z])!=A[i][4]) continue;//4_not

//                    printf("(f2)%d : %d + %d -> %d(%d)\n",i,x,y,z,add);

                    int status=0,allstatus=0;
                    if ((rig[0][x]                    )&&B[i+1][0]) status|=1<<0;
                    if ((rig[1][x]|rig[0][y]          )&&B[i+1][1]) status|=1<<1;
                    if ((          rig[1][y]|rig[0][z])&&B[i+1][2]) status|=1<<2;
                    if ((                    rig[1][z])&&B[i+1][3]) status|=1<<3;

//                    printf("(f2)%d : %d + %d -> %d(%d) status=%d\n",i,x,y,z,add,status);
//                    printf("%d %d %d\n",i+1,status,add);
                    if (!okay[i+1][status][add]) continue;//could
                    node *ptr=&ans[i+1][status][add];

                    status=0;allstatus=0;
                    if ((lef[0][x]                    )&&B[i][0]) status|=1<<0;
                    if ((lef[1][x]|lef[0][y]          )&&B[i][1]) status|=1<<1;
                    if ((          lef[1][y]|lef[0][z])&&B[i][2]) status|=1<<2;
                    if ((                    lef[1][z])&&B[i][3]) status|=1<<3;
                    REP(j,4) if (B[i][j]) allstatus|=1<<j;
//                    puts("check");
//                    printf("L:%d %d %d\n",status,allstatus,mark);
                    REP(j,16) if (((j|(allstatus^status))==j)&&((j|allstatus)==allstatus)) {
//                        printf("%d %d\n",j,j&allstatus);
                        okay[i][j][mark]=1;
                        ans[i][j][mark]=node(x,y,z,ptr);
                    }
//                    printf("  (f3)%d : %d + %d -> %d(%d) status2=%d\n",i,x,y,z,add,status);
                }
            }
        }
    }
    if (okay[1][0][0]){
        node *now;
        for (now=&ans[1][0][0];now->next!=nullptr;now=now->next) printf("%d",now->x);puts("");
        for (now=&ans[1][0][0];now->next!=nullptr;now=now->next) printf("%d",now->y);puts("");
        for (now=&ans[1][0][0];now->next!=nullptr;now=now->next) printf("%d",now->z);puts("");
    }else puts("NO");
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/
