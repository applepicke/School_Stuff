using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Security.Cryptography;

namespace Assignment1
{
    class Administrator
    {
        public string Username
        {
            get;
            set;
        }
        public string Password
        {
            get;
            set;

        }

        public Administrator(string username, string password)
        {
            Username = username;
            Password = password;
        }

        public Administrator()
        {

        }

        public void CreateAdministrator()
        {
            string query = "INSERT INTO \"Administrator\" (Username, Password) VALUES ('" + Username + "', '" + Encryption.EncryptMD5(Password) + "')";

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

        public void ReadAdministrator()
        {
            string query = "SELECT * FROM \"Administrator\" WHERE Username = '" + Username + "'";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                if (reader.Read())
                {
                    Username = reader["Username"].ToString();
                    Password = reader["Password"].ToString();
                }
                else
                    throw new Exception("Admin not found!");
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

        public static ICollection<Administrator> ReadAllAdministrators(){
            List<Administrator> adminList = new List<Administrator>();
            string query = "SELECT * FROM \"Administrator\"";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                while (reader.Read())
                {
                    Administrator admin = new Administrator();
                    admin.Username = reader["Username"].ToString();
                    admin.Password = reader["Password"].ToString();
                    adminList.Add(admin);
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
            return adminList;
        }

        public void UpdateAdministrator()
        {
            string query = "UPDATE \"Administrator\" SET Username = '" + Username + "', Password = '" + Password + "' WHERE Username = '" + Username + "'";

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

        public void DeleteAdministrator()
        {
            string query = "DELETE FROM \"Administrator\" WHERE Username = '" + Username + "'";

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
            string query = "DELETE FROM \"Administrator\"";

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
