using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace kofile_c_charp.Models
{
	public class Fee_Model
	{
		[JsonProperty("order_item_type")]
		public string order_item_type { get; set; }

		[JsonProperty("fees")]
		public IList<Fees> fees { get; set; }

		[JsonProperty("distributions")]
		public IList<Distribution> distributions { get; set; }
	}

	public class Fees
	{
		[JsonProperty("name")]
		public string name { get; set; }
		[JsonProperty("amount")]
		public string amount { get; set; }
		[JsonProperty("type")]
		public string type { get; set; }
	}

	public class Distribution
	{
		[JsonProperty("name")]
		public string name { get; set; }
		[JsonProperty("amount")]
		public string amount { get; set; }
	}
}