<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Create.aspx.cs" Inherits="Create" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        Email: <asp:TextBox ID="email" runat="server"/> <br />
        First Name: <asp:TextBox ID="fName" runat="server" /> <br />
        Last Name: <asp:TextBox ID="lName" runat="server" /> <br />
        Password: <asp:TextBox TextMode="Password" ID="password" runat="server" /> <br />

        <asp:Button ID="submit" OnClick="Submit" Text="Submit" runat="server" />
    </div>
    </form>
</body>
</html>
