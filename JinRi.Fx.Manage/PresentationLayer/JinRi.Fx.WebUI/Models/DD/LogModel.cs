﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace JinRi.Fx.WebUI.Models.DD
{
    public class LogModel
    {
        public int Id { get; set; }
        public string SvrName { get; set; }
        public string DbName { get; set; }
        public string SchemaName { get; set; }
        public string TblName { get; set; }
        public string ColName { get; set; }
        public string OldOwner { get; set; }
        public string NewOwner { get; set; }
        public string OldDesc { get; set; }
        public string NewDesc { get; set; }
        public string Dealer { get; set; }
        public DateTime DealTime { get; set; }
    }
}