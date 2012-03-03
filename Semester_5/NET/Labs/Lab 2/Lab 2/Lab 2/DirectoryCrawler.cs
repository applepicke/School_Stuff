using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Lab_2
{
    class DirectoryCrawler
    {

        static void Main(string[] args)
        {
            long totalFileSize;

            Console.Out.WriteLine("DIRECTORY/FILE\tNAME\tPATH\tSIZE(KB)");

            totalFileSize = (long)DisplayDirectoryContents(Environment.GetEnvironmentVariable("SystemRoot"));
            Console.Out.WriteLine("The total size of " + Environment.GetEnvironmentVariable("SystemRoot") + " is " + totalFileSize + "mb");
            Console.In.ReadLine();

        }

        /// <summary>
        /// A recursive function that descends into the bottom of a directory structure
        /// printing names and sizes as it goes.
        /// </summary>
        /// <param name="directoryName"> The name of the directory to search</param>
        /// <returns>Returns the size (in MB) of the directory</returns>
        static double DisplayDirectoryContents(String directoryName)
        {
            double totalFileSize = 0;
            String[] files;
            String[] directories;

            try
            {
                files = Directory.GetFiles(directoryName);
                directories = Directory.GetDirectories(directoryName);
            }
            catch (UnauthorizedAccessException)
            {
                return 0;
            }

            foreach (String filename in files)
            {
                FileInfo currentFile = new FileInfo(filename);
                Console.Out.WriteLine("FILE\t" +
                    currentFile.Name + "\t\t" +
                    currentFile.FullName + "\t\t" +
                    currentFile.Length / 1024.0 + " KB");
                totalFileSize += currentFile.Length / 1048576.0;
            }

            foreach (String dirname in directories)
            {
                DirectoryInfo currentDirectory = new DirectoryInfo(dirname);
                Console.Out.WriteLine("DIRECTORY\t" +
                    currentDirectory.Name + "\t\t" +
                    currentDirectory.FullName + "\t\t" +
                    "--");
                totalFileSize += DisplayDirectoryContents(dirname);
            }
            return totalFileSize;
        }

    }
}
