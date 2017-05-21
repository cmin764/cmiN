using System;
using System.Globalization;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using System.Web;
using System.Web.Mvc;

using ASP.NET_Client.Models;

namespace ASP.NET_Client.Controllers
{
    [Authorize]
    public class AccountController : Controller
    {

        private CustomerReference.CustomerServiceClient client;

        public CustomerReference.CustomerServiceClient Client
        {
            get
            {
                if (client == null)
                    client = new CustomerReference.CustomerServiceClient();
                return client;
            }
        }
        
        [AllowAnonymous]
        public ActionResult Login(string returnUrl)
        {
            ViewBag.ReturnUrl = returnUrl;
            return View();
        }
        
        [HttpPost]
        [AllowAnonymous]
        [ValidateAntiForgeryToken]
        public ActionResult Login(LoginViewModel model, string returnUrl)
        {
            if (!ModelState.IsValid)
            {
                return View(model);
            }

            int id = Client.CheckCustomerExists(model.Email, model.Password);
            if (id == -1)
            {
                return View(model);
            }
            else
            {              
                var customer = Client.GetCustomerById(id);
                if (customer != null)
                {
                    Session["LoggedUserId"] = customer.CustomerId;
                    Session["LoggedUserName"] = customer.Name;
                    return RedirectToAction("Index", "Home");
                }
            }
            return View(model);
        }


        [AllowAnonymous]
        public ActionResult Register()
        {
            return View();
        }


        [HttpPost]
        [AllowAnonymous]
        [ValidateAntiForgeryToken]
        public ActionResult Register(RegisterViewModel model)
        {
            if (ModelState.IsValid)
            {
                    var customer = Client.CreateCustomer(model.Name, model.Phone, model.Address, model.Email, model.Password);
                    if (customer != null)
                    {
                        Session["LoggedUserId"] = customer.CustomerId;
                        Session["LoggedUserName"] = customer.Name;
                        return RedirectToAction("Index", "Home");
                    }
            }
            return View(model);
        }

        [AllowAnonymous]
        public ActionResult LogOff()
        {
            Session.Remove("LoggedUserId");
            Session.Remove("LoggedUserName");
            return RedirectToAction("Index", "Home");
        }
                
    }
}