
public class Start {
	
	public static void main(String[] strings){
		Figura d = new Dreptunghi(2,2);
		//System.out.println(d.aria());
		
		//System.out.println(d.perimetru());
		
		d = (Dreptunghi)(d);
		System.out.println( ((Dreptunghi) d).diagonala());
		
		
	System.out.println(Math.sqrt(4+4));
	
	Figura c =new Cerc(3);
	System.out.println(c.aria());
	

	
			
	}

}
