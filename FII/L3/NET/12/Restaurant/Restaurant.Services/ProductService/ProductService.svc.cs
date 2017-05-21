using System.Linq;
using System.Collections.Generic;
using Restaurant.Data.Entities;
using Restaurant.Data.Infrastructure;
using System.ServiceModel;
using System;

namespace Restaurant.Services.ProductService
{
    [ServiceBehavior(IncludeExceptionDetailInFaults = true)]
    public class ProductService : IProductService
    {
        private readonly EntityIO<Product> productRepository;
        private readonly EntityIO<OrderProduct> orderProductRepository;

        public ProductService()
        {
            this.productRepository = new EntityIO<Product>();
            this.orderProductRepository = new EntityIO<OrderProduct>();
        }

        public List<Product> GetProductsByName(string productName)
        {
            var products = (from p in productRepository.Query()
                            where p.Name.Contains(productName)
                            select p).ToList();

            return products;
        }
        
        public List<Product> GetTopMostExpensiveProducts(int nrOfProducts)
        {
            var products = (from p in productRepository.Query()
                            orderby p.Price descending
                            select p).Take(nrOfProducts).ToList();

           return products;
        }

        public List<Product> GetTopMostExpensiveProductsUnderPrice(int nrOfProducts, decimal maxPrice)
        {
            var products = (from p in productRepository.Query()
                            where p.Price < maxPrice
                            orderby p.Price descending
                            select p).Take(nrOfProducts).ToList();

            return products;
        }

        public List<Product> GetProductsOfOrder(int orderNumber)
        {
            //Have to run the queries separate as each repository uses a different database context and thus I cannot use join linq queries
            var productIds = (from op in orderProductRepository.Query()
                                where op.OrderId == orderNumber
                                select op.ProductId).ToList();

            var products = (from p in productRepository.Query()
                            where productIds.Contains(p.ProductId)
                            select p).ToList();

            return products;
        }

        public List<Product> GetAllProducts()
        {
            var products = (from p in productRepository.Query()
                            select p).ToList();

            return products;
        }

        public void CreateProduct(string name, string description, decimal price, int kcal)
        {
            Product prod = new Product();
            prod.Name = name;
            prod.Kcal = kcal;
            prod.Description = description;
            prod.Price = price;
            
            productRepository.Insert(prod);
        }

        public void DeleteProduct(int productId)
        {
            productRepository.Delete(GetProductById(productId));
        }

        public void IncreaseProductPrice(int productId, decimal percent)
        {
            var product = GetProductById(productId);

            product.Price = product.Price + percent * product.Price / 100;
            productRepository.Update(product);
        }

        public void DescreaseProductPrice(int productId, decimal percent)
        {
            var product = GetProductById(productId);

            product.Price = product.Price - percent * product.Price / 100;
            productRepository.Update(product);
        }

        public void ModifyProductDescription(int productId, string description)
        {
            var product = GetProductById(productId);

            product.Description = description;
            productRepository.Update(product);
        }

        public Product GetProductById(int productId)
        {
            var product = (from p in productRepository.Query()
                           where p.ProductId == productId
                           select p).SingleOrDefault();

            return product;
        }

        public List<Product> GetProductsByDescription(string productDescription)
        {
            var products = (from p in productRepository.Query()
                            where p.Description.Contains(productDescription)
                            select p).ToList();

            return products;
        }
    }
}
