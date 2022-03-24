using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LuceneDotNet
{
    public class SampleDataFileRow
    {
        public int LineNumber { get; set; }
        public string LineText { get; set; }
        public string FileName { get; set; }
        public float Score { get; set; }
    }
}
