
/*大小写转换函数*/
a=tolower(a);
b=toupper(b);

/**sstream**/
string  sstream
string str; getline(cin,str);
stringstream ss(str);//对string对象进行读写
while(ss>>x)
   s.compare(b);

ss.clear();//多次使用stringstream，要先清空下
/**stringstream可以用来把string类型的字符串转换成int **/
string s("12345");
int x;
stringstream ss(s);
ss>>x;
/**法二**/
string s("12345");
int x;
stringstream ss;
ss<<s;
ss>>x;

/**将多种数值转换成字符串**/
typename x=5.222;
cin>>x;
stringstream ss;
ss<<x;
string s;
s=ss.str(); //s="5.222"

/**字符串处理*/
    char s[] = "a,b*c,d";
    const char *sep = ",*"; //可按多个字符来分割
    char *p;
    p = strtok(s, sep);// 在第一次被调用的时间str是传入需要被切割字符串的首地址；在后面调用的时间传入NULL
    while(p){
        printf("%s ", p);
        p = strtok(NULL, sep);
    }

/*取子串*/
string sub1 = s.substr(5); //从下标为5开始一直到结尾
string sub2 = s.substr(5, 3); //从下标为5开始截取长度为3位
