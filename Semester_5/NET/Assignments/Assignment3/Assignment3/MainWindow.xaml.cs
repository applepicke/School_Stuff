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
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace Assignment3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OpenMedia(object sender, RoutedEventArgs e)
        {
            //give the user a file dialog to open a media file
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "*.mp3";
            dlg.Filter = "mp3 |*.mp3|avi|*.avi";
            bool? result = dlg.ShowDialog();

            //Get out of here if user doesn't pick a file
            if (result != true)
            {
                return;
            }

            //Add the file(s) to the playlist
            foreach (string s in dlg.FileNames)
            {
                Label label = new Label();
                label.MouseDoubleClick += PlayMedia;
                label.Content = dlg.FileName;
                playlist.Items.Add(label);
            }
        }

        private void StopMedia(object sender, RoutedEventArgs e)
        {
            media.Stop();
        }

        private void PlayMedia(object sender, RoutedEventArgs e)
        {
            string mediaName;

            //Set the media source
            if (playlist.SelectedItem != null)
                mediaName = (string)((Label)playlist.SelectedItem).Content;
            else if (!playlist.Items.IsEmpty)
                mediaName = (string)((Label)playlist.Items.GetItemAt(0)).Content;
            else
                return;

            media.Source = new Uri(mediaName);
            media.LoadedBehavior = MediaState.Manual;

            //Set the current file playing label
            currentSong.Content = mediaName.Substring(mediaName.LastIndexOf('\\') + 1);

            media.Play();
        }

    }
}
