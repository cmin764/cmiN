public class SingleCMS {

   private static CMS instance = new CMS();

   //make the constructor private so that this class cannot be
   //instantiated
   private SingleCMS(){}

   //Get the only object available
   public static CMS getInstance(){
      return instance;
   }

   public static void showMessage(){
      System.out.println("Utilizatori:");
      instance.showUsers();
   }
}
