using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Client
{
    public class AuthenticationController
    {
        private static AuthenticationController instance;

        private AuthenticationController()
        {

        }

        public static AuthenticationController Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new AuthenticationController();
                }
                return instance;
            }
        }

        private CustomerReference.CustomerServiceClient client;

        public CustomerReference.CustomerServiceClient Client
        {
            get
            {
                if (client == null)
                    client = new CustomerReference.CustomerServiceClient();
                return client;
            }
        }

        public int UserId { get; set; }
        public string Username { get; set; }
        public string Phone { get; set; }
        public string Name { get; set; }
        public string Address { get; set; }

        public bool LoggedIn { get; set; }

        public bool LogIn(string email, string pass)
        {
            int id = Client.CheckCustomerExists(email, pass);
            if (id != -1)
            {
                var customer = Client.GetCustomerById(id);
                if (customer != null)
                {
                    LoggedIn = true;
                    LogUserData(customer);
                    return true;
                }
            }
            return false;
        }

        private void LogUserData(CustomerReference.Customer customer)
        {
            UserId = customer.CustomerId;
            Username = customer.Name;
            Phone = customer.Phone;
            Name = customer.Name;
            Address = customer.Address;
        }


        public bool Register(string name, string phone, string address, string email, string pass)
        { 
            var customer = Client.CreateCustomer(name, phone, address, email, pass);
            if (customer != null)
            {
                LoggedIn = true;
                LogUserData(customer);

                return true;
             }
            return false;
        }

    }
}
