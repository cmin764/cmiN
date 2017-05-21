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
using System.Collections.ObjectModel;
using WPF_Client.Models;
using WPF_Client.Controllers;

namespace WPF_Client.Windows
{
    /// <summary>
    /// Interaction logic for OrdersWindow.xaml
    /// </summary>
    public partial class OrdersWindow : Window
    {
        public OrdersWindow()
        {
            InitializeComponent();
        }

        private List<OrderModel> source;

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            source = OrdersController.Instance.GetAllOrders();
            dataGrid.ItemsSource = source;
            dataGrid.IsReadOnly = true;

            var buttonColumn = new DataGridTemplateColumn();
            buttonColumn.Header = "Anuleaza comanda";

            DataTemplate buttonTemplate = new DataTemplate();
            FrameworkElementFactory buttonFactory = new FrameworkElementFactory(typeof(Button));
            buttonTemplate.VisualTree = buttonFactory;
            buttonFactory.AddHandler(Button.ClickEvent, new RoutedEventHandler(button_click));


            buttonFactory.SetValue(ContentProperty, "Anuleaza");
            buttonColumn.CellTemplate = buttonTemplate;

            dataGrid.Columns.Add(buttonColumn);

            var buttonColumn2 = new DataGridTemplateColumn();
            buttonColumn2.Header = "Vezi detalii";

            DataTemplate buttonTemplate2 = new DataTemplate();
            FrameworkElementFactory buttonFactory2 = new FrameworkElementFactory(typeof(Button));
            buttonTemplate2.VisualTree = buttonFactory2;
            buttonFactory2.AddHandler(Button.ClickEvent, new RoutedEventHandler(button2_click));


            buttonFactory2.SetValue(ContentProperty, "Detalii");
            buttonColumn2.CellTemplate = buttonTemplate2;

            dataGrid.Columns.Add(buttonColumn2);

        }

        void button_click(object sender, RoutedEventArgs e)
        {
            var obj = dataGrid.SelectedValue as OrderModel;
           
            OrdersController.Instance.DeleteOrder(obj);
            source.Remove(obj);
            dataGrid.Items.Refresh();
        }

        void button2_click(object sender, RoutedEventArgs e)
        {
            var obj = dataGrid.SelectedValue as OrderModel;

            var window = new PlaceOrderView(obj.Id);
            window.Show();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            MainMenu window = new MainMenu();
            this.Close();
            window.Show();
        }
    }
}
