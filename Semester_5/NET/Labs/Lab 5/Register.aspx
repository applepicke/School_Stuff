<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Register.aspx.cs" Inherits="Register" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Registration</title>
    <style type="text/css">
        #errorLabel { color: Red; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <asp:HyperLink Text="Home" NavigateUrl="~/Default.aspx" runat="server" /> <br />
    <div>
        First Name: <asp:TextBox id="fname" runat="server"/> <br />
        Last Name: <asp:TextBox id="lname" runat="server"/> <br />
        Birthday: mm/dd/yy <asp:TextBox id="bday" MaxLength="10" runat="server"/> <br />
        Occupation: 
        <asp:DropDownList id="occupation" runat="server">
            <asp:ListItem Text="Student" />
            <asp:ListItem Text="Faculty" />
        </asp:DropDownList> 
        <br />
        Phone Number: <asp:TextBox id="number" runat="server" /> <br />
        Program of Study: <asp:TextBox id="program" runat="server" /> <br />
        <asp:Button id="submit" runat="server" Text="Submit" OnClick="checkInputs"/> <br />
        <asp:Label id="errorLabel" runat="server" />

    </div>
    </form>
</body>
</html>
