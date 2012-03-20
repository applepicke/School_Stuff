using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Create : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void Submit(object sender, EventArgs e)
    {
        AccountInformationDataContext dc = new AccountInformationDataContext();
        AccountInformation info = new AccountInformation();
        info.emailAddress = email.Text;
        info.firstName = fName.Text;
        info.lastName = lName.Text;
        info.password = password.Text;
        dc.AccountInformations.InsertOnSubmit(info);
        dc.SubmitChanges();
        Response.Redirect("~/Create.aspx");
    }
}