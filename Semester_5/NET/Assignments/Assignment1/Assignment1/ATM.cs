using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.IO;

namespace Assignment1
{
    class ATM
    {

        private ICollection<Administrator> admins;

        private ICollection<Transaction> transactions;

        private ICollection<Person> accounts;

        public Person currentUser
        {
            get;
            set;
        }

        public Administrator admin
        {
            get;
            set;
        }

        public ATM()
        {
            RefreshCurrentDatabaseInstance();
        }

        /// <summary>
        /// Creates a new user account in the ATM
        /// </summary>
        public void CreateAccount()
        {
            Person newAccount = new Person();
            while (true)
            {
                Console.Out.WriteLine("First Name: ");
                if ((newAccount.FirstName = Console.In.ReadLine()).Length <= 50)
                    break;
                Console.Out.WriteLine("Name must be less than 50 Characters");
            }

            while (true)
            {
                Console.Out.WriteLine("Last Name: ");
                if ((newAccount.LastName = Console.In.ReadLine()).Length <= 50)
                    break;
                Console.Out.WriteLine("Name must be less than 50 Characters");
            }

            while (true)
            {
                Console.Out.WriteLine("Email Address: ");
                if ((newAccount.EmailAddress = Console.In.ReadLine()).Length <= 255 &&
                    (from li in accounts where li.EmailAddress.Equals(newAccount.EmailAddress) select li).Count() == 0)
                    break;
                Console.Out.WriteLine("Email cannot be used.");
            }

            while (true)
            {
                Console.Out.WriteLine("Password: ");
                if ((newAccount.Password = Console.In.ReadLine()).Length <= 10)
                    break;
                Console.Out.WriteLine("Password must be betwen 0 and 10 Characters");
            }

            while (true)
            {
                Console.Out.WriteLine("Social Insurance Number: ");
                if ((newAccount.SIN = Console.In.ReadLine()).Length <= 11)
                    break;
                Console.Out.WriteLine("SIN must be between 0 and 11 characters");
            }

            newAccount.CreatePerson();
            newAccount.ReadPerson();
            accounts.Add(newAccount);

            Console.Out.WriteLine("Account successfully created!");
        }

        /// <summary>
        /// Logs in to a user account
        /// </summary>
        /// <returns>Whether the login was successful</returns>
        public bool Login()
        {
            Person user = new Person();
            string password;

            Console.Out.WriteLine("Email: ");
            user.EmailAddress = Console.In.ReadLine();
            Console.Out.WriteLine("Password: ");
            password = Console.In.ReadLine();

            try
            {
                user.ReadPerson();

                if (!Encryption.EncryptMD5(password).Equals(user.Password))
                {
                    Console.Out.WriteLine("Password is incorrect!");
                    return false;
                }

                Console.Out.WriteLine("Login successful!");
                currentUser = user;
            }
            catch (Exception e)
            {
                Console.Out.WriteLine(e.Message);
                return false;
            }
            return true;
        }

        /// <summary>
        /// Log the current user out of the atm
        /// </summary>
        public void Logout()
        {
            currentUser = null;
        }

        /// <summary>
        /// Asks the user for an amount of money to deposit, and deposits it
        /// </summary>
        public void Deposit()
        {
            Transaction transaction = new Transaction();

            while (true)
            {
                bool doWeContinue = true;
                try
                {
                    Console.Out.WriteLine("How much would you like to deposit: ");
                    transaction.AmountTransferred = decimal.Parse(Console.In.ReadLine());
                }
                catch (FormatException)
                {
                    Console.Out.WriteLine("That is not a valid number!");
                    doWeContinue = false;
                }
                if (doWeContinue)
                    break;
            }
            transaction.PersonId = currentUser.PersonId;
            transaction.TransactionTypeId = TransactionType.DEPOSIT_ID;

            transaction.CreateTransaction();
            transaction.ReadLastTransaction();
            transactions.Add(transaction);
            Console.Out.WriteLine("Deposit successful!");

        }

