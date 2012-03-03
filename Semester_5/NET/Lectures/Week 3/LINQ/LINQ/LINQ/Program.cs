using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;

using System.Deployment;

namespace LINQ
{
    class Program
    {
        static List<FileInfo> fileInformationList = new List<FileInfo>();

        static void Main(string[] args)
        {
            Crawl("C:/Users/justin/Desktop/Mesh Share/Development/Applications/AMP");

            // select all
            var example1 = (from fi in fileInformationList select fi);

            foreach (FileInfo f in example1)
                OutputFileInfo(f);



            // select all where length is greater than 100000
            var example2 = (from fi in fileInformationList where fi.Length > 100000 select fi);

            foreach (FileInfo f in example2)
                OutputFileInfo(f);



            // select all where name contains Media
            var example3 = (from fi in fileInformationList where fi.Name.Contains("Media") select fi);

            foreach (FileInfo f in example3)
                OutputFileInfo(f);



            // count select all where name contains Media
            var example4 = (from fi in fileInformationList where fi.Name.Contains("Media") select fi).Count();

            Console.Out.WriteLine("Example 4 counted: " + example4);



            // distinct select all where name contains Media
            var example5 = (from fi in fileInformationList where fi.Name.Contains("Media") select fi).Distinct();

            foreach (FileInfo f in example5)
                OutputFileInfo(f);



            // order by length
            var example6 = (from fi in fileInformationList orderby fi.Length select fi);

            foreach (FileInfo f in example6)
                OutputFileInfo(f);





            // for more visit http://msdn.microsoft.com/en-us/vcsharp/aa336746.aspx





            Console.In.ReadLine();
        }

        static void Crawl(string path)
        {
            string[] directories = Directory.GetDirectories(path);

            foreach (string directory in directories)
                Crawl(directory);

            string[] files = Directory.GetFiles(path);

            foreach (string file in files)
                fileInformationList.Add(new FileInfo(file));
        }

        static void OutputFileInfo(FileInfo fi)
        {
            Console.Out.WriteLine("{0}\t\t{1}\t\t{2}", fi.Name, fi.Length, fi.Directory.Name);
        }
    }
}
