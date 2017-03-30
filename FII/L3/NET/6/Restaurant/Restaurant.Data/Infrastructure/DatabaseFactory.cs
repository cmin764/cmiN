using System.Data.Entity;

namespace Restaurant.Data.Infrastructure
{
    public static class DatabaseFactory
    {
        private static DbContext dataContext;

        public static DbContext Get()
        {
            if (dataContext != null)
                return dataContext;
            dataContext = new RestaurantContext();
            return dataContext;
        }
    }
}
