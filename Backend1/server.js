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
    return res.status(400).send('Bad Request: Missing parameter "hello"');
  }

  // Construct the shell command with the provided parameter
  const command = `echo \"${hello}lol\"`;
  // const command = ``

  // Execute the shell command
  exec(command, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error executing command: ${error.message}`);
      return res.status(500).send('Internal Server Error');
    }
    console.log(`Command output: ${stdout}`);
    res.json({ output: stdout });
    // res.send(`Response: ${stdout}`);
  });
});

app.get('/run-command', (req, res) => {
  const command = 'echo "hi"';

  exec(command, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error executing command: ${error.message}`);
      return res.status(500).send('Internal Server Error');
    }

    console.log(`Command output: ${stdout}`);
    res.send(`Command output: ${stdout}`);
  });
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});

