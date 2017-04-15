﻿using kofile_c_charp.Models;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Net;
using System;
using System.Net.Http;
using System.Web.Http;
using Newtonsoft.Json;
using kofile_c_charp.helper;

namespace kofile_c_charp.Controllers
{
	public class DistributionsController : ApiController 
	{
		private Helper hlpr = new Helper();

		public DistributionsController() { }

		// GET api/fees
		public List<OrderModel> Get()
		{
			return Helper.getOrderData();
		}

		/*
		*	computePriceTotal
		*
		*	@param List of order_transaction
		*	@return Computed prices for each order item and the total for the order
		*
		* 	POST api/fees
		*/
		[HttpPost]
		public HttpResponseMessage Post([FromBody]List<OrderModel> OM)
		{
			List<ReturnFundOrderModel> ls = hlpr.computeDistributionsAndTotal(OM);
			hlpr.print_to_console_distribution(ls);

			return Request.CreateResponse(HttpStatusCode.OK, JsonConvert.SerializeObject(ls));
		}

		// PUT api/fees
		public void Put(int id, [FromBody]string value) { }

		// DELETE api/fees
		public void Delete(int id) { }
	}
}
