   M S B A M L   `   `   `  ����E  AWPF-Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:WPF_Client.WindowsWPF_Client.Windows  5   	   '    !WPF_Client.Windows.RegisterWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   2local clr-namespace:WPF_Client.Windows     5   	     � Title$  RegisterWindow��5   	   $	��600��6    $��460         ��6-   $��Microsoft Sans Serif)�5	      $��24(�6-   
�������.��5
      � $��
0,0,3,-0.4q�6    J� Opacity$ 5Q�6   ��5   
   �� 5       �� ImageSource$/ )/WPF-Client;component/Resources/Food6.jpg��6    j� Stretch$ UniformToFill=�6Q    �� Opacity$
 0.85Q�6i    � RowDefinitions 5   
   �� 5      .+�5   
   �� -   5         ��Name$ Login��5      $��Logare��6    $��Center=�61   $��Center=�6N   $	��160��6i   $��145,513,145.6,23.2q�6u   $��35��6�   
���   �$��1q�6�   $��Microsoft YaHei UI)�6�   $��18(�6�    � UseLayoutRounding .  J� RenderTransformOrigin$ 0.512,0.137&�6   ���	#FF86043C��5      �� 5      	 �� Color$	 	#FFDFDFDF��6"   $	 0.9Q�64   5      �� 5   
   -   5        
 ��Name$
 passBox��5      $��Center=�6#   $��32��6@    �� TextWrapping$
 Wrap=�6L   $��Center=�6`   $	��207��6{   $��169,380,74.6,159.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�    �� TextAlignment$ Center=�6�   $��Italic$�6�   
���   �$��2q�6   �� 
CaretBrush
 �   �$��Center=�6<   . &   System.Windows.Media.TextOptions   TextHintingMode$ Fixed=�6w  ���	#FFFAE1E1$	 0.9Q�6�  �� 5   
   -   5         ��Name$ 
textBlock1��5      $��Center=�6(   $
��Wrap=�6E   $��Center=�6Y   $��79,394,297.6,159.2q�6t   $��Microsoft JhengHei UI)�6�   $��16(�6�    �� TextAlignment$ Center=�6�   $��74��6�   $��Parola:��6�   $
��Bold"�6�   
�������6  �� 5   
   -   5        $ Register��5      $��Inregistrare��6#   $��Center=�6:   $��Center=�6W   $	��164��6r   $��145,471,141.6,63.2q�6~   $��37��6�   
���   �$��1q�6�   $��Microsoft YaHei UI)�6�   $��18(�6�    . ���	#FF86043C��5      �� 5      $	 	#FFDFDFDF��6"   $	 0.9Q�64   5      �� 5   
   -   5        $
 passConfirmedBox��5      $��Center=�6,   $��32��6I   $
 Wrap=�6U   $��Center=�6i   $	��171��6�   $��205,418,74.6,123.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�   $ Center=�6�   $��Italic$�6�   
���   �$��2q�6  
 �   �$��Center=�6E   . $ Fixed=�6�  ���	#FFFAE1E1$	 0.9Q�6�  �� 5   
   -   5        $ textBlock1_Copy��5      $��Center=�6-   $
��Wrap=�6J   $��Center=�6^   $��79,431,262.6,122.2q�6y   $��Microsoft JhengHei UI)�6�   $��16(�6�   $ Center=�6�   $	��109��6�   $��Confirmare:��6�   $
��Bold"�6�   
�������6  �� 5   
   -   5        $
 
addressBox��5      $��Center=�6&   $��32��6C   $
 Wrap=�6O   $��Center=�6c   $	��207��6~   $��169,343,74.6,196.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�   $ Center=�6�   $��Italic$�6�   
���   �$��2q�6  
 �   �$��Center=�6?   . $ Fixed=�6z  ���	#FFFAE1E1$	 0.9Q�6�  �� 5    
   -   5        $ textBlock1_Copy1��5       $��Center=�6.   $
��Wrap=�6K   $��Center=�6_   $��79,357,295.6,196.2q�6z   $��Microsoft JhengHei UI)�6�   $��16(�6�   $ Center=�6�   $��76��6�   $��Adresa:��6�   $
��Bold"�6�   
�������6
  �� 5!   
   -	   5        $
 emailBox��5!      $��Center=�6$   $��32��6A   $
 Wrap=�6M   $��Center=�6a   $	��207��6|   $��169,306,74.6,233.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�   $ Center=�6�   $��Italic$�6�   
���   �$��2q�6  
 �   �$��Center=�6=   . $ Fixed=�6x  ���	#FFFAE1E1$	 0.9Q�6�  �� 5"   
   -
   5        $ textBlock1_Copy2��5"      $��Center=�6.   $
��Wrap=�6K   $��Center=�6_   $��79,320,300.6,233.2q�6z   $��Microsoft JhengHei UI)�6�   $��16(�6�   $ Center=�6�   $��71��6�   $��Email:��6�   $
��Bold"�6�   
�������6	  �� 5#   
   -   5        $
 phoneBox��5#      $��Center=�6$   $��32��6A   $
 Wrap=�6M   $��Center=�6a   $	��207��6|   $��169,269,74.6,270.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�   $ Center=�6�   $��Italic$�6�   
���   �$��2q�6  
 �   �$��Center=�6=   . $ Fixed=�6x  ���	#FFFAE1E1$	 0.9Q�6�  �� 5$   
   -   5        $ textBlock1_Copy3��5$      $��Center=�6.   $
��Wrap=�6K   $��Center=�6_   $��77,283,295.6,270.2q�6z   $��Microsoft JhengHei UI)�6�   $��16(�6�   $ Center=�6�   $��78��6�   $��Telefon:��6�   $
��Bold"�6�   
�������6  �� 5%   
   -   5        $
 nameBox��5%      $��Center=�6#   $��32��6@   $
 Wrap=�6L   $��Center=�6`   $	��207��6{   $��169,232,74.6,307.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�   $ Center=�6�   $��Italic$�6�   
���   �$��2q�6  
 �   �$��Center=�6<   . $ Fixed=�6w  ���	#FFFAE1E1$	 0.9Q�6�  �� 5&   
   -   5        $ textBlock1_Copy4��5&      $��Center=�6.   $
��Wrap=�6K   $��Center=�6_   $��79,246,299.6,307.2q�6z   $��Microsoft JhengHei UI)�6�   $��16(�6�   $ Center=�6�   $��72��6�   $��Nume:��6�   $
��Bold"�6�   
�������6  �� 5'   
   -   5        $ textBlock_Copy��5'      $
��Left=�6,   $
��Wrap=�6G   $��La .NET��6[   $��Center=�6j   $��96,146,0,337.2q�6�   $��88��6�   $	��280��6�   $��60(�6�   $��Microsoft YaHei UI)�6�   
�������$ Center=�6�   �� 5(   
   -   5         ��Name$
 Logo��5(      $.��(/WPF-Client;component/Resources/Logo.jpg��6   $��110,10,99.6,430.2q�6P   $��Center=�6k   $	��241��6�   $��Center=�6�   5*      5+      