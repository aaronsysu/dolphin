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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace dolphin.eye
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

        private void btnPlay_Click(object sender, RoutedEventArgs e)
        {
            videoDisplay.Source = new Uri("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");
            videoDisplay.Play();
        }

        private void btnPause_Click(object sender, RoutedEventArgs e)
        {
            if (videoDisplay.HasVideo)
            {
                videoDisplay.Pause();
            }
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            if (videoDisplay.HasVideo)
            {
                videoDisplay.Stop();
            }
        }
    }
}
