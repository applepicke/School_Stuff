using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    /// <summary>
    /// Page Load,
    /// 
    /// Fired every time the page is loaded or posted back upon itself
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack) // determine if this is the very first time the page is loaded, if it is -- bind the content
        {
            // access our data context
            ProgramDataContext db = new ProgramDataContext();

            // bind the data to the the drop down list
            programList.DataTextField = "ProgramName";  // the text value to be displayed to the user
            programList.DataValueField = "ProgramCode"; // the value that uniquely identifies the object being bound, usually a database id
            programList.DataSource = db.Programs;       // the collection we are binding
            programList.DataBind();                     // bind the data




            // bind information to the grid view
            automaticProgramGridView.DataSource = (from p in db.Programs                     // choose the data source
                                                   select p).Take(10);
            automaticProgramGridView.DataBind(); // bind the data




            // bind information to the grid view
            programGridView.DataSource = (from p in db.Programs                     // choose the data source
                                          select p).Take(10);
            programGridView.DataBind(); // bind the data




            // bind information to the grid view
            advancedBindingProgramGridView.DataSource = (from p in db.Programs                     // choose the data source
                                                        select p).Take(10);
            advancedBindingProgramGridView.DataBind(); // bind the data
        }
    }
}