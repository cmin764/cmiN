using System.Data.Entity;

using Restaurant.Data.Entities;

namespace Restaurant.Data.Infrastructure
{
    public class RestaurantContext: DbContext
    {
        public DbSet<Customer> Customers { get; set; }

        public DbSet<Product> Products { get; set; }

        public DbSet<Order> Orders { get; set; }

        public DbSet<OrderProduct> OrderProducts { get; set; }

        public DbSet<Employee> Employees { get; set; }


        public RestaurantContext() 
            : base("name=Restaurant")
        {
            Configuration.LazyLoadingEnabled = false;
            Configuration.ProxyCreationEnabled = false;
        }
        

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Product>().ToTable("Products");
            modelBuilder.Entity<Employee>().ToTable("Employees");
            modelBuilder.Entity<Order>().ToTable("Orders");
            modelBuilder.Entity<Customer>().ToTable("Customers");
            modelBuilder.Entity<OrderProduct>().ToTable("OrderProduct").HasKey(x => new { x.ProductId, x.OrderId });
        }

     }
}
