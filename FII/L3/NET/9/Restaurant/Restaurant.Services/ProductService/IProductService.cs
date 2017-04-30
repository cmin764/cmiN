using System.ServiceModel;
using System.Collections.Generic;
using Restaurant.Data.Entities;

namespace Restaurant.Services.ProductService
{
    [ServiceContract]
    public interface IProductService
    {
        [OperationContract]
        List<Product> GetAllProducts();

        [OperationContract]
        List<Product> GetProductsByName(string productName);

        [OperationContract]
        List<Product> GetProductsByDescription(string productDescription);

        [OperationContract]
        List<Product> GetProductsOfOrder(int orderNumber);
        
        [OperationContract]
        List<Product> GetTopMostExpensiveProducts(int nrOfProducts);

        [OperationContract]
        List<Product> GetTopMostExpensiveProductsUnderPrice(int nrOfProducts, decimal maxPrice);

        [OperationContract]
        void CreateProduct(string name, string description, decimal price, int kcal);

        [OperationContract]
        void DeleteProduct(int productId);

        [OperationContract]
        void IncreaseProductPrice(int productId, decimal percent);

        [OperationContract]
        void DescreaseProductPrice(int productId, decimal percent);

        [OperationContract]
        void ModifyProductDescription(int productId, string description);

        [OperationContract]
        Product GetProductById(int productId);

    }
}
