<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Login.aspx.cs" Inherits="Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        Email Address: <asp:TextBox ID="email" runat="server" /><br />
        Password: <asp:TextBox ID="password" TextMode="Password" runat="server" /><br />
        <asp:Button ID="login" runat="server" OnClick="LoginUser" Text="Login" />
        <asp:Button ID="create" runat="server" Text="Register" PostBackUrl="~/Create.aspx"/>
    </div>
    </form>
</body>
</html>
