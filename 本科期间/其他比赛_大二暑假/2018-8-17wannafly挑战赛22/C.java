//package oj4th_practice;

/**
 * Built using CHelper plug-in
 */

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	static class node{
		int A;
		BigInteger B;
		public node(int x,int y){
			A=x; B=new BigInteger(y+"");
		}
	}
	static char str[];
	static void merge(node A,node B) {
//        System.out.println(A.A+" "+A.B+"  "+B.A+" "+B.B);
		if (A.A<B.A) {A.A=B.A; A.B=B.B;}
		else if (A.A>B.A) return;
		else A.B=A.B.add(B.B);
	}
	static node solve(int l,int r) {
//        System.out.println("solve:"+l+"  "+r);
		if (r-l==1) return new node(1,1);
		int j;
		node now=new node(0,1),ret=new node(0,1),nxt;
		for(int i=l;i<r;i++) {
			if (str[i]=='(') {
				int cnt=1;
				for (j=i+1; cnt!=0; j++) {
					if (str[j]=='(') cnt++;
					else if (str[j]==')') cnt--;
				} nxt=solve(i+1,j-1);
			} else {
				j = i + 1;
				nxt = new node(1, 1);
			}
			now.A+=nxt.A;
			now.B=now.B.multiply(nxt.B);
//            System.out.println(str[j]);
			if (j==str.length||str[j]!='*') {
				merge(ret,now);
				now=new node(0,1);
			} i=j;
		}
		// printf("%d %d\n",ret.first,ret.second);
		return ret;
	}
	static BigInteger gcd(BigInteger A,BigInteger B){
		if (B.equals(BigInteger.ZERO)) return A;
		else return gcd(B,A.mod(B));
	}
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		String s=sc.next();
		str=s.toCharArray();
		node A=solve(0,str.length);
		s=sc.next();
		str=s.toCharArray();
		node B=solve(0,str.length);
		if (A.A>B.A) System.out.println("1/0");
		if (A.A<B.A) System.out.println("0/1");
		if (A.A==B.A) {
			BigInteger g = gcd(A.B, B.B);
			A.B=A.B.divide(g);
			B.B=B.B.divide(g);
			System.out.println(A.B + "/" + B.B);
		}
//        System.out.println(A.A+"  "+A.B);
//        System.out.println(B.A+"  "+B.B);
	}
}
/*
 */