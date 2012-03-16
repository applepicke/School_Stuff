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

    protected void StoreInformation(object sender, EventArgs e)
    {
        DataClassesDataContext context = new DataClassesDataContext();
        Registrant registrant = new Registrant();

        registrant.fname = fname.Text;
        registrant.lname = lname.Text;
        registrant.bday = bday.SelectedDate;
        registrant.occ = occupation.Text;
        registrant.telnum = number.Text;
        registrant.program = program.Text;
        registrant.games = "";
        foreach (ListItem game in gameList.Items)
        {
            if (game.Selected)
                registrant.games = registrant.games + game.Text + ", ";
        }
        registrant.description = description.Text;

        context.Registrants.InsertOnSubmit(registrant);
        context.SubmitChanges();

        Response.Redirect("~/Default.aspx");
    }
}