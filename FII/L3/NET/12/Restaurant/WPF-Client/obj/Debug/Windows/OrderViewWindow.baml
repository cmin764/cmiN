   M S B A M L   `   `   `  ����E  AWPF-Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:WPF_Client.WindowsWPF_Client.Windows  5   	   (    "WPF_Client.Windows.OrderViewWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   2local clr-namespace:WPF_Client.Windows     5   	   -   5          � Title$  Comanda curenta��5   	   $	��350��6!   $��735.2��6.   $��Center=�6S   .��5	      � -   5         �Name$ ProductsWindow1��5	       J� Opacity$	 0.9Q�6$    � RowDefinitions 5
   
   �� 5      $
��119* �6   �� 5      $
��201* �6    � ColumnDefinitions 5   
   �� 5      $
��307* �6   �� 5      $
��387* �6   ��5   
   �� 5       �� ImageSource$9 3/WPF-Client;component/Resources/Blog-Post-Hero2.jpg��6    j� Stretch$ UniformToFill=�6[   .+�5   
   &   System.Windows.Controls.DataGrid  -   5          Name$ dataGrid��5      $��Center=�6%   $��Center=�6B   $	��250��6]   $	��729��6j   $��0,0,-0.2,70.8q�6v   $��Center=�6�   $��Center=�6�   $��2q�6�      CanUserReorderColumns .  	   CanUserResizeColumns	 .  
   CanUserResizeRows
 .  $��Microsoft JhengHei UI)�6<  $��14(�6_  
���   �   
IsReadOnly .    	RowHeight$ 35Q�6�   �� IsTextSearchEnabled .  � UseLayoutRounding .    ColumnHeaderHeight$ 50Q�6�     GridLinesVisibility$ 
Horizontal=�6�  $��2��6  $��2��6     AlternatingRowBackground 5      �� 5       �� Color$ 	#FFFFC3C3��6"    �� Opacity$	 0.6Q�64      VerticalGridLinesBrush 5      �� 5      $ Black��6"   $	 0.2Q�60      HorizontalGridLinesBrush 5      �� 5      $ 	#FF7F3131��6"   $	 0.2Q�64      RowBackground 5      �� 5       $ White��6"   $	 0.6Q�60   ��5"      �� 5#      $ UniformToFill=�6   $9 3/WPF-Client;component/Resources/Blog-Post-Hero2.jpg��65   $ 0Q�6w   5&      �� 5'   
   -   5         ��Name$ 
priceLabel��5'      $
��Left=�6(   $
��Wrap=�6C   $��Total pret:��6W   $	��Top=�6j   $��28,138.8,0,0q�6�   $��Microsoft PhagsPa)�6�   $��16(�6�   
�������$��	ExtraBold"�6�   $��1��6�   ��5(      �� 5)      $ Black��6"   $	 0.5Q�60   5+      �� 5,   
   -   5        $ 	kcalLabel��5,      $
��Left=�6'   $
��Wrap=�6B   $��Total kcal:��6V   $	��Top=�6i   $��28,159.8,0,0q�6�   $��Microsoft PhagsPa)�6�   $��16(�6�   
�������$��	ExtraBold"�6�   $��1��6�   ��5-      �� 5.      $ Black��6"   $	 0.5Q�60   50      �� 51   
   -   5        $ 
totalPrice��51      $
��Wrap=�6(   $	��Top=�6<   $��163,138.8,94.2,0q�6T   $��Microsoft PhagsPa)�6n   $��16(�6�   
�������$��	ExtraBold"�6�   $��0��6�   $��1��6�   ��52      �� 53      $ Black��6"   $	 0.5Q�60   55      �� 56   
   -   5        $ 	totalKcal��56      $
��Left=�6'   $
��Wrap=�6B   $��0��6V   $	��Top=�6_   $��163,159.8,0,0q�6w   $��Microsoft PhagsPa)�6�   $��16(�6�   
�������$��	ExtraBold"�6�   $��1��6�   $��55��6�   ��57      �� 58      $ Black��6"   $	 0.5Q�60   5:      �� 5;   
   -   5         ��Name$ button��5;      $��Trimite comanda��6!   $
��Left=�6;   $	��Top=�6V   $	��299��6n   $��223,139.8,0,0q�6z   $��40��6�   $��Microsoft JhengHei UI)�6�   $��16(�6�   ���	#FF200117$��1��6�   $��2��6	  ���	#FFFFF2F2$	 0.9Q�64   . 6B  �� 5<   
   -	   5        $ button1��5<      $��Inapoi��6"   $
��Left=�63   $	��Top=�6N   $	��157��6f   $��1��6r   $��219.8,140.8,0,0q�6�   $��1��6�   $��39��6�   $��Microsoft JhengHei UI)�6�   $��16(�6�   ���	#FFFFF2F2$	 0.9Q�6�   ���	#FF200117 . 6:  5>      5?      