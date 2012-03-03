using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace Assignment1
{
    class Person
    {
        public int PersonId
        {
            get;
            set;
        }

        public string FirstName
        {
            get;
            set;
        }

        public String LastName
        {
            get;
            set;
        }
        public String EmailAddress
        {
            get;
            set;
        }
        public String Password
        {
            get;
            set;
        }
        public String SIN
        {
            get;
            set;
        }

        public Person(string firstName, string lastName, string email, string password, string sin)
        {
            PersonId = 0;
            FirstName = firstName;
            LastName = lastName;
            EmailAddress = email;
            Password = password;
            SIN = sin;
        }

        public Person()
        {
        }

        public void CreatePerson()
        {
            string query = "INSERT INTO \"Person\" (FirstName, LastName, EmailAddress, Password, SIN) VALUES ('" +
                                                    FirstName + 
                                               "','" + LastName + 
                                               "','" + EmailAddress + 
                                               "','" + Encryption.EncryptMD5(Password) + 
                                               "','" + Encryption.EncryptMD5(SIN) + "');";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();
                reader = command.ExecuteReader();

                if (reader.Read())
                {
                    PersonId = Int32.Parse(reader["PersonId"].ToString());
                }
            }
            catch (SqlException e)
            {
                throw e;
            }
            connection.Close();
        }

        public void ReadPerson()
        {
            string query = "SELECT * FROM \"Person\" WHERE EmailAddress = '" + EmailAddress + "'";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                if (reader.Read())
                {
                    PersonId = Int32.Parse(reader["PersonId"].ToString());
                    FirstName = reader["FirstName"].ToString();
                    LastName = reader["LastName"].ToString();
                    EmailAddress = reader["EmailAddress"].ToString();
                    Password = reader["Password"].ToString();
                    SIN = reader["SIN"].ToString();

                }
                else
                    throw new Exception("Person not found!");
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (reader != null)
                    reader.Close();

                connection.Close();
            }
        }

        public static ICollection<Person> ReadAllPeople()
        {
            List<Person> personList = new List<Person>();
            string query = "SELECT * FROM \"Person\"";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                while (reader.Read())
                {
                    Person person = new Person();
                    person.PersonId = Int32.Parse(reader["PersonId"].ToString());
                    person.FirstName = reader["FirstName"].ToString();
                    person.LastName = reader["LastName"].ToString();
                    person.EmailAddress = reader["EmailAddress"].ToString();
                    person.Password = reader["Password"].ToString();
                    person.SIN = reader["SIN"].ToString();
                    personList.Add(person);
                }

            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (reader != null)
                    reader.Close();

                connection.Close();
            }
            return personList;
        }

        public void UpdatePerson()
        {
            string query = "UPDATE \"Person\" SET " + 
                                    "FirstName = '" + FirstName +
                                    "', LastName = '" + LastName +
                                    "', EmailAddress = '" + EmailAddress +
                                    "', Password = '" + Password +
                                    "', SIN = '" + SIN +
                                 "' WHERE EmailAddress = '" + EmailAddress + "'";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);

            try
            {
                connection.Open();
                command.ExecuteNonQuery();
            }
            catch (SqlException e)
            {
                throw e;
            }
            connection.Close();
        }

        public void DeletePerson()
        {
            string query = "DELETE FROM \"Person\" WHERE EmailAddress = '" + EmailAddress + "'";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);

            try
            {
                connection.Open();
                command.ExecuteNonQuery();
            }
            catch (SqlException e)
            {
                throw e;
            }
            connection.Close();
        }

        public static void DeleteAll()
        {
            string query = "DELETE FROM \"Person\"";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);

            try
            {
                connection.Open();
                command.ExecuteNonQuery();
            }
            catch (SqlException e)
            {
                throw e;
            }
            connection.Close();
        }


    }
}
