using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WPF_Client.Models;

namespace WPF_Client.Controllers
{
    public class OrdersController
    {
        private static OrdersController instance;

        private OrdersController()
        {
        }

        public static OrdersController Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new OrdersController();
                }
                return instance;
            }
        }

        private OrderReference.OrderServiceClient client;

        public OrderReference.OrderServiceClient Client
        {
            get
            {
                if (client == null)
                    client = new OrderReference.OrderServiceClient();
                return client;
            }
        }

        public List<OrderModel> GetAllOrders()
        {
            var orders = Client.GetAllOrders();
            int customerId = AuthenticationController.Instance.UserId;
            var orderGridItems = orders.AsQueryable().Where(p => p.CustomerId == customerId).Select(p => new OrderModel() { Data_plasare = p.OrderDate, Id = p.OrderId, Data_livrare = p.ShipmentDate, Pret_total = p.TotalPrice });

            return orderGridItems.ToList();
        }

        private List<ProductModel> orderedProducts;

        public void AddProductToCurrentOrder(ProductModel product)
        {
            if (orderedProducts == null)
                orderedProducts = new List<ProductModel>();

            foreach(var prod in orderedProducts)
                if(prod.Nume == product.Nume)
                {
                    return;
                }

            product.Cantitate = 1;
            orderedProducts.Add(product);
        }

        public int GetCurrentKcal()
        {
            int kcal = 0;
            foreach (var prod in orderedProducts)
            {
                kcal += prod.Kcal * prod.Cantitate;
            }
            return kcal;
        }
        
        public void SendCurrentOrder()
        {
            int customerId = AuthenticationController.Instance.UserId;
            
            int id = Client.CreateOrder(DateTime.Today, DateTime.Today.AddDays(3), 0, customerId);

            foreach (var item in orderedProducts)
            {
                Client.AddProductToOrder(id, item.Id, item.Cantitate);
            }

            orderedProducts.Clear();
        }

        public void DeleteOrder(OrderModel obj)
        {
            Client.CancelOrder(obj.Id);
        }
        
        public List<ProductModel> GetCurrentOrder()
        {
            return orderedProducts;
        }

        public decimal GetCurrentPrice()
        { 
            decimal price = 0;
            foreach (var prod in orderedProducts)
            {
                price += prod.Pret * prod.Cantitate;
            }
            return price;
        }
    }
}
