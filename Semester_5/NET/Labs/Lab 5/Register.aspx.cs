using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Lab5Model;

public partial class Register : System.Web.UI.Page
{
   
    

    protected void Page_Load(object sender, EventArgs e)
    {
    }

    public void checkInputs(object sender, EventArgs e)
    {
        if (fname.Text.Equals("") ||
            lname.Text.Equals("") ||
            bday.Text.Equals("") ||
            occupation.Equals("") ||
            number.Text.Equals("") ||
            program.Text.Equals(""))
        {
            errorLabel.Text = "There are missing fields!";
        }
        else
        {
            errorLabel.Text = "";
            try
            {
                Registrant registrant = new Registrant();
                registrant.fname = fname.Text;
                registrant.lname = lname.Text;
                registrant.bday = bday.Text;
                registrant.number = number.Text;
                registrant.program = program.Text;
                registrant.occupation = occupation.Text;
                Lab5Entities1 entities = new Lab5Entities1();
                entities.Registrants.AddObject(registrant);
                entities.SaveChanges();
                Response.Redirect("~/Register.aspx");

            }
            catch (Exception)
            {
                errorLabel.Text = "Error adding registrant";
            }
            
        }
    }
}