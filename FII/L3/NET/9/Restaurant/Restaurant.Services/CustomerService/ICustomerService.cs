using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

using Restaurant.Data.Entities;
namespace Restaurant.Services.ClientService
{
    [ServiceContract]
    public interface ICustomerService
    {
        [OperationContract]
        int CheckCustomerExists(string email, string pass);

        [OperationContract]
        Customer GetCustomerById(int id);

        [OperationContract]
        Customer CreateCustomer(string name, string phone, string address, string email, string password);
    }
}
