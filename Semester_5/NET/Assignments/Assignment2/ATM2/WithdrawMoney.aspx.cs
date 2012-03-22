using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class WithdrawMoney : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void WithdrawAmount(object sender, EventArgs e)
    {
        ATMDataContext dc = new ATMDataContext();
        Transaction trans = new Transaction();
        trans.TransactionTypeId = 2;
        trans.DateOfTransaction = DateTime.Now;

        try
        {
            trans.PersonId = ((Person)Session["Person"]).PersonId;
            trans.AmountTransferred = Decimal.Parse(Withdraw.Text);
            if (trans.AmountTransferred < 0)
            {
                errors.Text = "Cannot withdraw negative amount!";
                return;
            }
        }
        catch (FormatException)
        {
            errors.Text = "That is not a valid number!";
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