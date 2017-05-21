using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace WPF_Client.Models
{
    public class ProductModel
    {
        [DisplayName("Id")]
        public int Id { get; set; }

        [DisplayName("Nume")]
        public string Nume { get; set; }

        public decimal Pret { get; set; }

        public int Kcal { get; set; }

        public string Descriere { get; set; }

        public int Cantitate { get; set; }
    }
}
