using System;
namespace kofile_c_charp.Models
{
	public class Orders
	{
		public string order_date { get; set; }
		public string order_number { get; set; }
		public OrderItems[] order_items { get; set; }
	}

	public class OrderItems
	{
		public string order_item_id { get; set; }
		public int pages { get; set; }
		public string type { get; set; }
	}
}
