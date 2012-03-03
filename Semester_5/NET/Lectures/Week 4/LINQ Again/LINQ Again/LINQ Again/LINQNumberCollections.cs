using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LINQ_Again
{
    class LINQNumberCollections
    {
        private int[] collection = { 83, 12, 34, 942, 230, 43, 204, 11, 223, 223, 32, 56, 86, 32 };

        public LINQNumberCollections()
        {

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

        public void Max()
        {
            int max = collection.Max();

            Console.Out.WriteLine("Max: " + max);

            Space();
        }

        public void Min()
        {
            int min = collection.Min();

            Console.Out.WriteLine("Min: " + min);

            Space();
        }

        public void Count()
        {
            int count = collection.Count();

            Console.Out.WriteLine("Count: " + count);

            Space();
        }

        public void Average()
        {
            double average = collection.Average();

            Console.Out.WriteLine("Average: " + average);

            Space();
        }

        public void SortAsc()
        {
            var sortedNumbers = (from number in collection orderby number ascending select number);

            Console.Out.Write("Sorted numbers ascending: ");

            foreach (int number in sortedNumbers)
                Console.Out.Write(number + ", ");

            Space();
        }

        public void SortDesc()
        {
            var sortedNumbers = (from number in collection orderby number descending select number);

            Console.Out.Write("Sorted numbers descending: ");

            foreach (int number in sortedNumbers)
                Console.Out.Write(number + ", ");

            Space();
        }

        public void SimpleSelectWhere()
        {
            var greaterThan500 = (from number in collection where number > 500 select number);

            Console.Out.Write("Simple Select - all numbers greater than 500: ");

            foreach (int number in greaterThan500)
                Console.Out.Write(number + ", ");

            Space();
        }

        public void SimpleSelectWhereOrderBy()
        {
            var greaterThan500 = (from number in collection where number < 500 && number > 32 orderby number select number);

            Console.Out.Write("Simple Select - all numbers less than 500 and greater than 32: ");

            foreach (int number in greaterThan500)
                Console.Out.Write(number + ", ");

            Space();
        }

        public void SimpleSelectTake()
        {
            var take = (from number in collection select number).Take(5);

            Console.Out.Write("Take 5: ");

            foreach (int number in take)
                Console.Out.Write(number + ", ");

            Space();
        }
        

        public void SimpleSelectDistinct()
        {
            var take = (from number in collection select number).Distinct();

            Console.Out.Write("Distinct - multiple same values removed: ");

            foreach (int number in take)
                Console.Out.Write(number + ", ");

            Space();
        }


        public void SimpleSelectToArray()
        {
            int[] intArray = (from number in collection select number).ToArray();

            Console.Out.Write("To Array: ");

            foreach (int number in intArray)
                Console.Out.Write(number + ", ");

            Space();
        }


        public void SimpleSelectSingle()
        {
            int single = (from number in collection where number == 83 select number).Single();

            Console.Out.Write("Single - get the first element in the collection, instead of a collection with 1 item: " + single);

            Space();
        }
        
        public void SimpleSelectSingle_Fail()
        {
            try
            {
                int single = (from number in collection where number == 32 select number).Single();

                Console.Out.Write("Single - get the first element in the collection, instead of a collection with 1 item: " + single);

                Space();
            }
            catch
            {
                Console.Out.WriteLine("Single - Fail, the collection contains more than one match! Use First Instead!!");
            }

            Space();
        }
        
        public void SimpleSelectFirstOrDefault()
        {
            int firstOrDefault = (from number in collection where number > 1000 select number).FirstOrDefault();

            Console.Out.Write("Single - get the first element in the collection. if null, get the default type value (in the case of int - will return 0): " + firstOrDefault);

            Space();
        }

        private void Space()
        {
            Console.Out.WriteLine();
            Console.Out.WriteLine();
        }
    }
}
