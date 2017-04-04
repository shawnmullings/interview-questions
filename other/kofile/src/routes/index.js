const routes = require('express').Router();
const ordersData = require('../../data/orders.json');
const feesData = require('../../data/fees.json');
const fees = require('../components/fees.js');
const distributions = require('../components/distributions.js');
const _  = require('underscore');

routes.get('/', (req, res) => {
  	res.status(200).json({ message: 'API Endpoints => /fees/[data], /distributions/[data]' });
});

/*****
	Uncomment to run.
*****/

// Challenge Part 1
fees.challenge();

// Challenge Part 2
//distributions.challenge();

/*
*	Fees Endpoint
*
*	@param List of order transaction
*	@return JSON structure containing computed prices for each order item and the total for the order
*
*/
routes.post('/fees/', (req, res) => {

  	var computed_prices = fees.computePriceTotal(req.body,feesData);

	res.status(200).json(JSON.stringify(computed_prices));
});

/*
*	Distributions Endpoint
*
*	@param List of order transaction
*	@return JSON structure containing computed distribution totals for each order
*
*/
routes.post('/distributions', (req, res) => {

  	var computed_Funds = distributions.computeDistributionsAndTotal(req.body,feesData);

	res.status(200).json(JSON.stringify(computed_Funds));
});

module.exports = routes;


