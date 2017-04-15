using kofile_c_charp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.IO;
using System.Dynamic;
using System.Web.Http;
using Newtonsoft.Json;

namespace kofile_c_charp.helper
{
	public class Helper
	{
		private static List<FeeModel> _FM = new List<FeeModel>();
		private static List<OrderModel> _OM = new List<OrderModel>();

		public Helper()
		{
			init();
		}

		private void init()
		{
			string filePath = System.IO.Path.GetFullPath("./data/fees.json");
			using (StreamReader r = new StreamReader(filePath))
			{
				string json = r.ReadToEnd();
				Helper._FM = JsonConvert.DeserializeObject<List<FeeModel>>(json);
			}
			filePath = System.IO.Path.GetFullPath("./data/orders.json");
			using (StreamReader r = new StreamReader(filePath))
			{
				string json = r.ReadToEnd();
				Helper._OM = JsonConvert.DeserializeObject<List<OrderModel>>(json);
			}
		}
		/**
		 *  getFeeData
		 *
		 *  Get Fees data
		 *
       	 *  @return List<FeeModel> structure containing fees data
       	 * 	
		 */
		public static List<FeeModel> getFeeData()
		{
			return Helper._FM;
		}

		/**
		 *  getOrderData
		 *
		 *  Get Order data
		 *
		 *  @return List<OrderModel> structure containing oredr data
		 * 	
		 */
		public static List<OrderModel> getOrderData()
		{
			return Helper._OM;
		}


		/**
         * 	getOrderTotalWithItemTotal
		 *
         * 	Compute order total and item total price
		 *
         * 	@param List<OrderModel> list of order transactions
	  	 * 	@return List<ReturnOrder> structure containing orders with total
		 * 	 
		 */
		public List<ReturnOrder> getOrderTotalWithItemTotal(List<OrderModel> OM)
		{
			List<ReturnOrder> ret = new List<ReturnOrder>();

			foreach (OrderModel or in OM)
			{
				ret.Add( getOrderTotal(or) );
			}

			return ret;
		}

		/**
        * 	getOrderTotal
		*
		* 	Compute order total
		*
        * 	@param OrderModel order transaction
		*  	@return ReturnOrder structure containing orders with total
		* 		 
		*/
		public ReturnOrder getOrderTotal(OrderModel _order)
		{
			ReturnOrder ret = new ReturnOrder();
			ret.order_number = _order.order_number;
			ret.total_order_price = 0;
			ret.order_items = new List<ReturnOrderItem>();

			foreach (OrderItem item in _order.order_items.ToList<OrderItem>())
			{
				ReturnOrderItem oi = new ReturnOrderItem();
				oi.order_item_id = item.order_item_id;
				oi.pages = item.pages;
				oi.type = item.type;
				oi.price = 0;

				oi.price = getItemTotalPrice(item);
				ret.total_order_price += oi.price;
				ret.order_items.Add(oi);
			}

			return ret;
		}

		/**
         * 	getItemTotalPrice
		 *
		 * 	Compute order item total price
		 *
         * 	@param OrderItem order item
		 *  @return decimal of item total price
		 * 				
		 */
		public decimal getItemTotalPrice(OrderItem item)
		{
			// Get flat rate
			decimal _flat_fee = System.Convert.ToDecimal(_FM.Where(a => a.order_item_type == item.type).First().fees.Where(b => b.type == "flat").FirstOrDefault().amount);

			// Get per-page fee
			decimal per_page_fee = Decimal.Zero;
			var _page_fee = _FM.Where(a => a.order_item_type == item.type).First().fees.Where(b => b.type == "per-page").Select(c => c.amount);
			if (!_page_fee.Any())
			{
				per_page_fee = Decimal.Zero;
			}
			else
			{
				per_page_fee = System.Convert.ToDecimal(_page_fee.First());
			}

			// Compute total item price
			decimal total_page_fee = ((System.Convert.ToDecimal(item.pages) - 1) > 0) ? per_page_fee * (System.Convert.ToDecimal(item.pages) - 1) : 0;

			return _flat_fee + total_page_fee;
		}

