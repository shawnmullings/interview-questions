const ordersData = require('../../data/orders.json');
const feesData = require('../../data/fees.json');
const helper = require('./helper.js');
const _  = require('underscore');

const distributions = new Object();

/*
	Distributions Challenge #2

	Each fee for each order item has a set of funds associated with it. 
	The money associated with each fee is split among the funds based on the amount specified in the distribution. 
	Any extra money associated with the order that isn't allocated to a fund should be assigned to a generic "Other" fund.

	Challenge:

	Write Javascript that outputs to the console the fund distributions for each order in the orders.json file, 
	and then output the totals in each fund after processing all orders.

	The output should be of the form:

	Order ID: <order number>  
	  Fund - <fund name>: $<amount>
	  Fund - <fund name>: $<amount>
	  ..  
	  ..  

	Order ID: <order number>
	  Fund - <fund name>: $<amount>
	  Fund - <fund name>: $<amount>
	  ..  
	  ..  
	  ..  

	Total distributions:
	  Fund - <fund name>: $<amount>
	  Fund - <fund name>: $<amount>
	  ..  
	  ..  
*/


distributions.challenge = () => {
	console.log("\n\nChallenge: Part 2 \n\nWrite Javascript that outputs to the console the fund distributions for " +
		"each order in the orders.json file, and then output the totals in each fund after processing all orders. \n\n"); 

	distributions.print_to_console( distributions.computeDistributionsAndTotal(ordersData, feesData) );
}

/*
*	computePriceTotal
*
*	@param List of order_transaction
*   @param List of fees for transaction type
*	@return Computed funds distributions for each order and the total for the order
*
*/
distributions.computeDistributionsAndTotal = (order_transaction, fee_data) => {
   
   	// return object
	var ret = {}; 
	ret.total_funds_map = {};
	ret.total_funds_map.title = "Total distributions:";
	ret.per_order_funds_map = [];

  	_.each(order_transaction, (item) => {

  		// Create order obj
  		var per_order_obj = {}; 
	   	per_order_obj.sum = 0;

  		per_order_obj.order_number = item.order_number;
	    per_order_obj.items = [];

	    // Calculate Fund amount per order
	   	_.each(item.order_items, (orderItem) => {

			let distro = _.chain(fee_data).where({"order_item_type" : orderItem.type})
			.pluck('distributions')
			.flatten()
	   		.each((_x) => {
	   			
	   			// Create fund  obj
	   			var fund_obj = {}; 
	   			fund_obj.fund = "";
	   			fund_obj.amount = 0;

	   			if(ret.total_funds_map[_x.name] != null){
   					ret.total_funds_map[_x.name] += parseInt(_x.amount);
   				}
   				else{
   					ret.total_funds_map[_x.name] = parseInt(_x.amount);
   				}

	   			if(fund_obj.fund != null){
   					fund_obj.fund = _x.name ;
   					fund_obj.amount = parseInt(_x.amount);
   					per_order_obj.sum += parseInt(_x.amount);
   					ret.funds_total_per_order += parseInt(_x.amount);
   				}
   				else{
   					fund_obj.fund = _x.name ;
   					fund_obj.amount = parseInt(_x.amount);
   					per_order_obj.sum += parseInt(_x.amount);
   				}

   				per_order_obj.items.push(fund_obj);
	   		});
   		});

	   	// Create "Other" fund obj
		var total = helper.getOrderTotalWithItems(item.order_items, fee_data);
		if ((total['total-price'] - per_order_obj.sum) > 0){
			var fund_obj = {}; 
			fund_obj.fund = "Other" ;
   			fund_obj.amount = (total['total-price'] - per_order_obj.sum);
			ret.total_funds_map["Other"] = (total['total-price'] - per_order_obj.sum);
			per_order_obj.items.push(fund_obj);
		}

		ret.per_order_funds_map.push(per_order_obj);

	});

	return ret;
}

/*
*	print_to_console
*
*	Custom prints to console
*
*	@param List of order_transaction
*
*/
distributions.print_to_console = (funds_log) => {


  	_.each(funds_log.per_order_funds_map, (order_obj) => {

	    console.log("Order ID: " + order_obj.order_number); 

	    _.each(order_obj.items, (order_items_obj) => {
	    	console.log("\t" + "Fund - " + order_items_obj.fund + " : " + order_items_obj.amount);
		});
	});

  	console.log("Total distributions:");
	for(i in funds_log.total_funds_map) {
	    console.log("\t" + "Fund - " + i + " : " + funds_log.total_funds_map[i]);
	}
}


module.exports  = distributions;






