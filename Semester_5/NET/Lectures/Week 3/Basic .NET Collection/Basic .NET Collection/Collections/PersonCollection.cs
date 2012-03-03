using System;
using System.Collections;
using System.Linq;
using System.Text;

namespace Collections
{
    class PersonCollection : CollectionBase
    {
        public void Add(Person person)
        {
            this.List.Add(person);
        }

        public void Remove(Person person)
        {
            this.List.Remove(person);
        }

        public void Display()
        {
            if (this.List.Count == 0)
                Console.Out.WriteLine("Person Collection Empty");
            else
            {
                foreach (Person p in this.List)
                    Console.Out.WriteLine(p.FullName + " : " + p.Age);
            }

            Console.Out.WriteLine();
            Console.Out.WriteLine();
            Console.Out.WriteLine();
        }
    }
}
