using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Cryptography;

namespace Assignment1
{
    class Encryption
    {

        public static string EncryptMD5(string text)
        {

            MD5CryptoServiceProvider encryptor = new MD5CryptoServiceProvider();
            byte[] textBytes = Encoding.UTF8.GetBytes(text);
            byte[] bytes = encryptor.ComputeHash(textBytes);

            string encryptedString = BitConverter.ToString(bytes).Replace("-", "").Substring(0, 9);

            return encryptedString.ToString();

        }


    }
}
