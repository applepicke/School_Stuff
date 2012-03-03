using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LINQ_to_SQL
{
    class Program
    {
        static void Main(string[] args)
        {
            ATMDataContext db = new ATMDataContext();

            // insert
            People insert = new People();
            insert.FirstName = "Justin Allan";
            insert.LastName = "Antoszek";
            insert.Birthday = DateTime.Now.Date.Subtract(new TimeSpan(10000, 0, 0, 0));

            db.Peoples.InsertOnSubmit(insert);  
            db.SubmitChanges();
            
            // IMPORTANT!!!
            //
            // when the insert object is added to the database the identity column is assigned the value from the database
            //
            // IMPORTANT!!!





            // select
            People selectPerson = (from p in db.Peoples where p.PersonId == insert.PersonId - 1 select p).FirstOrDefault();
            OutputPerson(selectPerson);
                      




            // update
            selectPerson.FirstName = "THis is my new name";
            db.SubmitChanges();
            




            // select all to show the update
            var allPeople = (from p in db.Peoples select p);

            foreach (People p in allPeople)
                OutputPerson(p);

            Break();

            // delete
            db.Peoples.DeleteOnSubmit(selectPerson);
            db.SubmitChanges();





            // select all again to show the delete
            allPeople = (from p in db.Peoples select p);

            foreach (People p in allPeople)
                OutputPerson(p);





            Console.In.ReadLine();
        }

        private static void OutputPerson(People people)
        {
            Console.Out.WriteLine("{0}\t\t{1}\t\t{2}", people.FirstName, people.LastName, people.Birthday);
        }

        private static void Break()
        {
            Console.Out.WriteLine();
            Console.Out.WriteLine();
            Console.Out.WriteLine();
        }
    }
}
