using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Overview : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        ATMDataContext dc = new ATMDataContext();
        overviewGrid.DataSource = (from t in dc.Transactions orderby t.DateOfTransaction descending select t).Take(3);
        overviewGrid.DataBind();

        decimal balanceTotal = 0;
        foreach (Transaction t in dc.Transactions)
        {
            if (t.TransactionTypeId == 1)
            {
                balanceTotal += t.AmountTransferred;
            }
            if (t.TransactionTypeId == 2)
            {
                balanceTotal -= t.AmountTransferred;
            }
        }
        balance.Text = balanceTotal.ToString();
    }
}