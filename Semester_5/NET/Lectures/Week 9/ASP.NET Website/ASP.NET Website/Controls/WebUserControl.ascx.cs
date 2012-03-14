using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class WebUserControl : System.Web.UI.UserControl
{
    public string ButtonText
    {
        get
        {
            return this.button.Text;
        }
        set
        {
            this.button.Text = value;
        }
    }

    protected void Page_Load(object sender, EventArgs e)
    {
    }
}