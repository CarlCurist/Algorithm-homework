import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner in=new Scanner(System.in);
		System.out.println("输入数组元素个数以及元素");
		int i,j,temp;
		i=in.nextInt();
		MyArray arr=new MyArray(i);
		for(j=0;j<i;j++)
		{
			temp=in.nextInt();
			arr.setData(j, temp);
		}
		System.out.println("输入要删除的元素偏移及删除个数");
		i=in.nextInt();
		j=in.nextInt();
		arr.deleteData(i, j);
		arr.printArray();
		
	}
}

class MyArray
{
	private int sum=0;
	private int[] data=null;
	
	public MyArray(int n)
	{
		data=new int[n];
		sum=n;
	}
	public boolean setData(int offset,int value)
	{
		if(offset<0||offset>=sum)
			return false;
		data[offset]=value;
		return true;
	}
	public boolean deleteData(int offset,int total)
	{
		if(offset+total>=sum)
		{
			sum=offset;
			return true;
		}
		for(int i=offset;i+total<sum;i++)
		{
			data[i]=data[i+total];
		}
		sum-=total;
		return true;
	}
	public void printArray()
	{
		for(int i=0;i<sum;i++)
		{
			System.out.print(data[i]+" ");
		}
	}
}
