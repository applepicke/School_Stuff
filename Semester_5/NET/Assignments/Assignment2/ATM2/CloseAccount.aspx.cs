using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class CloseAccount : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void CloseUserAccount(object sender, EventArgs e)
    {
        try
        {
            ATMDataContext dc = new ATMDataContext();
            Person person = (from p in dc.Persons where p.PersonId == Int32.Parse(UserId.Text) && p.Password == Password.Text select p).First();
            Person sessionPerson = (Person)Session["Person"];

            if (person == null || person.PersonId != sessionPerson.PersonId || person.Password != sessionPerson.Password)
            {
                errors.Text = "Incorrect UserId or password";
                return;
            }

            dc.Persons.DeleteOnSubmit(person);
            dc.Transactions.DeleteAllOnSubmit((from t in dc.Transactions where t.PersonId == person.PersonId select t));

            dc.SubmitChanges();
            Response.Redirect("~/Default.aspx");
        }
        catch (FormatException)
        {
            errors.Text = "UserId must be a number!";
        }
        catch (InvalidOperationException)
        {
            errors.Text = "Incorrect UserId or Password!";
        }

    }
}