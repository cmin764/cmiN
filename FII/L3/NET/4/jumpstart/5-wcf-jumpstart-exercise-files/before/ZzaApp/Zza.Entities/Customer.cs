using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;

namespace Zza.Entities
{
    [DataContract]
    public class Customer
    {
        [DataMember]
        public Guid Id { get; set; }
        [DataMember]
        public string FirstName { get; set; }
        [DataMember]
        public string LastName { get; set; }
        [DataMember]
        public string Phone { get; set; }
        [DataMember]
        public string Email { get; set; }
        [DataMember]
        public string Street { get; set; }
        [DataMember]
        public string City { get; set; }
        [DataMember]
        public string State { get; set; }
        [DataMember]
        public string Zip { get; set; }
        // Need to have set block or will get obscure error during serialization
        [DataMember]
        public string FullName { get { return string.Format("{0} {1}", FirstName, LastName); } set { } }
    }
}
