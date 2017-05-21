using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

using ASP.NET_Client.Models.ViewModels;
namespace ASP.NET_Client.Controllers
{
    public class ManageController : Controller
    {
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

        private ProductReference.ProductServiceClient clientProduct;
        public ProductReference.ProductServiceClient ClientProduct
        {
            get
            {
                if (clientProduct == null)
                    clientProduct = new ProductReference.ProductServiceClient();
                return clientProduct;
            }
        }

        public ActionResult Index()
        {
            if (Session["LoggedUserId"] != null)
            {
                var orders = Client.GetAllOrders();
                int customerId = Int32.Parse(Session["LoggedUserId"].ToString());
                var orderGridItems = orders.AsQueryable().Where(p => p.CustomerId == customerId).Select(p => new FullOrderModel() { OrderDate = p.OrderDate, OrderId = p.OrderId, ShipmentDate = p.ShipmentDate, TotalPrice = p.TotalPrice });

                return View(orderGridItems);
            }
            else

            {
                return RedirectToAction("Index", "Home");
            }
        }

        public ActionResult Details(int id)
        {
            var products = ClientProduct.GetProductsOfOrder(id);
            var productGridItems = products.AsQueryable().Select(p => new ProductGridItem() { Description = p.Description, Kcal = p.Kcal, Name = p.Name, Price = p.Price });

            return View(productGridItems);
        }

        public ActionResult Delete(FullOrderModel model)
        {
            return View(model);
        }

        [HttpPost]
        public ActionResult Delete(int id, FormCollection collection)
        {
            try
            {
                Client.CancelOrder(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
