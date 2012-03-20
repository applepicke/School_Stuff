using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Report : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        ATMDataContext db = new ATMDataContext();
        transactionGrid.DataSource = db.Transactions;
        transactionGrid.DataBind();
    }
}