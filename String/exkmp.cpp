#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
using namespace std;
const int maxn=1e5+5;
struct exKMP
{
    char t[maxn];
    char p[maxn];
    int f[maxn];
    int extend[maxn];
    void getfail(char *p,int *f)
    {
        int m=strlen(p);
        f[0]=m;
        int i=0;
        while(i<m-1&&p[i]==p[i+1])
            i++;
        f[1]=i;
        int po=1;
        for(i=2;i<m;i++)
        {
            if(f[i-po]+i<po+f[po])
                f[i]=f[i-po];
            else
            {
                int j=po+f[po]-i;
                if(j<0)
                    j=0;
                while((i+j<m)&&p[i+j]==p[j])
                    j++;
                f[i]=j;
                po=i;
            }
        }
    }
    void getextend(char *t,char *p,int *f,int *extend)
    {
        int n=strlen(t);
        int m=strlen(p);
        getfail(p,f);
        int i=0;
        while(t[i]==p[i]&&i<n&&i<m)
            i++;
        extend[0]=i;
        int po=0;
        for(int i=1;i<n;i++)
        {
            if(f[i-po]+i<extend[po]+po)
                extend[i]=f[i-po];
            else
            {
                int j=extend[po]+po-i;
                if(j<0)
                    j=0;
                while(i+j<n&&j<m&&t[i+j]==p[j])
                    j++;
                extend[i]=j;
                po=i;
            }
        }
    }
}ans;
map<char,char> m;
int main()
{
    int T;
    scanf("%d",&T);
    char code[30];
    while(T--)
    {
        scanf("%s",code);
        scanf("%s",ans.t);
        int n=strlen(ans.t);
        for(int i=0;i<26;i++)
            m[code[i]]=i+'a';
        for(int i=0;i<n;i++)
        {
            ans.p[i]=m[ans.t[i]];
        }
        ans.p[n]='\0';
        ans.getfail(ans.p,ans.f);
        ans.getextend(ans.t,ans.p,ans.f,ans.extend);
        int i;
        for( i=0;i<n;i++)
            if(i+ans.extend[i]>=n&&i>=ans.extend[i])
            {
                break;
            }
        for(int j=0;j<i;j++)
            printf("%c",ans.t[j]);
        for(int j=0;j<i;j++)
            printf("%c",ans.p[j]);
        printf("\n");
    }
    return 0;
}
