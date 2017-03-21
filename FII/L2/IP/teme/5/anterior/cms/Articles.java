public class Articles implements Container {
   public ArrayList<Articol> articole;

   @Override
   public Iterator getIterator() {
      return new ArticolIterator();
   }

   private class ArticolIterator implements Iterator {

      int index;

      @Override
      public boolean hasNext() {
      
         if(index < articole.size()){
            return true;
         }
         return false;
      }

      @Override
      public Object next() {
      
         if(this.hasNext()){
            return articole.get(index++);
         }
         return null;
      }		
   }
}