using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ASP.NET_Client.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult About()
        {
            ViewBag.Message = "Ati intrat aici ca sa aflati mai multe despre noi ?";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Daca doriti sa ne transmiteti un mesaj, folositi acest formular:";

            return View();
        }

        [HttpPost]
        public ActionResult Contact(string message)
        {
            ViewBag.Message = "Multumim, am primit mesajul dvs !";

            return View();
        }
    }
}