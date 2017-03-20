using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;

namespace Zza.Entities
{
    [DataContract]
    public partial class OrderItem
    {
        [DataMember]
        public long Id { get; set; }
        [DataMember]
        public long OrderId { get; set; }
        [DataMember]
        public int ProductId { get; set; }
        [DataMember]
        public int Quantity { get; set; }
        [DataMember]
        public decimal UnitPrice { get; set; }
        [DataMember]
        public decimal TotalPrice { get; set; }
    }
}
