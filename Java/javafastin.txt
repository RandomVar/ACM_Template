import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.*;
import java.nio.Buffer;
import java.util.*;
public class Main {

	public static void main(String[] args) {
		
		int n;
		FastScanner sc=new FastScanner();
		PrintWriter pw=new PrintWriter(System.out);
		
		n = sc.nextInt();
                int ans;
		pw.println(ans);
	
		pw.flush();
	}
	
}
class FastScanner{
		BufferedReader br;
		StringTokenizer st;
		
		public FastScanner()
		{
			try{
				br=new BufferedReader(new InputStreamReader(System.in),32768);
				st=new StringTokenizer("");
			}
			catch (Exception e) {
				// TODO: handle exception
			   e.printStackTrace();
			}
		}
	 public boolean hasNext() {
		while(!st.hasMoreTokens()){
			String line=nextLine();
			if(line==null)
				return false;
		   st=new StringTokenizer(line);
		}
		return true;
	}
	 public String next()
	 {
		 while(!st.hasMoreTokens()){
			 st=new StringTokenizer(nextLine());
		 }
		 return st.nextToken();
	 }
	 public int nextInt(){
		 return Integer.parseInt(next());
	 }
	 public long nextLong(){
		 return Long.parseLong(next());
	 }
	 public double nextDouble(){
		 return Double.parseDouble(next());
	 }
	 public String nextLine(){
		 String line="";
		 try{
			 line=br.readLine();
		 }catch (Exception e) {
			 e.printStackTrace();
			// TODO: handle exception
		}
		 return line;
	 }
	 
	}
