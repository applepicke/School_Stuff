using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Collections
{
    public class Person
    {
        public string FirstName
        {
            get;
            set;
        }

        public string LastName
        {
            get;
            set;
        }

        public string FullName
        {
            get
            {
                return FirstName + " " + LastName;
            }
        }

        public int Age
        {
            get
            {
                return +(DateTime.Now.Year - Birthday.Year);
            }
        }

        public DateTime Birthday
        {
            get;
            set;
        }

        public Person()
        {
            FirstName = string.Empty;
            LastName = string.Empty;
            Birthday = DateTime.MinValue;
        }
    }
}
