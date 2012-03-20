using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void Login(object sender, EventArgs e)
    {
        try
        {
            ATMDataContext context = new ATMDataContext();
            Person person = (from p in context.Persons where p.PersonId == Int32.Parse(UserId.Text) && p.Password == Password.Text select p).First();

            if (person == null)
            {
                errorMsg.Text = "UserId or password is incorrect!";
                return;
            }

            person.LastLoginDateTime = DateTime.Now;
            context.SubmitChanges();

            Session["Person"] = person;
            Response.Redirect("~/Overview.aspx");
        }
        catch (FormatException)
        {
            errorMsg.Text = "UserId must be a number!";
        }
        catch (InvalidOperationException)
        {
            errorMsg.Text = "Incorrect UserId or Password!";
        }
        
    }
}