        /// <summary>
        /// Withdraws a user specified amount from the atm
        /// </summary>
        public void Withdraw()
        {
            if (currentUser == null) return;
            Transaction transaction = new Transaction();

            while (true)
            {
                bool doWeContinue = true;
                try
                {
                    Console.Out.WriteLine("How much would you like to withdraw: ");
                    transaction.AmountTransferred = decimal.Parse(Console.In.ReadLine());
                }
                catch (FormatException)
                {
                    Console.Out.WriteLine("That is not a valid number!");
                    doWeContinue = false;
                }
                if (doWeContinue)
                    break;            
            }

            if (CalculateBalance() - transaction.AmountTransferred < 0)
            {
                Console.Out.WriteLine("Insufficient Funds!");
                return;
            }

            transaction.PersonId = currentUser.PersonId;
            transaction.TransactionTypeId = TransactionType.WITHDRAW_ID;

            transaction.CreateTransaction();
            transaction.ReadLastTransaction();
            transactions.Add(transaction);
            Console.Out.WriteLine("Withrawal succesful!");
        }

        /// <summary>
        /// Check the users balance
        /// </summary>
        public void CheckBalance()
        {
            if (currentUser == null) return;
            decimal balance = CalculateBalance();

            Console.Out.WriteLine("Total Balance: $" + balance + "\n");
            Console.Out.WriteLine("Export balance to Excel file?(y/n)");

            if (!Console.In.ReadLine().ToLower().Equals("y"))
            {
                return;
            }

            StreamWriter writer = new StreamWriter("balance.csv", false);
            writer.Write("Total Balance," + balance);
            writer.Flush();
            writer.Close();

            Console.Out.WriteLine("Successfully exported records to file!");
            
        }

        /// <summary>
        /// Report the latest transactions for the current user
        /// </summary>
        public void Report()
        {
            string input;
            int numTransactionsToShow;
            Console.Out.WriteLine("How many transactions would you like to see: ");
            Console.Out.WriteLine("1 - Five");
            Console.Out.WriteLine("2 - Ten");
            Console.Out.WriteLine("3 - Fifteen");
            input = Console.In.ReadLine();
            if (input.Equals("1"))
            {
                numTransactionsToShow = 5;
            }
            else if (input.Equals("2"))
            {
                numTransactionsToShow = 10;
            }
            else if (input.Equals("3"))
            {
                numTransactionsToShow = 15;
            }
            else
            {
                Console.Out.WriteLine("Not a valid choice!");
                return;
            }
 
            var latestTransactions = (from li in transactions where li.PersonId == currentUser.PersonId orderby li.PersonId select li).Reverse().Take(numTransactionsToShow);

            Console.Out.WriteLine("The last " + numTransactionsToShow + " transactions are: ");
            foreach (Transaction t in latestTransactions)
            {
                string type = t.TransactionTypeId == TransactionType.DEPOSIT_ID ? "Deposited" : "Withdrew";
                Console.Out.WriteLine(currentUser.FirstName + " " + currentUser.LastName + " " + type + " $" + t.AmountTransferred);
            }

            Console.Out.WriteLine("Export report to Excel file?(y/n)");

            if (!Console.In.ReadLine().ToLower().Equals("y"))
            {
                return;
            }

            ExportToFile(latestTransactions, "report.csv");
            Console.Out.WriteLine("Successfully reported last " + numTransactionsToShow + " records!");           
        }

        /// <summary>
        /// Close the current user's account
        /// </summary>
        public void CloseAccount()
        {
            Console.Out.WriteLine(currentUser.FirstName + ", are you sure you want to delete your account?");
            while (true)
            {
                string response = Console.In.ReadLine();
                if (response.StartsWith("y"))
                {
                    break;
                }
                else
                    return;
            }

            var userRecords = (from li in transactions where li.PersonId == currentUser.PersonId select li);

            foreach (Transaction t in userRecords)
            {
                t.DeleteTransaction();
            }

            currentUser.DeletePerson();

            transactions = Transaction.ReadAllTransactions();

            Console.Out.WriteLine("User successfully deleted!");
            Logout();
        }

        /// <summary>
        /// Logs in to an administrator account
        /// </summary>
        /// <returns>Whether the login was successful</returns>
        public bool LoginAdmin()
        {
            Administrator admin = new Administrator();
            string password;

            Console.Out.WriteLine("Username: ");
            admin.Username = Console.In.ReadLine();
            Console.Out.WriteLine("Password: ");
            password = Console.In.ReadLine();

            try
            {
                admin.ReadAdministrator();

                if (!Encryption.EncryptMD5(password).Equals(admin.Password))
                {
                    Console.Out.WriteLine("Password is incorrect!");
                    return false;
                }

                Console.Out.WriteLine("Login successful!");
                this.admin = admin;
            }
            catch (Exception e)
            {
                Console.Out.WriteLine(e.Message);
                return false;
            }
            return true;
        }

