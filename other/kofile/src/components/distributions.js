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
	ret.per_order_funds_map = [];

  	_.each(order_transaction, (item) => {

  		// Create order obj
  		var per_order_obj = {}; 
	   	per_order_obj.sum = 0;

  		per_order_obj.order_number = item.order_number;
	    per_order_obj.items = {};

	    // Calculate Fund amount per order
	   	_.each(item.order_items, (orderItem) => {

			let distro = _.chain(fee_data).where({"order_item_type" : orderItem.type})
			.pluck('distributions')
			.flatten()
	   		.each((_x) => {

				if(per_order_obj.items[_x.name] != null){
	   				per_order_obj.items[_x.name] += parseInt(_x.amount);
	   			}else{
	   				per_order_obj.items[_x.name] = parseInt(_x.amount);
	   			}

				if(ret.total_funds_map[_x.name] != null){
	   				ret.total_funds_map[_x.name] += parseInt(_x.amount);
	   			}else{
	   				ret.total_funds_map[_x.name] = parseInt(_x.amount);
	   			}

	   			per_order_obj.sum += parseInt(_x.amount);
	   			ret.funds_total_per_order += parseInt(_x.amount);
	   		});
   		});

	   	// Create "Other" fund obj
		var total = helper.getOrderTotalWithItems(item.order_items, fee_data);
		if ((total['total-price'] - per_order_obj.sum) > 0){

			if(per_order_obj.items["Other"] != null){
   				per_order_obj.items["Other"] += (total['total-price'] - per_order_obj.sum);
   			}else{
   				per_order_obj.items["Other"] = (total['total-price'] - per_order_obj.sum);
   			}

			if(ret.total_funds_map["Other"] != null){
   				ret.total_funds_map["Other"] += (total['total-price'] - per_order_obj.sum);
   			}else{
   				ret.total_funds_map["Other"] = (total['total-price'] - per_order_obj.sum);
   			}
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
	    for(i in order_obj.items) {
	    	console.log("\t" + "Fund - " + i + " : " + order_obj.items[i]);
		}
	});

  	console.log("Total distributions:");
	for(i in funds_log.total_funds_map) {
	    console.log("\t" + "Fund - " + i + " : " + funds_log.total_funds_map[i]);
	}
}


module.exports  = distributions;






