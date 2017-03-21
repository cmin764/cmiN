import java.util.List;
import java.util.ArrayList;

public class Users {    // Builder
   private List<User> users = new ArrayList<User>();	

   public void addUser(User user){
      users.add(user);
   }
   
   public User getUser(int idx) {
       return users.get(idx);
   }

   public void showUsers(){
   
      for (User user : users) {
         System.out.println("User name: " + user.username);
         System.out.println("User password: " + user.password);
      }		
   }	
}