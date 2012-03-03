using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data;
using System.Data.SqlClient;

public class Person
{
    // holds the objects connection string
    private string connectionString = ConnectionString.ATMConnectionString;

    /// <summary>
    /// Property, holds the database id of the object
    /// </summary>
    public int PersonId
    {
        get;
        set;
    }

    /// <summary>
    /// Property, holds the first name of the object
    /// </summary>
    public string FirstName
    {
        get;
        set;
    }

    /// <summary>
    /// Property, holds the last name of the object
    /// </summary>
    public string LastName
    {
        get;
        set;
    }

    /// <summary>
    /// Property, retrieves the first and last of the object
    /// </summary>
    public string FullName
    {
        get
        {
            return FirstName + " " + LastName;
        }
    }

    /// <summary>
    /// Property, retrieves the ages of the person using the birthday provided to the object
    /// </summary>
    public int Age
    {
        get
        {
            return +(DateTime.Now.Year - Birthday.Year);
        }
    }

    /// <summary>
    /// Property, holds the birthday of the object
    /// </summary>
    public DateTime Birthday
    {
        get;
        set;
    }

    /// <summary>
    /// Constructor, default, creates a new empty Person object
    /// </summary>
    public Person()
    {
        FirstName = string.Empty;
        LastName = string.Empty;
        Birthday = DateTime.MinValue;
    }

    /// <summary>
    /// Method, inserts a person to the database
    /// </summary>
    public void InsertPerson()
    {
        string sqlQuery = "INSERT INTO People (FirstName, LastName, Birthday) VALUES('" + this.FirstName + "', '" + this.LastName + "', '" + this.Birthday.ToShortDateString() + "')";

        SqlConnection connection = new SqlConnection(this.connectionString);
        SqlCommand command = new SqlCommand(sqlQuery, connection);

        try
        {
            connection.Open();

            command.ExecuteNonQuery();
        }
        catch (Exception ex)
        {
            throw ex;
        }
        finally
        {
            connection.Close();
        }
    }

    /// <summary>
    /// Method, updates this person object in the database
    /// </summary>
    public void UpdatePerson()
    {
        string sqlQuery = "UPDATE People SET FirstName = '" + this.FirstName + "', LastName = '" + this.LastName + "', Birthday = '" + this.Birthday.ToShortDateString() + "' WHERE PersonId = '" + this.PersonId + "'";

        SqlConnection connection = new SqlConnection(this.connectionString);
        SqlCommand command = new SqlCommand(sqlQuery, connection);

        try
        {
            connection.Open();

            command.ExecuteNonQuery();
        }
        catch (Exception ex)
        {
            throw ex;
        }
        finally
        {
            connection.Close();
        }
    }

    /// <summary>
    /// Method, deletes this person from the database
    /// </summary>
    public void DeletePerson()
    {

    }

    /// <summary>
    /// Method, gets a person from the database using the person id provided
    /// </summary>
    public void GetPerson()
    {
        string sqlQuery = "SELECT * FROM People WHERE PersonId = '" + this.PersonId + "'";

        SqlConnection connection = new SqlConnection(this.connectionString);
        SqlCommand command = new SqlCommand(sqlQuery, connection);
        SqlDataReader reader = null;

        try
        {
            connection.Open();

            reader = command.ExecuteReader();

            if (reader.Read())
            {
                this.FirstName = reader["FirstName"].ToString();
                this.LastName = reader["LastName"].ToString();
                this.Birthday = Convert.ToDateTime(reader["Birthday"]);
            }
            else
                throw new Exception("Person Not Found");
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

    /// <summary>
    /// Method, gets all the people from the database
    /// </summary>
    /// <returns></returns>
    public List<Person> GetPeople()
    {
        List<Person> peopleCollection = new List<Person>();

        string sqlQuery = "SELECT * FROM People";

        SqlConnection connection = new SqlConnection(this.connectionString);
        SqlCommand command = new SqlCommand(sqlQuery, connection);
        SqlDataReader reader = null;

        try
        {
            connection.Open();

            reader = command.ExecuteReader();

            while (reader.Read())
            {
                Person p = new Person();
                p.PersonId = Convert.ToInt32(reader["PersonId"]);
                p.FirstName = reader["FirstName"].ToString();
                p.LastName = reader["LastName"].ToString();
                p.Birthday = Convert.ToDateTime(reader["Birthday"]);

                peopleCollection.Add(p);
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

        return peopleCollection;
    }
}