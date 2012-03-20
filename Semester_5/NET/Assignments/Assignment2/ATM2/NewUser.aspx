<%@ Page Language="C#" MasterPageFile="~/AtmMasterNoMenu.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="NewUser.aspx.cs" Inherits="NewUser" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">

    <h2>Create New User</h2>
    <table>
        <tr> 
            <td>
                <p>First Name:</p> 
            </td>
            <td>
                <asp:TextBox ID="fName" runat="server" />
                <asp:RequiredFieldValidator ControlToValidate="fName" 
                                            CssClass="errors" 
                                            Display="Dynamic"
                                            ErrorMessage="UserId cannot be empty" 
                                            runat="server" />
                <asp:RegularExpressionValidator ControlToValidate="fName"
                                                ValidationExpression=".{1,50}"
                                                CssClass="errors"
                                                Display="Dynamic"
                                                ErrorMessage="UserId must be between 1 and 50 characters"
                                                runat="server" />
            </td>
        </tr>
        <tr> 
            <td>
                <p>Last Name:</p> 
            </td>
            <td>
                <asp:TextBox ID="lName" runat="server" />
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="lName" 
                                            CssClass="errors" 
                                            Display="Dynamic"
                                            ErrorMessage="UserId cannot be empty" 
                                            runat="server" />
                <asp:RegularExpressionValidator ID="RegularExpressionValidator1" ControlToValidate="lName"
                                                ValidationExpression=".{1,50}"
                                                CssClass="errors"
                                                Display="Dynamic"
                                                ErrorMessage="UserId must be between 1 and 50 characters"
                                                runat="server" />
            </td>
        </tr>
        <tr> 
            <td>
                <p>Email:</p> 
            </td>
            <td>
                <asp:TextBox ID="email" runat="server" />
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="email" 
                                            CssClass="errors" 
                                            Display="Dynamic"
                                            ErrorMessage="UserId cannot be empty" 
                                            runat="server" />
                <asp:RegularExpressionValidator ID="RegularExpressionValidator2" ControlToValidate="email"
                                                ValidationExpression=".{1,255}"
                                                CssClass="errors"
                                                Display="Dynamic"
                                                ErrorMessage="UserId must be between 1 and 255 characters"
                                                runat="server" />
            </td>
        </tr>
        <tr>
            <td>
                <p>Password: </p>
            </td>
            <td>
                <asp:TextBox ID="Password" TextMode="Password" runat="server" />
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
        <tr> 
            <td>
                <p>SIN:</p> 
            </td>
            <td>
                <asp:TextBox ID="sin" runat="server" />
                <asp:RequiredFieldValidator ID="RequiredFieldValidator3" ControlToValidate="sin" 
                                            CssClass="errors" 
                                            Display="Dynamic"
                                            ErrorMessage="UserId cannot be empty" 
                                            runat="server" />
                <asp:RegularExpressionValidator ID="RegularExpressionValidator3" ControlToValidate="sin"
                                                ValidationExpression=".{1,50}"
                                                CssClass="errors"
                                                Display="Dynamic"
                                                ErrorMessage="UserId must be between 1 and 11 characters"
                                                runat="server" />
            </td>
        </tr>
    </table>
    <asp:Button ID="Submit" OnClick="CreateUser" Text="Register" runat="server" />

</asp:Content>