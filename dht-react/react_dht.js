const express = require('express');
const mysql = require('mysql');
const net = require('net');

const app = express();
const port = 3001;
const cors = require('cors');

app.use(cors());

const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password : 'damdam',
    database : 'dht_testDB'
});

db.connect((err) =>{
        if(err){
            console.error('database connection failed: ', err.stack);
            return ;
        }
        console.log('Connected to database.');
});

const toggleServerState = (callback) => {
    const client = new net.Socket();
    client.connect(9000, '127.0.0.1', () => {
            console.log('Connected to C server for state toggle');
            client.write('TOGGLE_STATE*'); //send to C server "TOGGLE_STATE"
    });
    client.on('data', (data) => {
            console.log('Recived from C server : ', data.toString());
            client.destroy(); // if response abailable, close connect
            callback(null, data.toString());
    });
    client.on('error', (err) => {
            console.error('Error connecting to C server : ', err.message);
            callback(err, null);
    });
};

app.post('/api/state', (req, res) => {
        toggleServerState((err, result) => {
                if(err){
                    return res.status(500).json({ error: 'Falied to toggle state' });
                }

                // if you sucess to change the state value, save to DB
                const query = 'UPDATE temp_humi SET state = state^1 ORDER BY id DESC LIMIT 1';
                db.query(query, (dbErr, dbResult) => {
                        if(dbErr){
                            console.error('Database update error:' ,dbErr);
                            return res.status(500).json({ error: 'Failed to update database'});
                        }
                        res.json({ message: 'State toggled successfully', state: result });
                });
        });
});

app.get('/api/data', (req, res) => {
        const query = 'SELECT * FROM temp_humi ORDER BY id DESC LIMIT 1';
        db.query(query, (err, result) => {
                if(err){
                   res.status(500).send(err);
               } else{
                   res.json(result[0]);
               }
        });
});


app.listen(port, () => {
        console.log('Server is running on http://localhost:${port}');
});

