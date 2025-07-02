const dgram = require('dgram');
const server = dgram.createSocket('udp4');

const PORT = 5005;
const HOST = '127.0.0.1';

server.on('listening', () => {
  const address = server.address();
  console.log(`UDP server listening on ${address.address}:${address.port}`);
});

server.on('message', (message, remote) => {
  try {
    const data = JSON.parse(message.toString());
    console.log(`Received from ${remote.address}:${remote.port}`);
    console.log(data);
    console.log('-----------------------------');
  } catch (err) {
    console.error('Failed to parse message:', err.message);
  }
});

server.bind(PORT, HOST);
