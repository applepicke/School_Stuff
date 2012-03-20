using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class DepositMoney : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void DepositAmount(object sender, EventArgs e)
    {
        ATMDataContext dc = new ATMDataContext();
        Transaction trans = new Transaction();
        trans.TransactionTypeId = 1;
        trans.DateOfTransaction = DateTime.Now;

        try
        {
            trans.PersonId = ((Person)Session["Person"]).PersonId;
            trans.AmountTransferred = Decimal.Parse(Deposit.Text);
        }
        catch (FormatException)
        {
            errors.Text = "That is not a valid number";
            return;
        }
        catch (OverflowException)
        {
            errors.Text = "Number is too large!";
            return;
        }
        dc.Transactions.InsertOnSubmit(trans);
        dc.SubmitChanges();
        Response.Redirect("~/Overview.aspx");
    }
}