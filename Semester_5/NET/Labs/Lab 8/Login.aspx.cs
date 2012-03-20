using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Login : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void LoginUser(object sender, EventArgs e)
    {

        AccountInformationDataContext db = new AccountInformationDataContext();
        AccountInformation ai = (from _ai in db.AccountInformations where _ai.emailAddress == email.Text && _ai.password == password.Text select _ai).FirstOrDefault();

        if (ai != null)
            Session["AccountInformation"] = ai;

        Response.Redirect("~/Default.aspx");

    }
}