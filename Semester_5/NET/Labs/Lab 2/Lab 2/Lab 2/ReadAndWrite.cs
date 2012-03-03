using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Lab_2
{
    class ReadAndWrite
    {
        static void Main(string[] args)
        {
            try
            {
                String inputText = GetFileContents("input.txt");
                String userSelection;
                while (true)
                {
                    Console.Out.WriteLine("1. Print input.txt to screen");
                    Console.Out.WriteLine("2. Write modified input.txt to output.txt");
                    Console.Out.WriteLine("3. Exit");

                    userSelection = Console.In.ReadLine();
                    if (userSelection.Equals("1"))
                    {
                        Console.Out.WriteLine(inputText);
                    }
                    else if (userSelection.Equals("2"))
                    {
                        StreamWriter outputTextWriter = new StreamWriter("output.txt");
                        outputTextWriter.Write(CapitalizeEvenLetters(inputText));
                        outputTextWriter.Close();
                        Console.Out.WriteLine("output.txt written successfully!\n");
                    }
                    else if (userSelection.Equals("3"))
                    {
                        Console.Out.WriteLine("Toodles!!");
                        Environment.Exit(0);
                    }
                    else
                    {
                        Console.Out.WriteLine("That is not a valid choice!\n");
                    }
                }
            }
            catch (IOException e)
            {
                Console.Out.WriteLine("IO Error: " + e.Message);
                Environment.Exit(1);
            }
          
        }

        /// <summary>
        /// Given a filename, open that file and return a string of it's contents
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns>A string of the file's content</returns>
        static String GetFileContents(String fileName)
        {
            String contents = null;
            try
            {
                StreamReader fileReader = new StreamReader(fileName);
                contents = fileReader.ReadToEnd();
                fileReader.Close();
            }
            catch (IOException)
            {
                throw new IOException();
            }
            return contents;

        }

        /// <summary>
        /// Convert every other letter in a string to uppercase.
        /// </summary>
        /// <param name="stringToConvert">The string to be converted</param>
        /// <returns>The resulting string after conversion</returns>
        static String CapitalizeEvenLetters(String stringToConvert)
        {
            int characterPosition = 1;
            StringBuilder builder = new StringBuilder();
            foreach (char c in stringToConvert)
            {
                //Every second character is converted to uppercase
                if (characterPosition % 2 == 0)
                {
                    builder.Append(Char.ToUpper(c));
                }
                else
                {
                    builder.Append(c);
                }
                characterPosition++;
            }
            return builder.ToString();
        }
    }
}
