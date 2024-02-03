const express = require('express');
const { exec } = require('child_process');
const cors = require('cors'); // Import the cors middleware

const app = express();
const port = 3000;
app.use(cors()); // Enable CORS for all routes

app.use(express.json()); // Middleware to parse JSON requests

app.post('/run-command', (req, res) => {
  // Extract data from the request body
  const { hello } = req.body;

  // Check if the required parameter is provided
  if (!hello) {
    return res.status(400).send({"error": 'Bad Request: Missing parameter "hello"'});
  }

  // Construct the shell command with the provided parameter
  const command = `cd ~/ICHACK24; ./test.sh "${hello}"`;
  // const command = ``

  // Execute the shell command
  exec(command, (error, stdout, stderr) => {
    console.log(error);
    console.log(stdout);
    console.log(stderr);
    if (error) {
      console.error(`Error executing command: ${error.message}`);
      return res.status(500).send({"error":'Internal Server Error'});
    }
    if (stderr) {
      console.log("stderr")
      return res.status(200).send({"error":stderr});
    }
    console.log("ok")
    return res.status(200).send({"result":stdout, "error":"none"});
  });

});

app.get('/run-command', (req, res) => {
  let command = 'echo "hi"';

  exec(command, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error executing command: ${error.message}`);
      return res.status(500).send('Internal Server Error');
    }
    if (stderr) {
      return res.status(200).send(stderr);
    }

    console.log(`Command output: ${stdout}`);
  });

  

});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});

