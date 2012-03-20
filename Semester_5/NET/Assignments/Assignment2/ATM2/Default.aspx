<%@ Page Language="C#" MasterPageFile="~/AtmMasterNoMenu.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" Theme="AtmTheme" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">
    
    <table>
        <tr>
            <td>
                <p>UserId:</p>
            </td>
            <td>
                <asp:TextBox ID="UserId" runat="server"/>
                <asp:RequiredFieldValidator ValidationGroup="LoginValidation" 
                                            ControlToValidate="UserId" 
                                            CssClass="errors" 
                                            ErrorMessage="UserId must not be empty" 
                                            runat="server"/>
            </td>
        </tr>
        <tr>
            <td>
                <p>Password:</p>
            </td>
            <td>
                <asp:TextBox TextMode="Password" ID="Password" runat="server" />
                <asp:RequiredFieldValidator ValidationGroup="LoginValidation" 
                                            ControlToValidate="Password" 
                                            CssClass="errors" 
                                            ErrorMessage="Password must not be empty" 
                                            runat="server" />
            </td>
        </tr> 
    </table>
    <asp:Label id="errorMsg" CssClass="errors" runat="server"/><br />
    <asp:Button ValidationGroup="LoginValidation" Text="Login" OnClick="Login" runat="server" />
    <asp:Button Text="Register" PostBackUrl="~/NewUser.aspx" runat="server"/>

</asp:Content>
