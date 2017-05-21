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

namespace WPF_Client.Windows
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Window
    {
        public MainMenu()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            AboutWindow window = new AboutWindow();
            this.Close();
            window.Show();
        }

        private void Orders_Click(object sender, RoutedEventArgs e)
        {
            OrdersWindow window = new OrdersWindow();
            this.Close();
            window.Show();
        }

        private void Products_Click(object sender, RoutedEventArgs e)
        {
            ProductsWindow window = new ProductsWindow();
            this.Close();
            window.Show();
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
