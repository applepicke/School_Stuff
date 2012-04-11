using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;

namespace Lab10
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        int i;
        ICollection<FileInfo> files
        {
            get;
            set;
        }

        public Window1()
        {
            i = 0;
            files = new List<FileInfo>();
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            files = Crawl(Environment.GetEnvironmentVariable("SystemRoot"));
            list.ItemsSource = files;
            grid.ItemsSource = files;
        }

        public ICollection<FileInfo> Crawl(string directory)
        {
            ICollection<FileInfo> FileInfoList = new List<FileInfo>();
            String[] files;
            String[] directories;

            if (i == 50)
                return new List<FileInfo>();

            i++;
            try
            {
                files = Directory.GetFiles(directory);
                directories = Directory.GetDirectories(directory);
            }
            catch (UnauthorizedAccessException)
            {
                return new List<FileInfo>();
            }

            foreach (String filename in files)
            {
                FileInfo currentFile = new FileInfo(filename);
                FileInfoList.Add(currentFile);
            }
            foreach (String dirname in directories)
            {
                foreach (FileInfo info in Crawl(dirname))
                {
                    FileInfoList.Add(info);
                }
            }

            return FileInfoList;
        }

        private void list_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            path.Text = list.SelectedItem.ToString();
        }

        private void grid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (grid.SelectedItem == null)
            {
                return;
            }
            path.Text = grid.SelectedItem.ToString();
        }
    }


}
