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

        DataClassesDataContext dc = new DataClassesDataContext();
        gridView.DataSource = dc.Registrants;
        gridView.DataBind();

    }

    protected void UpdateData(object sender, EventArgs e)
    {
        DataClassesDataContext dc = new DataClassesDataContext();
        if (dropDown.SelectedIndex == 0)
        {
            gridView.DataSource = (from r in dc.Registrants select r).Take(3);
        }
        else if (dropDown.SelectedIndex == 1)
        {
            gridView.DataSource = (from r in dc.Registrants select r).Take(5);
        }
        else 
        {
            gridView.DataSource = (from r in dc.Registrants select r).Take(10);
        }
        gridView.DataBind();
        
    }

}