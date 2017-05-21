using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ASP.NET_Client.Models.ViewModels
{

    public class OrderGridItem
    {
        public int Id { get; set; }

        public string Name { get; set; }

        public decimal Price { get; set; }

        public int Kcal { get; set; }

        public string Description { get; set; }

        public int Quantity { get; set; }
    }
}