using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Collections
{
    class Program
    {
        static void Main(string[] args)
        {
            PersonCollection ic = new PersonCollection();

            Person person = new Person();
            person.FirstName = "Justin";
            person.LastName = "Antoszek";
            person.Birthday = DateTime.Now.Subtract(new TimeSpan(12000, 0, 0, 0, 0));
            
            Person person1 = new Person();
            person1.FirstName = "John";
            person1.LastName = "Smith";
            person1.Birthday = DateTime.Now.Subtract(new TimeSpan(2000, 0, 0, 0, 0));

            // add a new person
            ic.Add(person);
            ic.Add(person1);

            // use the custom display
            ic.Display();

            // remove that person by referencing the same object
            ic.Remove(person);

            // use the custom display
            ic.Display();

            // remove that person by referencing the same object
            ic.Remove(person1);

            // use the custom display
            ic.Display();

            Console.In.ReadLine();
        }
    }
}
