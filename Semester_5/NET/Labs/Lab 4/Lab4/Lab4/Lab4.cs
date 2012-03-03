using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data.SqlClient;

namespace Lab4
{
    class Lab4
    {
        static void Main(string[] args)
        {
            bool filesAdded = false;
            Crawler myCrawler = new Crawler(50);
            List<FileInfo> list = (List<FileInfo>)myCrawler.Crawl(Environment.GetEnvironmentVariable("WINDIR"));
            while (true)
            {
                Console.Out.WriteLine("\n1. Insert files");
                Console.Out.WriteLine("2. Remove file");
                Console.Out.WriteLine("3. Update file");
                Console.Out.WriteLine("4. Select file");
                Console.Out.WriteLine("5. Select all files");
                Console.Out.WriteLine("6. Exit");


                string userInput = Console.In.ReadLine();
                if (userInput.Equals("1"))
                {
                    if (!filesAdded)
                        InsertFiles(list);
                    else 
                        filesAdded = true;
                }
                if (userInput.Equals("2"))
                {
                    DeleteFile();
                } 
                if (userInput.Equals("3"))
                {
                    UpdateFile();
                }
                if (userInput.Equals("4"))
                {
                    SelectFile();
                }
                if (userInput.Equals("5"))
                {
                    SelectFiles();
                }
                if (userInput.Equals("6"))
                {
                    Console.Out.WriteLine("Toodles");
                    Environment.Exit(0);
                }

            }

        }

        static void InsertFiles(ICollection<FileInfo> files)
        {
            try
            {
                foreach (FileInfo info in files)
                {
                    new ADOFile(info).InsertFile();
                }
            }
            catch (Exception e)
            {
                Console.Out.WriteLine(e.Message);
            }
            Console.Out.WriteLine("Successfully inserted files.");
        }

        static void DeleteFile()
        {
            string num;
            Console.Out.WriteLine("Please enter the id of the file to delete: ");
            num = Console.In.ReadLine();

            try
            {
                ADOFile file = new ADOFile();
                file.id = Int32.Parse(num);
                file.DeleteFile();
            }
            catch (Exception e)
            {
                Console.Out.WriteLine("Could not delete file: " + e.Message);
                return;
            }
            Console.Out.WriteLine("File successfully deleted!");
        }

        static void UpdateFile()
        {
            string num;
            string name;
            string path;
            Console.Out.WriteLine("Please enter the id of the file to update: ");
            num = Console.In.ReadLine();
            Console.Out.WriteLine("Please enter the new name: ");
            name = Console.In.ReadLine();
            Console.Out.WriteLine("Please enter the new path: ");
            path = Console.In.ReadLine();

            try
            {
                ADOFile file = new ADOFile();
                file.id = Int32.Parse(num);
                file.name = name;
                file.path = path;
                file.UpdateFile();
            }
            catch (Exception)
            {
                Console.Out.WriteLine("Could not update file.");
                return;
            }
            Console.Out.WriteLine("File successfully updated!");
        }

        static void SelectFile()
        {
            string num;
            ADOFile file;
            Console.Out.WriteLine("Please enter the id of the file to get: ");
            num = Console.In.ReadLine();

            try
            {
                file = new ADOFile();
                file.id = Int32.Parse(num);
                file.GetFile();
            }
            catch (Exception)
            {
                Console.Out.WriteLine("Could not get file.");
                return;
            }
            Console.Out.WriteLine(file.id + " " + file.name + " " + file.path + " " + file.length);
        }

        static void SelectFiles()
        {
            try
            {
                foreach (ADOFile file in ADOFile.getFiles())
                {
                    Console.Out.WriteLine(file.id + " " + file.name + " " + file.path + " " + file.length);
                }
            }
            catch (Exception e)
            {
                Console.Out.WriteLine(e.Message);
            }
        }

    }
}