        /// <summary>
        /// Logs out of the administrator account
        /// </summary>
        public void LogoutAdmin()
        {
            admin = null;
        }

        /// <summary>
        /// Creates a new administator account
        /// </summary>
        public void CreateAdmin()
        {
            Administrator admin = new Administrator();

            while (true)
            {
                Console.Out.WriteLine("Enter a username for the admin: ");
                if ((admin.Username = Console.In.ReadLine()).Length <= 20)
                    break;
                Console.Out.WriteLine("Username must be less than 20 characters.");
            }

            while (true)
            {
                Console.Out.WriteLine("Enter a password for the admin: ");
                if ((admin.Password = Console.In.ReadLine()).Length <= 20)
                    break;
                Console.Out.WriteLine("Password must be less than 20 characters.");
            }

            admin.CreateAdministrator();
            admin.ReadAdministrator();
            admins.Add(admin);

            Console.Out.WriteLine("Admin successfully created!");
        }

        /// <summary>
        /// Make a backup of the database
        /// </summary>
        public void ExportDatabase()
        {
            try
            {
                File.Delete("C:\\Users\\Public\\backup.bak");
                string query = "BACKUP DATABASE Assignment1 TO DISK = 'C:\\Users\\Public\\backup.bak'";
                ExecuteSqlStatement(query);
                Console.Out.WriteLine("Database successfully backed up!");
            }
            catch (SqlException)
            {
                Console.Out.WriteLine("Could not export database!");
            }
            catch (FileNotFoundException)
            {
                //Do nothing if file is not found
            }
        }

        /// <summary>
        /// Deletes the current database
        /// </summary>
        public void DeleteDatabase()
        {
            try
            {
                ExecuteSqlStatement("USE master RESTORE DATABASE Assignment1 FROM DISK = 'C:\\Users\\Public\\assignment1_empty.bak'");
                RefreshCurrentDatabaseInstance();
                Console.Out.WriteLine("Database successfully deleted!");
            }
            catch (SqlException e)
            {
                Console.Out.WriteLine("Could not delete database!" + e.Message);
            }
        }

        /// <summary>
        /// Restores a backup of the database
        /// </summary>
        public void RestoreDatabase()
        {
            try
            {
                string query = "USE master RESTORE DATABASE Assignment1 FROM DISK = 'C:\\Users\\Public\\backup.bak'";
                ExecuteSqlStatement(query);
                RefreshCurrentDatabaseInstance();
                Console.Out.WriteLine("Database successfully restored!");
            }
            catch (SqlException e)
            {
                Console.Out.WriteLine("Could not restore database! " + e.Message);
            }
        }


        private void ExportToFile(IEnumerable<Transaction> transactions, string filename)
        {
            StreamWriter writer = new StreamWriter(filename, false);

            writer.Write("Transaction Id" + ",");
            writer.Write("Action" + ",");
            writer.Write("User Id" + ",");
            writer.Write("Amount" + "\n");
            foreach (Transaction t in transactions)
            {
                string type = t.TransactionTypeId == TransactionType.DEPOSIT_ID ? "Deposit" : "Withdraw";
                writer.Write(t.TransactionId + ",");
                writer.Write(t.TransactionTypeId + ",");
                writer.Write(t.PersonId + ",");
                writer.Write(t.AmountTransferred + "\n");
            }
            writer.Flush();
            writer.Close();
        }

        private decimal CalculateBalance()
        {
            decimal balance = 0m;
            var userRecords = (from li in transactions where li.PersonId == currentUser.PersonId select li);

            foreach (Transaction t in userRecords)
            {
                if (t.TransactionTypeId == TransactionType.DEPOSIT_ID)
                {
                    balance += t.AmountTransferred;
                }
                else if (t.TransactionTypeId == TransactionType.WITHDRAW_ID)
                {
                    balance -= t.AmountTransferred;
                }
            }
            return balance;
        }

        private void ExecuteSqlStatement(string query)
        {
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

        private void RefreshCurrentDatabaseInstance()
        {
            admins = Administrator.ReadAllAdministrators();
            transactions = Transaction.ReadAllTransactions();
            accounts = Person.ReadAllPeople();
        }

    }
}
