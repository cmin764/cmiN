using System.ServiceModel;
using System;
using System.Collections.Generic;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {
            //Testing the ProductService

            var productClient = new Client.ProductServiceReference.ProductServiceClient();

            Console.WriteLine("All current products:");
            var listProducts = productClient.GetAllProducts();
            foreach (var prod in listProducts)
            {
                Console.WriteLine("Product {0} ({1}), with {2} kcal, and the price {3} --- has ID: {4}", prod.Name, prod.Description, prod.Kcal, prod.Price, prod.ProductId);
            }

            Console.WriteLine();
            
            Console.WriteLine("The most expensive 3 products:");
            var expensiveProducts = productClient.GetTopMostExpensiveProducts(3);
            foreach(var prod in expensiveProducts)
            {
                Console.WriteLine(prod.Name + " " + prod.Price);
            }

            Console.WriteLine();

            /*productClient.CreateProduct(
                "Chipsuri de sfelca rosie",
                "Chipsuri de sfecla rosie la cuptor cu numeroase mirodenii",
                5.99M,
                100
                );*/
            
            Console.WriteLine("All products now:");
            listProducts = productClient.GetAllProducts();
            foreach (var prod in listProducts)
            {
                Console.WriteLine("Product {0} ({1}), with {2} kcal, and the price {3}", prod.Name, prod.Description, prod.Kcal, prod.Price);
            }

            //productClient.DeleteProduct(11); //to be uncommented after running createproduct in order to not have duplicate data

            Console.WriteLine();

            Console.WriteLine("List the order numbered 3:");
            listProducts = productClient.GetProductsOfOrder(3);
            foreach (var prod in listProducts)
            {
                Console.WriteLine("Product {0} ({1}), with {2} kcal, and the price {3}", prod.Name, prod.Description, prod.Kcal, prod.Price);
            }

            Console.WriteLine();

            Console.WriteLine("Increase price on item with productID 6 with 50 percent:");

            var product = productClient.GetProductById(6);
            Console.WriteLine("Product {0} has price before: {1} ", product.Name, product.Price);

            productClient.IncreaseProductPrice(6, 50);
            product = productClient.GetProductById(6);
            Console.WriteLine("Product {0} has price after: {1} ", product.Name, product.Price);

            Console.WriteLine();
            
            //Testing the OrderService
            var orderClient = new Client.OrderServiceReference.OrderServiceClient();

            Console.WriteLine("Currently, there are a number of {0} orders alredy placed", orderClient.CountOrders());

            //Creates order
            orderClient.CreateOrder(DateTime.Today, DateTime.Today.AddDays(3), 0M, 3);
            Console.WriteLine(orderClient.DisplayOrder(5));
            
            //Add the 3 most expensive products to the order (useful, if if there was a 'menu of the day')
            var products = productClient.GetTopMostExpensiveProducts(3);
            //Manual conversion from ProductService.Product to OrderService.Product
            var orderProducts = new List<OrderServiceReference.Product>();

            foreach (var prod in products)
            {
                var pr = new OrderServiceReference.Product();

                pr.Name = prod.Name;
                pr.Description = prod.Description;
                pr.ProductId = prod.ProductId;
                pr.Kcal = prod.Kcal;
                pr.Price = prod.Price;

                orderProducts.Add(pr);
            }
            orderClient.AddProductsToOrder(5, orderProducts);

    
            Console.WriteLine("The order we have just placed (we can see the price has been updated after adding the products):");
            Console.WriteLine(orderClient.DisplayOrder(5));
            
            Console.ReadLine();       
        }
    }
}
