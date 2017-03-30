using System;
using System.ServiceModel;
using System.ServiceModel.Description;

using Restaurant.Services.ProductService;
using Restaurant.Services.OrderService;

namespace Restaurant.SelfHost
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceHost productServiceHost = null;
            try
            {
                Uri httpProductServiceAddress = new Uri("http://localhost:4321/ProductService");

                productServiceHost = new ServiceHost(typeof(ProductService), httpProductServiceAddress);
                productServiceHost.AddServiceEndpoint(typeof(IProductService), new WSHttpBinding(), httpProductServiceAddress);

                ServiceMetadataBehavior serviceBehavior = new ServiceMetadataBehavior();
                serviceBehavior.HttpGetEnabled = true;
                productServiceHost.Description.Behaviors.Add(serviceBehavior);

                //For debugging purposes
                //ServiceDebugBehavior debug = productServiceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
                //if (debug == null)
                //{
                //    productServiceHost.Description.Behaviors.Add(new ServiceDebugBehavior() { IncludeExceptionDetailInFaults = true });
                //}
                //else
                //{
                //    if (!debug.IncludeExceptionDetailInFaults)
                //    {
                //        debug.IncludeExceptionDetailInFaults = true;
                //    }
                //}

                productServiceHost.Open();
                Console.WriteLine("Service ProductService is live now at {0}", httpProductServiceAddress.ToString());

            }
            catch (Exception ex)
            {
                productServiceHost = null;
                Console.WriteLine("There is an issue with ProductService" + ex.Message);
            }


            ServiceHost orderServiceHost = null;
            try
            {
                Uri httpOrderServiceAddress = new Uri("http://localhost:4321/OrderService");

                orderServiceHost = new ServiceHost(typeof(OrderService), httpOrderServiceAddress);
                orderServiceHost.AddServiceEndpoint(typeof(IOrderService), new WSHttpBinding(), httpOrderServiceAddress);

                ServiceMetadataBehavior serviceBehavior = new ServiceMetadataBehavior();
                serviceBehavior.HttpGetEnabled = true;
                orderServiceHost.Description.Behaviors.Add(serviceBehavior);

                //For debugging purposes
                //ServiceDebugBehavior debug = orderServiceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
                //if (debug == null)
                //{
                //    orderServiceHost.Description.Behaviors.Add(new ServiceDebugBehavior() { IncludeExceptionDetailInFaults = true });
                //}
                //else
                //{
                //    if (!debug.IncludeExceptionDetailInFaults)
                //    {
                //        debug.IncludeExceptionDetailInFaults = true;
                //    }
                //}

                orderServiceHost.Open();
                Console.WriteLine("Service OrderService is live now at {0}", httpOrderServiceAddress.ToString());

            }
            catch (Exception ex)
            {
                orderServiceHost = null;
                Console.WriteLine("There is an issue with OrderService " + ex.Message);
            }

            Console.ReadKey();
        }
    }
}
