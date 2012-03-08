﻿#pragma warning disable 1591
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.261
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



[global::System.Data.Linq.Mapping.DatabaseAttribute(Name="Lab6")]
public partial class DataClassesDataContext : System.Data.Linq.DataContext
{
	
	private static System.Data.Linq.Mapping.MappingSource mappingSource = new AttributeMappingSource();
	
  #region Extensibility Method Definitions
  partial void OnCreated();
  partial void InsertRegistrant(Registrant instance);
  partial void UpdateRegistrant(Registrant instance);
  partial void DeleteRegistrant(Registrant instance);
  #endregion
	
	public DataClassesDataContext() : 
			base(global::System.Configuration.ConfigurationManager.ConnectionStrings["Lab6ConnectionString"].ConnectionString, mappingSource)
	{
		OnCreated();
	}
	
	public DataClassesDataContext(string connection) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public DataClassesDataContext(System.Data.IDbConnection connection) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public DataClassesDataContext(string connection, System.Data.Linq.Mapping.MappingSource mappingSource) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public DataClassesDataContext(System.Data.IDbConnection connection, System.Data.Linq.Mapping.MappingSource mappingSource) : 
			base(connection, mappingSource)
	{
		OnCreated();
	}
	
	public System.Data.Linq.Table<Registrant> Registrants
	{
		get
		{
			return this.GetTable<Registrant>();
		}
	}
}

[global::System.Data.Linq.Mapping.TableAttribute(Name="dbo.Registrant")]
public partial class Registrant : INotifyPropertyChanging, INotifyPropertyChanged
{
	
	private static PropertyChangingEventArgs emptyChangingEventArgs = new PropertyChangingEventArgs(String.Empty);
	
	private string _fname;
	
	private string _lname;
	
	private System.DateTime _bday;
	
	private string _occ;
	
	private string _telnum;
	
	private string _program;
	
	private string _games;
	
	private string _description;
	
	private int _id;
	
    #region Extensibility Method Definitions
    partial void OnLoaded();
    partial void OnValidate(System.Data.Linq.ChangeAction action);
    partial void OnCreated();
    partial void OnfnameChanging(string value);
    partial void OnfnameChanged();
    partial void OnlnameChanging(string value);
    partial void OnlnameChanged();
    partial void OnbdayChanging(System.DateTime value);
    partial void OnbdayChanged();
    partial void OnoccChanging(string value);
    partial void OnoccChanged();
    partial void OntelnumChanging(string value);
    partial void OntelnumChanged();
    partial void OnprogramChanging(string value);
    partial void OnprogramChanged();
    partial void OngamesChanging(string value);
    partial void OngamesChanged();
    partial void OndescriptionChanging(string value);
    partial void OndescriptionChanged();
    partial void OnidChanging(int value);
    partial void OnidChanged();
    #endregion
	
	public Registrant()
	{
		OnCreated();
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_fname", DbType="VarChar(50) NOT NULL", CanBeNull=false)]
	public string fname
	{
		get
		{
			return this._fname;
		}
		set
		{
			if ((this._fname != value))
			{
				this.OnfnameChanging(value);
				this.SendPropertyChanging();
				this._fname = value;
				this.SendPropertyChanged("fname");
				this.OnfnameChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_lname", DbType="VarChar(50) NOT NULL", CanBeNull=false)]
	public string lname
	{
		get
		{
			return this._lname;
		}
		set
		{
			if ((this._lname != value))
			{
				this.OnlnameChanging(value);
				this.SendPropertyChanging();
				this._lname = value;
				this.SendPropertyChanged("lname");
				this.OnlnameChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_bday", DbType="Date NOT NULL")]
	public System.DateTime bday
	{
		get
		{
			return this._bday;
		}
		set
		{
			if ((this._bday != value))
			{
				this.OnbdayChanging(value);
				this.SendPropertyChanging();
				this._bday = value;
				this.SendPropertyChanged("bday");
				this.OnbdayChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_occ", DbType="VarChar(50) NOT NULL", CanBeNull=false)]
	public string occ
	{
		get
		{
			return this._occ;
		}
		set
		{
			if ((this._occ != value))
			{
				this.OnoccChanging(value);
				this.SendPropertyChanging();
				this._occ = value;
				this.SendPropertyChanged("occ");
				this.OnoccChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_telnum", DbType="VarChar(50) NOT NULL", CanBeNull=false)]
	public string telnum
	{
		get
		{
			return this._telnum;
		}
		set
		{
			if ((this._telnum != value))
			{
				this.OntelnumChanging(value);
				this.SendPropertyChanging();
				this._telnum = value;
				this.SendPropertyChanged("telnum");
				this.OntelnumChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_program", DbType="VarChar(50) NOT NULL", CanBeNull=false)]
	public string program
	{
		get
		{
			return this._program;
		}
		set
		{
			if ((this._program != value))
			{
				this.OnprogramChanging(value);
				this.SendPropertyChanging();
				this._program = value;
				this.SendPropertyChanged("program");
				this.OnprogramChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_games", DbType="VarChar(500)")]
	public string games
	{
		get
		{
			return this._games;
		}
		set
		{
			if ((this._games != value))
			{
				this.OngamesChanging(value);
				this.SendPropertyChanging();
				this._games = value;
				this.SendPropertyChanged("games");
				this.OngamesChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_description", DbType="VarChar(500)")]
	public string description
	{
		get
		{
			return this._description;
		}
		set
		{
			if ((this._description != value))
			{
				this.OndescriptionChanging(value);
				this.SendPropertyChanging();
				this._description = value;
				this.SendPropertyChanged("description");
				this.OndescriptionChanged();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_id", AutoSync=AutoSync.OnInsert, DbType="Int NOT NULL IDENTITY", IsPrimaryKey=true, IsDbGenerated=true)]
	public int id
	{
		get
		{
			return this._id;
		}
		set
		{
			if ((this._id != value))
			{
				this.OnidChanging(value);
				this.SendPropertyChanging();
				this._id = value;
				this.SendPropertyChanged("id");
				this.OnidChanged();
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
