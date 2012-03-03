using System;
using System.Collections;
using System.Linq;
using System.Text;

namespace _.NET_Collections
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Out.WriteLine("array list demo");

            ArrayList al = new ArrayList();
            al.Add(1);
            al.Add(2);
            al.Add("this is a test");
            al.Insert(0, "adding to the first slot");

            Console.Out.WriteLine(al[0]);
            Console.Out.WriteLine(al[1]);
            Console.Out.WriteLine(al[2]);
            Console.Out.WriteLine(al[3]);
            //Console.Out.WriteLine(al[4]); Will obviously crash





            Console.Out.WriteLine();
            Console.Out.WriteLine();
            Console.Out.WriteLine();
            Console.Out.WriteLine();





            Console.Out.WriteLine("Queue Demo");

            Queue q = new Queue();
            q.Enqueue(1);
            q.Enqueue(2);
            q.Enqueue("this is a test");
            q.Enqueue("adding to the first slot");

            Console.Out.WriteLine(q.Peek()); // show the first item

            q.Dequeue(); // remove the first item

            Console.Out.WriteLine(q.Peek()); // remove the new first item





            Console.Out.WriteLine();
            Console.Out.WriteLine();
            Console.Out.WriteLine();
            Console.Out.WriteLine();





            Console.Out.WriteLine("Hast table demo");

            Hashtable hash = new Hashtable();
            Random randomNumber = new Random(DateTime.Now.Second);

            // Add some numbers to the list
            for (int i = 0; i < 10; i++)
                hash.Add(i, randomNumber.Next());

            // display the numbers in the account
            Console.WriteLine("Number of Items: " + hash.Count);

            ///
            /// Enumerators allow programmatic access to interate through all the items in a collection
            /// Most, but not all, collections employ enumberators
            /// 
            /// in this cause we are using a dictionary enumerator; dictionary values have a Key you are looking up, and each key has
            /// a Value associated with it -- like a real dictionary
            ///
            IDictionaryEnumerator listEnumerator = hash.GetEnumerator();

            while (listEnumerator.MoveNext())
                Console.WriteLine("{0}: \t{1}", listEnumerator.Key, (int)listEnumerator.Value); // cause the value to an int
                        
            Console.In.ReadLine();
        }
    }
}
