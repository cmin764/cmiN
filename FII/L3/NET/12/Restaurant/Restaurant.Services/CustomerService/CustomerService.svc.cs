using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

using Restaurant.Data.Entities;
using Restaurant.Data.Infrastructure;
namespace Restaurant.Services.ClientService
{
    public class CustomerService : ICustomerService
    {
        private readonly EntityIO<Customer> customerRepository;
        public CustomerService()
        {
            this.customerRepository = new EntityIO<Customer>();
        }

        public int CheckCustomerExists(string email, string pass)
        {
            int p = customerRepository.Count();
            int q = customerRepository.Query().Where(x => x.Email == email && x.Parola == pass).Count();
            if (q != 0)
            {
                int id = customerRepository.Query().Where(x => x.Email == email && x.Parola == pass).Select(x => x.CustomerId).FirstOrDefault();
                return id;
            }
            return -1;
        }

        public Customer CreateCustomer(string name, string phone, string address, string email, string password)
        {
            customerRepository.Insert(new Customer { Name = name, EmployeeId = 1, Parola = password, Address = address, Email = email, Phone = phone });
            return customerRepository.Query().Where(x => x.Email == email && x.Parola == password).First();
        }

        public Customer GetCustomerById(int id)
        {
            return customerRepository.Query().Where(x => x.CustomerId == id).FirstOrDefault();
        }
    }
}
