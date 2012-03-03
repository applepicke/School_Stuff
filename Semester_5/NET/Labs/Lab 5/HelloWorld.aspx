<%@ Page Language="C#" AutoEventWireup="true" CodeFile="HelloWorld.aspx.cs" Inherits="HelloWorld" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Hello World</title>
    <style type="text/css">
        h1 { color:Orange; }
        div { background-color:Blue; color:Yellow; }     
    </style> 
</head>
<body>
    <form id="form1" runat="server">
    <asp:HyperLink NavigateUrl="~/Default.aspx" Text="Home" runat="server" /> <br />
    <h1>Hello World</h1>
    <div>
        This is my first ASP.NET Website
    </div>
    </form>
</body>
</html>
