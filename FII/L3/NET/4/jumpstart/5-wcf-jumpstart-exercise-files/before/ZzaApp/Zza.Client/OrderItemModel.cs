using Microsoft.Practices.Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Zza.Client
{
    public class OrderItemModel : BindableBase
    {
        private int _ProductId;

        public int ProductId
        {
            get { return _ProductId; }
            set { SetProperty(ref _ProductId, value); }
        }

        private string _ProductName;

        public string ProductName
        {
            get { return _ProductName; }
            set { SetProperty(ref _ProductName, value); }
        }

        private int _Quantity;

        public int Quantity
        {
            get { return _Quantity; }
            set { SetProperty(ref _Quantity, value); }
        }

        private decimal _TotalPrice;

        public decimal TotalPrice
        {
            get { return _TotalPrice; }
            set { SetProperty(ref _TotalPrice, value); }
        }
    }
}
