using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LuceneDotNet
{
    class Controller
    {
        private ILuceneService luceneService;
        private ISampleDataFileReader sampleDataFileReader;
        private IEnumerable<SampleDataFileRow> sampleDataFileRows;

        public Controller()
        {
            sampleDataFileReader = new SampleDataFileReader();
            this.luceneService = new LuceneService();
        }

        public void DoLuceneIndex(string dir)
        {
            string[] fileArray = Directory.GetFiles(dir, "*.txt", SearchOption.AllDirectories);
            foreach(var file in fileArray)
            {
                sampleDataFileRows = sampleDataFileReader.ReadAllRows(file);
                this.luceneService.BuildIndex(sampleDataFileRows);
            }
        }

        public void DoLuceneSearch(string str)
        {
            var results = this.luceneService.Search(str);

            foreach (var result in results)
            {
                Console.WriteLine(result.LineNumber + " " +  result.FileName);
            }
        }
    }
}
