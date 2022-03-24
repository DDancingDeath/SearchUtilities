using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace LuceneDotNet
{
    public interface ISampleDataFileReader
    {
        IEnumerable<SampleDataFileRow> ReadAllRows(string filePath);
    }

    public class SampleDataFileReader : ISampleDataFileReader
    {
        public IEnumerable<SampleDataFileRow> ReadAllRows(string filePath)
        {
            FileInfo assFile = new FileInfo(Assembly.GetExecutingAssembly().Location);
            string file = string.Format(filePath, assFile.Directory.FullName);
            string[] lines = File.ReadAllLines(file);
            for (int i = 0; i < lines.Length; i++)
		    {
                yield return new SampleDataFileRow
                {
                    FileName = filePath,
                    LineNumber = i + 1,
                    LineText = lines[i]
                };
		    }     
        }
    }
}
