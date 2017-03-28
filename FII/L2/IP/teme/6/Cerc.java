public class Cerc implements Figura{


	public float raza;
	
	public float perimetru(float raza){

		if(raza < 0){
			throw new NullPointerException();
		}

		return (float) ((float) 2 * Math.PI * raza);
	}

	@Override
	public float aria(){

		if(raza < 0){
			throw new NullPointerException();
		}

		return (float) ((float) Math.PI * Math.pow((float)raza, 2.0));
	}
	

	public float ariaSectorCerc(float raza, float unghi){

		try{
		if(raza < 0 || unghi < 0 || unghi > 360){
			throw new MyException("data");
		}
		
		return (float) ((float) (Math.PI * Math.pow((float)raza, 2.0) * unghi) / 360.0);
		
		}
		catch (MyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return unghi;
		}
	

	public float lungimeaCoardei(float raza, float unghi){

		try{
		if(raza < 0 || unghi < 0 || unghi > 360){
			throw new MyException("wrong data inserted ");
		}
		}
		catch (MyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		if(unghi > 180){
			return (float) ((float) 2 * raza * Math.sin((float)(360 - unghi) / 2.0));
		}else{
			return (float) ((float) 2 * raza * Math.sin((float)unghi / 2.0));
		}
	}

	

	public Cerc(){
		
	}
public Cerc(float raza){
	if(raza>0)
	this.raza=raza;
	else
		raza=-1;
		
	}
	
	@Override
	public float perimetru() {
		// TODO Auto-generated method stub
		return 0;
	}


	public float getRaza() {
		return raza;
	}


	public void setRaza(float raza) {
		if(raza>0){
			this.raza = raza;
		}
		raza=-1;
		
	}
}