using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data.SqlClient;

namespace Lab4
{
    class ADOFile
    {
        static private string connectionString = "Data Source=WILLY-LAPTOP\\SQLEXPRESS;Initial Catalog=Lab4;User Id=net;Password=willy;";

        public int id
        {
            get;
            set;
        }

        public string name
        {
            get;
            set;
        }

        public string path
        {
            get;
            set;
        }

        public long length
        {
            get;
            set;
        }

        public ADOFile(FileInfo info)
        {
            id = 0;
            name = info.Name;
            path = info.FullName;
            length = info.Length;
        }

        public ADOFile()
        {
            id = 0;
            name = " ";
            path = " ";
            length = 0;
        }

        public void InsertFile()
        {
            string query = "INSERT INTO \"File\" (Name, Path, Length) VALUES ('" + name + "', '" + path + "', " + length + ")";

            SqlConnection connection = new SqlConnection(connectionString);
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

        public void UpdateFile()
        {
            string query = "UPDATE \"File\" SET Name = '" + name + "', Path = '" + path + "', Length = '" + length + "' WHERE FileId = '" + id + "'";

            SqlConnection connection = new SqlConnection(connectionString);
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

        public void DeleteFile()
        {
            string query = "DELETE FROM \"File\" WHERE FileId = '" + id + "'";

            SqlConnection connection = new SqlConnection(connectionString);
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

        public void GetFile()
        {
            string query = "SELECT * FROM \"File\" WHERE FileId = '" + id + "'";

            SqlConnection connection = new SqlConnection(connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                if (reader.Read())
                {
                    name = reader["Name"].ToString();
                    path = reader["Path"].ToString();
                    length =  Int32.Parse(reader["Length"].ToString());
                }
                else
                    throw new Exception("File Not Found!");
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

        static public ICollection<ADOFile> getFiles()
        {
            string query = "SELECT * FROM \"File\"";

            SqlConnection connection = new SqlConnection(connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            List<ADOFile> fileList = new List<ADOFile>();
            ADOFile tempFile;

            try
            {
                connection.Open();
                reader = command.ExecuteReader();
                while (reader.Read())
                {
                    tempFile = new ADOFile();
                    tempFile.id = Int32.Parse(reader["FileId"].ToString());
                    tempFile.name = reader["Name"].ToString();
                    tempFile.path = reader["Path"].ToString();
                    tempFile.length = Int32.Parse(reader["Length"].ToString());
                    fileList.Add(tempFile);
                }
            }
            catch (SqlException e)
            {
                throw e;
            }
            connection.Close();
            return fileList;
        }
    }
}
