﻿#pragma warning disable 1591
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Linq;
using System.Data.Linq.Mapping;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;



[global::System.Data.Linq.Mapping.DatabaseAttribute(Name="ATM")]
public partial class ProgramDataContext : System.Data.Linq.DataContext
{
	
	private static System.Data.Linq.Mapping.MappingSource mappingSource = new AttributeMappingSource();
	
  #region Extensibility Method Definitions
  partial void OnCreated();
  partial void InsertProgram(Program instance);
  partial void UpdateProgram(Program instance);
  partial void DeleteProgram(Program instance);
  #endregion
	
	public ProgramDataContext() : 
			base(global::System.Configuration.ConfigurationManager.ConnectionStrings["ATMConnectionString"].ConnectionString, mappingSource)
	{
		OnCreated();
	}
	
	public ProgramDataContext(string connection) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public ProgramDataContext(System.Data.IDbConnection connection) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public ProgramDataContext(string connection, System.Data.Linq.Mapping.MappingSource mappingSource) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public ProgramDataContext(System.Data.IDbConnection connection, System.Data.Linq.Mapping.MappingSource mappingSource) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public System.Data.Linq.Table<Program> Programs
	{
		get
		{
			return this.GetTable<Program>();
		}
	}
}

[global::System.Data.Linq.Mapping.TableAttribute(Name="dbo.Programs")]
public partial class Program : INotifyPropertyChanging, INotifyPropertyChanged
{
	
	private static PropertyChangingEventArgs emptyChangingEventArgs = new PropertyChangingEventArgs(String.Empty);
	
	private System.DateTime _StartDate;
	
	private string _ProgramCode;
	
	private string _ProgramName;
	
    #region Extensibility Method Definitions
    partial void OnLoaded();
    partial void OnValidate(System.Data.Linq.ChangeAction action);
    partial void OnCreated();
    partial void OnStartDateChanging(System.DateTime value);
    partial void OnStartDateChanged();
    partial void OnProgramCodeChanging(string value);
    partial void OnProgramCodeChanged();
    partial void OnProgramNameChanging(string value);
    partial void OnProgramNameChanged();
    #endregion
	
	public Program()
	{
		OnCreated();
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_StartDate", DbType="DateTime NOT NULL", IsPrimaryKey=true)]
	public System.DateTime StartDate
	{
		get
		{
			return this._StartDate;
		}
		set
		{
			if ((this._StartDate != value))
			{
				this.OnStartDateChanging(value);
				this.SendPropertyChanging();
				this._StartDate = value;
				this.SendPropertyChanged("StartDate");
				this.OnStartDateChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_ProgramCode", DbType="VarChar(50) NOT NULL", CanBeNull=false, IsPrimaryKey=true)]
	public string ProgramCode
	{
		get
		{
			return this._ProgramCode;
		}
		set
		{
			if ((this._ProgramCode != value))
			{
				this.OnProgramCodeChanging(value);
				this.SendPropertyChanging();
				this._ProgramCode = value;
				this.SendPropertyChanged("ProgramCode");
				this.OnProgramCodeChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_ProgramName", DbType="VarChar(150)")]
	public string ProgramName
	{
		get
		{
			return this._ProgramName;
		}
		set
		{
			if ((this._ProgramName != value))
			{
				this.OnProgramNameChanging(value);
				this.SendPropertyChanging();
				this._ProgramName = value;
				this.SendPropertyChanged("ProgramName");
				this.OnProgramNameChanged();
			}
		}
	}
	
	public event PropertyChangingEventHandler PropertyChanging;
	
	public event PropertyChangedEventHandler PropertyChanged;
	
	protected virtual void SendPropertyChanging()
	{
		if ((this.PropertyChanging != null))
		{
			this.PropertyChanging(this, emptyChangingEventArgs);
		}
	}
	
	protected virtual void SendPropertyChanged(String propertyName)
	{
		if ((this.PropertyChanged != null))
		{
			this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
		}
	}
}
#pragma warning restore 1591
