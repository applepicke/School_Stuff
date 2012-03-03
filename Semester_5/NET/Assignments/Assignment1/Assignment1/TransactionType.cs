using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace Assignment1
{
    class TransactionType
    {
        public static int DEPOSIT_ID = 1;
        public static int WITHDRAW_ID = 2;

        public int TransactionTypeId
        {
            get;
            set;
        }
        public string Transaction
        {
            get;
            set;
        }

        public TransactionType(int transactionTypeId)
        {
            TransactionTypeId = transactionTypeId;
        }

        public void CreateTransactionType()
        {
            string query = "INSERT INTO \"TransactionType\" (TransactionTypeId, Transaction) VALUES ('" + 
                                            TransactionTypeId + "','" + Transaction + "')";

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

        public void ReadTransactionType()
        {
            string query = "SELECT * FROM \"TransactionType\" WHERE TransactionTypeId = '" + TransactionTypeId + "'";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                if (reader.Read())
                {
                    TransactionTypeId = Int32.Parse(reader["TransactionTypeId"].ToString());
                    Transaction = reader["Transaction"].ToString();
                }
                else
                    throw new Exception("Transaction type not found!");
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

        public void UpdateTransactionType()
        {
            string query = "UPDATE \"TransactionType\" SET Transaction = '" + Transaction +
                                             "' WHERE TransactionTypeId = '" + TransactionTypeId + "'";

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

        public void DeleteTransactionType()
        {
            string query = "DELETE FROM \"TransactionType\" WHERE TransactionTypeId = '" + TransactionTypeId + "'";

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
            string query = "DELETE FROM \"TransactionType\"";

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
