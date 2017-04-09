const ordersData = require('../../data/orders.json');
const feesData = require('../../data/fees.json');
const helper = require('./helper.js');
const _  = require('underscore');

const fees = new Object();

/*
Fees - Challenge #1

The file fees.json describes fees that are applied to each of the items in an order. 
Each type of item in a order can have one or more fees associated with it. 
The total cost for the order item is the aggregate of all of fees associated with that item. 
There are different types of fees. Flat fees are simply a single charge. 
Per-page fees add an additional fee on top of a flat fee for each page after the first.

Challenge:

Write Javascript that outputs to the console the prices for each order item and order in the orders.json file based on the fees in the fees.json file.

The output should be of the form:


Order ID: <order number>  
   Order item <type>: $<price>
   Order item <type>: $<price>
   ..
   ..

   Order total: $<total>

*/
fees.challenge = () => {
	console.log("\n\nChallenge: Part 1 \n\nWrite Javascript that outputs to the console the prices for each order item and order in the orders.json file based on the fees in the fees.json file. \n\n"); 

	fees.print_to_console( fees.computePriceTotal(ordersData, feesData) );
}
/*
*	computePriceTotal
*
*	@param List of order_transaction
*   @param List of fees for transaction type
*	@return Computed prices for each order item and the total for the order
*
*/
fees.computePriceTotal = (order_transaction, fee_data) => {
   
   // return object
  	var ret = [];

  	_.each(order_transaction, (item) => {

  		// Create order obj
  		var order_obj = new Object();
  		order_obj.items = [];
  		order_obj.order_number = item.order_number;

  		// Get fee total from all order items
	    var total = helper.getOrderTotalWithItems(item.order_items, fee_data);

	    // Create items obj
	    _.each(total["items"], (item) => {
	    	var item_obj = new Object();
	    	item_obj.order_item_id = item.order_item_id;
        	item_obj.type = item.type;
        	item_obj.pages = item.pages;
        	item_obj.price = item.price;

        	order_obj.items.push(item_obj);
		  });

		  order_obj.order_total = total['total-price'];
		  ret.push(order_obj);
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
fees.print_to_console = (transactions_log) => {

  	_.each(transactions_log, (order_obj) => {

	    console.log("Order ID: " + order_obj.order_number); 

	    _.each(order_obj.items, (item_obj) => {
	    	console.log("\t" + "Order item " + item_obj.type + " : " + item_obj.price ) 
		});

   		console.log("\t" +"Order total: " + order_obj.order_total.toFixed(2));
	});
}

module.exports = fees;


