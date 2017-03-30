using System.Linq;
using System.Data.Entity;

namespace Restaurant.Data.Infrastructure
{
    public class EntityIO<T> where T : class
    {
        private DbContext db;
        private readonly DbSet<T> dbset;

        public EntityIO()
        {
            if (db == null)
                db = DatabaseFactory.Get();

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

        public void Update(T entity)
        {
            dbset.Attach(entity);
            db.Entry(entity).State = EntityState.Modified;
        }

        public IQueryable<T> Query()
        {
            return dbset.AsQueryable();
        }
    }
}