   M S B A M L   `   `   `  ����  Data Binding    Data_Binding.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	     � Title$  
MainWindow��5   	   $	��250��5   	   $	��750��5   	   .��5      � -   5        $��
RootLayout��5       � RowDefinitions 5	   
   �� 5
      �� 5       � ColumnDefinitions 5   
   �� 5      �� 5      �� 5      .+�5   
   �� -   5        $��comboBox��5      $��0��6#   $��35��63   $	��Top=�6?   ��5      �� 5      .R�5      �� ��6    ��  �� Path$ ProgramName�5      5      �� 5   
   -   5        $��listView��5      $��1��6#   ��5      �� 5      .R�5      �� ��6    �� $ ProgramName�5       5"      &   System.Windows.Controls.DataGrid  5$   
   -   5        $��dataGrid��5$      $��2��6#      AutoGenerateColumns . 63   �� 5&   
   $��1��6   $��3��6!   $��Center=�6o   $��Center=�6�   ��65   ��  �� ElementName$ 
RootLayout��$ ActualWidth���6�   �� $ comboBox��$ Height�5'      5(      