using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace LINQ_Again
{
    class LINQFileInfoCollection
    {
        private List<FileInfo> fileInformationList;

        public LINQFileInfoCollection()
        {
            fileInformationList = new List<FileInfo>();

            Crawl("C:/users/justin/documents/algonquin");
        }

        void Crawl(string path)
        {
            string[] directories = Directory.GetDirectories(path);

            foreach (string directory in directories)
                Crawl(directory);

            string[] files = Directory.GetFiles(path);

            foreach (string file in files)
                fileInformationList.Add(new FileInfo(file));
        }

        void OutputFileInfo(FileInfo fi)
        {
            Console.Out.WriteLine("{0}\t\t{1}\t\t{2}", fi.Name, fi.Length, fi.Directory.Name);
        }

        public void BeingLinqTransactions()
        {
            Max();

            Min();

            Count();

            Average();

            SortAsc();

            SortDesc();

            SimpleSelectWhere();

            SimpleSelectWhereOrderBy();

            SimpleSelectTake();

            SimpleSelectDistinct();

            SimpleSelectToArray();

            SimpleSelectSingle();

            SimpleSelectSingle_Fail();

            SimpleSelectFirstOrDefault();
        }

        /// <summary>
        /// Max file length
        /// </summary>
        public void Max()
        {
            // we cant do a Max on the fileinfo itself, but we can do a max on one of its properties
            long max = (from fileinfo in fileInformationList select fileinfo.Length).Max();

            // or for those interested in lambda expressions
            // long max = fileInformationList.Max(fi => fi.Length);

            Console.Out.WriteLine("Max: " + max);

            Space();
        }

        public void Min()
        {
            // we cant do a Min on the fileinfo itself, but we can do a min on one of its properties
            long min = (from fileinfo in fileInformationList select fileinfo.Length).Min();
            
            // or for those interested in lambda expressions
            // long min = fileInformationList.Max(fi => fi.Length);

            Console.Out.WriteLine("Min: " + min);

            Space();
        }

        public void Count()
        {
            int count = fileInformationList.Count();

            Console.Out.WriteLine("Count: " + count);

            Space();
        }

        public void Average()
        {
            // we cant do an Average on the fileinfo itself, but we can do an Average on one of its properties
            double average = (from fileinfo in fileInformationList select fileinfo.Length).Average();

            // or for those interested in lambda expressions
            // long min = fileInformationList.Average(fi => fi.Length);

            Console.Out.WriteLine("Average: " + average);

            Space();
        }

        public void SortAsc()
        {
            // will fail, can not compare 2 fileinfos without a custom comparer object
            //var files = (from fileinfo in fileInformationList orderby fileinfo ascending select fileinfo);

            var files = (from fileinfo in fileInformationList orderby fileinfo.Length ascending select fileinfo);

            Console.Out.Write("Sorted files ascending: ");

            foreach (FileInfo fileInfo in files.Take(10))
                OutputFileInfo(fileInfo);

            Space();
        }

        public void SortDesc()
        {
            // will fail, can not compare 2 fileinfos without a custom comparer object
            //var files = (from fileinfo in fileInformationList orderby fileinfo descending select fileinfo);

            var files = (from fileinfo in fileInformationList orderby fileinfo.Length descending select fileinfo);

            Console.Out.Write("Sorted files descending: ");

            foreach (FileInfo fileInfo in files.Take(10))
                OutputFileInfo(fileInfo);

            Space();
        }

        public void SimpleSelectWhere()
        {
            var greaterThan50000 = (from fileinfo in fileInformationList where fileinfo.Length > 50000 select fileinfo);

            Console.Out.Write("Simple Select - all files with file size greater than 50000: ");

            foreach (FileInfo fileinfo in greaterThan50000.Take(10))
                OutputFileInfo(fileinfo);

            Space();
        }

        public void SimpleSelectWhereOrderBy()
        {
            var lessThan50000 = (from fileinfo in fileInformationList where fileinfo.Length < 50000 && fileinfo.Length > 3200 orderby fileinfo.Length select fileinfo);

            Console.Out.Write("Simple Select - all files with file size 50000 and greater than 3200: ");

            foreach (FileInfo fileinfo in lessThan50000.Take(10))
                OutputFileInfo(fileinfo);

            Space();
        }

        public void SimpleSelectTake()
        {
            var take = (from fileinfo in fileInformationList select fileinfo).Take(5);

            Console.Out.Write("Take 5: ");

            foreach (FileInfo fileinfo in take)
                OutputFileInfo(fileinfo);

            Space();
        }
        

        public void SimpleSelectDistinct()
        {
            var distinct = (from fileinfo in fileInformationList select fileinfo).Distinct();

            Console.Out.Write("Distinct - multiple same values removed: ");

            foreach (FileInfo fileinfo in distinct.Take(10))
                OutputFileInfo(fileinfo);

            Space();
        }


        public void SimpleSelectToArray()
        {
            FileInfo[] fileinfoarray = (from fileinfo in fileInformationList select fileinfo).ToArray();

            Console.Out.Write("To Array: ");

            foreach (FileInfo fileinfo in fileinfoarray.Take(10))
                OutputFileInfo(fileinfo);

            Space();
        }


        public void SimpleSelectSingle()
        {
            FileInfo single = (from fileinfo in fileInformationList where fileinfo.Name == "Sunlife.docx" select fileinfo).Single();

            Console.Out.Write("Single - get the first element in the collection, instead of a collection with 1 item: " + single);

            Space();
        }
        
        public void SimpleSelectSingle_Fail()
        {
            try
            {
                FileInfo single = (from fileinfo in fileInformationList select fileinfo).Single();

                Console.Out.Write("Single - get the first element in the collection, instead of a collection with 1 item: " + single);

                Space();
            }
            catch
            {
                Console.Out.WriteLine("Single - Fail, the collection contains more than one element.");
            }

            Space();
        }
        
        public void SimpleSelectFirstOrDefault()
        {
            FileInfo firstOrDefault = (from fileinfo in fileInformationList where fileinfo.Length == 50000 select fileinfo).FirstOrDefault();

            Console.Out.Write("Single (will return null if fileinfo.Lenght != 50000): " + firstOrDefault);

            Space();
        }

        private void Space()
        {
            Console.Out.WriteLine();
            Console.Out.WriteLine();
        }
    }
}
