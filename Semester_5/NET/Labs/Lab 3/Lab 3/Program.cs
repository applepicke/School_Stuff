using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;

namespace Lab_3
{
    class Crawler
    {
        static void Main(string[] args)
        {
            Console.Out.WriteLine("Please wait while the collection loads...");
            ICollection<FileInfo> windowsFileInfoList = Crawl(Environment.GetEnvironmentVariable("windir"));
            Console.Out.WriteLine("Collection loaded successfully.");

            while (true)
            {
                Console.Out.WriteLine("\n1. Count files in the collection");
                Console.Out.WriteLine("2. Get largest file");
                Console.Out.WriteLine("3. Show files with names larger than 10 characters");
                Console.Out.WriteLine("4. Sort and display files");
                Console.Out.WriteLine("5. Get all dlls");
                Console.Out.WriteLine("6. Get Length attributes");
                Console.Out.WriteLine("7. Get first entry");
                Console.Out.WriteLine("8. Exit");


                string userInput = Console.In.ReadLine();
                if (userInput.Equals("1"))
                {
                    var allfiles = (from fi in windowsFileInfoList select fi);
                    Console.Out.WriteLine("Number of Files: " + allfiles.Count());
                }
                if (userInput.Equals("2"))
                {
                    var largestFile = (from fi in windowsFileInfoList orderby fi.Length select fi).Last();
                    Console.Out.WriteLine("Largest file: " + largestFile.Name + " " + largestFile.FullName + " " + largestFile.Length / 1024 + "KB");
                }
                if (userInput.Equals("3"))
                {
                    var longerThanTen = (from fi in windowsFileInfoList where fi.Name.Length > 10 select fi.Name);
                    foreach (string name in longerThanTen)
                    {
                        Console.Out.WriteLine(name);
                    }
                }
                if (userInput.Equals("4"))
                {
                    var sorted = (from fi in windowsFileInfoList orderby fi.Length select fi);
                    foreach (FileInfo fi in sorted)
                    {
                        Console.Out.WriteLine(fi.Name + " " + fi.FullName + " " + fi.Length / 1024 + "KB");
                    }
                }
                if (userInput.Equals("5"))
                {
                    var dlls = (from fi in windowsFileInfoList where fi.Name.EndsWith(".dll") select fi).Distinct();
                    foreach (FileInfo fi in dlls)
                    {
                        Console.Out.WriteLine(fi.Name);
                    }
                }
                if (userInput.Equals("6"))
                {
                    var lengthsAscend = (from fi in windowsFileInfoList orderby fi.Length select fi.Length);
                    foreach (int l in lengthsAscend)
                    {
                        Console.Out.WriteLine(l);
                    }
                    Console.Out.WriteLine("Press enter to list in descending order...");
                    Console.In.ReadLine();
                    foreach (int l in lengthsAscend.Reverse())
                    {
                        Console.Out.WriteLine(l);
                    }
                    Console.Out.WriteLine("Press enter to see other properties...");
                    Console.In.ReadLine();
                    Console.Out.WriteLine("MAX: " + lengthsAscend.Max());
                    Console.Out.WriteLine("MIN: " + lengthsAscend.Min());
                    Console.Out.WriteLine("AVG: " + lengthsAscend.Average());
                    Console.Out.WriteLine("SUM: " + lengthsAscend.Sum());
                }
                if (userInput.Equals("7"))
                {
                    var first = (from fi in windowsFileInfoList select fi).First();
                    Console.Out.WriteLine(first.Name + " " + first.FullName + " " + first.Length / 1000 + "KB");
                }
                if (userInput.Equals("8"))
                {
                    Console.Out.WriteLine("Toodles");
                    Environment.Exit(0);
                }
            }
        }

        static ICollection<FileInfo> Crawl(string directory)
        {
            ICollection<FileInfo> FileInfoList = new List<FileInfo>();
            String[] files;
            String[] directories;

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
    }
}
