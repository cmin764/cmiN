using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace ASP.NET_Client.Models
{
    public class LoginViewModel
    {
        [Required]
        [Display(Name = "Email")]
        [EmailAddress]
        public string Email { get; set; }

        [Required]
        [DataType(DataType.Password)]
        [Display(Name = "Parola")]
        public string Password { get; set; }

        [Display(Name = "Retine-mi datele?")]
        public bool RememberMe { get; set; }
    }

    public class RegisterViewModel
    {
        [Display(Name = "Nume")]
        public string Name { get; set; }

        [Display(Name = "Numar telefon")]
        public string Phone { get; set; }

        [Display(Name = "Adresa")]
        public string Address { get; set; }

        [Required]
        [EmailAddress]
        [Display(Name = "Email")]
        public string Email { get; set; }

        [Required]
        [StringLength(100, ErrorMessage = "Email-ul trebuie sa aiba cel putin 6 caractere")]
        [DataType(DataType.Password)]
        [Display(Name = "Parola")]
        public string Password { get; set; }

        [DataType(DataType.Password)]
        [Display(Name = "Confirmare parola")]
        [Compare("Password", ErrorMessage = "Parolele nu corespund. Reincercati.")]
        public string ConfirmPassword { get; set; }

    }

}
