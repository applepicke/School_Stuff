using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Lab4
{
    class Lab4A
    {
        static void Main(string[] args)
        {
            Lab4ADataContext db = new Lab4ADataContext();
            Crawler crawler = new Crawler(50);
            ICollection<FileInfo> fileList = crawler.Crawl(Environment.GetEnvironmentVariable("WINDIR"));

            //Insert
            Console.Out.WriteLine("INSERT");
            ICollection<File> files = new List<File>();
            foreach (FileInfo info in fileList)
            {
                File file = new File();
                file.Name = info.Name;
                file.Path = info.FullName;
                file.Length = info.Length;
                files.Add(file);
            }
            db.Files.InsertAllOnSubmit(files);
            db.SubmitChanges();
            Console.Out.WriteLine("Files inserted into database.");
            Console.In.ReadLine();

            //Select
            Console.Out.WriteLine("SELECT");
            File selectFile = (from fi in db.Files select fi).First();
            Console.Out.WriteLine(selectFile.FileId + " " + selectFile.Name + " " + selectFile.Path + " " + selectFile.Length);
            Console.In.ReadLine();

            //Update
            Console.Out.WriteLine("UPDATE");
            selectFile.Name = "Boobies";
            db.SubmitChanges();
            Console.Out.WriteLine("Changes submitted.");
            Console.Out.WriteLine(selectFile.FileId + " " + selectFile.Name + " " + selectFile.Path + " " + selectFile.Length);
            Console.In.ReadLine();

            //Delete
            Console.Out.WriteLine("DELETE");
            db.Files.DeleteOnSubmit(selectFile);
            db.SubmitChanges();
            Console.Out.WriteLine("File deleted.");
            Console.In.ReadLine();

            //Select All
            Console.Out.WriteLine("SELECT ALL");
            IQueryable<File> allFiles = (from fi in db.Files select fi);
            foreach (File file in allFiles)
            {
                Console.Out.WriteLine(file.Name);
            }
            Console.In.ReadLine();

            //Delete All
            Console.Out.WriteLine("DELETE ALL");
            db.Files.DeleteAllOnSubmit(allFiles);
            db.SubmitChanges();
            Console.Out.WriteLine("Database has been vapourized!");
            Console.In.ReadLine();
        }    

    }
}
