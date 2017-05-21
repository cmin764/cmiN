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
    /// Interaction logic for OrderViewWindow.xaml
    /// </summary>
    public partial class OrderViewWindow : Window
    {
        public OrderViewWindow()
        {
            InitializeComponent();
        }

        private List<ProductModel> source;

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            dataGrid.IsReadOnly = true;
            var buttonColumn = new DataGridTemplateColumn();
            buttonColumn.Header = "Sterge produs";

            source = OrdersController.Instance.GetCurrentOrder();

            dataGrid.ItemsSource = source;
            dataGrid.Columns[0].Visibility = System.Windows.Visibility.Hidden;
            DataTemplate buttonTemplate = new DataTemplate();
            FrameworkElementFactory buttonFactory = new FrameworkElementFactory(typeof(Button));
            buttonTemplate.VisualTree = buttonFactory;
            buttonFactory.AddHandler(Button.ClickEvent, new RoutedEventHandler(button_click));


            buttonFactory.SetValue(ContentProperty, "Sterge");
            buttonColumn.CellTemplate = buttonTemplate;


            dataGrid.Columns.Add(buttonColumn);
            totalKcal.Text = OrdersController.Instance.GetCurrentKcal().ToString();
            totalPrice.Text = OrdersController.Instance.GetCurrentPrice().ToString();
        }

        void button_click(object sender, RoutedEventArgs e)
        {
            var obj = dataGrid.SelectedValue as ProductModel;
            
            obj.Cantitate--;
            if (obj.Cantitate == 0)
                source.Remove(obj);

            dataGrid.Items.Refresh();
            
            totalKcal.Text = OrdersController.Instance.GetCurrentKcal().ToString();
            totalPrice.Text = OrdersController.Instance.GetCurrentPrice().ToString();
            
        }

        private void RefreshData()
        {
        }

        private void button_Click_1(object sender, RoutedEventArgs e)
        {
            OrdersController.Instance.SendCurrentOrder();
            MessageBoxResult res = MessageBox.Show("Comanda s-a trimis cu succes!", "Info", MessageBoxButton.OK);

            if (res == MessageBoxResult.OK)
            {
                MainMenu window = new MainMenu();
                this.Close();
                window.Show();
            }
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            MainMenu window = new MainMenu();
            this.Close();
            window.Show();
        }
    }
}
