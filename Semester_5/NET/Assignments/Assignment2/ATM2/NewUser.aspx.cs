using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class NewUser : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void CreateUser(object sender, EventArgs e)
    {
        ATMDataContext dc = new ATMDataContext();
        Person person = new Person();
        person.FirstName = fName.Text;
        person.LastName = lName.Text;
        person.EmailAddress = email.Text;
        person.Password = Password.Text;
        person.SIN = sin.Text;
        person.DateAccountCreated = DateTime.Now;
        person.LastLoginDateTime = DateTime.Now;

        dc.Persons.InsertOnSubmit(person);
        dc.SubmitChanges();

        Session["Person"] = person;
        Response.Redirect("~/Overview.aspx");
    }
}