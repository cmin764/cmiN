public class UserFactory {
	
   public User getUser(String userType) {
      if(userType == null){
         return null;
      }		
      if(userType.equalsIgnoreCase("ADMIN")){
         return new AdminUser();
         
      } else if(userType.equalsIgnoreCase("NORMAL")){
         return new NormalUser();
         
      return null;
   }
}