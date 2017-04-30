using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using ASP.NET_Client.Models.ViewModels;

namespace ASP.NET_Client.Controllers
{
    public class OrderController : Controller
    {
        public decimal totalPrice = 0;
        public decimal totalKcal = 0;

        private static List<OrderGridItem> items = new List<OrderGridItem>();

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

        // GET: Order
        public ActionResult Index()
        {
            return View(items);
        }

        public ActionResult Delete(OrderGridItem product)
        {
            OrderGridItem toDelete = null;
            foreach (var it in items)
            {
                if (it.Name == product.Name)
                    toDelete = it;
            }
            if(toDelete != null)
              items.Remove(toDelete);

            return View("Index",items);
        }

        public ActionResult PlaceOrder()
        {
            int customerId = Int32.Parse(Session["LoggedUserId"].ToString());
            if (client == null)
                client = new OrderReference.OrderServiceClient();
            int id = client.CreateOrder(DateTime.Today, DateTime.Today.AddDays(3), 0, customerId);

            foreach(var item in items)
            {
                client.AddProductToOrder(id, item.Id, item.Quantity);
            }
            
            items.Clear();
            return View("Index", items);

        }
        public ActionResult IncreaseQuantity(OrderGridItem product)
        {
            foreach(var it in items)
            {
                if (it.Name == product.Name)
                {
                    it.Quantity++;
                    break;
                }
            }

            return View("Index",items);
        }

        public ActionResult DescreaseQuantity(OrderGridItem product)
        {
            OrderGridItem toDelete = null;
            foreach (var it in items)
            {
                if (it.Name == product.Name)
                {
                    it.Quantity--;
                    if (it.Quantity == 0)
                        toDelete = it;
                    break;
                }
            }
            if(toDelete != null)
                items.Remove(toDelete);

            return View("Index",items);
        }

        // GET: Order
        public ActionResult AddProduct(ProductGridItem product)
        {
            foreach (var it in items)
                if (it.Name == product.Name)
                {
                    it.Quantity++;
                    totalKcal += it.Kcal;
                    totalPrice += it.Price;
                    return RedirectToAction("Index", "Products");
                }
            
            items.Add(new OrderGridItem {Name = product.Name, Kcal = product.Kcal, Id = product.Id, Price = product.Price, Quantity = 1 });
            return RedirectToAction("Index", "Products", new { sortOrder = "Name" });
            
        }
    }
}