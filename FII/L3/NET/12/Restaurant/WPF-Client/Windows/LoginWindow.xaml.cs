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
namespace WPF_Client.Windows
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public const string userNotExisting = "Acest user nu exista ! Reverificati sau folositi meniul de inregistrare !";
        public const string authenticationProblem = "Autentificarea nu s-a incheiat cu succes. Ne scuzati !";
        public const string emptyErr = "Trebuie sa completati toate campurile.";
        
        private string username;
        private int id;

        public LoginWindow()
        {
            InitializeComponent();
        }

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            string email = emailBox.Text;
            string pass = passBox.Text;

            if (email == "" || pass == "")
                MessageBox.Show(emptyErr, "Eroare", MessageBoxButton.OK, MessageBoxImage.Error);

            bool ok = AuthenticationController.Instance.LogIn(email, pass);
            if (ok)
            {
                MainMenu menu = new MainMenu();
                this.Close();
                menu.Show();
                return;
            }
            else
            { 
                MessageBox.Show(authenticationProblem, "Eroare", MessageBoxButton.OK, MessageBoxImage.Error);

                emailBox.Text = "";
                passBox.Text = "";

            }

            return;
        }

        private void Register_Click(object sender, RoutedEventArgs e)
        {
            RegisterWindow register = new RegisterWindow();
            this.Hide();
            register.Show();
        }
    }
}
