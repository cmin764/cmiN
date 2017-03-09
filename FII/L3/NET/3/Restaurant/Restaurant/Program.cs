using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Restaurant
{
    class Program
    {
        static void Main(string[] args)
        {
            var customerIO = new EntityIO<Customer>();
            var employeeIO = new EntityIO<Employee>();
            var orderIO = new EntityIO<Order>();
            var productIO = new EntityIO<Product>();

            customerIO.Clear();
            employeeIO.Clear();
            orderIO.Clear();
            productIO.Clear();

            // Add new employee.

            var employee = new Employee { Name = "Ion", Salary = 300 };
            employeeIO.Insert(employee);
            Console.WriteLine(employeeIO.Count().ToString());

            // Tie new customer to the previous employee.
            //customerIO.Insert(new Customer { Name = "Ion", Phone = "123", Employee = employee });
            Console.WriteLine(customerIO.Count().ToString());
            var query = from emp in employeeIO.Dbset
                        orderby emp.Name
                        select emp;
            var employees = employeeIO.Retrieve(query);
            foreach (var e in employees)
            {
                Console.WriteLine(String.Format("{0} has salary: {1} euro",
                    e.Name, e.Salary.ToString()));
            }
        }
    }
}