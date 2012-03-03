﻿//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Data.Objects;
using System.Data.Objects.DataClasses;
using System.Data.EntityClient;
using System.ComponentModel;
using System.Xml.Serialization;
using System.Runtime.Serialization;

[assembly: EdmSchemaAttribute()]

namespace Lab5Model
{
    #region Contexts
    
    /// <summary>
    /// No Metadata Documentation available.
    /// </summary>
    public partial class Lab5Entities1 : ObjectContext
    {
        #region Constructors
    
        /// <summary>
        /// Initializes a new Lab5Entities1 object using the connection string found in the 'Lab5Entities1' section of the application configuration file.
        /// </summary>
        public Lab5Entities1() : base("name=Lab5Entities1", "Lab5Entities1")
        {
            this.ContextOptions.LazyLoadingEnabled = true;
            OnContextCreated();
        }
    
        /// <summary>
        /// Initialize a new Lab5Entities1 object.
        /// </summary>
        public Lab5Entities1(string connectionString) : base(connectionString, "Lab5Entities1")
        {
            this.ContextOptions.LazyLoadingEnabled = true;
            OnContextCreated();
        }
    
        /// <summary>
        /// Initialize a new Lab5Entities1 object.
        /// </summary>
        public Lab5Entities1(EntityConnection connection) : base(connection, "Lab5Entities1")
        {
            this.ContextOptions.LazyLoadingEnabled = true;
            OnContextCreated();
        }
    
        #endregion
    
        #region Partial Methods
    
        partial void OnContextCreated();
    
        #endregion
    
        #region ObjectSet Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        public ObjectSet<Registrant> Registrants
        {
            get
            {
                if ((_Registrants == null))
                {
                    _Registrants = base.CreateObjectSet<Registrant>("Registrants");
                }
                return _Registrants;
            }
        }
        private ObjectSet<Registrant> _Registrants;

        #endregion
        #region AddTo Methods
    
        /// <summary>
        /// Deprecated Method for adding a new object to the Registrants EntitySet. Consider using the .Add method of the associated ObjectSet&lt;T&gt; property instead.
        /// </summary>
        public void AddToRegistrants(Registrant registrant)
        {
            base.AddObject("Registrants", registrant);
        }

        #endregion
    }
    

    #endregion
    
    #region Entities
    
    /// <summary>
    /// No Metadata Documentation available.
    /// </summary>
    [EdmEntityTypeAttribute(NamespaceName="Lab5Model", Name="Registrant")]
    [Serializable()]
    [DataContractAttribute(IsReference=true)]
    public partial class Registrant : EntityObject
    {
        #region Factory Method
    
        /// <summary>
        /// Create a new Registrant object.
        /// </summary>
        /// <param name="id">Initial value of the id property.</param>
        public static Registrant CreateRegistrant(global::System.Int32 id)
        {
            Registrant registrant = new Registrant();
            registrant.id = id;
            return registrant;
        }

        #endregion
        #region Primitive Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=true)]
        [DataMemberAttribute()]
        public global::System.String fname
        {
            get
            {
                return _fname;
            }
            set
            {
                OnfnameChanging(value);
                ReportPropertyChanging("fname");
                _fname = StructuralObject.SetValidValue(value, true);
                ReportPropertyChanged("fname");
                OnfnameChanged();
            }
        }
        private global::System.String _fname;
        partial void OnfnameChanging(global::System.String value);
        partial void OnfnameChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=true)]
        [DataMemberAttribute()]
        public global::System.String lname
        {
            get
            {
                return _lname;
            }
            set
            {
                OnlnameChanging(value);
                ReportPropertyChanging("lname");
                _lname = StructuralObject.SetValidValue(value, true);
                ReportPropertyChanged("lname");
                OnlnameChanged();
            }
        }
        private global::System.String _lname;
        partial void OnlnameChanging(global::System.String value);
        partial void OnlnameChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=true)]
        [DataMemberAttribute()]
        public global::System.String bday
        {
            get
            {
                return _bday;
            }
            set
            {
                OnbdayChanging(value);
                ReportPropertyChanging("bday");
                _bday = StructuralObject.SetValidValue(value, true);
                ReportPropertyChanged("bday");
                OnbdayChanged();
            }
        }
        private global::System.String _bday;
        partial void OnbdayChanging(global::System.String value);
        partial void OnbdayChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=true)]
        [DataMemberAttribute()]
        public global::System.String occupation
        {
            get
            {
                return _occupation;
            }
            set
            {
                OnoccupationChanging(value);
                ReportPropertyChanging("occupation");
                _occupation = StructuralObject.SetValidValue(value, true);
                ReportPropertyChanged("occupation");
                OnoccupationChanged();
            }
        }
        private global::System.String _occupation;
        partial void OnoccupationChanging(global::System.String value);
        partial void OnoccupationChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=true)]
        [DataMemberAttribute()]
        public global::System.String number
        {
            get
            {
                return _number;
            }
            set
            {
                OnnumberChanging(value);
                ReportPropertyChanging("number");
                _number = StructuralObject.SetValidValue(value, true);
                ReportPropertyChanged("number");
                OnnumberChanged();
            }
        }
        private global::System.String _number;
        partial void OnnumberChanging(global::System.String value);
        partial void OnnumberChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=true)]
        [DataMemberAttribute()]
        public global::System.String program
        {
            get
            {
                return _program;
            }
            set
            {
                OnprogramChanging(value);
                ReportPropertyChanging("program");
                _program = StructuralObject.SetValidValue(value, true);
                ReportPropertyChanged("program");
                OnprogramChanged();
            }
        }
        private global::System.String _program;
        partial void OnprogramChanging(global::System.String value);
        partial void OnprogramChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=true, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.Int32 id
        {
            get
            {
                return _id;
            }
            set
            {
                if (_id != value)
                {
                    OnidChanging(value);
                    ReportPropertyChanging("id");
                    _id = StructuralObject.SetValidValue(value);
                    ReportPropertyChanged("id");
                    OnidChanged();
                }
            }
        }
        private global::System.Int32 _id;
        partial void OnidChanging(global::System.Int32 value);
        partial void OnidChanged();

        #endregion
    
    }

    #endregion
    
}
