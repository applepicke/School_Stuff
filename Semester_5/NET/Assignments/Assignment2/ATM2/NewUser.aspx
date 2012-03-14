<%@ Page Language="C#" MasterPageFile="~/AtmMasterNoMenu.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="NewUser.aspx.cs" Inherits="NewUser" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">

    <h2>Create New User</h2>
    <table>
        <tr> 
            <td>
                <p>New UserId:</p> 
            </td>
            <td>
                <asp:TextBox ID="UserId" runat="server" />
                <asp:RequiredFieldValidator ControlToValidate="UserId" 
                                            CssClass="errors" 
                                            Display="Dynamic"
                                            ErrorMessage="UserId cannot be empty" 
                                            runat="server" />
                <asp:RegularExpressionValidator ControlToValidate="UserId"
                                                ValidationExpression=".{1,50}"
                                                CssClass="errors"
                                                Display="Dynamic"
                                                ErrorMessage="UserId must be between 1 and 50 characters"
                                                runat="server" />
            </td>
        </tr>
        <tr>
            <td>
                <p>Password: </p>
            </td>
            <td>
                <asp:TextBox ID="Password" runat="server" />
                <asp:RequiredFieldValidator ControlToValidate="Password" 
                                            CssClass="errors"
                                            Display="Dynamic" 
                                            ErrorMessage="Password cannot be empty" 
                                            runat="server" />
                <asp:RegularExpressionValidator ControlToValidate="Password"
                                                ValidationExpression=".{1,10}"
                                                CssClass="errors"
                                                Display="Dynamic"
                                                ErrorMessage="Password must be between 1 and 10 characters"
                                                runat="server" />

            </td>
        </tr>
    </table>
    <asp:Button ID="Submit" OnClick="CreateUser" Text="Register" runat="server" />

</asp:Content>