using System;
namespace kofile_c_charp.Models
{
	public class Fee_Model
	{

	[JsonProperty("result")]
		public string order_item_type { get; set; }
		public Fee_Obj[] fees { get; set; }	
	}

	public class Fee_Obj { 
		public string name { get; set; }
		public int amount { get; set; }
		public string type { get; set; }
	}

	public class Distribution
	{
		public Fund [] items { get; set; }
	}

	public class Fund
	{
		public string name { get; set; }
		public int amount { get; set; }	
	}
}





public class ResponseActual
{

	[JsonProperty("response")]
	public Response2 Response { get; set; }
}

public class Response2
{

	[JsonProperty("result")]
	public Result Result { get; set; }

	[JsonProperty("uri")]
	public string Uri { get; set; }
}

public class Result
{

	[JsonProperty("Contacts")]
	public Contacts Contacts { get; set; }
}

public class Contacts
{

	[JsonProperty("row")]
	public IList<Row> Row { get; set; }
}

public class Row
{

	[JsonProperty("no")]
	public string No { get; set; }

	[JsonProperty("FL")]
	public IList<FL> FL { get; set; }
}

public class FL
{

	[JsonProperty("content")]
	public string Content { get; set; }

	[JsonProperty("val")]
	public string Val { get; set; }
}

//To De-serialize
ResponseActual respone = JsonConvert.DeserializeObject<ResponseActual>(jSON_sTRING)

//Get the contacts list
List<FL> contacts = respone.Response.Result.Contacts.Row[0].FL.ToList();

//Now Get the required value using LINQ
var value = contacts.Where<FL>((s, e) => s.Val == "Email").Select(x => x.Content).Single();