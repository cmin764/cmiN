using System.Runtime.Serialization;
using System;
using System.Collections.Generic;

namespace Restaurant.Data.Entities
{
    [DataContract]
    public class OrderProduct
    {

        [DataMember]
        public int OrderId { get; set; }

        [DataMember]
        public int ProductId { get; set; }

        [DataMember]
        public int Quantity { get; set; }

        [DataMember]
        public Order Order { get; set; }

        [DataMember]
        public Product Product { get; set; }
    }
}
