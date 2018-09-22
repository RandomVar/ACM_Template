/*Java大数高精度亲情讲义

java输入输出架构（注意主类为Main）
*/
import java.util.Scanner;//输入架构
public class Main {
	public static void main(String[] args) {
		Scanner s=new Scanner(System.in);
		int a,b;
		a=s.nextInt();
		b=s.nextInt();
		System.out.println((a+b));
	}
}

/*java函数调用*/
import java.util.Scanner;
public class Main {
	public static int gcd(int a,int b)
	{
		if(b==0)
			return a;
		else
			return gcd(b,a%b);
	}
	public static void main(String[] args) {
		Scanner s=new Scanner(System.in);
		int a,b,sum,i;
		while(s.hasNext())
		{
		a=s.nextInt();
		b=s.nextInt();
		sum=1;
		i=b;
		while(i!=0)
		{
			int temp=gcd(a,b);
			if(temp==1)
				break;
			else
			{
				sum*=temp;
				a/=temp;
			}
			i--;
		}
		System.out.print(sum+"\n");
		}
	}

}


