   M S B A M L   `   `   `  ����E  AWPF-Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:WPF_Client.WindowsWPF_Client.Windows  5   	   '    !WPF_Client.Windows.PlaceOrderView   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   2local clr-namespace:WPF_Client.Windows     5   	   -   5          � Title$  PlaceOrderView��5   	   $	��350��6    $��568.097��6-   $��Center=�6T   .��5	      � -   5         �Name$ ProductsWindow1��5	       J� Opacity$	 0.9Q�6$    � RowDefinitions 5
   
   �� 5      $
��119* �6   �� 5      $
��201* �6    � ColumnDefinitions 5   
   �� 5      $
��307* �6   �� 5      $
��387* �6   ��5   
   �� 5       �� ImageSource$9 3/WPF-Client;component/Resources/Blog-Post-Hero2.jpg��6    j� Stretch$ UniformToFill=�6[   .+�5   
   &   System.Windows.Controls.DataGrid  -   5          Name$ dataGrid��5      $��Center=�6%   $��Center=�6B   $	��250��6]   $	��562��6j   $��0,0,-0.4,70.8q�6v   $��Center=�6�   $��Center=�6�   $��2q�6�      CanUserReorderColumns .  	   CanUserResizeColumns	 .  
   CanUserResizeRows
 .  $��Microsoft JhengHei UI)�6<  $��14(�6_  
���   �   
IsReadOnly .    	RowHeight$ 35Q�6�   �� IsTextSearchEnabled .  � UseLayoutRounding .    ColumnHeaderHeight$ 50Q�6�     GridLinesVisibility$ 
Horizontal=�6�  $��2��6  $��2��6     AlternatingRowBackground 5      �� 5       �� Color$ 	#FFFFC3C3��6"    �� Opacity$	 0.6Q�64      VerticalGridLinesBrush 5      �� 5      $ Black��6"   $	 0.2Q�60      HorizontalGridLinesBrush 5      �� 5      $ 	#FF7F3131��6"   $	 0.2Q�64      RowBackground 5      �� 5       $ White��6"   $	 0.6Q�60   ��5"      �� 5#      $ UniformToFill=�6   $9 3/WPF-Client;component/Resources/Blog-Post-Hero2.jpg��65   $ 0Q�6w   5&      �� 5'   
   -   5         ��Name$ button1��5'      $��Inchide��6"   $
��Left=�64   $	��Top=�6O   $	��157��6g   $��1��6s   $��146.2,152.8,0,0q�6�   $��1��6�   $��39��6�   $��Microsoft JhengHei UI)�6�   $��16(�6�   ���	#FFFFF2F2$	 0.9Q�6�   ���	#FF200117 . 6;  5)      5*      