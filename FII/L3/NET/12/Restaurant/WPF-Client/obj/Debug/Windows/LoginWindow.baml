   M S B A M L   `   `   `  ����E  AWPF-Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:WPF_Client.WindowsWPF_Client.Windows  5   	   $    WPF_Client.Windows.LoginWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   2local clr-namespace:WPF_Client.Windows     5   	     � Title$  LoginWindow��5   	   $	��600��6   $	��460��6*   $��Microsoft Sans Serif)�66   $��24(�6X   
�������.��5	      � $��
0,0,3,-0.4q�6    J� Opacity$
 0.95Q�6   ��5
   
   �� 5       �� ImageSource$/ )/WPF-Client;component/Resources/Food2.jpg��6    �� Opacity$
 0.95Q�6Q    j� Stretch$ UniformToFill=�6`    � RowDefinitions 5   
   �� 5      .+�5   
   �� -   5         ��Name$
 Logo��5      $��../Resources/Logo.jpg��6   $��105,30,104.6,410.2q�6=   $��Center=�6Y   $	��241��6v   $��Center=�6�   �� 5   
   -   5        $ image��5      $
��Left=�6   $	��100��6:   $��
315,74,0,0q�6G   $	��Top=�6[   $	��100��6s   $��2��6   �� 5   
   -   5         ��Name$ Login��5      $��Logare��6    $��Center=�61   $��Center=�6N   $	��160��6i   $��0,453,0,75.2q�6u   $��40��6�   ���	#FFD9D9D9
���   �$��1q�6�   $��Microsoft YaHei UI)�6�   $��18(�6�    � UseLayoutRounding . ���	#FFA3004661  �� 5   
   -   5        	 ��Name$	 emailBox��5      $��Center=�6$   $��36��6A   
 �� TextWrapping$

 Wrap=�6M   $��Center=�6a   $	��257��6|   $��105,327,88.6,208.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�    �� TextAlignment$ Center=�6�   $��Italic$�6�   
���   �$��2q�6   �� 
CaretBrush
 �   �$��Center=�6=   . ���	#FFFFD5D5$
 0.85Q�6�  �� 5   
   -   5        $	 passBox��5      $��Center=�6#   $��36��6@   $

 Wrap=�6L   $��Center=�6`   $	��257��6{   $��105,399,88.6,136.2q�6�   $��Microsoft JhengHei Light)�6�   $��14(�6�   $ Center=�6�   $��Italic$�6�   
���   �$��2q�6  
 �   �$��Center=�6<   . &   System.Windows.Media.TextOptions   TextHintingMode$ Fixed=�6w  ���	#FFFFD5D5$
 0.85Q�6�  �� 5   
   -   5         ��Name$ 	textBlock��5      $��Center=�6'   $
��Wrap=�6D   $��Center=�6X   $��82,295,61.6,253.2q�6s   $��Microsoft New Tai Lue)�6�   $��18(�6�    �� TextAlignment$ Center=�6�   $	��307��6�    J� RenderTransformOrigin$ 0.502,0.504&�6�   $��Adresa de email:��6  $
��Bold"�6  
�������60  �� 5   
   -   5        $ 
textBlock1��5      $��Center=�6(   $
��Wrap=�6E   $��Center=�6Y   $��168,365,168,170.4q�6t   $��Microsoft New Tai Lue)�6�   $��18(�6�   $ Center=�6�   $	��241��6�   $��Parola��6�   $
��Bold"�6�   
�������6  �� 5   
   -   5        $ Register��5      $��Inregistrare��6#   $��Center=�6:   $��Center=�6W   $	��160��6r   $��0,503,0,25.2q�6~   $��40��6�   ���	#FFD9D9D9
���   �$��1q�6�   $��Microsoft YaHei UI)�6�   $��18(�6�    . ���	#FFA300466=  �� 5   
   -	   5        $ textBlock_Copy��5      $
��Left=�6,   $
��Wrap=�6G   $��La .NET��6[   $��Center=�6j   $��82,202,0,281.2q�6�   $��88��6�   $	��280��6�   $��60(�6�   $��Microsoft YaHei UI)�6�   
�������$ Center=�6�   5      5      