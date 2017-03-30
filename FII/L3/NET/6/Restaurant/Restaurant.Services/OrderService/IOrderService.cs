using System.Collections.Generic;
using System.ServiceModel;
using System;

using Restaurant.Data.Entities;

namespace Restaurant.Services.OrderService
{
    [ServiceContract]
    public interface IOrderService
    {
        [OperationContract]
        void CreateOrder(DateTime date, DateTime shipmentDate, decimal totalPrice, int customerId);

        [OperationContract]
        void AddProductToOrder(int orderId, int productId, int quantity);

        [OperationContract]
        int CountOrders();

        [OperationContract]
        void AddProductsToOrder(int orderId, List<Product> products);

        [OperationContract]
        List<Order> GetAllOrders();

        [OperationContract]
        void UpdateOrderTotalPrice(int orderId);

        [OperationContract]
        string DisplayOrder(int orderId);

        [OperationContract]
        List<Order> GetOrdersByProduct(int productId);

        [OperationContract]
        void UpdateOrder(Order order);
    }
}
