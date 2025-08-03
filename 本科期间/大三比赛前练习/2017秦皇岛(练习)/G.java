import java.math.BigInteger;
import java.util.Scanner;


public class Main {
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		int T=in.nextInt();
		for (;T!=0; T--){
//			 System.out.println("check");
			BigInteger n=in.nextBigInteger(),m=in.nextBigInteger();
			BigInteger ans=BigInteger.ZERO,mul=BigInteger.ONE;
			while (mul.compareTo(n)<0) mul=mul.multiply(new BigInteger("2"));
			while (mul.compareTo(BigInteger.ZERO)>0){
				if (n.compareTo((mul.add(BigInteger.ONE.negate())).multiply(m))>0){
					n=n.add(n.divide(mul).min(m).multiply(mul).negate());
					ans=ans.add(mul);
				} mul=mul.divide(new BigInteger("2"));
//				System.out.println("n="+n+"  ans="+ans);
			} if (n.compareTo(BigInteger.ZERO)>0) ans=ans.add(BigInteger.ONE);
			System.out.println(ans);
		}
		in.close();
	}
}
