using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace kofile_c_charp.Models
{
	/**
	*	Fee Model
	*/
	public class FeeModel
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

	/**
	 *	Order Model
	 */
	public class OrderModel
	{
		[JsonProperty("order_date")]
		public string order_date { get; set; }

		[JsonProperty("order_number")]
		public string order_number { get; set; }

		[JsonProperty("order_items")]
		public IList<OrderItem> order_items { get; set; }
	}

	public class OrderItem
	{
		[JsonProperty("order_item_id")]
		public string order_item_id { get; set; }

		[JsonProperty("pages")]
		public int pages { get; set; }

		[JsonProperty("type")]
		public string type { get; set; }	
	}

	/**
	 * 	Return Model
	 */
	public class ReturnModel
	{
		public decimal total_price { get; set; }
		public IList<ReturnOrder> items { get; set; }
	}
	public class ReturnOrder
	{
		public string order_number { get; set; }
		public decimal total_order_price { get; set; }
		public IList<ReturnOrderItem> order_items { get; set; }
	}

	public class ReturnOrderItem : OrderItem
	{
		public decimal price { get; set; }
	}

	// Return object models for funds distribution challenge
	public class ReturnFundOrderModel : OrderModel
	{ 
		public bool isTotal { get; set; }
		public Dictionary<string, decimal> funds { get; set; }
	}
}