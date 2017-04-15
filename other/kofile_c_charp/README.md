Part 1: Fees

The file fees.json describes fees that are applied to each of the items in an order. Each type of item in a order can have one or more fees associated with it.
The total cost for the order item is the aggregate of all of fees associated with that item. There are different types of fees. Flat fees are simply a single charge. Per-page fees add an additional fee on top of a flat fee for each page after the first.

Challenge:

Write Javascript that outputs to the console the prices for each order item and order in the orders.json file based on the fees in the fees.json file. 

The output should be of the form:  
```
Order ID: <order number>  
   Order item <type>: $<price>
   Order item <type>: $<price>
   ..
   ..

   Order total: $<total>
```

Part 2: Distributions

Each fee for each order item has a set of funds associated with it. The money associated with each fee is split among the funds based on the amount specified in the distribution. Any extra money associated with the order that isn't allocated to a fund should be assigned to a generic "Other" fund.

Challenge:

Write Javascript that outputs to the console the fund distributions for each order in the orders.json file, and then output the totals in each fund after processing all orders.

The output should be of the form:  
```
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
```

Part 3: API

Challenge:

Create a RESTful API using whatever server-side framework you want (or no framework). The API should 2 have endpoints. One endpoint should take an array of orders and return a JSON structure containing the prices for each order item and the total for the order.  The second endpoint should take an array of orders and return a JSON structure containing the distribution totals for each order. It is up to you to define an appropriate JSON structure for the order prices and an appropriate JSON structure for the distributions.