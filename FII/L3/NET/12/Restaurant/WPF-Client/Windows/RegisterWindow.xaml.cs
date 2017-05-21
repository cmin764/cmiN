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
using System.ComponentModel.DataAnnotations;

namespace WPF_Client.Windows
{
    /// <summary>
    /// Interaction logic for RegisterWindow.xaml
    /// </summary>
    public partial class RegisterWindow : Window
    {
        public const string emptyFields = "Trebuie sa completati toate field-urile !";
        public const string emailBad = "Email-ul nu este unul valid.";
        public const string matchingPassword = "Parolele nu corespund, reincercati !";
        public const string failedAuthentificatiom = "Autentificarea nu a reusit. Ne scuzati !";

        public RegisterWindow()
        {
            InitializeComponent();
        }

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
            this.Close();

        }

        private void Register_Click(object sender, RoutedEventArgs e)
        {
            string name = nameBox.Text;
            string phone = phoneBox.Text;
            string email = emailBox.Text;
            string pass1 = passBox.Text;
            string pass2 = passConfirmedBox.Text;
            string address = addressBox.Text;

            if(name == ""  || phone == "" || email == "" || pass1 == "" || pass2 == "" || address == "")
            {
                MessageBox.Show(emptyFields,"Eroare", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            var checker = new EmailAddressAttribute();
            if (checker.IsValid(email) == false)
            {
                MessageBox.Show(emailBad, "Eroare", MessageBoxButton.OK, MessageBoxImage.Error);
                emailBox.Text = "";
                return;
            }

            if (pass1 != pass2)
            {
                MessageBox.Show(matchingPassword, "Eroare", MessageBoxButton.OK, MessageBoxImage.Error);
                passBox.Text = "";
                passConfirmedBox.Text = "";
                return;
            }

            bool ok = AuthenticationController.Instance.Register(name,phone,address,email,pass1);
            if (!ok)
            {
                MessageBox.Show(failedAuthentificatiom, "Eroare", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                MainMenu menu = new MainMenu();
                this.Close();
                menu.Show();
            }
        }
    }
}
