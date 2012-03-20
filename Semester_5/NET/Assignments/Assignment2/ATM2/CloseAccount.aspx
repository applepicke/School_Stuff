<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" AutoEventWireup="true" Theme="AtmTheme" CodeFile="CloseAccount.aspx.cs" Inherits="CloseAccount" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">
    <h2>Close Account</h2>
    <table>
        <tr> 
            <td>
                <p>UserId:</p> 
            </td>
            <td>
                <asp:TextBox ID="UserId" runat="server" />
                <asp:RequiredFieldValidator ControlToValidate="UserId" 
                                            CssClass="errors" 
                                            Display="Dynamic"
                                            ErrorMessage="UserId cannot be empty" 
                                            runat="server" />
            </td>
        </tr>
        <tr>
            <td>
                <p>Password: </p>
            </td>
            <td>
                <asp:TextBox ID="Password" TextMode="Password" runat="server" />
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="Password" 
                                            CssClass="errors"
                                            Display="Dynamic" 
                                            ErrorMessage="Password cannot be empty" 
                                            runat="server" />
                <asp:Label ID="errors" CssClass="errors" runat="server" />
            </td>
        </tr>
    </table>
    <asp:Button ID="Submit" OnClick="CloseUserAccount" Text="Close Account" runat="server" />
</asp:Content>