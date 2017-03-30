using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
namespace Restaurant.Data.Entities
{
    [DataContract]
    public class Order
    {

        [DataMember]
        public int OrderId { get; set; }

        [DataMember]
        public DateTime OrderDate { get; set; }

        [DataMember]
        public int CustomerId { get; set; }

        [DataMember]
        public DateTime ShipmentDate { get; set; }

        [DataMember]
        public decimal TotalPrice { get; set; }

        [DataMember]
        public List<Product> Products { get; set; }
        public Customer Customer { get; set; }
    }
}

