using System;
using System.Collections.Generic;
using System.Runtime.Serialization;

namespace Restaurant.Data.Entities
{
    [DataContract]
    public class Employee
    {
        [DataMember]
        public int EmployeeId { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public Nullable<int> Salary { get; set; }

        [DataMember]
        public List<Customer> Customers { get; set; }
    }
}
