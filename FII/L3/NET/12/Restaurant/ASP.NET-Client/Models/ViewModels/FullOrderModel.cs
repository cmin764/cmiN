using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ASP.NET_Client.Models.ViewModels
{
    public class FullOrderModel
    {

        public int OrderId { get; set; }
        
        public DateTime OrderDate { get; set; }
        
        public DateTime ShipmentDate { get; set; }

        public decimal TotalPrice { get; set; }
    }
}