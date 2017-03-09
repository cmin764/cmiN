using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data.Entity;
using System.Data.Entity.Infrastructure;


namespace Restaurant
{
    class EntityIO<T> where T : class
    {
        private static RestaurantContext db;
        private readonly DbSet<T> dbset;

        public EntityIO()
        {
            if (db == null)
            {
                db = new RestaurantContext();
            }
            dbset = db.Set<T>();
        }

        public DbSet<T> Dbset { get { return dbset; } }

        public void Insert(T entity)
        {
            dbset.Add(entity);
            db.SaveChanges();
        }

        public void Delete(T entity)
        {
            dbset.Remove(entity);
            db.SaveChanges();
        }

        public List<T> Retrieve(IOrderedQueryable<T> query)
        {
            return query.ToList();
        }

        public int Count()
        {
            return dbset.Count();
        }

        public void Clear()
        {
            foreach (var entity in dbset)
            {
                dbset.Remove(entity);
            }
        }
    }
}