<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" Theme="SkinFile"%>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <div>
        <table>
            <tr>
                <td>
                    First Name:
                </td>
                <td>
                    <asp:TextBox ID="fname" runat="server" />
                    <asp:RequiredFieldValidator runat="server" ControlToValidate="fname"/>
                </td>
            </tr>
            <tr>
                <td>
                    Last Name:
                </td>
                <td>
                    <asp:TextBox ID="lname" runat="server" />
                    <asp:RequiredFieldValidator runat="server" ControlToValidate="lname" />
                </td>
            </tr>
            <tr>
                <td>
                    Birthday: (mm/dd/yyyy)
                </td>
                <td>
                    <asp:Calendar ID="bday" runat="server" />
                </td>
            </tr>
            <tr>
                <td>
                    Occupation:
                </td>
                <td>
                    <asp:DropDownList ID="occupation" runat="server">
                        <asp:ListItem Text="Student" />
                        <asp:ListItem Text="Staff" />
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td>
                    Phone Number:
                </td>
                <td>
                    <asp:TextBox ID="number" runat="server" />
                    <asp:RequiredFieldValidator runat="server" ControlToValidate="number"/>
                    <asp:RegularExpressionValidator runat="server" ControlToValidate="number" ValidationExpression="[0-9]{3}-[0-9]{3}-[0-9]{4}" ErrorMessage="Does not match format (nnn-nnn-nnnn)"/>
                </td>
            </tr>
            <tr>
                <td>
                    Program of Study:
                </td>
                <td>
                    <asp:TextBox ID="program" runat="server" />
                </td>
            </tr>
            <tr>
                <td>
                    Video Game of Choice:
                </td>
                <td>
                    <asp:CheckBoxList ID="gameList" runat="server">
                        <asp:ListItem Text="Donkey Kong" />
                        <asp:ListItem Text="Super Mario Bros." />
                        <asp:ListItem Text="Yoshi's Island" />
                        <asp:ListItem Text="Super Metroid" />
                    </asp:CheckBoxList>
                </td>
            </tr>
            <tr>
                <td>
                    Description:
                </td>
                <td>
                    <asp:TextBox id="description" TextMode="MultiLine" runat="server" Width="300" Height="100" />
                </td>
            </tr>
        </table>
        <asp:Button id="submit" Text="Submit" runat="server" OnClick="StoreInformation" />
        
    </div>
</asp:Content>
