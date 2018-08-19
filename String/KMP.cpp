
const int maxn = " ";
int fail[maxn];
void getfail(char *x)
{
    int m=strlen(x);
    int i = 0, j = fail[0] = -1;
    while (i < m)
    {
        while (j != -1 && x[i] != x[j]) j = fail[j];
        fail[++i] = ++j;
    }
}
 //x是模式串，y是主串
// 返回y中x的个数
int kmp(char *x,char *y)
{
    int i, j, ans;
    i = j = ans = 0;
    getfail(x);
    int m=strlen(x);
    int n=strlen(y);
    while (i < n)
    {
        while (j != -1 && y[i] != x[j]) j = fail[j];
        i++, j++;
        if (j >= m) ans++, j = fail[j];
    }
    return ans;
}