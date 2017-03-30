using System;
using System.Runtime.Serialization;

namespace Restaurant.Data.Entities
{
    [DataContract]
    public class Customer
    {
        [DataMember]
        public int CustomerId { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public string Phone { get; set; }

        [DataMember]
        public string Address { get; set; }

        [DataMember]
        public int EmployeeId { get; set; }

        [DataMember]
        public Employee Employee { get; set; }
    }
}