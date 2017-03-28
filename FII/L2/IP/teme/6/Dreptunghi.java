import java.util.EmptyStackException;


public class Dreptunghi implements Figura{

	
	float lungime;
	float latime;
	

	public Dreptunghi(){
		
	}
	public Dreptunghi(float lungime,float latime){
		
		setLungime(lungime);
		setLatime(latime);
		
	}
	@Override
	public float aria() {
		// TODO Auto-generated method stub
		
		if(lungime>0&&latime>0){
			return latime*lungime;
		}
		else{
			try {
				throw new MyException("Aria gresita eroare la laturi");
			} catch (MyException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return -1;
		}
	}

	@Override
	public float perimetru() {
		// TODO Auto-generated method stub
		
		try{
			if(lungime <= 0 || latime <= 0 ){
				throw new MyException("Perimetru nu se poate calcula eroare la laturi");
				
				
			}
			else{
				return 2*(lungime+latime);
			}

			}
		catch (MyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 return -1;
	}

	public float getLungime() {
		return lungime;
	}

	public void setLungime(float lungime) {
		try{
			
		if(lungime>0){
			this.lungime = lungime;
			
		}else{
			throw new MyException("Erorare setare lungime");
		}
		}
		catch (MyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		}
		

	public float getLatime() {
		return latime;
	}

	public void setLatime(float latime) {
		try{
			
			if(latime>0){
				this.latime = latime;
				
			}else{
				throw new MyException("Erorare setare latime");
			}
			}
			catch (MyException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			}
		
	
	
	public float diagonala() {
		// TODO Auto-generated method stub
		
		try{
			if(lungime <= 0 || latime <= 0 ){
				throw new MyException("Diagonala nu se poate calcula eroare la laturi");
				
				
			}
			else{
				return (float) Math.sqrt(lungime*lungime+latime*latime);
			}

			}
		catch (MyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 return -1;
	}
	 
	
	
	public boolean patrat() {
		// TODO Auto-generated method stub
		
		try{
			if(lungime <= 0 || latime <= 0 ){
				throw new MyException("Nu se poate calcula eroare la laturi");
				
			}
			else{
				if(lungime==latime){
					return true;
				}
				else
				return false;
			}

			}
		catch (MyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Nu imi pot da seama");
		return false;
	}
	
	
	
}
