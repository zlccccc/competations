#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=11000;
struct SAM
{
    struct node
    {
        int ch[26];
        int par,val;
        node(int val=0):par(0),val(val)
        {
            memset(ch,0,sizeof(ch));
        }
    }sam[maxn];
    int last,m,n;
    int sz[maxn],rs[maxn],h[maxn],b[maxn];
    void append(int w)
    {
        int p=last,np,q,nq;
        sam[last=np=++m]=node(sam[p].val+1);
        rs[np]=1;
        while (p&&sam[p].ch[w]==0)
            sam[p].ch[w]=np,p=sam[p].par;
        if (p==0)
        {
            sam[np].par=1;
            return;
        }
        q=sam[p].ch[w];
        if (sam[p].val+1==sam[q].val) sam[np].par=q;
        else{
            sam[nq=++m]=sam[q];
            sam[nq].val=sam[p].val+1;
            sam[q].par=sam[np].par=nq;
            while (p&&sam[p].ch[w]==q)
                sam[p].ch[w]=nq,p=sam[p].par;
        }
    }
    ll sub[maxn];
    ll sz_sum[maxn][26],sub_sum[maxn][26];
    void clear(){
        for (int i=0;i<=m;i++){
            for (int j=0;j<26;j++)
                sz_sum[i][j]=sub_sum[i][j]=0;
            sub[i]=0; sz[i]=0;
            rs[i]=0; h[i]=0; b[i]=0;
        }
    }
    void init_sam(char *st)
    {
        sam[last=m=1]=node(0);
        n=strlen(st+1);
        for (int i=1;i<=n;i++)
            append(st[i]-'a');
        for (int i=1;i<=m;i++)
            ++h[sam[i].val],sub[i]=0;
        for (int i=1;i<=n;i++)
            h[i]+=h[i-1];
        for (int i=m;i>0;i--)
            b[h[sam[i].val]--]=i;
        for (int i=m;i>0;i--)
        {
            int u=b[i];
            rs[sam[u].par]+=rs[u];//cnt
        }
        rs[1]=0;
        for (int i=m;i>=1;i--)
        {
            int u=b[i];
            sz[u]=rs[u];
            for (int j=0;j<26;j++)
                sz[u]+=sz[sam[u].ch[j]];
            for (int j=0;j<26;j++)
                sub[u]+=sub[sam[u].ch[j]];
            sub[u]+=sz[u];
            ll sum1=0,sum2=0;
            for (int j=0;j<26;j++){
                sum1+=sub[sam[u].ch[j]];
                sum2+=sz[sam[u].ch[j]];
                sub_sum[u][j]=sum1;
                sz_sum[u][j]=sum2;
            }
        }
    }
    char a[maxn];
    char query(ll cnt){
        int p=1,l=0; cnt--;
        for (int i=0;p;i++){
            if (cnt<(ll)rs[p]*(ll)i) {
//                printf("a=%s\n",a);
                cnt%=i; return a[cnt];
            } else cnt-=(ll)rs[p]*(ll)i;
            //this
            int l=-1,r=26;
            while (l+1<r) {
                int mid=(l+r)/2;
                if (i*sz_sum[p][mid]+sub_sum[p][mid]<=cnt)
                    l=mid;
                else r=mid;
            }
            if (r) cnt-=(ll)i*sz_sum[p][r-1]+sub_sum[p][r-1];
//            printf("%d : %d l=%d %lld; remain_cnt=%lld\n",i,p,r,i*sz_sum[p][r]+sub_sum[p][r],cnt);
            p=sam[p].ch[r];
            if (!p) break;
            a[i]=r+'a'; a[i+1]=0;
        }
//        puts("no! not find");
    }
    void print(int x=1,int len=0){
//        printf("%s: sz=%d;rs=%d; sub=%lld\n",a,sz[x],rs[x],sub[x]);
        for (int i=0;i<26;i++) if (sam[x].ch[i]){
            a[len]=i+'a';
            print(sam[x].ch[i],len+1);
            a[len]=0;
        }
    }
}A;
int m;
ll a[111000];
char st[110000];
char ans[100000];
int main()
{
    int _=0;
    while (scanf("%d",&m)&&m) {
        _++;
        scanf("%s",st+1);
        A.init_sam(st);
        // A.print();
        for (int i=1;i<=m;i++){
            scanf("%lld",&a[i]);
            ans[i-1]=A.query(a[i]);
        } ans[m]=0;
        A.clear();
        printf("Case #%d: %s\n",_,ans);
    }
    return 0;
}