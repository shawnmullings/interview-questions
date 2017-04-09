using kofile_c_charp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.IO;
using System.Web.Http;
using Newtonsoft.Json;

namespace kofile_c_charp.Controllers
{
	public class FeesController : ApiController
	{
		List<Fee_Model> FM;


		// GET api/distributions
		public IEnumerable<Fee_Model> Get()
		{
			string filePath = System.IO.Path.GetFullPath("./data/fees.json");
			using (StreamReader r = new StreamReader(filePath))
			{
				string json = r.ReadToEnd();
				FM = JsonConvert.DeserializeObject<List<Fee_Model>>(json);
			}

			return FM;
		}

		// POST api/distributions
		[HttpPost]
		public HttpResponseMessage Post([FromBody]string value)
		{
			FM = JsonConvert.DeserializeObject<List<Fee_Model>>(value);

			return Request.CreateResponse(HttpStatusCode.OK, FM);
		}

		// PUT api/distributions
		public void Put(int id, [FromBody]string value) { }

		// DELETE api/distributions
		public void Delete(int id) { }
	}
}
