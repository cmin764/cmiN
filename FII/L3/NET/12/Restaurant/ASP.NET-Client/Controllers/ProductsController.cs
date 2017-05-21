using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.ServiceModel;

using PagedList;
using ASP.NET_Client.Models.ViewModels;
namespace ASP.NET_Client.Controllers
{
    public class ProductsController : Controller
    {
        private ProductReference.ProductServiceClient client;

        public ProductReference.ProductServiceClient Client
        {
            get
            {
                if (client == null)
                    client = new ProductReference.ProductServiceClient();
                return client;
            }
        }

        public ViewResult Index(string sortOrder, int? page)
        {
            ViewBag.CurrentSort = sortOrder;

            ViewBag.NameSortParm = String.IsNullOrEmpty(sortOrder) ? "name_desc" : "";
            ViewBag.PriceSortParm = sortOrder == "Price" ? "price_desc" : "Price";
            ViewBag.KcalSortParm = sortOrder == "Kcal" ? "kcal_desc" : "Kcal";


            var products = Client.GetAllProducts();
            var productGridItems = products.Select(p => new ProductGridItem() { Id = p.ProductId, Description = p.Description, Name = p.Name, Kcal = p.Kcal, Price = p.Price });

            switch (sortOrder)
            {
                case "name_desc":
                    productGridItems = productGridItems.OrderByDescending(s => s.Name);
                    break;
                case "Price":
                    productGridItems = productGridItems.OrderBy(s => s.Price);
                    break;
                case "price_desc":
                    productGridItems = productGridItems.OrderByDescending(s => s.Price);
                    break;
                case "Kcal":
                    productGridItems = productGridItems.OrderBy(s => s.Kcal);
                    break;
                case "kcal_desc":
                    productGridItems = productGridItems.OrderByDescending(s => s.Kcal);
                    break;
                default:
                    productGridItems = productGridItems.OrderBy(s => s.Name);
                    break;
            }

            int pageSize = 4;
            int pageNumber = (page ?? 1);

            return View(productGridItems.ToPagedList(pageNumber, pageSize));
        }

        public ActionResult Search(string productName, int? page)
        {
            var productsByProductName = Client.GetProductsByName(productName ?? string.Empty);

            var productGridItems = productsByProductName.Select(p => new ProductGridItem() { Id = p.ProductId, Description = p.Description, Name = p.Name, Kcal = p.Kcal, Price = p.Price });

            int pageSize = 4;
            int pageNumber = (page ?? 1);

            return View("Index", productGridItems.ToPagedList(pageNumber, pageSize));
        }

        public ActionResult PriceLimit(decimal price, int? page)
        {
            var productsByPrice = Client.GetTopMostExpensiveProductsUnderPrice(100, price);

            var productGridItems = productsByPrice.Select(p => new ProductGridItem() { Id = p.ProductId, Description = p.Description, Name = p.Name, Kcal = p.Kcal, Price = p.Price });

            int pageSize = 4;
            int pageNumber = (page ?? 1);

            return View("Index", productGridItems.ToPagedList(pageNumber, pageSize));
        }


        public ActionResult AddToOrder(ProductGridItem product)
        {

            if (Session["LoggedUserId"] != null)
            {
                return RedirectToAction("AddProduct", "Order", product);
            }
            else
                return RedirectToAction("Register", "Account");
        }
    }
}
