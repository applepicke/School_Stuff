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
        ATMDataContext context = new ATMDataContext();
        Person person = (from p in context.Persons where p.PersonId == Int32.Parse(UserId.Text) && p.Password == Password.Text select p).First();

        if (person == null)
        {
            errorMsg.Text = "Holy shit no! You suck.";
            return;
        }
        
        
    }
}