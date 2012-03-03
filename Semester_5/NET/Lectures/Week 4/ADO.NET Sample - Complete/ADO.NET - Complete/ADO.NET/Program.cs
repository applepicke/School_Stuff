using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        // insert
        Person personToInsert = new Person();
        personToInsert.FirstName = "John";
        personToInsert.LastName = "Smith" + DateTime.Now.Ticks.ToString();
        personToInsert.Birthday = DateTime.Now;
        personToInsert.InsertPerson();

        // select
        Person getPerson = new Person();
        getPerson.PersonId = 1;
        getPerson.GetPerson();

        OutputPerson(getPerson);

        // update
        getPerson.LastName = "Smith-Blue";
        getPerson.UpdatePerson();

        // select all
        Person selectAllPerson = new Person();
        List<Person> people = selectAllPerson.GetPeople();

        foreach (Person p in people)
            OutputPerson(p);

        //delete, implement yourself for practice
        
        Console.In.ReadLine();
    }

    private static void OutputPerson(Person person)
    {
        Console.Out.WriteLine("{0}\t\t{1}\t\t{2}", person.FirstName, person.LastName, person.Birthday);
    }
}
