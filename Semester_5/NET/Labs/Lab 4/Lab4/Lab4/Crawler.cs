using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.IO;

namespace Lab4
{
    class Crawler
    {
        private uint maxFiles;
        private uint count;

        public Crawler(uint maxFiles)
        {
            this.maxFiles = maxFiles;
            count = 0;
        }

        public ICollection<FileInfo> Crawl(string fileName)
        {
            List<FileInfo> fileList = new List<FileInfo>();
            foreach (string file in Directory.GetFiles(fileName))
            {
                if (count == maxFiles)
                {
                    return fileList;
                }
                FileInfo info = new FileInfo(file);
                fileList.Add(info);
                count++;
            }

            try
            {
                foreach (string file in Directory.GetDirectories(fileName))
                {
                    fileList.AddRange(Crawl(file));
                }
            }
            catch (UnauthorizedAccessException)
            {
                return fileList;
            }

            return fileList;
        }
    }

    
}
