public class Main {
    
    public static void main(String[] args)
    {
        CMS cms = SingleCMS.getInstance();
        NormalUser user = new NormalUser();
        AdminUser admin = new AdminUser();
        
        cms.users.addUser(user);
        cms.users.addUser(admin);
        
        SingleCMS.showMessage();
        
        Articles articles = cms.users.getUser(0).menu.articles;
        
        for(Iterator iter = articles.getIterator(); iter.hasNext();){
         Articol articol = (Articol)iter.next();
         articol.show();
      } 
    }
}