		/**
         * 	computeDistributionsAndTotal
		 *
		 * 	Compute funds distribution per order and total distribution amount
		 *
         * 	@param List<OrderModel> List of order transactions
         * 	@return List<ReturnFundOrderModel> structure containing funds distribution
		 * 		
		 */
		public List<ReturnFundOrderModel> computeDistributionsAndTotal (List<OrderModel> OM) { 

			List<ReturnFundOrderModel> ret = new List<ReturnFundOrderModel>();

			foreach (OrderModel or in OM)
			{
				ret.Add( computeDistributionsPerOrder(or) );
			}

			ReturnFundOrderModel total_distribution = new ReturnFundOrderModel();
			total_distribution.isTotal = true;
			total_distribution.funds = new Dictionary<string, decimal>();

			foreach (ReturnFundOrderModel rfom in ret)
			{
				foreach (KeyValuePair<string, decimal> fund in rfom.funds)
				{
					bool result = total_distribution.funds.ContainsKey(fund.Key);
					if (result)
					{
						total_distribution.funds[fund.Key] += fund.Value;
					}
					else { 
						total_distribution.funds[fund.Key] = fund.Value;
					}
				}
			}

			ret.Add( total_distribution );

			return ret;
		}

		/**
         * 	computeDistributionsPerOrder
		 *
		 * 	Compute funds distribution per order 
		 * 
		 * 	@param OrderModel order transaction
         * 	@return ReturnFundOrderModel structure containing funds distribution
		 * 			
		 */
		public ReturnFundOrderModel computeDistributionsPerOrder(OrderModel _order)
		{
			ReturnFundOrderModel ret = new ReturnFundOrderModel();
			ret.order_number = _order.order_number;
			ret.funds = new Dictionary<string, decimal>();

			decimal total = Decimal.Zero;

			// Calculate funds distribution per order 
			foreach (OrderItem item in _order.order_items)
			{
				var distributions = _FM.Where(a => a.order_item_type == item.type).First().distributions;

				//
				foreach (Distribution dist in distributions)
				{
					bool result = ret.funds.ContainsKey(dist.name);
					if (result)
					{
						ret.funds[dist.name] += System.Convert.ToDecimal(dist.amount);
					}
					else
					{
						ret.funds[dist.name] = System.Convert.ToDecimal(dist.amount);
					}

					total += System.Convert.ToDecimal(dist.amount);
				}
			}

			ret.funds["Other"] = getOrderTotal(_order).total_order_price - total;

			return ret;
		}

		/**
         * 	print_to_console_distribution
		 *
		 * 	Print to console
		 * 
         * 	@param List<ReturnFundOrderModel> list of order structure containing funds distribution
		 * 			 
		 */
		public void print_to_console_distribution(List<ReturnFundOrderModel> list) {

			Console.Write("Challenge: Part 2\n\nWrite Javascript that outputs to the console the fund distributions for each order in the orders.json file, and then output the totals in each fund after processing all orders.\n\n");

			foreach (ReturnFundOrderModel rfom in list)
			{
				if (rfom.isTotal)
				{
					Console.Write("Total Distributions: " + "\n");
				}
				else
				{
					Console.Write("Order ID: " + rfom.order_number + "\n");
				}

				foreach (KeyValuePair<string, decimal> fund in rfom.funds) {
					Console.Write("\t" + "Fund - " + fund.Key + " : " + fund.Value + "\n");
				}
			}
		}

		/**
         * 	print_to_console_fees
		 *
         * 	Print to console 
		 * 
		 * 	@param List<ReturnOrder> list of order structure containing fee totals
		 * 				 
		 */
		public void print_to_console_fees(List<ReturnOrder> list)
		{
			Console.Write("Challenge: Part 1\n\nWrite Javascript that outputs to the console the prices for each order item and order in the orders.json file based on the fees in the fees.json file.\n\n");

			foreach (ReturnOrder ro in list)
			{
				Console.Write("Order ID: " + ro.order_number + "\n");

				foreach (ReturnOrderItem roi in ro.order_items)
				{
					Console.Write("\t" + "Order item " + roi.type + " : " + roi.price + "\n");
				}

				Console.Write("\t" + "Order total : " + ro.total_order_price + "\n");
			}
		}
	}
}
