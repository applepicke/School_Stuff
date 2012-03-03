using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LINQ_Again
{
    class Program
    {
        static void Main(string[] args)
        {
            LINQNumberCollections linqnc = new LINQNumberCollections();
            linqnc.BeingLinqTransactions();

            LINQFileInfoCollection linqfic = new LINQFileInfoCollection();
            linqfic.BeingLinqTransactions();

            // wait for exit
            Console.In.ReadLine();
        }
    }
}
