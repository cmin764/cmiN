using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WPF_Client.Models;

namespace WPF_Client.Controllers
{
    public class ProductsController
    {
        private static ProductsController instance;

        private ProductsController()
        {
        }

        public static ProductsController Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new ProductsController();
                }
                return instance;
            }
        }

        private ProductReference.ProductServiceClient client;

        public ProductReference.ProductServiceClient Client
        {
            get
            {
                if (client == null)
                    client = new ProductReference.ProductServiceClient();
                return client;
            }
        }

        public List<ProductReference.Product> GetProductsOfOrder(int id)
        {
            return Client.GetProductsOfOrder(id);
        }

        public List<ProductModel> GetAllProducts()
        {
            var products = Client.GetAllProducts();
            return products.Select(p => new ProductModel() { Id = p.ProductId, Descriere = p.Description, Nume = p.Name, Kcal = p.Kcal, Pret = p.Price }).ToList();
        }

       


    }
}