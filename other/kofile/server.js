// Bring in our dependencies
const app = require('express')(),
	routes = require('./src/routes'),
	bodyParser = require('body-parser'),
	PORT = process.env.PORT || 3000;

// support json encoded bodies
app.use(bodyParser.json()); 

// support encoded bodies
app.use(bodyParser.urlencoded({ extended: true })); 

// Routing
app.use('/', routes);

// Start server!
app.listen(PORT, () => {
  console.log(`App started at 127.0.0.1 on port ${PORT}`);
  console.log(`http://127.0.0.1:${PORT}`);
});
