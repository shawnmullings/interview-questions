const _  = require('underscore');

const helper = new Object();

/*
*  getOrderTotalWithItems
*
*  Compute order total
*
*  @param List of order transaction
*  @param List of fees for transaction type
*  @return JSON structure containing computed prices for each order item and the total for the order
*
*/
helper.getOrderTotalWithItems = (order_items, fee_data) => {

   // return object
   let ret = {'total-price':0, 'items': []};

      _.each(order_items, (order_item) => {
         
         // Gather base fee
         let base_fee = _.chain(fee_data).where({"order_item_type" : order_item.type})
         .pluck('fees')
         .flatten()
            .filter((_x) => _x.type == "flat")
            .pluck('amount').value();

         // Gather per page fee
         let per_page_fee = _.chain(fee_data).where({"order_item_type" : order_item.type})
         .pluck('fees')
         .flatten()
         .filter((_x) => _x.type == "per-page")
         .pluck('amount').value();

         // Calculate total fee for amount of pages
         const page_fee_calculated = (--order_item.page) > 0 ? (--order_item.pages * per_page_fee) : 0;
         // Calculate item price
         const item_price = parseInt(base_fee) + parseInt(page_fee_calculated);
         
         ret['total-price'] += parseInt(item_price);
         order_item["price"] = item_price;

         ret['items'].push(order_item);
      });

   return ret;
}

/*
*  Fees Endpoint
*
*  @param List of order transaction
*  @param List of fees for transaction type
*  @return JSON structure containing computed prices for each order item and the total for the order
*
*/
helper.isJsonString = (str) => {
    try {
        JSON.parse(str);
    } catch (e) {
        return false;
    }
    return true;
}

module.exports = helper;

