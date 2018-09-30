/*
复杂度线性
加完特殊字符后，最长子串的长度是半径减1，起始位置是中间位置减去半径再除以2。
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
struct Manacher
{
    char p[maxn];
    char temp[maxn<<1];
    int f[maxn<<1];
    void init(char *p,char *temp)
    {
        int n=strlen(p);
        temp[0]='*';
        for(int i=0;i<=n;i++)
        {
            temp[i*2+1]='#';
            temp[i*2+2]=p[i];
        }
        temp[2*n+2]='\0';
    }
    void getlen(char *p,int *f)
    {
        int mx=0,po=0;
        int n=strlen(p);
        f[0]=0;
        for(int i=2;i<n;i++)
        {
            if(mx>i)
                f[i]=min(mx-i,f[2*po-i]);
            else
                f[i]=1;
            while(p[i-f[i]]==p[i+f[i]])
                f[i]++;
            if(f[i]+i>mx)
            {
                po=i;
                mx=f[i]+i;
            }
        }
    }
}ans;
int main()
{
    int kase=0;
    while(scanf("%s",ans.p)==1&&ans.p[0]!='E')
    {
        ans.init(ans.p,ans.temp);
        ans.getlen(ans.temp,ans.f);
        int n=strlen(ans.temp);
        int res=1;
        for(int i=2;i<n;i++)
        {
            res=max(res,ans.f[i]-1);
        }
        printf("Case %d: %d\n",++kase,res);
    }
    return 0;
}
