<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="ControlsAndEvents.aspx.cs" Inherits="ControlsAndEvents" %>

<%@ Register TagPrefix="userControl" TagName="MyFirstControl" Src="Controls/WebUserControl.ascx" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <h2>My User Control</h2>
    <userControl:MyFirstControl runat="server" ButtonText="Press this button now" />
</asp:Content>

