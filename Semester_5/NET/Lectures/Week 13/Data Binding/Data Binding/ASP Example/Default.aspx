<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
    <head runat="server">
        <title></title>
    </head>
    <body>
        <form id="form1" runat="server">
            <asp:DropDownList ID="programList" runat="server" />
            <br />
            <br />
            <br />
            <asp:GridView ID="automaticProgramGridView" runat="server" AutoGenerateColumns="true" />
            <br />
            <br />
            <br />
            <asp:GridView ID="programGridView" runat="server" AutoGenerateColumns="false">
                <Columns>
                    <asp:BoundField DataField="StartDate" HeaderText="Fall Start Date" />
                    <asp:BoundField DataField="ProgramCode" HeaderText="Program Code" />
                    <asp:BoundField DataField="ProgramName" HeaderText="Program Name" />
                </Columns>
            </asp:GridView>
            <br />
            <br />
            <br />
            <asp:GridView ID="advancedBindingProgramGridView" runat="server" AutoGenerateColumns="false" ShowHeader="true" ShowFooter="true">
                <Columns>
                    <asp:TemplateField>
                        <HeaderTemplate>
                            <b>Start Date</b>
                        </HeaderTemplate>
                        
                        <ItemTemplate>
                            The start date is: <%# Eval("StartDate") %>
                        </ItemTemplate>

                        <FooterTemplate>
                            <b>Start Date</b>
                        </FooterTemplate>
                    </asp:TemplateField>
                    
                    <asp:TemplateField>
                        <HeaderTemplate>
                            <b>Program Code</b>
                        </HeaderTemplate>
                        
                        <ItemTemplate>
                            The formal program code is: <%# Eval("ProgramCode") %>
                        </ItemTemplate>

                        <FooterTemplate>
                            <b>Program Code</b>
                        </FooterTemplate>
                    </asp:TemplateField>
                    
                    <asp:TemplateField>
                        <HeaderTemplate>
                            <b>Program Name</b>
                        </HeaderTemplate>
                        
                        <ItemTemplate>
                            The name of the program is:<br /><%# Eval("ProgramName") %>
                        </ItemTemplate>

                        <FooterTemplate>
                            <b>Program Name</b>
                        </FooterTemplate>
                    </asp:TemplateField>
                </Columns>
            </asp:GridView>
        </form>
    </body>
</html>
