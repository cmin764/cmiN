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
using System.Reflection;

using WPF_Client.Controllers;
using WPF_Client.Models;

namespace WPF_Client.Windows
{
    /// <summary>
    /// Interaction logic for ProductsWindow.xaml
    /// </summary>
    public partial class ProductsWindow : Window
    {
        public ProductsWindow()
        {
            InitializeComponent();

        }
        
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            dataGrid.ItemsSource = ProductsController.Instance.GetAllProducts();
            dataGrid.Columns[0].Visibility = System.Windows.Visibility.Hidden;
            dataGrid.Columns[5].Visibility = System.Windows.Visibility.Hidden;
            dataGrid.IsReadOnly = true;

            var buttonColumn = new DataGridTemplateColumn();
            buttonColumn.Header = "Adauga la comanda";

            DataTemplate buttonTemplate = new DataTemplate();
            FrameworkElementFactory buttonFactory = new FrameworkElementFactory(typeof(Button));
            buttonTemplate.VisualTree = buttonFactory;
            buttonFactory.AddHandler(Button.ClickEvent, new RoutedEventHandler(button_click));


            buttonFactory.SetValue(ContentProperty, "Adauga");
            buttonColumn.CellTemplate = buttonTemplate;
            
            dataGrid.Columns.Add(buttonColumn);
            
        }

        void button_click(object sender, RoutedEventArgs e)
        {
            var obj = dataGrid.SelectedValue as ProductModel;

            obj.Cantitate++;
            OrdersController.Instance.AddProductToCurrentOrder(obj);

            totalKcal.Text = OrdersController.Instance.GetCurrentKcal().ToString();
            totalPrice.Text = OrdersController.Instance.GetCurrentPrice().ToString();
        }

        private void button_Click_1(object sender, RoutedEventArgs e)
        {
            OrderViewWindow window = new OrderViewWindow();
            this.Close();
            window.Show();
        }

      

        private void button1_Click_1(object sender, RoutedEventArgs e)
        {
            MainMenu window = new MainMenu();
            this.Close();
            window.Show();
        }
    }
}
