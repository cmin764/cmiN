using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;

using Restaurant.Data.Entities;
using Restaurant.Data.Infrastructure;

namespace Restaurant.Services.OrderService
{
    [ServiceBehavior(IncludeExceptionDetailInFaults = true)]
    public class OrderService : IOrderService
    {
        private readonly EntityIO<Order> orderRepository;
        private readonly EntityIO<Product> productRepository;
        private readonly EntityIO<OrderProduct> orderProductRepository;

        public OrderService()
        {
            this.orderRepository = new EntityIO<Order>();
            this.productRepository = new EntityIO<Product>();
            this.orderProductRepository = new EntityIO<OrderProduct>();

        }

        public int CreateOrder(DateTime date, DateTime shipmentDate, decimal totalPrice, int customerId )
        {
            Order order = new Order();
            order.OrderDate = date;
            order.ShipmentDate = shipmentDate;
            order.TotalPrice = 0M;
            order.CustomerId = customerId;

            orderRepository.Insert(order);

            var ord = GetAllOrders().Last();
            return ord.OrderId;
        }

        public void AddProductToOrder(int orderId, int productId, int quantity)
        {
            var orderProduct = new OrderProduct();
            orderProduct.OrderId = orderId;
            orderProduct.ProductId = productId;
            orderProduct.Quantity = quantity;

            orderProductRepository.Insert(orderProduct);
            UpdateOrderTotalPrice(orderId);
        }

        public void AddProductsToOrder(int orderId, List<Product> products)
        {
            foreach (var product in products)
            {
                OrderProduct orderProduct = new OrderProduct();

                orderProduct.Quantity = products.GroupBy(p => product).ToList().Count();
                orderProduct.OrderId = orderId;
                orderProduct.ProductId = product.ProductId;

                orderProductRepository.Insert(orderProduct);
             }
            UpdateOrderTotalPrice(orderId);
        }

        public void UpdateOrderTotalPrice(int orderId)
        {
            var orderedProducts = (from op in orderProductRepository.Query()
                              where op.OrderId == orderId
                              select new {op.ProductId, op.Quantity}).ToList();
            
            var products = (from p in productRepository.Query()
                            select new { p.ProductId, p.Price }).ToList();
            
            decimal price = 0;
            foreach (var product in orderedProducts)
            {
                var prod = products.SingleOrDefault(x => x.ProductId == product.ProductId);

                price += prod.Price * product.Quantity;
            }

            Order order = GetOrderById(orderId);
            order.TotalPrice = price;

            orderRepository.Update(order);
        }

        private Order GetOrderById(int orderId)
        {
            var order = (from o in orderRepository.Query()
                         where o.OrderId == orderId
                         select o).SingleOrDefault();

            return order;
        }

        public string DisplayOrder(int orderId)
        {
            var order = (from o in orderRepository.Query()
                         where o.OrderId == orderId
                         select o).SingleOrDefault();

            return String.Format("Order with the id {0} has a total price of {1}, the order was made on {2} and the shipment is estimated on {3}",
                order.OrderId,
                order.TotalPrice,
                order.OrderDate,
                order.ShipmentDate);

        }

        public List<Order> GetOrdersByProduct(int productId)
        {
            var orderIds = (from op in orderProductRepository.Query()
                            where op.ProductId == productId
                            select op.OrderId).ToList();

            var orders = (from o in orderRepository.Query()
                          where orderIds.Contains(o.OrderId)
                          select o).ToList();

            return orders;
        }

        public List<Order> GetAllOrders()
        {
            var orders = (from o in orderRepository.Query()
                          select o).ToList();

            return orders;
        }

        public void UpdateOrder(Order order)
        {
            orderRepository.Update(order);
        }

        public int CountOrders()
        {
            return orderRepository.Count();
        }

        public void CancelOrder(int orderId)
        {
            var order = GetOrderById(orderId);
            orderRepository.Delete(order);
        }
    }
}
