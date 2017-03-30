using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Restaurant.Data.Infrastructure;
using Restaurant.Data.Entities;

namespace Restaurant.Data
{
    class Program
    {
        static void Main(string[] args)
        {
            //Testing the OrderService
            EntityIO<Order> orderRepository = new EntityIO<Order>();
            Console.WriteLine(orderRepository.Count());
            
            Order ord = new Entities.Order();
            ord.OrderDate = DateTime.Today;
            ord.ShipmentDate = DateTime.Today.AddDays(3); 
            ord.CustomerId = 3;
            ord.TotalPrice = 0M;

            orderRepository.Insert(ord);

            var order = (from o in orderRepository.Query()
                         where o.OrderId == 5
                         select o).SingleOrDefault();
            Console.WriteLine(String.Format("Order with the id {0} has a total price of {1}, the order was made on {2} and the shipment is estimated on {3}",
                order.OrderId,
                order.TotalPrice,
                order.OrderDate,
                order.ShipmentDate));

            //Add the 3 most expensive products to the order (useful, if if there was a 'menu of the day')
            EntityIO<Product> productRepository = new EntityIO<Product>();
            var products = (from p in productRepository.Query()
                                           orderby p.Price descending
                                           select p).Take(3).ToList();


            EntityIO<OrderProduct> orderProductRepository = new EntityIO<OrderProduct>();
            foreach (var product in products)
            {
                OrderProduct orderProduct = new OrderProduct();

                orderProduct.Quantity = products.GroupBy(p => product).ToList().Count();
                orderProduct.OrderId = 5;
                orderProduct.ProductId = product.ProductId;

                orderProductRepository.Insert(orderProduct);
            }

            
            var orderedProducts = (from op in orderProductRepository.Query()
                                   where op.OrderId == 5
                                   select new { op.ProductId, op.Quantity }).ToList();

            var prroducts = (from p in productRepository.Query()
                            select new { p.ProductId, p.Price }).ToList();

            decimal price = 0;
            foreach (var product in orderedProducts)
            {
                var prod = prroducts.SingleOrDefault(x => x.ProductId == product.ProductId);

                price += prod.Price * product.Quantity;
            }

            Order ordern = (from o in orderRepository.Query()
                                       where o.OrderId == 5
                                       select o).SingleOrDefault();
            ordern.TotalPrice = price;

            orderRepository.Update(ordern);

            Console.WriteLine(String.Format("Order with the id {0} has a total price of {1}, the order was made on {2} and the shipment is estimated on {3}",
                ordern.OrderId,
                ordern.TotalPrice,
                ordern.OrderDate,
                ordern.ShipmentDate));


            Console.ReadLine();
            /*  //Creates order
              DateTime shipmentDate = DateTime.Today;
              shipmentDate.AddDays(3);

              orderClient.CreateOrder(DateTime.Today, shipmentDate, 0, 2);

              //Add the 3 most expensive products to the order (useful, if if there was a 'menu of the day')
              var products = productClient.GetTopMostExpensiveProducts(3);
              //Manual conversion from ProductService.Product to OrderService.Product
              var orderProducts = new List<OrderService.Product>();
              foreach(var prod in products)
              {
                  var pr = new OrderService.Product();

                  pr.Name = prod.Name;
                  pr.Description = prod.Description;
                  pr.ProductId = prod.ProductId;
                  pr.Kcal = prod.Kcal;
                  pr.Price = prod.Price;

                  orderProducts.Add(pr);
              }
              orderClient.AddProductsToOrder(5, orderProducts);

              Console.WriteLine("The order we have jut placed:");
              Console.WriteLine(orderClient.DisplayOrder(5));
              */
        }
    }
}