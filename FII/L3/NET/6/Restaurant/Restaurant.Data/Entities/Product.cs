using System;
using System.Collections.Generic;
using System.Runtime.Serialization;

namespace Restaurant.Data.Entities
{
    [DataContract]
    public class Product
    {

        [DataMember]
        public int ProductId { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public decimal Price { get; set; }

        [DataMember]
        public int Kcal { get; set; }

        [DataMember]
        public string Description { get; set; }

        [DataMember]
        public List<Order> Orders { get; set; }
    }
}