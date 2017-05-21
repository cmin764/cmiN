using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using WPF_Client.Controllers;
using WPF_Client.Models;

namespace WPF_Client.Windows
{
    /// <summary>
    /// Interaction logic for PlaceOrderView.xaml
    /// </summary>
    public partial class PlaceOrderView : Window
    {
        public int OrderId { get; set; }

        public PlaceOrderView()
        {
            InitializeComponent();
        }

        public PlaceOrderView(int orderId)
        {
            InitializeComponent();
            OrderId = orderId;
        }


        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var products = ProductsController.Instance.GetProductsOfOrder(OrderId);
            var productGridItems = products.AsQueryable().Select(p => new ProductModel() { Descriere = p.Description, Kcal = p.Kcal, Nume = p.Name, Pret = p.Price });

            dataGrid.ItemsSource = productGridItems;
            dataGrid.Columns[0].Visibility = System.Windows.Visibility.Hidden;
            dataGrid.Columns[5].Visibility = System.Windows.Visibility.Hidden;
            dataGrid.IsReadOnly = true;
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
