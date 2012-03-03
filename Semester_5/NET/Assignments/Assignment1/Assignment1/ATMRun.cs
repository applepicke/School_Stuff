using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assignment1
{
    class ATMRun
    {
        public static void Main(string []args)
        {            
            ATM atm = new ATM();

            Console.Out.WriteLine("****************************************");
            Console.Out.WriteLine("      [.       [... [......[..       [..");
            Console.Out.WriteLine("     [. ..          [..    [. [..   [...");
            Console.Out.WriteLine("    [.  [..         [..    [.. [.. [ [..");
            Console.Out.WriteLine("   [..   [..        [..    [..  [..  [..");
            Console.Out.WriteLine("  [...... [..       [..    [..   [.  [..");
            Console.Out.WriteLine(" [..       [..      [..    [..       [..");
            Console.Out.WriteLine("[..         [..     [..    [..       [..");
            Console.Out.WriteLine("****************************************");

            while (true)
            {
                Console.Out.WriteLine("1 - Create New Account");
                Console.Out.WriteLine("2 - User Login");
                Console.Out.WriteLine("3 - Admin Login");
                Console.Out.WriteLine("4 - Exit");

                string choice = Console.In.ReadLine();

                if (choice.Equals("1"))
                {
                    atm.CreateAccount();
                }
                if (choice.Equals("2"))
                {
                    if (atm.Login())
                    {
                        LoginUser(atm);
                    }
                }
                if (choice.Equals("3"))
                {
                    if (atm.LoginAdmin())
                    {
                        LoginAdmin(atm);
                    }
                }
                if (choice.Equals("4"))
                {
                    Environment.Exit(0);
                }
            }
        }

        private static void LoginUser(ATM atm)
        {
            Console.Out.WriteLine();
            Console.Out.WriteLine("You are currently logged in as: " + atm.currentUser.FirstName + " " + atm.currentUser.LastName);

            while (true)
            {
                Console.Out.WriteLine("1 - Deposit");
                Console.Out.WriteLine("2 - Withdraw");
                Console.Out.WriteLine("3 - Check Balance");
                Console.Out.WriteLine("4 - Show Report");
                Console.Out.WriteLine("5 - Close Account");
                Console.Out.WriteLine("6 - Logout");

                string choice = Console.In.ReadLine();

                if (choice.Equals("1")){
                    atm.Deposit();
                }
                if (choice.Equals("2")){
                    atm.Withdraw();
                }
                if (choice.Equals("3")){
                    atm.CheckBalance();
                }
                if (choice.Equals("4")){
                    atm.Report();
                }
                if (choice.Equals("5")){
                    atm.CloseAccount();
                    break;
                }
                if (choice.Equals("6")){
                    atm.Logout();
                    Console.Out.WriteLine("Successfully logged out!");
                    break;
                }
            }
        }

        private static void LoginAdmin(ATM atm)
        {
            while (true)
            {
                Console.Out.WriteLine("1 - Create new admin");
                Console.Out.WriteLine("2 - Export Database");
                Console.Out.WriteLine("3 - Delete Database");
                Console.Out.WriteLine("4 - Restore Database");
                Console.Out.WriteLine("5 - Logout");

                string input = Console.In.ReadLine();

                if (input.Equals("1"))
                {
                    atm.CreateAdmin();
                }
                if (input.Equals("2"))
                {
                    atm.ExportDatabase();
                }
                if (input.Equals("3"))
                {
                    atm.DeleteDatabase();
                }
                if (input.Equals("4"))
                {
                    atm.RestoreDatabase();
                }
                if (input.Equals("5"))
                {
                    atm.LogoutAdmin();
                    Console.Out.WriteLine("Logged off!");
                    break;
                }


            }
        }

    }
}
