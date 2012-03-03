using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace Assignment1
{
    class Transaction
    {

        public int TransactionId
        {
            get;
            set;
        }

        public int PersonId
        {
            get;
            set;
        }
        public int TransactionTypeId
        {
            get;
            set;
        }
        public decimal AmountTransferred
        {
            get;
            set;
        }

        public Transaction(int personId, int transactionTypeId, decimal amountTransferred)
        {
            PersonId = personId;
            TransactionTypeId = transactionTypeId;
            AmountTransferred = amountTransferred;
        }

        public Transaction()
        {

        }

        public void CreateTransaction()
        {
            string query = "INSERT INTO \"Transaction\" (PersonId, TransactionTypeId, AmountTransferred) VALUES ('" + PersonId + "','" + TransactionTypeId + "','" + AmountTransferred + "')";

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

        public void ReadTransaction()
        {
            string query = "SELECT * FROM \"Transaction\" WHERE TransactionId = '" + TransactionId + "'";

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
                    TransactionTypeId = Int32.Parse(reader["TransactionTypeId"].ToString());
                    AmountTransferred = Decimal.Parse(reader["AmountTransferred"].ToString());
                }
                else
                    throw new Exception("Transaction not found!");
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

        public static ICollection<Transaction> ReadAllTransactions()
        {
            List<Transaction> transactionList = new List<Transaction>();
            string query = "SELECT * FROM \"Transaction\"";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                while (reader.Read())
                {
                    Transaction transaction = new Transaction();
                    transaction.TransactionId = Int32.Parse(reader["TransactionId"].ToString());
                    transaction.PersonId = Int32.Parse(reader["PersonId"].ToString());
                    transaction.TransactionTypeId = Int32.Parse(reader["TransactionTypeId"].ToString());
                    transaction.AmountTransferred = Decimal.Parse(reader["AmountTransferred"].ToString());
                    transactionList.Add(transaction);
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
            return transactionList;
        }

        public void ReadLastTransaction()
        {
            string query = "SELECT * FROM \"Transaction\" WHERE TransactionId = IDENT_CURRENT ('Transaction')";

            SqlConnection connection = new SqlConnection(ConnectionString.connectionString);
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataReader reader = null;

            try
            {
                connection.Open();

                reader = command.ExecuteReader();

                if (reader.Read())
                {
                    TransactionId = Int32.Parse(reader["TransactionId"].ToString());
                    PersonId = Int32.Parse(reader["PersonId"].ToString());
                    TransactionTypeId = Int32.Parse(reader["TransactionTypeId"].ToString());
                    AmountTransferred = Decimal.Parse(reader["AmountTransferred"].ToString());
                }
                else
                    throw new Exception("Transaction not found!");
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

        public void UpdateTransaction()
        {
            string query = "UPDATE \"Transaction\" SET PersonId = '" + PersonId + 
                                                        "', TransactionTypeId = '" + TransactionTypeId + 
                                                        "', AmountTransferred = '" + AmountTransferred +
                                                        "' WHERE TransactionId = '" + TransactionId + "'";

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

        public void DeleteTransaction()
        {
            string query = "DELETE FROM \"Transaction\" WHERE TransactionId = " + TransactionId;

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

        public static void DeleteTransactions(int personId)
        {
            string query = "DELETE FROM \"Transaction\" WHERE PersonId = '" + personId + "'";

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
            string query = "DELETE FROM \"Transaction\"";

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
