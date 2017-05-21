using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Client.Models
{
    public class OrderModel
    {

        public int Id { get; set; }

        public DateTime Data_plasare { get; set; }

        public DateTime Data_livrare { get; set; }

        public decimal Pret_total { get; set; }
    }
}
